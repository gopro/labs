# HDRI Merge (optimized for GoPro MAX2)

Create HDRI with this two QR codes: ![macroQR](./macroQR.png)
![presetQR](./presetQR.png)

<fieldset>
  <legend>Inputs</legend>
  <div class="row">
    <input id="files" type="file" accept="image/jpeg" multiple />
    <button id="run">Merge HDR</button>
    <button id="runHalf">Merge HDR (½ Res)</button>
    <button id="runQuarter">Merge HDR (¼ Res)</button>
    <button id="saveHdr" disabled>Download .HDR</button>
  </div>
  <div class="row">
    <label>Preview exposure: <input id="previewExp" type="number" step="0.1" value="2.0" title="Photographic exposure for preview" style="width: 100px;"></label>
  </div>
</fieldset>

<fieldset>
  <legend>Progress</legend>
  <div id="stage">Idle</div>
  <progress id="overall" value="0" max="100" style="width: 800px;"></progress>
  <div class="muted" style="margin-top:6px;">Per-stage</div>
  <progress id="perfile" value="0" max="100" style="width: 800px;"></progress>
</fieldset>

<fieldset>
  <legend>Preview (tone-mapped)</legend>
  <canvas id="preview" width="800" height="400"></canvas>
</fieldset>

<fieldset>
  <legend>Log</legend>
  <pre id="log" aria-live="polite"></pre>
</fieldset>

<script src="https://cdn.jsdelivr.net/npm/exifr@7.1.3/dist/lite.umd.js"></script>
<script>
/* ===================== Config & constants ===================== */
const KSIZE        = 9;         // Gaussian blur kernel (odd) in float
const WHITE_PCT    = 99.0;      // robust white normalization percentile
const SHORT_EXPOSURE_T = 2e-5;  // 0.00002s threshold for "very short" exposure (Python parity)
const SUN_BLUR1    = 15;
const SUN_BLUR2    = 31;
const CLIPPED_THRESH = 0.99;    // test threshold in linear (post-blur)
const CLIPPED_COUNT  = 1000;    // number of clipped pixels to consider "has clipped sun"

/* ===================== Helpers / UI ===================== */
const $ = sel => document.querySelector(sel);
const logEl = $('#log');
function logLine(msg, cls='') {
  const line = document.createElement('div');
  if (cls) line.className = cls;
  line.textContent = msg;
  logEl.appendChild(line);
  logEl.scrollTop = logEl.scrollHeight;
}
function setStage(msg) { $('#stage').textContent = msg; }
function setOverall(pct) { $('#overall').value = Math.max(0, Math.min(100, pct)); }
function setPerFile(pct) { $('#perfile').value = Math.max(0, Math.min(100, pct)); }
function nextFrame() { return new Promise(r => requestAnimationFrame(() => r())); }

/* ===================== sRGB 2.2 → Linear ===================== */
function srgbToLinear_u8(imgData) {
  const { data, width, height } = imgData;
  const out = new Float32Array(width * height * 3);
  for (let i = 0, j = 0; i < data.length; i += 4, j += 3) {
    const sr = data[i]   / 255;
    const sg = data[i+1] / 255;
    const sb = data[i+2] / 255;
    const r = Math.pow(sr, 2.2);
    const g = Math.pow(sg, 2.2);
    const b = Math.pow(sb, 2.2);
    out[j] = r; out[j+1] = g; out[j+2] = b;
  }
  return out;
}

/* ===================== GoPro Flat (log 113) → Linear ===================== */
function goProFlatToLinear_u8(imgData) {
  const { data, width, height } = imgData;
  const out = new Float32Array(width * height * 3);
  for (let i = 0, j = 0; i < data.length; i += 4, j += 3) {
    const sr = data[i]   / 255;
    const sg = data[i+1] / 255;
    const sb = data[i+2] / 255;
    const r = (Math.pow(113.0,sr)-1.0)/112.0;
    const g = (Math.pow(113.0,sg)-1.0)/112.0;
    const b = (Math.pow(113.0,sb)-1.0)/112.0;
    out[j] = r; out[j+1] = g; out[j+2] = b;
  }
  return out;
}

function gaussianBlurFloatRGB(floatRGB, w, h, ksize=5) {
  if (!(Number.isInteger(ksize) && ksize>1 && (ksize%2)===1)) return floatRGB;
  const half = (ksize-1)/2;
  const sigma = 0.3*((ksize-1)*0.5 - 1) + 0.8;
  const kern = [];
  let sum = 0;
  for (let k=-half;k<=half;k++){ const v = Math.exp(-(k*k)/(2*sigma*sigma)); kern.push(v); sum+=v; }
  for (let i=0;i<kern.length;i++) kern[i] /= sum;

  const tmp = new Float32Array(floatRGB.length);
  const out = new Float32Array(floatRGB.length);

  // Horizontal
  for (let y=0; y<h; y++) {
    for (let x=0; x<w; x++) {
      let r=0,g=0,b=0;
      for (let k=-half;k<=half;k++){
        const xx = Math.max(0, Math.min(w-1, x+k));
        const p = (y*w+xx)*3;
        const wgt = kern[k+half];
        r += floatRGB[p  ]*wgt;
        g += floatRGB[p+1]*wgt;
        b += floatRGB[p+2]*wgt;
      }
      const o = (y*w+x)*3;
      tmp[o]=r; tmp[o+1]=g; tmp[o+2]=b;
    }
  }
  // Vertical
  for (let y=0; y<h; y++) {
    for (let x=0; x<w; x++) {
      let r=0,g=0,b=0;
      for (let k=-half;k<=half;k++){
        const yy = Math.max(0, Math.min(h-1, y+k));
        const p = (yy*w+x)*3;
        const wgt = kern[k+half];
        r += tmp[p  ]*wgt;
        g += tmp[p+1]*wgt;
        b += tmp[p+2]*wgt;
      }
      const o = (y*w+x)*3;
      out[o]=r; out[o+1]=g; out[o+2]=b;
    }
  }
  return out;
}


/**
 * In-place separable Gaussian blur on a rectangular ROI of a Float32 RGB image.
 *
 * @param {Float32Array} floatLinearRGB - Interleaved RGB (float) buffer, length = pitch * height * 3
 * @param {number} pitch - Image width (pixels per row)
 * @param {number} x1 - ROI left (inclusive)
 * @param {number} y1 - ROI top (inclusive)
 * @param {number} x2 - ROI right (exclusive)
 * @param {number} y2 - ROI bottom (exclusive)
 * @param {number} ksize - Odd kernel size (e.g., 3,5,7,9...)
 */
function gaussianBlurROI(floatLinearRGB, pitch, x1, y1, x2, y2, ksize) {
  // ---- Validate & fast exits ----
  if (!Number.isInteger(ksize) || ksize < 3 || (ksize & 1) === 0) return;
  if (x2 <= x1 || y2 <= y1) return; // empty
  // Clamp ROI to image bounds (we don't know height, but we use indices via pitch & y)
  // Caller should ensure bounds are valid; we still defensively clamp to >=0.
  x1 = Math.max(0, x1|0); y1 = Math.max(0, y1|0);
  x2 = x2|0; y2 = y2|0;

  const rw = x2 - x1;                 // ROI width
  const rh = y2 - y1;                 // ROI height
  const chans = 3;
  const half = (ksize - 1) >> 1;

  // ---- Build 1D Gaussian kernel ----
  const sigma = 0.3 * ((ksize - 1) * 0.5 - 1) + 0.8; // common heuristic
  const kern = new Float32Array(ksize);
  let sum = 0;
  for (let i = -half, j = 0; i <= half; i++, j++) {
    const v = Math.exp(-(i * i) / (2 * sigma * sigma));
    kern[j] = v; sum += v;
  }
  for (let j = 0; j < ksize; j++) kern[j] /= sum;

  // ---- Temp buffers for ROI (horizontal pass -> tmp, vertical -> out) ----
  const tmp = new Float32Array(rw * rh * chans);
  const out = new Float32Array(rw * rh * chans);

  // ---- Horizontal pass (within ROI, clamp to ROI edges) ----
  for (let ry = 0; ry < rh; ry++) {
    const gy = y1 + ry;
    for (let rx = 0; rx < rw; rx++) {
      const gx = x1 + rx;

      let accR = 0, accG = 0, accB = 0;
      for (let k = -half, j = 0; k <= half; k++, j++) {
        let sx = rx + k;
        if (sx < 0) sx = 0;
        else if (sx >= rw) sx = rw - 1;

        const srcIdx = ((gy * pitch) + (x1 + sx)) * chans;
        accR += floatLinearRGB[srcIdx    ] * kern[j];
        accG += floatLinearRGB[srcIdx + 1] * kern[j];
        accB += floatLinearRGB[srcIdx + 2] * kern[j];
      }

      const dstIdx = (ry * rw + rx) * chans;
      tmp[dstIdx    ] = accR;
      tmp[dstIdx + 1] = accG;
      tmp[dstIdx + 2] = accB;
    }
  }

  // ---- Vertical pass (within ROI, clamp to ROI edges) ----
  for (let ry = 0; ry < rh; ry++) {
    for (let rx = 0; rx < rw; rx++) {
      let accR = 0, accG = 0, accB = 0;
      for (let k = -half, j = 0; k <= half; k++, j++) {
        let sy = ry + k;
        if (sy < 0) sy = 0;
        else if (sy >= rh) sy = rh - 1;

        const srcIdx = (sy * rw + rx) * chans;
        accR += tmp[srcIdx    ] * kern[j];
        accG += tmp[srcIdx + 1] * kern[j];
        accB += tmp[srcIdx + 2] * kern[j];
      }
      const dstIdx = (ry * rw + rx) * chans;
      out[dstIdx    ] = accR;
      out[dstIdx + 1] = accG;
      out[dstIdx + 2] = accB;
    }
  }

  // ---- Write back to original buffer (in place) ----
  for (let ry = 0; ry < rh; ry++) {
    const gy = y1 + ry;
    for (let rx = 0; rx < rw; rx++) {
      const gx = x1 + rx;
      const srcIdx = (ry * rw + rx) * chans;
      const dstIdx = ((gy * pitch) + gx) * chans;
      floatLinearRGB[dstIdx    ] = out[srcIdx    ];
      floatLinearRGB[dstIdx + 1] = out[srcIdx + 1];
      floatLinearRGB[dstIdx + 2] = out[srcIdx + 2];
    }
  }
}


/* ===================== Merge radiance (linear) ===================== */
function wellExposedWeight(rgb, mid=0.5, sigma=0.1225) {
  const m = (rgb[0]+rgb[1]+rgb[2])/3;
  return Math.exp(-((m-mid)*(m-mid)) / (2*sigma*sigma));
}
async function mergeRadiance_linear(images, times) {
  const w = images[0].w, h = images[0].h;
  const num = new Float32Array(w*h*3);
  const den = new Float32Array(w*h);
  const total = images.length;

  for (let i=0; i<images.length; i++) {
    const {data} = images[i];
    const t = times[i];
	let sigma = 0.1225 + 0.1225 * Math.sin(i*3.14159/(images.length-1));
    for (let p=0, px=0; p<data.length; p+=3, px++) {
      const r=data[p], g=data[p+1], b=data[p+2];
      const wgt = wellExposedWeight([r,g,b], 0.5, );
      if (wgt>0) {
        num[p  ] += wgt * (r / t);
        num[p+1] += wgt * (g / t);
        num[p+2] += wgt * (b / t);
        den[px]  += wgt;
      }
    }
	setOverall(35+((i+1)/total)*30);
    setPerFile(((i+1)/total)*100);
	await nextFrame(); // let the browser paint the bars
  }
  for (let p=0, px=0; p<num.length; p+=3, px++) {
    const d = den[px] || 1e-8;
    num[p  ] /= d; num[p+1] /= d; num[p+2] /= d;
  }
  return { w, h, data: num };
}


/**
 * Robust HDR merge tolerant to small exposure errors (JPEG/8-bit).
 * images: [{ w, h, data: Float32Array }]  // linear RGB
 * times:  number[]                         // effective exposure times
 * onProgress?: (percent)=>void
 * options?: { mid?: number, sigma?: number, k?: number, logDomain?: boolean }
 */
async function mergeRadiance_linearRobust(images, times, onProgress, options = {}) {
  const width  = images[0].w;
  const height = images[0].h;
  const N = images.length;

  const mid     = options.mid   ?? 0.5;   // exposure center
  const sigma   = options.sigma ?? 0.30;  // broader than classic 0.225
  const k       = options.k     ?? 4.685; // Tukey constant
  const useLog  = options.logDomain ?? true;

  const num = new Float32Array(width*height*3); // output RGB radiance
  // den is kept for parity with older API; here we normalize per-pixel already.
  // const den = new Float32Array(width*height);

  // Precompute exposure/clip weights per frame, per pixel (based on luminance)
  const Yw = new Float32Array(width*height*N);
  const twoSig2 = 2 * sigma * sigma;
  const luminance = (r,g,b) => 0.2126*r + 0.7152*g + 0.0722*b;
  const eps = 1e-8;

  for (let i=0; i<N; i++) {
    const data = images[i].data;
    for (let p=0, px=0; p<data.length; p+=3, px++) {
      const y  = luminance(data[p], data[p+1], data[p+2]);
      const d  = y - mid;
      const wBell = Math.exp(-(d*d)/twoSig2);                  // bell around mid
      const darkGate   = 1 / (1 + Math.exp(-(y - 0.02)/0.02)); // rises after ~0.02
      const brightGate = 1 / (1 + Math.exp( (y - 0.98)/0.02)); // falls before ~0.98
      Yw[i*(width*height) + px] = wBell * darkGate * brightGate;
    }
  }

  function robustCenter(arr) {
    const tmp = Array.from(arr).sort((a,b)=>a-b);
    const med = tmp[tmp.length >> 1];
    for (let i=0;i<tmp.length;i++) tmp[i] = Math.abs(tmp[i] - med);
    const mad = tmp[tmp.length >> 1] || eps;
    return [med, mad];
  }

  // Progress control
  let lastYield = performance.now();
  const YIELD_MS = 500;

  for (let y=0; y<height; y++) {
    for (let x=0; x<width; x++) {
      const px = y*width + x;
      const off = px*3;

      // Gather candidate radiances r_i = v_i / t_i
      const R = new Float64Array(N);
      const G = new Float64Array(N);
      const B = new Float64Array(N);
      for (let i=0;i<N;i++){
        const v = images[i].data;
        const t = times[i];
        R[i] = v[off  ] / t;
        G[i] = v[off+1] / t;
        B[i] = v[off+2] / t;
      }

      // Robust center (median) + MAD scale
      const [mR, madR] = robustCenter(R);
      const [mG, madG] = robustCenter(G);
      const [mB, madB] = robustCenter(B);

      let accR = 0, accG = 0, accB = 0, wSum = 0;

      for (let i=0;i<N;i++){
        const uR = (R[i]-mR)/(k*madR);
        const uG = (G[i]-mG)/(k*madG);
        const uB = (B[i]-mB)/(k*madB);

        const wR = (Math.abs(uR) < 1) ? Math.pow(1 - uR*uR, 2) : 0;
        const wG = (Math.abs(uG) < 1) ? Math.pow(1 - uG*uG, 2) : 0;
        const wB = (Math.abs(uB) < 1) ? Math.pow(1 - uB*uB, 2) : 0;

        const wRobust = (wR + wG + wB) / 3;
        const wExp    = Yw[i*(width*height) + px];

        const wgt = wRobust * wExp + eps;

        if (useLog) {
          accR += wgt * Math.log(R[i] + eps);
          accG += wgt * Math.log(G[i] + eps);
          accB += wgt * Math.log(B[i] + eps);
        } else {
          accR += wgt * R[i];
          accG += wgt * G[i];
          accB += wgt * B[i];
        }
        wSum += wgt;
      }

      if (useLog) {
        num[off  ] = Math.exp(accR / (wSum || 1));
        num[off+1] = Math.exp(accG / (wSum || 1));
        num[off+2] = Math.exp(accB / (wSum || 1));
      } else {
        num[off  ] = accR / (wSum || 1);
        num[off+1] = accG / (wSum || 1);
        num[off+2] = accB / (wSum || 1);
      }
    }

    // progress + cooperative yield
    const now = performance.now();
    if (now - lastYield > YIELD_MS) { 
		lastYield = now;
		setOverall(35+(y/height)*30);
		setPerFile((y/height)*100);
		await nextFrame(); // let the browser paint the bars
	 }
  }

  return { w: width, h: height, data: num };
}


/* ===================== Normalize white ~1.0 ===================== */
function luminance709(r,g,b){ return 0.2126*r + 0.7152*g + 0.0722*b; }
function normalizeWhitePercentile(hdr, pct=WHITE_PCT) {
  const {data} = hdr, N = data.length/3;
  const h = Math.trunc(Math.sqrt(N/2));
  const w = h*2;
  const scale = 1 + Math.trunc(w/1000);
  const offset = Math.trunc(scale/2);
  const lum = new Float32Array((h/scale) * (w/scale));
  let i = 0;
  for(let y=offset;y<h;y+=scale)
  {
	for(let x=offset;x<w;x+=scale)
	{
		let p = (y * w + x) * 3;
		lum[i] = luminance709(data[p],data[p+1],data[p+2]);
		i++
	}
  }
  const arr = Array.from(lum).sort((a,b)=>a-b);
  const idx = Math.min(arr.length-1, Math.max(0, Math.floor((pct/100)*arr.length)));
  const white = Math.max(1e-8, arr[idx]);
  for (let p=0; p<data.length; p++) data[p] /= white;
  return white;
}

/* ===================== Monochrome-above-threshold (optional) ===================== */
function monochromeAbove(hdr, thr=1.0) {
  const {data} = hdr;
  for (let p=0;p<data.length;p+=3) {
    const r=data[p], g=data[p+1], b=data[p+2];
    if (r>thr || g>thr || b>thr) {
      const Y = luminance709(r,g,b);
      data[p]=data[p+1]=data[p+2]=Y;
    }
  }
}

/* ===================== Filmic tone map with dithering ===================== */
async function tonemap_filmic(hdr, exposure=1.0) {
  const {w,h,data} = hdr;
  const out = new Uint8ClampedArray(w*h*4);
  //const A=0.22, B=0.30, C=0.10, D=0.20, E=0.01, F=0.30, W=11.2;  // too contrasty
  const A=0.2, B=0.30, C=0.10, D=0.05, E=0.0, F=0.10, W=20;  // lower contrast
  const whiteScale = ((W*(A*W+C*B)+D*E)/(W*(A*W+B)+D*F)) - (E/F);
  function rnd(i){ let x = i ^ (i>>>17); x ^= x<<13; x ^= x>>>7; x ^= x>>>17; return ((x>>>8)&0xFF)/255; }

  for (let p=0,q=0,i=0; p<data.length; p+=3, q+=4, i++) {
    let r = data[p  ] * exposure;
    let g = data[p+1] * exposure;
    let b = data[p+2] * exposure;
    const fr = ((r*(A*r+C*B)+D*E)/(r*(A*r+B)+D*F)) - (E/F);
    const fg = ((g*(A*g+C*B)+D*E)/(g*(A*g+B)+D*F)) - (E/F);
    const fb = ((b*(A*b+C*B)+D*E)/(b*(A*b+B)+D*F)) - (E/F);
    let rr = Math.min(1, Math.max(0, fr/whiteScale));
    let gg = Math.min(1, Math.max(0, fg/whiteScale));
    let bb = Math.min(1, Math.max(0, fb/whiteScale));
    const d = (rnd(i)-0.5) / 255;
    rr = Math.min(1, Math.max(0, rr + d));
    gg = Math.min(1, Math.max(0, gg + d));
    bb = Math.min(1, Math.max(0, bb + d));
    out[q  ] = (rr*255)|0;
    out[q+1] = (gg*255)|0;
    out[q+2] = (bb*255)|0;
    out[q+3] = 255;
  }
  return { w, h, data: out };
}

//function drawToCanvas(ldr, canvas) {
//  canvas.width = ldr.w; canvas.height = ldr.h;
//  const ctx = canvas.getContext('2d', { willReadFrequently: true }); // perf hint
//  ctx.putImageData(new ImageData(ldr.data, ldr.w, ldr.h), 0, 0);
//}
function drawToCanvas(ldr, canvas, targetW = 800, targetH = 400, mode = 'contain') {
  // 1) paint the RGBA into a temp canvas at native size
  const srcC = document.createElement('canvas');
  srcC.width = ldr.w; srcC.height = ldr.h;
  const srcCtx = srcC.getContext('2d', { willReadFrequently: true });
  srcCtx.putImageData(new ImageData(ldr.data, ldr.w, ldr.h), 0, 0);

  // 2) set preview canvas to fixed size
  canvas.width = targetW;
  canvas.height = targetH;

  const ctx = canvas.getContext('2d', { willReadFrequently: true });
  ctx.imageSmoothingEnabled = true;         // better downscale
  ctx.imageSmoothingQuality = 'high';       // ask for HQ filters

  if (mode === 'stretch') {
    // Fill exactly 800x400 (may distort aspect)
    ctx.clearRect(0, 0, targetW, targetH);
    ctx.drawImage(srcC, 0, 0, targetW, targetH);
  } else {
    // 'contain' => preserve aspect ratio, letterbox
    const scale = Math.min(targetW / ldr.w, targetH / ldr.h);
    const drawW = Math.max(1, Math.floor(ldr.w * scale));
    const drawH = Math.max(1, Math.floor(ldr.h * scale));
    const offX = Math.floor((targetW - drawW) / 2);
    const offY = Math.floor((targetH - drawH) / 2);

    ctx.clearRect(0, 0, targetW, targetH);
    ctx.drawImage(srcC, 0, 0, ldr.w, ldr.h, offX, offY, drawW, drawH);
  }
}

/**
 * Async Radiance .HDR (RGBE) encoder with scanline RLE, progress + yielding.
 * @param {{w:number,h:number,data:Float32Array}} hdr  // linear RGB
 * @param {(pct:number)=>void=} onProgress            // 0..100
 * @param {{yieldMs?:number, signal?:AbortSignal}=} opts
 * @returns {Promise<Blob>}
 */
async function encodeRadianceHDR_RGBE_RLE_Async(hdr, onProgress, opts = {}) {
  const { w, h, data } = hdr;
  const yieldMs = opts.yieldMs ?? 16;
  const signal = opts.signal;

  const header = [
    "#?RADIANCE",
    "FORMAT=32-bit_rle_rgbe",
    "",
    `-Y ${h} +X ${w}\n`
  ].join("\n");
  const headerBytes = new TextEncoder().encode(header);

  // RGB -> RGBE
  function toRGBE(r,g,b) {
    const maxc = Math.max(r,g,b);
    if (maxc < 1e-32) return [0,0,0,0];
    const e = Math.ceil(Math.log2(maxc));
    const scale = Math.pow(2, e) / 256;
    return [
      Math.min(255, Math.round(r/scale)),
      Math.min(255, Math.round(g/scale)),
      Math.min(255, Math.round(b/scale)),
      e + 128
    ];
  }

  // Write one channel with Radiance RLE
  function encodeRLEChannel(line /* Uint8Array of length w */) {
    const out = [];
    let x = 0;
    while (x < w) {
      // try run
      let runLen = 1;
      const maxRun = Math.min(w - x, 127);
      const val = line[x];
      while (runLen < maxRun && line[x + runLen] === val) runLen++;
      if (runLen >= 4) {
        out.push(128 + runLen, val);
        x += runLen;
      } else {
        // literal packet, avoid swallowing a future run
        const start = x;
        let count = 0;
        const maxLit = Math.min(w - x, 128);
        while (count < maxLit) {
          if (count >= 1) {
            let lookRun = 1;
            const maxLook = Math.min(w - (x + count), 127);
            const lookVal = line[x + count];
            while (lookRun < maxLook && line[x + count + lookRun] === lookVal) lookRun++;
            if (lookRun >= 4) break;
          }
          count++;
        }
        out.push(count);
        for (let i = 0; i < count; i++) out.push(line[start + i]);
        x += count;
      }
    }
    return Uint8Array.from(out);
  }

  // Fallback to old flat RGBE when width not supported
  if (w < 8 || w > 0x7fff) {
    const flat = new Uint8Array(w*h*4);
    for (let i=0,p=0;i<w*h;i++,p+=3) {
      const [R,G,B,E] = toRGBE(data[p], data[p+1], data[p+2]);
      const q = i*4; flat[q]=R; flat[q+1]=G; flat[q+2]=B; flat[q+3]=E;
    }
    if (onProgress) onProgress(100);
    return new Blob([headerBytes, flat], { type: "image/vnd.radiance" });
  }

  // Build output in chunks to avoid one giant growable array
  const chunks = [headerBytes];
  let lastYield = performance.now();

  for (let y = 0; y < h; y++) {
    if (signal?.aborted) throw new DOMException("Encoding aborted", "AbortError");

    // Scanline header: 0x02 0x02 w_hi w_lo
    const scanHdr = new Uint8Array([0x02, 0x02, (w >> 8) & 0xff, w & 0xff]);

    // Prepare channel buffers
    const R = new Uint8Array(w);
    const G = new Uint8Array(w);
    const B = new Uint8Array(w);
    const E = new Uint8Array(w);

    let p = y * w * 3;
    for (let x = 0; x < w; x++, p += 3) {
      const [r8,g8,b8,e8] = toRGBE(data[p], data[p+1], data[p+2]);
      R[x] = r8; G[x] = g8; B[x] = b8; E[x] = e8;
    }

    // Encode four channels
    const rleR = encodeRLEChannel(R);
    const rleG = encodeRLEChannel(G);
    const rleB = encodeRLEChannel(B);
    const rleE = encodeRLEChannel(E);

    // Concatenate this scanline: hdr + R + G + B + E
    const line = new Uint8Array(scanHdr.length + rleR.length + rleG.length + rleB.length + rleE.length);
    let o = 0;
    line.set(scanHdr, o); o += scanHdr.length;
    line.set(rleR, o);    o += rleR.length;
    line.set(rleG, o);    o += rleG.length;
    line.set(rleB, o);    o += rleB.length;
    line.set(rleE, o);

    chunks.push(line);

    // Progress + cooperative yield
    if (onProgress) onProgress(((y + 1) / h) * 100);
    const now = performance.now();
    if (now - lastYield > yieldMs) {
      lastYield = now;
      await new Promise(r => requestAnimationFrame(r));
    }
  }

  return new Blob(chunks, { type: "image/vnd.radiance" });
}


function encodeRadianceHDR_RGBE_RLE(hdr) {
  const { w, h, data } = hdr;

  // --- header ---
  const header = [
    "#?RADIANCE",
    "FORMAT=32-bit_rle_rgbe",
    "", // blank line
    `-Y ${h} +X ${w}\n`
  ].join("\n");
  const headerBytes = new TextEncoder().encode(header);

  // helper: RGB->RGBE (float32 -> 4x uint8)
  function toRGBE(r, g, b) {
    const maxc = Math.max(r, g, b);
    if (maxc < 1e-32) return [0, 0, 0, 0];
    const e = Math.ceil(Math.log2(maxc));
    const scale = Math.pow(2, e) / 256;
    return [
      Math.min(255, Math.round(r / scale)),
      Math.min(255, Math.round(g / scale)),
      Math.min(255, Math.round(b / scale)),
      e + 128
    ];
  }

  // If width unsupported by RLE, write old style (flat RGBE)
  if (w < 8 || w > 0x7fff) {
    const flat = new Uint8Array(w * h * 4);
    for (let i = 0, p = 0; i < w * h; i++, p += 3) {
      const [R, G, B, E] = toRGBE(data[p], data[p + 1], data[p + 2]);
      const q = i * 4;
      flat[q] = R; flat[q + 1] = G; flat[q + 2] = B; flat[q + 3] = E;
    }
    return new Blob([headerBytes, flat], { type: "image/vnd.radiance" });
  }

  // --- RLE output builder ---
  const out = [];
  const pushByte = (b) => out.push(b & 0xff);
  const pushBytes = (arr) => { for (let i = 0; i < arr.length; i++) pushByte(arr[i]); };

  // write one channel (Uint8 array of length w) using Radiance RLE
  function writeRLEChannel(line) {
    let x = 0;
    while (x < w) {
      // Try to find a run at x
      let runLen = 1;
      const maxRun = Math.min(w - x, 127);
      const val = line[x];

      while (runLen < maxRun && line[x + runLen] === val) runLen++;

      if (runLen >= 4) {
        // Write run packet
        pushByte(128 + runLen);
        pushByte(val);
        x += runLen;
      } else {
        // Write literal packet up to 128 or until a future run (>=4) is about to start
        let start = x;
        let count = 0;
        const maxLit = Math.min(w - x, 128);

        while (count < maxLit) {
          // Look ahead to see if a run starts here; if so, stop literals
          if (count >= 1) {
            let lookRun = 1;
            const maxLook = Math.min(w - (x + count), 127);
            const lookVal = line[x + count];
            while (lookRun < maxLook && line[x + count + lookRun] === lookVal) lookRun++;
            if (lookRun >= 4) break; // stop before run
          }
          count++;
        }
        pushByte(count);
        for (let i = 0; i < count; i++) pushByte(line[start + i]);
        x += count;
      }
    }
  }

  // Progress control
  let lastYield = performance.now();
  const YIELD_MS = 500;
  
  // --- encode scanlines ---
  for (let y = 0; y < h; y++) {
    // scanline header: 0x02 0x02 width_hi width_lo
    pushByte(0x02);
    pushByte(0x02);
    pushByte((w >> 8) & 0xff);
    pushByte(w & 0xff);

    // Prepare per-channel arrays for this scanline
    const R = new Uint8Array(w);
    const G = new Uint8Array(w);
    const B = new Uint8Array(w);
    const E = new Uint8Array(w);

    let p = y * w * 3;
    for (let x = 0; x < w; x++, p += 3) {
      const [r8, g8, b8, e8] = toRGBE(data[p], data[p + 1], data[p + 2]);
      R[x] = r8; G[x] = g8; B[x] = b8; E[x] = e8;
    }

    // Write 4 channels (R, G, B, E), each RLE-compressed
    writeRLEChannel(R);
    writeRLEChannel(G);
    writeRLEChannel(B);
    writeRLEChannel(E);
  }

  return new Blob([headerBytes, new Uint8Array(out)], { type: "image/vnd.radiance" });
}


/* ===================== Radiance .HDR (RGBE) encoder ===================== */
function encodeRadianceHDR_RGBE(hdr) {
  const {w,h,data} = hdr;
  const header = [
    "#?RADIANCE",
    "FORMAT=32-bit_rle_rgbe",
    "",
    `-Y ${h} +X ${w}\n`
  ].join("\n");
  const headerBytes = new TextEncoder().encode(header);
  const body = new Uint8Array(w*h*4);
  for (let i=0,p=0;i<w*h;i++,p+=3) {
    const r=data[p], g=data[p+1], b=data[p+2];
    const maxc = Math.max(r,g,b);
    if (maxc < 1e-32) { body[i*4+0]=0; body[i*4+1]=0; body[i*4+2]=0; body[i*4+3]=0; }
    else {
      const e = Math.ceil(Math.log2(maxc));
      const scale = Math.pow(2, e) / 256;
      body[i*4+0] = Math.min(255, Math.round(r/scale));
      body[i*4+1] = Math.min(255, Math.round(g/scale));
      body[i*4+2] = Math.min(255, Math.round(b/scale));
      body[i*4+3] = e + 128;
    }
  }
  const out = new Uint8Array(headerBytes.length + body.length);
  out.set(headerBytes, 0); out.set(body, headerBytes.length);
  return new Blob([out], {type: 'image/vnd.radiance'});
}

/* ===================== Load, EXIF, preprocess + SHORT-SUN LOGIC ===================== */
async function loadAndPreprocessOld(files, scale = 1) {
  const bitmaps = [];
  const exposures = [];
  setPerFile(0);

  // EXIF + decode
  for (let i=0;i<files.length;i++) {
    const f = files[i];
    try {
      const exif = await exifr.parse(f).catch(()=>null);
      let t = null;
      if (exif) {
        if (typeof exif.ExposureTime === 'number') t = exif.ExposureTime;
        else if (typeof exif.ShutterSpeedValue === 'number') t = Math.pow(2, -exif.ShutterSpeedValue);
      }
      if (!t) throw new Error("Missing ExposureTime/ShutterSpeedValue");
      exposures.push(t);

      const bmp = await createImageBitmap(f);
      bitmaps.push(bmp);
      logLine(`Loaded: ${f.name} (t=${t})`, 'ok');
    } catch (e) {
      logLine(`Error reading ${f.name}: ${e.message || e}`, 'err');
    }
    setPerFile(((i+1)/files.length)*100);
    await nextFrame();
  }
  if (!bitmaps.length) throw new Error("No valid images decoded.");

  // sort by exposure (shortest first)
  const idx = exposures.map((t,i)=>[t,i]).sort((a,b)=>a[0]-b[0]).map(x=>x[1]);
  const sortedExpos = idx.map(i=>exposures[i]);
  const sortedBmps  = idx.map(i=>bitmaps[i]);
  
  const shortestFileName = files[idx[0]].name;  // name of shortest exposure file
  const baseName = shortestFileName.replace(/\.[^.]+$/, ''); // strip extension



  // common size = first image
  const w = sortedBmps[0].width, h = sortedBmps[0].height;
  const c = document.createElement('canvas'); c.width=w; c.height=h;
  const ctx = c.getContext('2d', { willReadFrequently: true }); // perf hint

  const linearImages = [];
  const expandedTimes = [];

  for (let i=0;i<sortedBmps.length;i++) {
    ctx.clearRect(0,0,w,h);
    ctx.drawImage(sortedBmps[i], 0, 0, w, h);
    const imgData = ctx.getImageData(0,0,w,h);

    // sRGB → linear (float)
    let lin = srgbToLinear_u8(imgData);
    // Log113 (Flat) → linear (float)
    //let lin = goProFlatToLinear_u8(imgData);
    let t = sortedExpos[i];

    // ---------- Short-exposure logic (ported from Python) ----------
    if (t < SHORT_EXPOSURE_T) {
      // Emulate Python's exp *= 4 pre-step
      // Base push (analogous to appending img8 with exp=t_eff)
      linearImages.push({ w, h, data: lin.slice(0) });
      expandedTimes.push(t);
      logLine(`Short exposure base push: t=${t}`, 'muted');

      // Detect clipped sun on a blurred copy
      let blurForSun = gaussianBlurFloatRGB(lin, w, h, SUN_BLUR1);
      let clippedCount = 0;
      for (let p=0; p<blurForSun.length; p++) if (blurForSun[p] > CLIPPED_THRESH) clippedCount++;
	  clippedCount *= (7680*3840*3 / blurForSun.length);
      const hasClippedSun = clippedCount > CLIPPED_COUNT && clippedCount < CLIPPED_COUNT*10;
      logLine(`Sun clipped? ${hasClippedSun} (count=${clippedCount})`, hasClippedSun ? 'warn' : 'muted');

      if (hasClippedSun) 
	  {
		let minx = w;
		let maxx = 0;
		let miny = h;
		let maxy = 0;
        for (let yy=0; yy<h; yy++) {
			for (let xx=0; xx<w; xx++) {
				const p = (yy*w+xx)*3;
				const r=lin[p], g=lin[p+1], b=lin[p+2];
				if (r>CLIPPED_THRESH || g>CLIPPED_THRESH || b>CLIPPED_THRESH) {
					if(minx > xx) minx = xx;
					if(maxx < xx) maxx = xx;
					if(miny > yy) miny = yy;
					if(maxy < yy) maxy = yy;
				}
			}
		}
		
		minx -= 64;  if(minx < 0) minx=0;
		miny -= 64;  if(miny < 0) miny=0;
		maxx += 64;  if(maxx >= w) maxx=w-1;
		maxy += 64;  if(maxy >= h) maxy=h-1;
		
		gaussianBlurROI(lin, w, minx, miny, maxx, maxy, SUN_BLUR1);
		
        for (let yy=miny; yy<maxy; yy++) {
			for (let xx=minx; xx<maxx; xx++) {
				const p = (yy*w+xx)*3;
				const r=lin[p], g=lin[p+1], b=lin[p+2];
				if (r>0.99 || g>0.99 || b>0.99) {
					lin[p]=lin[p+1]=lin[p+2] = 800;
				}
			}
		}
		
		
		logLine(`Sun's location ${minx},${miny} to ${maxx},${maxy}`, 'muted');
        gaussianBlurROI(lin, w, minx, miny, maxx, maxy, SUN_BLUR1);
        linearImages.push({ w, h, data: lin.slice(0) });
        expandedTimes.push(t);

        // B: blur heavier, scale *16, then t/=16
        gaussianBlurROI(lin, w, minx, miny, maxx, maxy, SUN_BLUR1);
        // multiply by 16 (keep float linear domain)
        for (let p=0; p<lin.length; p++) lin[p] /= 16.0;
        t /= 16.0;
        linearImages.push({ w, h, data: lin.slice(0) });
        expandedTimes.push(t);
        logLine(`Synthetic B push: t=${t}`, 'muted');

        // C: blur heavier, scale *1.0, then t/=16
        gaussianBlurROI(lin, w, minx, miny, maxx, maxy, SUN_BLUR1);
        for (let p=0; p<lin.length; p++) lin[p] /= 16.0;
        t /= 16.0;
        linearImages.push({ w, h, data: lin.slice(0) });
        expandedTimes.push(t);
        logLine(`Synthetic C push: t=${t}`, 'muted');

        // D: blur heavier, scale *0.25, then t/=16
        gaussianBlurROI(lin, w, minx, miny, maxx, maxy, SUN_BLUR1);
        for (let p=0; p<lin.length; p++) lin[p] /= 16.0;
        t /= 16.0;
        linearImages.push({ w, h, data: lin.slice(0) });
        expandedTimes.push(t);
        logLine(`Synthetic D push: t=${t}`, 'muted');

      } else {
        // No clipped sun → one synthetic step: exp/=4 (Python branch)
        linearImages.push({ w, h, data: lin.slice(0) });
        expandedTimes.push(t);
      }

    } else {
      // Normal (non-short) exposure → single push
      linearImages.push({ w, h, data: lin.slice(0) });
      expandedTimes.push(t);
    }

    setPerFile(((i+1)/sortedBmps.length)*100);
    await nextFrame();
  }

  return { linearImages, sortedExpos: expandedTimes, w, h, baseName };
}

/**
 * Load JPGs, read EXIF shutter times, sort by exposure, optionally scale,
 * convert to linear, apply short-sun logic (ROI blur + synthetic pushes),
 * and return arrays ready for HDR merge.
 *
 * @param {File[]} files
 * @param {number} scale   // 1.0 = full, 0.5 = half, etc.
 * @returns {Promise<{linearImages:Array<{w:number,h:number,data:Float32Array}>,sortedExpos:number[],sortedExif:Object[],w:number,h:number,baseName:string}>}
 */
async function loadAndPreprocess(files, scale = 1.0) {
  // ---- NEW: parameter sanity for scale ----
  scale = Math.max(0.05, Math.min(2.0, Number(scale) || 1.0));

  const bitmaps = [];
  const exposures = [];
  const exifList = [];
  setPerFile(0);

  // Decode + EXIF ----------------------------------------
  for (let i = 0; i < files.length; i++) {
    const f = files[i];
    try {
      const exif = await exifr.parse(f).catch(() => null);
      exifList.push(exif || {});

      // Shutter time (seconds)
      let t = null;
      if (exif) {
        if (typeof exif.ExposureTime === 'number') t = exif.ExposureTime;
        else if (typeof exif.ShutterSpeedValue === 'number') t = Math.pow(2, -exif.ShutterSpeedValue);
      }
      if (!t) throw new Error("Missing ExposureTime/ShutterSpeedValue");
      exposures.push(t);

      const bmp = await createImageBitmap(f);
      bitmaps.push(bmp);

      logLine(`Loaded: ${f.name} (t=${t})`, 'ok');
    } catch (e) {
      logLine(`Error reading ${f.name}: ${e.message || e}`, 'err');
    }
    setPerFile(((i + 1) / files.length) * 100);
    await nextFrame();
  }
  if (!bitmaps.length) throw new Error("No valid images decoded.");

  // Sort by exposure (ascending: shortest first) --------
  const idx = exposures.map((t, i) => [t, i]).sort((a, b) => a[0] - b[0]).map(x => x[1]);
  const sortedExpos = idx.map(i => exposures[i]);
  const sortedExif  = idx.map(i => exifList[i]);
  const sortedBmps  = idx.map(i => bitmaps[i]);

  const shortestFileName = files[idx[0]].name;
  const baseName = shortestFileName.replace(/\.[^.]+$/, '');

  // ---- NEW: target output size with scale factor -------
  const nativeW = sortedBmps[0].width;
  const nativeH = sortedBmps[0].height;
  const w = Math.max(1, Math.floor(nativeW * scale));
  const h = Math.max(1, Math.floor(nativeH * scale));

  // Work canvas at target resolution ---------------------
  const c = document.createElement('canvas');
  c.width = w; c.height = h;
  const ctx = c.getContext('2d', { willReadFrequently: true });
  ctx.imageSmoothingEnabled = true;
  ctx.imageSmoothingQuality = 'high';

  const linearImages = [];
  const expandedTimes = [];

  // Process each bracket --------------------------------
  for (let i = 0; i < sortedBmps.length; i++) {
    ctx.clearRect(0, 0, w, h);

    // ---- NEW: scaled draw to target resolution ----
    const bmp = sortedBmps[i];
    ctx.drawImage(bmp, 0, 0, bmp.width, bmp.height, 0, 0, w, h);

    const imgData = ctx.getImageData(0, 0, w, h);

    // sRGB → linear (your existing function)
    let lin = srgbToLinear_u8(imgData);

    let t = sortedExpos[i];

    // ---------- Short-exposure "sun" logic (unchanged behavior, now at scaled size) ----------
    if (t < SHORT_EXPOSURE_T) {
      // A) base push
      linearImages.push({ w, h, data: lin.slice(0) });
      expandedTimes.push(t);
      logLine(`Short exposure base push: t=${t}`, 'muted');

      // Detect clipped sun on a blurred copy (first pass blur)
      let blurForSun = gaussianBlurFloatRGB(lin, w, h, SUN_BLUR1);
      let clippedCount = 0;
      for (let p = 0; p < blurForSun.length; p++) if (blurForSun[p] > CLIPPED_THRESH) clippedCount++;
      // Scale count to approx native 7680×3840 reference if you use that heuristic
      clippedCount *= (7680 * 3840 * 3 / blurForSun.length);
      const hasClippedSun = clippedCount > CLIPPED_COUNT && clippedCount < CLIPPED_COUNT * 10;
      logLine(`Sun clipped? ${hasClippedSun} (count=${Math.round(clippedCount)})`, hasClippedSun ? 'warn' : 'muted');

      if (hasClippedSun) {
        // Find bbox of bright region
        let minx = w, maxx = 0, miny = h, maxy = 0;
        for (let yy = 0; yy < h; yy++) {
          for (let xx = 0; xx < w; xx++) {
            const p = (yy * w + xx) * 3;
            const r = lin[p], g = lin[p + 1], b = lin[p + 2];
            if (r > CLIPPED_THRESH || g > CLIPPED_THRESH || b > CLIPPED_THRESH) {
              if (minx > xx) minx = xx;
              if (maxx < xx) maxx = xx;
              if (miny > yy) miny = yy;
              if (maxy < yy) maxy = yy;
            }
          }
        }
        // pad ROI a bit; clamp to image
        minx = Math.max(0, minx - 64);
        miny = Math.max(0, miny - 64);
        maxx = Math.min(w - 1, maxx + 64);
        maxy = Math.min(h - 1, maxy + 64);

        // First soften (ROI blur; x2/y2 exclusive → pass max+1)
        gaussianBlurROI(lin, w, minx, miny, maxx + 1, maxy + 1, SUN_BLUR1);

        // Spike core & desaturate > 0.99 (prevent color fringing)
        for (let yy = miny; yy <= maxy; yy++) {
          for (let xx = minx; xx <= maxx; xx++) {
            const p = (yy * w + xx) * 3;
            const r = lin[p], g = lin[p + 1], b = lin[p + 2];
            if (r > 0.99 || g > 0.99 || b > 0.99) lin[p] = lin[p + 1] = lin[p + 2] = 800.0;
          }
        }

        logLine(`Sun ROI @ ${minx},${miny} → ${maxx},${maxy}`, 'muted');

        // A: soften again, push with same t
        gaussianBlurROI(lin, w, minx, miny, maxx + 1, maxy + 1, SUN_BLUR1);
        linearImages.push({ w, h, data: lin.slice(0) });
        expandedTimes.push(t);

        // B: heavier blur & *multiply by 16*, then t/=16  (synthetic shorter exposure)
        gaussianBlurROI(lin, w, minx, miny, maxx + 1, maxy + 1, SUN_BLUR2);
        for (let p = 0; p < lin.length; p++) lin[p] *= 16.0;
        t /= 16.0;
        linearImages.push({ w, h, data: lin.slice(0) });
        expandedTimes.push(t);
        logLine(`Synthetic B push: t=${t}`, 'muted');

        // C: heavier blur, ×1.0, then t/=16
        gaussianBlurROI(lin, w, minx, miny, maxx + 1, maxy + 1, SUN_BLUR2);
        // (no intensity scale)
        t /= 16.0;
        linearImages.push({ w, h, data: lin.slice(0) });
        expandedTimes.push(t);
        logLine(`Synthetic C push: t=${t}`, 'muted');

        // D: heavier blur, ×0.25, then t/=16
        gaussianBlurROI(lin, w, minx, miny, maxx + 1, maxy + 1, SUN_BLUR2);
        for (let p = 0; p < lin.length; p++) lin[p] *= 0.25;
        t /= 16.0;
        linearImages.push({ w, h, data: lin.slice(0) });
        expandedTimes.push(t);
        logLine(`Synthetic D push: t=${t}`, 'muted');
      }
      // else: only base push already added
    } else {
      // Normal exposure
      linearImages.push({ w, h, data: lin.slice(0) });
      expandedTimes.push(t);
    }

    setPerFile(((i + 1) / sortedBmps.length) * 100);
    await nextFrame();
  }

  return { linearImages, sortedExpos: expandedTimes, sortedExif, w, h, baseName };
}

/**
 * Remove isolated hot speckles from an HDR buffer (in place).
 * Detects pixels whose luminance is far above the 3×3 neighborhood
 * and clamps them to a robust neighborhood target while preserving chroma.
 *
 * @param {{w:number,h:number,data:Float32Array}} hdr  // linear RGB
 * @param {object} [opts]
 * @param {number} [opts.radius=1]     // 1 => 3x3; (only 1 supported here)
 * @param {number} [opts.factor=3.0]   // trigger if Yc > factor * median(Ynbrs)
 * @param {number} [opts.abs=0.2]      // and Yc > median + abs (absolute guard in scene-linear)
 * @param {number} [opts.pct=0.95]     // target upper bound uses neighborhood percentile (e.g. 95th)
 * @param {number} [opts.soft=1.2]     // target also limited to soft * median
 * @param {boolean}[opts.requirePeak=true] // require the center to be the unique local max
 * @returns {number}                   // number of pixels corrected
 */
function removeHDRSpeckles(hdr, opts = {}) {
  const { w, h, data } = hdr;
  const radius = 1;
  const factor = opts.factor ?? 3.0;
  const abs    = opts.abs    ?? 0.2;
  const pct    = opts.pct    ?? 0.95;
  const soft   = opts.soft   ?? 1.2;
  const requirePeak = (opts.requirePeak ?? true);
  const eps = 1e-8;

  // Precompute luminance for speed
  const Y = new Float32Array(w * h);
  for (let i = 0, px = 0; i < data.length; i += 3, px++) {
    const r = data[i], g = data[i + 1], b = data[i + 2];
    Y[px] = 0.2126 * r + 0.7152 * g + 0.0722 * b;
  }

  // Helper: median of 8 values (neighbors)
  function median8(vals) {
    // insertion sort small array
    for (let i = 1; i < 8; i++) {
      let v = vals[i], j = i - 1;
      while (j >= 0 && vals[j] > v) { vals[j + 1] = vals[j]; j--; }
      vals[j + 1] = v;
    }
    return (vals[3] + vals[4]) * 0.5; // middle of 8
  }

  // Helper: percentile (approx) of neighbors
  function percentile8(vals, p) {
    // vals length = 8; already sorted is not guaranteed
    for (let i = 1; i < 8; i++) {
      let v = vals[i], j = i - 1;
      while (j >= 0 && vals[j] > v) { vals[j + 1] = vals[j]; j--; }
      vals[j + 1] = v;
    }
    const idx = Math.min(7, Math.max(0, Math.round(p * 7)));
    return vals[idx];
  }

  let fixed = 0;

  // Scan interior pixels (skip 1px border)
  for (let y = 1; y < h - 1; y++) {
    for (let x = 1; x < w - 1; x++) {
      const cx = y * w + x;
      const Yc = Y[cx];

      // Collect neighbor luminances (8)
      const N = new Float32Array(8);
      let k = 0;
      let isPeak = true;
      for (let dy = -1; dy <= 1; dy++) {
        for (let dx = -1; dx <= 1; dx++) {
          if (dx === 0 && dy === 0) continue;
          const yy = y + dy, xx = x + dx;
          const ny = yy * w + xx;
          const Yn = Y[ny];
          N[k++] = Yn;
          if (Yn >= Yc - 1e-12) isPeak = false; // neighbor as bright or brighter
        }
      }

      if (requirePeak && !isPeak) continue;

      const med = median8(N.slice()); // median of neighbors
      const pHi = percentile8(N.slice(), pct);

      // Trigger if way above neighbors (both relative & absolute guards)
      if (!(Yc > med * factor && Yc > med + abs)) continue;

      // Compute target luminance: limit to both high-percentile and soft*median
      const targetY = Math.min(pHi, med * soft);

      // Preserve chroma: scale RGB so luminance becomes targetY
      const i = cx * 3;
      const r = data[i], g = data[i + 1], b = data[i + 2];
      const curY = Yc || eps;
      const s = Math.max(0, targetY / curY);

      data[i]     = r * s;
      data[i + 1] = g * s;
      data[i + 2] = b * s;
      Y[cx]       = targetY;
      fixed++;
    }
  }

  return fixed;
}

/**
 * Remove compact hot-speckle clusters up to 3x3 (in place), preserving edges/lines.
 * - Finds a cluster in the 3x3 window centered at (x,y) using a local "hot" test.
 * - Rejects line-like shapes (1xK or Kx1 with K>=2).
 * - Clamps all pixels in the cluster toward a robust target from the surrounding 5x5 ring.
 *
 * @param {{w:number,h:number,data:Float32Array}} hdr
 * @param {object} [opts]
 * @param {number} [opts.factor=3.0]   // "hot" if Y > factor * median(neigh-8)
 * @param {number} [opts.abs=0.2]      // and Y > median + abs
 * @param {number} [opts.soft=1.2]     // target cap vs local median
 * @param {number} [opts.ringPct=0.95] // target = min( percentile(ring), soft*median )
 * @returns {number} count of pixels corrected
 */
function removeHDRSpeckles3x3(hdr, opts = {}) {
  const { w, h, data } = hdr;
  const factor  = opts.factor  ?? 3.0;
  const abs     = opts.abs     ?? 0.2;
  const soft    = opts.soft    ?? 1.2;
  const ringPct = opts.ringPct ?? 0.95;
  const eps = 1e-8;

  // Build luminance buffer
  const Y = new Float32Array(w*h);
  for (let i=0, px=0; i<data.length; i+=3, px++) {
    Y[px] = 0.2126*data[i] + 0.7152*data[i+1] + 0.0722*data[i+2];
  }

  // Helpers
  function sortAsc(a){ for(let i=1;i<a.length;i++){ let v=a[i],j=i-1; while(j>=0 && a[j]>v){a[j+1]=a[j]; j--;} a[j+1]=v; } return a; }
  function median8(vals){ const s=sortAsc(vals.slice()); return 0.5*(s[3]+s[4]); }
  function percentile(vals, p){ const s=sortAsc(vals.slice()); const idx=Math.min(s.length-1, Math.max(0, Math.round(p*(s.length-1)))); return s[idx]; }

  // Visited map so we don’t re-fix overlapping clusters
  const visited = new Uint8Array(w*h);
  let fixed = 0;

  // We need a 5x5 ring ⇒ skip a 2px border
  for (let y=2; y<h-2; y++) {
    for (let x=2; x<w-2; x++) {
      const cIdx = y*w + x;
      if (visited[cIdx]) continue;

      // 1) Baseline from 8-neighbors of center
      const nb8 = new Float32Array(8);
      let k=0;
      for (let dy=-1; dy<=1; dy++) {
        for (let dx=-1; dx<=1; dx++) {
          if (!dx && !dy) continue;
          nb8[k++] = Y[(y+dy)*w + (x+dx)];
        }
      }
      const med = median8(nb8);
      const Yc  = Y[cIdx];

      // Is center hot enough to consider?
      if (!(Yc > med*factor && Yc > med + abs)) continue;

      // 2) Build 3x3 cluster mask using same hot criterion vs the SAME baseline median
      const mask = []; // list of [xx,yy] in cluster
      let minx= x, maxx= x, miny= y, maxy= y;
      for (let dy=-1; dy<=1; dy++) {
        for (let dx=-1; dx<=1; dx++) {
          const yy=y+dy, xx=x+dx, idx = yy*w + xx;
          const hot = (Y[idx] > med*factor && Y[idx] > med + abs);
          if (hot) {
            mask.push([xx,yy]);
            if (xx<minx) minx=xx; if (xx>maxx) maxx=xx;
            if (yy<miny) miny=yy; if (yy>maxy) maxy=yy;
          }
        }
      }
      if (mask.length === 0) continue;          // nothing hot
      if (mask.length > 9) continue;            // shouldn’t happen for 3x3 window
      // Reject line-like shapes (e.g., 1xK or Kx1 with K>=2)
      const dxSize = maxx - minx + 1;
      const dySize = maxy - miny + 1;
      const isLine = (dxSize === 1 && dySize >= 2) || (dySize === 1 && dxSize >= 2);
      if (isLine) continue;

      // If any pixel in cluster was already fixed, skip (avoid double adjustments)
      let overlap = false;
      for (const [xx,yy] of mask) { if (visited[yy*w+xx]) { overlap = true; break; } }
      if (overlap) continue;

      // 3) Compute robust target from 5x5 ring around the cluster bbox
      const ring = [];
      for (let yy=miny-2; yy<=maxy+2; yy++) {
        for (let xx=minx-2; xx<=maxx+2; xx++) {
          // outside image guard not needed due to outer loop
          const insideCluster = (xx>=minx && xx<=maxx && yy>=miny && yy<=maxy);
          if (insideCluster) continue; // skip cluster bbox interior
          ring.push(Y[yy*w + xx]);
        }
      }
      if (ring.length < 8) continue; // too small to be robust (very near border)
      const pHi = percentile(ring, ringPct);
      const targetY = Math.min(pHi, med * soft);

      // 4) Clamp each cluster pixel toward target, preserving chroma
      for (const [xx,yy] of mask) {
        const idx = yy*w + xx;
        const i3  = idx*3;
        const curY = Y[idx] || eps;
        if (targetY < curY) {
          const s = Math.max(0, (targetY || eps) / curY);
          data[i3    ] *= s;
          data[i3 + 1] *= s;
          data[i3 + 2] *= s;
          Y[idx] = targetY;
          fixed++;
        }
        visited[idx] = 1;
      }
    }
  }

  return fixed;
}

/**
 * Remove compact hot-speckle clusters up to 5x5 (in place), preserving lines/edges.
 * - Center test seeds a 5x5 "hot" mask using a robust baseline from the 8-neighbors.
 * - Rejects line-like shapes (1xK or Kx1) and very elongated blobs.
 * - Clamps cluster pixels toward a robust target from the surrounding 7x7 ring.
 *
 * @param {{w:number,h:number,data:Float32Array}} hdr
 * @param {object} [opts]
 * @param {number} [opts.factor=3.0]    // "hot" if Y > factor * median(neigh-8)
 * @param {number} [opts.abs=0.2]       // and Y > median + abs  (scene-linear)
 * @param {number} [opts.soft=1.2]      // cap target to soft * median
 * @param {number} [opts.ringPct=0.95]  // target = min(percentile(ring), soft*median)
 * @param {number} [opts.maxAspect=2.0] // reject blobs with width/height ratio > maxAspect
 * @returns {number} number of pixels corrected
 */
function removeHDRSpeckles5x5(hdr, opts = {}) {
  const { w, h, data } = hdr;
  const factor   = opts.factor   ?? 3.0;
  const abs      = opts.abs      ?? 0.2;
  const soft     = opts.soft     ?? 1.2;
  const ringPct  = opts.ringPct  ?? 0.95;
  const maxAspect= opts.maxAspect?? 2.0;
  const eps = 1e-8;

  // Luminance buffer
  const Y = new Float32Array(w*h);
  for (let i=0, px=0; i<data.length; i+=3, px++) {
    Y[px] = 0.2126*data[i] + 0.7152*data[i+1] + 0.0722*data[i+2];
  }

  // Small utils
  function sortAsc(a){ for(let i=1;i<a.length;i++){ let v=a[i],j=i-1; while(j>=0 && a[j]>v){a[j+1]=a[j]; j--;} a[j+1]=v; } return a; }
  function median8(vals){ const s=sortAsc(vals.slice()); return 0.5*(s[3]+s[4]); }
  function percentile(vals, p){ const s=sortAsc(vals.slice()); const idx=Math.min(s.length-1, Math.max(0, Math.round(p*(s.length-1)))); return s[idx]; }

  const visited = new Uint8Array(w*h);
  let fixed = 0;

  // Need 7x7 ring → skip 3px border
  for (let cy=3; cy<h-3; cy++) {
    for (let cx=3; cx<w-3; cx++) {
      const cIdx = cy*w + cx;
      if (visited[cIdx]) continue;

      // Baseline from 8-neighbors of center
      const nb8 = new Float32Array(8);
      let k=0;
      for (let dy=-1; dy<=1; dy++) for (let dx=-1; dx<=1; dx++) {
        if (!dx && !dy) continue;
        nb8[k++] = Y[(cy+dy)*w + (cx+dx)];
      }
      const med = median8(nb8);
      const Yc  = Y[cIdx];
      if (!(Yc > med*factor && Yc > med + abs)) continue; // not hot enough to seed

      // Build 5x5 cluster mask using the SAME baseline median
      const mask = []; // [x,y]
      let minx=cx, maxx=cx, miny=cy, maxy=cy;
      for (let dy=-2; dy<=2; dy++) {
        for (let dx=-2; dx<=2; dx++) {
          const yy=cy+dy, xx=cx+dx, idx=yy*w+xx;
          const hot = (Y[idx] > med*factor && Y[idx] > med + abs);
          if (hot) {
            mask.push([xx,yy]);
            if (xx<minx) minx=xx; if (xx>maxx) maxx=xx;
            if (yy<miny) miny=yy; if (yy>maxy) maxy=yy;
          }
        }
      }
      if (!mask.length || mask.length > 25) continue;

      // Reject line-like or elongated shapes
      const ww = maxx - minx + 1, hh = maxy - miny + 1;
      if ((ww === 1 && hh >= 2) || (hh === 1 && ww >= 2)) continue; // line
      const aspect = (ww>hh) ? ww/hh : hh/ww;
      if (aspect > maxAspect) continue; // too elongated (likely edge/line)

      // Skip if already touched
      let overlap=false;
      for (const [x,y] of mask) if (visited[y*w+x]) { overlap=true; break; }
      if (overlap) continue;

      // Build 7x7 ring (around bbox), excluding bbox interior
      const ring = [];
      const ringMinX = Math.max(0, minx-2), ringMaxX = Math.min(w-1, maxx+2);
      const ringMinY = Math.max(0, miny-2), ringMaxY = Math.min(h-1, maxy+2);
      for (let y=ringMinY; y<=ringMaxY; y++) {
        for (let x=ringMinX; x<=ringMaxX; x++) {
          if (x>=minx && x<=maxx && y>=miny && y<=maxy) continue; // skip bbox
          ring.push(Y[y*w + x]);
        }
      }
      if (ring.length < 12) continue; // too small to be robust

      const pHi = percentile(ring, ringPct);
      const targetY = Math.min(pHi, med * soft);

      // Clamp cluster pixels (only if above target), preserve chroma
      for (const [x,y] of mask) {
        const idx = y*w + x, i3 = idx*3;
        const curY = Y[idx] || eps;
        if (curY > targetY) {
          const s = Math.max(0, (targetY || eps) / curY);
          data[i3    ] *= s;
          data[i3 + 1] *= s;
          data[i3 + 2] *= s;
          Y[idx] = targetY;
          fixed++;
        }
        visited[idx] = 1;
      }
    }
  }
  return fixed;
}

/**
 * Remove tiny bright speckles using a Difference-of-Gaussians detector.
 * Works in luminance. Only suppresses *small positive blobs*, not edges/lines.
 *
 * @param {{w:number,h:number,data:Float32Array}} hdr (linear RGB, in place)
 * @param {object} [o]
 * @param {number} [o.sigma1=0.6]     // small blur sigma
 * @param {number} [o.sigma2=1.2]     // larger blur sigma (≈ 2*sigma1)
 * @param {number} [o.k=3.5]          // threshold in local std units
 * @param {number} [o.maxRadius=1]    // 1=affects ~3x3 blobs; use 2 for ~5x5
 * @param {number} [o.blend=0.75]     // 0..1: how much of the speckle to remove
 * @returns {number} pixels attenuated
 */
function removeSpeckle_DoG(hdr, o={}) {
  const { w, h, data } = hdr;
  const sigma1 = o.sigma1 ?? 0.6;
  const sigma2 = o.sigma2 ?? 1.2;
  const k      = o.k      ?? 3.5;
  const maxR   = o.maxRadius ?? 1;
  const blend  = Math.min(1, Math.max(0, o.blend ?? 0.75));
  const N = w*h;

  // Luminance
  const Y = new Float32Array(N);
  for (let i=0, p=0; i<data.length; i+=3, p++) {
    Y[p] = 0.2126*data[i] + 0.7152*data[i+1] + 0.0722*data[i+2];
  }

  // Gaussian blur helper (separable, auto kernel from sigma)
  function gauss1D(sigma){
    const r = Math.max(1, Math.round(sigma*3));
    const K = new Float32Array(2*r+1);
    const a = 1/(2*sigma*sigma);
    let sum=0;
    for (let i=-r;i<=r;i++){ const v=Math.exp(-i*i*a); K[i+r]=v; sum+=v; }
    for (let i=0;i<K.length;i++) K[i]/=sum;
    return {K,r};
  }
  function blur(src, dst, sigma){
    const {K,r} = gauss1D(sigma);
    // horiz
    const tmp = new Float32Array(N);
    for (let y=0;y<h;y++){
      for (let x=0;x<w;x++){
        let acc=0;
        for (let k=-r;k<=r;k++){
          const xx = Math.min(w-1, Math.max(0, x+k));
          acc += src[y*w+xx]*K[k+r];
        }
        tmp[y*w+x]=acc;
      }
    }
    // vert
    for (let x=0;x<w;x++){
      for (let y=0;y<h;y++){
        let acc=0;
        for (let k=-r;k<=r;k++){
          const yy = Math.min(h-1, Math.max(0, y+k));
          acc += tmp[yy*w+x]*K[k+r];
        }
        dst[y*w+x]=acc;
      }
    }
  }

  // DoG + local variance estimate
  const L1 = new Float32Array(N), L2 = new Float32Array(N);
  blur(Y, L1, sigma1);
  blur(Y, L2, sigma2);
  const R = new Float32Array(N);              // response
  for (let i=0;i<N;i++) R[i] = Math.max(0, L1[i]-L2[i]); // positive blobs only

  // Local mean/std of R using a small box (3x3 or 5x5 if maxR=2)
  const rad = (maxR===2)? 2 : 1;
  const area = (2*rad+1)*(2*rad+1);
  const Mean = new Float32Array(N), Var = new Float32Array(N);
  // integral images for fast box filter
  function integral(arr){
    const I = new Float32Array((w+1)*(h+1));
    for (let y=1;y<=h;y++){
      let rowSum=0;
      for (let x=1;x<=w;x++){
        rowSum += arr[(y-1)*w+(x-1)];
        I[y*(w+1)+x] = I[(y-1)*(w+1)+x] + rowSum;
      }
    }
    return I;
  }
  function boxSum(I, x1,y1,x2,y2){ // inclusive coords in image space
    x1=Math.max(0,x1); y1=Math.max(0,y1); x2=Math.min(w-1,x2); y2=Math.min(h-1,y2);
    const A = I[y1*(w+1)+x1];
    const B = I[y1*(w+1)+(x2+1)];
    const C = I[(y2+1)*(w+1)+x1];
    const D = I[(y2+1)*(w+1)+(x2+1)];
    return D - B - C + A;
  }
  const I1 = integral(R);
  const R2 = new Float32Array(N);
  for (let i=0;i<N;i++) R2[i]=R[i]*R[i];
  const I2 = integral(R2);

  for (let y=0;y<h;y++){
    for (let x=0;x<w;x++){
      const sum  = boxSum(I1, x-rad, y-rad, x+rad, y+rad);
      const sum2 = boxSum(I2, x-rad, y-rad, x+rad, y+rad);
      const m = sum/area;
      const v = Math.max(0, sum2/area - m*m);
      Mean[y*w+x]=m; Var[y*w+x]=v;
    }
  }

  // Non-maximum suppression within (2*maxR+1) to keep only isolated blobs
  function isLocalMax(idx, x, y){
    const r = maxR;
    const c = R[idx];
    for (let yy=y-r; yy<=y+r; yy++){
      if (yy<0||yy>=h) continue;
      for (let xx=x-r; xx<=x+r; xx++){
        if (xx<0||xx>=w) continue;
        const j = yy*w+xx;
        if (j!==idx && R[j] >= c) return false;
      }
    }
    return true;
  }

  let fixed=0;
  const eps = 1e-8;
  for (let y=0;y<h;y++){
    for (let x=0;x<w;x++){
      const i = y*w+x;
      const std = Math.sqrt(Var[i]) || 1e-8;
      // detection: response > local mean + k*std
      if (R[i] > Mean[i] + k*std && isLocalMax(i,x,y)) {
        // compute a *robust* local target: median of 3x3 luminance (exclude center)
        const neigh = [];
        for (let dy=-1;dy<=1;dy++){
          for (let dx=-1;dx<=1;dx++){
            if (!dx && !dy) continue;
            const xx = Math.min(w-1, Math.max(0, x+dx));
            const yy = Math.min(h-1, Math.max(0, y+dy));
            neigh.push(Y[yy*w+xx]);
          }
        }
        neigh.sort((a,b)=>a-b);
        const med = 0.5*(neigh[3]+neigh[4]);
        const curY = Y[i];
        if (curY > med){ // only pull downwards
          const target = med + (1.0-blend)*(curY - med); // partial pull: blend∈[0,1]
          const s = Math.max(0, target / (curY || eps));
          const q = i*3;
          data[q  ] *= s;
          data[q+1] *= s;
          data[q+2] *= s;
          Y[i] = target;
          fixed++;
        }
      }
    }
  }
  return fixed;
}


/**
 * Morphological white top-hat speckle attenuator (3x3 element).
 * Good complement to DoG; hits small bright residues that slip through.
 *
 * @param {{w:number,h:number,data:Float32Array}} hdr
 * @param {object} [o]
 * @param {number} [o.tau=6.0]      // threshold in MAD units of residue
 * @param {number} [o.blend=0.8]    // 0..1 attenuation toward local median
 * @returns {number} pixels attenuated
 */
function removeSpeckle_TopHat(hdr, o={}) {
  const { w,h,data } = hdr;
  const tau = o.tau ?? 6.0;
  const blend = Math.min(1, Math.max(0, o.blend ?? 0.8));
  const N = w*h;

  // luminance
  const Y = new Float32Array(N);
  for (let i=0,p=0;i<data.length;i+=3,p++){
    Y[p] = 0.2126*data[i] + 0.7152*data[i+1] + 0.0722*data[i+2];
  }

  // fast 3x3 min/max
  function min3x3(src){
    const out = new Float32Array(N);
    for (let y=0;y<h;y++){
      for (let x=0;x<w;x++){
        let m=Infinity;
        for (let dy=-1;dy<=1;dy++){
          const yy=Math.min(h-1,Math.max(0,y+dy));
          for (let dx=-1;dx<=1;dx++){
            const xx=Math.min(w-1,Math.max(0,x+dx));
            const v=src[yy*w+xx]; if (v<m) m=v;
          }
        }
        out[y*w+x]=m;
      }
    }
    return out;
  }
  function max3x3(src){
    const out = new Float32Array(N);
    for (let y=0;y<h;y++){
      for (let x=0;x<w;x++){
        let m=-Infinity;
        for (let dy=-1;dy<=1;dy++){
          const yy=Math.min(h-1,Math.max(0,y+dy));
          for (let dx=-1;dx<=1;dx++){
            const xx=Math.min(w-1,Math.max(0,x+dx));
            const v=src[yy*w+xx]; if (v>m) m=v;
          }
        }
        out[y*w+x]=m;
      }
    }
    return out;
  }

  // opening = dilate(erode(Y))
  const er = min3x3(Y);
  const op = max3x3(er);
  // residue = Y - opened
  const R = new Float32Array(N);
  for (let i=0;i<N;i++) R[i] = Math.max(0, Y[i]-op[i]);

  // Robust global threshold via MAD of R
  const samp = [];
  for (let i=0;i<N; i+=Math.max(1, (N/20000|0))) samp.push(R[i]);
  samp.sort((a,b)=>a-b);
  const med = samp[samp.length>>1] || 0;
  for (let i=0;i<samp.length;i++) samp[i] = Math.abs(samp[i]-med);
  const mad = samp[samp.length>>1] || 1e-8;
  const thr = med + tau * (1.4826 * mad); // ~ N(0,σ) equiv

  // Attenuate residues above threshold
  let fixed=0;
  for (let i=0;i<N;i++){
    if (R[i] > thr) {
      // local 3x3 median for target
      const x = i % w, y = (i / w) | 0;
      const neigh = [];
      for (let dy=-1;dy<=1;dy++){
        const yy=Math.min(h-1,Math.max(0,y+dy));
        for (let dx=-1;dx<=1;dx++){
          const xx=Math.min(w-1,Math.max(0,x+dx));
          if (xx===x && yy===y) continue;
          neigh.push(Y[yy*w+xx]);
        }
      }
      neigh.sort((a,b)=>a-b);
      const medN = 0.5*(neigh[3]+neigh[4]);
      const target = medN + (1.0-blend)*(Y[i]-medN);
      const s = Math.max(0, target / (Y[i] || 1e-8));
      const q = i*3;
      data[q  ] *= s; data[q+1] *= s; data[q+2] *= s;
      Y[i] = target;
      fixed++;
    }
  }
  return fixed;
}

/**
 * Suppress bright speckles in *shadows* (HDR, linear RGB, in place).
 * - Operates only where local 3x3 median luminance < shadowCut.
 * - Triggers if center is a strong *relative* outlier vs median + MAD.
 * - Optionally joins tiny 3x3 clusters; skips long lines.
 *
 * @param {{w:number,h:number,data:Float32Array}} hdr
 * @param {object} [o]
 * @param {number} [o.shadowCut=0.10]   // only process neighborhoods with median Y < this
 * @param {number} [o.rel=2.5]          // Yc > median * rel (relative contrast)
 * @param {number} [o.madK=6.0]         // Yc - median > madK * MAD (robust diff)
 * @param {number} [o.madFloorFrac=0.03]// MAD floor as fraction of median (noise floor)
 * @param {boolean}[o.allowCluster=true]// allow small 3x3 blobs (not lines)
 * @param {number} [o.soft=1.2]         // clamp target <= soft * median
 * @param {number} [o.pct=0.95]         // clamp target <= pct-neighbor (robust high)
 * @returns {number} count of pixels attenuated
 */
function removeShadowSpecklesHDR(hdr, o = {}) {
  const { w, h, data } = hdr;
  const shadowCut   = o.shadowCut   ?? 0.10;
  const rel         = o.rel         ?? 2.5;
  const madK        = o.madK        ?? 6.0;
  const madFloorFrac= o.madFloorFrac?? 0.03;
  const allowCluster= o.allowCluster?? true;
  const soft        = o.soft        ?? 1.2;
  const pct         = o.pct         ?? 0.95;
  const eps = 1e-8;

  // Luminance buffer
  const N = w*h;
  const Y = new Float32Array(N);
  for (let i=0, p=0; i<data.length; i+=3, p++) {
    Y[p] = 0.2126*data[i] + 0.7152*data[i+1] + 0.0722*data[i+2];
  }

  // small helpers
  function sort8(a){ for(let i=1;i<8;i++){ let v=a[i],j=i-1; while(j>=0&&a[j]>v){a[j+1]=a[j]; j--; } a[j+1]=v; } return a; }
  function median8(vals){ const s=sort8(vals.slice()); return 0.5*(s[3]+s[4]); }
  function perc8(vals,p){ const s=sort8(vals.slice()); const idx=Math.min(7,Math.max(0,Math.round(p*7))); return s[idx]; }

  // track visited cluster pixels to avoid over-adjustment
  const visited = new Uint8Array(N);
  let fixed = 0;

  // skip 1px border
  for (let y=1; y<h-1; y++) {
    for (let x=1; x<w-1; x++) {
      const idx = y*w + x;
      if (visited[idx]) continue;

      // gather 3x3 neighbors (excluding center) for baseline
      const nb = new Float32Array(8);
      let k=0;
      for (let dy=-1; dy<=1; dy++) {
        for (let dx=-1; dx<=1; dx++) {
          if (!dx && !dy) continue;
          nb[k++] = Y[(y+dy)*w + (x+dx)];
        }
      }
      const med = median8(nb);
      if (med >= shadowCut) continue; // only operate in shadows

      // robust noise (MAD) with floor proportional to median (accounts for photon noise)
      const dev = new Float32Array(8);
      for (let i=0;i<8;i++) dev[i] = Math.abs(nb[i] - med);
      const MAD = median8(dev);
      const madFloor = Math.max(med * madFloorFrac, 1e-6);
      const sigmaR = Math.max(MAD * 1.4826, madFloor); // ≈ robust std

      const Yc = Y[idx];

      // trigger purely on *relative* + robust absolute (in shadow scale)
      if (!(Yc > med * rel && (Yc - med) > madK * sigmaR)) continue;

      // optionally grow a 3x3 *compact* blob (not lines)
      let mask = [[x,y]];
      if (allowCluster) {
        for (let dy=-1; dy<=1; dy++) {
          for (let dx=-1; dx<=1; dx++) {
            if (!dx && !dy) continue;
            const xx=x+dx, yy=y+dy, j=yy*w+xx;
            const Yn = Y[j];
            if (Yn > med * rel && (Yn - med) > madK * sigmaR) mask.push([xx,yy]);
          }
        }
        // reject line-like clusters (1xK or Kx1 with K>=2)
        let minx=x, maxx=x, miny=y, maxy=y;
        for (const [xx,yy] of mask){ if(xx<minx)minx=xx; if(xx>maxx)maxx=xx; if(yy<miny)miny=yy; if(yy>maxy)maxy=yy; }
        const ww = maxx-minx+1, hh = maxy-miny+1;
        const isLine = (ww===1 && hh>=2) || (hh===1 && ww>=2);
        if (isLine) mask = [[x,y]]; // fall back to single-pixel fix
      }

      // robust target: cap to high-percentile of neighbors and soft*median
      const hi = perc8(nb, pct);
      const targetY = Math.min(hi, med * soft);

      // attenuate selected pixels (only if they’re above target), preserve chroma
      for (const [xx,yy] of mask) {
        const j = yy*w + xx;
        if (visited[j]) continue;
        const curY = Y[j];
        if (curY > targetY) {
          const s = Math.max(0, (targetY || eps) / (curY || eps));
          const q = j*3;
          data[q  ] *= s;
          data[q+1] *= s;
          data[q+2] *= s;
          Y[j] = targetY;
          fixed++;
        }
        visited[j] = 1;
      }
    }
  }
  return fixed;
}


async function runPipeline(scale) {
  try {
    $('#saveHdr').disabled = true;
    logEl.textContent = '';
    setOverall(0); setPerFile(0);

    const files = Array.from($('#files').files || []);
    if (!files.length) { logLine("Please select JPG files first.", 'warn'); return; }

    const previewExposure = parseFloat($('#previewExp').value || '2.0');

    setStage('Reading EXIF + decoding images…');
    setOverall(5);
    const { linearImages, sortedExpos, w, h, baseName } = await loadAndPreprocess(files, scale);
  
    setStage('Merging to HDR (radiance)…');
    setOverall(35);
	setPerFile(0);
    const hdr = await mergeRadiance_linear(linearImages, sortedExpos);
    setPerFile(100);
    await nextFrame();
	

    setStage('Normalizing white to ~1.0…');
    setOverall(75);
    const white = normalizeWhitePercentile(hdr, WHITE_PCT);
    logLine(`White percentile (${WHITE_PCT}%): ${white.toFixed(6)}`, 'ok');
    await nextFrame();
	
	let fixed = 0;
	//fixed += removeSpeckle_DoG(hdr, { sigma1:0.6, sigma2:1.2, k:2.0, maxRadius:1, blend:0.9 });
	//logLine(`Speckle attenuated (DoG 1): ${fixed} px`, fixed ? 'ok' : 'muted');
    //await nextFrame();
	//// optional: a second pass for slightly larger blobs
	//fixed += removeSpeckle_DoG(hdr, { sigma1:0.9, sigma2:1.8, k:2.0, maxRadius:2, blend:0.9 });
	//logLine(`Speckle attenuated (DoG 2): ${fixed} px`, fixed ? 'ok' : 'muted');
    //await nextFrame();
	// optional morphological pass if a few still remain
	//fixed += removeSpeckle_TopHat(hdr, { tau:6.0, blend:0.85 });
	//logLine(`Speckle attenuated (DoG/top-hat): ${fixed} px`, fixed ? 'ok' : 'muted');
    //await nextFrame();
	fixed += removeShadowSpecklesHDR(hdr, {
	  shadowCut: 0.10, // treat below ~10% as "shadow" in scene-linear
	  rel: 0.25,
	  madK: 6.0,
	  madFloorFrac: 0.03,
	  allowCluster: true,
	  soft: 1.2,
	  pct: 0.95
	});
	logLine(`Speckle attenuated (DoG/shadow): ${fixed} px`, fixed ? 'ok' : 'muted');
    await nextFrame();

	//const nFixed = removeHDRSpeckles(hdr, {
	//  factor: 3.0,   // try 2.5–4.0
	//  abs: 0.15,     // guard for mid/bright regions
	//  pct: 0.5,     // neighborhood high percentile
	//  soft: 1.0,     // also cap to 1.2×median
	//  requirePeak: true
	//});
	//logLine(`Speckle removed: ${nFixed}`, 'ok');
	//const n1 = removeHDRSpeckles(hdr, {
	//  factor: 3.0, abs: 0.15, soft: 1.0, pct: 0.5, requirePeak: true
	//});
	//const n2 = removeHDRSpeckles3x3(hdr, {
	//  factor: 3.0, abs: 0.15, soft: 1.0, ringPct: 0.5
	//});
	//
	//const n3 = removeHDRSpeckles5x5(hdr,   { 
	//  factor: 3.0, abs: 0.15, soft: 1.0, ringPct:0.5, maxAspect:2.0 
	//});
	//logLine(`Speckle removed: ${n} ${n2} ${n3} `, 'ok');

    setStage('Tone-mapping…');
    setOverall(85);
    const ldr = await tonemap_filmic(hdr, previewExposure);
    drawToCanvas(ldr, $('#preview'));
    await nextFrame();

    setStage('Preparing downloads…');
    setOverall(92);
    $('#saveHdr').disabled = false;
    $('#saveHdr').onclick = async () => {
      try {
	  
		// Optional: allow cancel
		const controller = new AbortController();
		// Expose cancel somewhere: controller.abort();

        //const blob = encodeRadianceHDR_RGBE(hdr)
        //const blob = encodeRadianceHDR_RGBE_RLE(hdr);
		const blob = await encodeRadianceHDR_RGBE_RLE_Async(
		  hdr,
		  pct => setPerFile(pct),            // progress bar
		  { yieldMs: 500, signal: controller.signal }
		);
	
        const a = document.createElement('a');
        a.href = URL.createObjectURL(blob);
        a.download = baseName + '.hdr';   // <— use shortest exposure basename
        a.click();
        URL.revokeObjectURL(a.href);
        logLine('HDR downloaded.', 'ok');
      } catch (e) {
        logLine(`HDR save failed: ${e.message||e}`, 'err');
      }
    };

    setStage('Done');
    setOverall(100);
    logLine('✅ Merge complete.', 'ok');
  } catch (err) {
    setStage('Error');
    setOverall(100);
    logLine(`❌ ${err.message || err}`, 'err');
    console.error(err);
  }
}


$('#run').addEventListener('click', async () => {
  await runPipeline(1.0);  // full res
});

$('#runHalf').addEventListener('click', async () => {
  await runPipeline(0.5);  // half res
});

$('#runQuarter').addEventListener('click', async () => {
  await runPipeline(0.25);  // half res
});
</script>
