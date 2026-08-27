<script src="../../jquery.min.js"></script>
<script src="../../qrcodeborder.js"></script>
<script src="../../html2canvas.min.js"></script>
<style>
        #qrcode{
            width: 100%;
        }
</style>


# HDRI Merge (optimized for GoPro MAX2)

<b>Why:</b> 360° HDRIs capture the full lighting environment in every direction, making them ideal for 
realistic image-based lighting in 3D rendering, VFX, and virtual production. By mapping an 
HDRI onto a sphere or dome, artists can recreate the natural reflections, colors, and brightness 
of real locations, perfect for matching CGI elements to live-action footage or achieving 
photorealistic lighting in visualizations and games.

[![Watch the video](./videoicon.jpg)](https://youtu.be/Q7apDnsnU-o)

## Configure Your MAX2 to Create HDRIs Easily 

<b>First QR Code</b> is a GoPro Labs macro that will taking up to 11 exposures, 2.0 stops apart for very wide HDRIs. 
Optionally optimize for moonlit nights (<input type="checkbox" id="moon" name="moon">very low light), 
this will add even longer exposures, which are otherwise useless for lit-interiors or daylight (recommended off.) 
The script will optionally name the files <b>H</b>ab<b>_GS01</b>xzwy.<b>JPG</b> 
(<input type="checkbox" id="lname" name="lname" checked>Enable Name Change), 
to help you find the exposure groups on the SD card, 
however the renamed files will not show in camera playback or in Quik. The HDRI script is 
designed for laptop/desktop workflows.<br>

**Start Delay** <input type="range" style="width: 180px;" id="delay" name="delay" min="0" max="9" value="0"><label for="delay"></label>&nbsp;&nbsp;<b id="delaytext"></b> seconds<br>
 
<div id="qrcode_txt" style="width: 540px">
  <center>
  <div id="qrcode" style="width: 540px"></div><br>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext"></em><br>
  <b><font color="#005CAC">HDRI Macro v1.1<em id="status"></em></font></b>
  </center>
</div>
<br>
<br>
<b>Second QR Code</b> makes a preset called "HDRI" from the above macro.<br>

<div id="qrcode_txt2" style="width: 540px">
  <center>
  <div id="qrcode2" style="width: 540px"></div><br>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext2"></em><br>
  <b><font color="#005CAC">HDRI Preset<em id="status"></em></font></b>
  </center>
</div>
<br>
<br>
<!-- <img src="https://gopro.github.io/labs/control/hdri/presetQR.png" alt="Preset"><br> -->
<br>

## On camera Setup

Go to the Menu -> Preferences -> General, scroll down to 360 Photo Format, and select .JPG (rather than .36P).  

## Using HDRI Preset

After scanning the above two QR Codes, to run HDRI mode, select the new HDRI preset from the photo menu. 
The camera will say "Labs processing", as it waiting for a shutter press to run the nine exposures. 
Shutter press via any compatible BLE remote, or the physical button (it will not work via Quik.) The camera should be stationary, 
as the nine exposures will take about 33 seconds. <br>
WARNING: While the HDRI preset is selected, the camera will remain on, no auto shutdown. 
You can manual power off, or go to any other preset for returned normal camera functionality.

# Merge your Bracketed Exposures

Press "Choose Files" below to select your files to compute a single HDRI.  
Then press Merge HDR (8K) for the ½ or ¼ Res merge for a faster preview.  
Once complete, click on Download .HDR.<br>
<br>
Looking for a free web tool to view and test your .HDR file, try <a href="https://wkjarosz.github.io/hdrview/">HDRview</a><br>

<fieldset>
  <legend>Inputs</legend>
  <div class="row" style="margin-bottom: 5px;">
    <input id="files" type="file" accept="image/jpeg" multiple /><br>
  </div>
  <div class="row" style="margin-bottom: 5px;">
	Select RGB color range before merging:
	<input type="radio" id="rec709" name="color" checked><label for="rec709">Rec709</label>&nbsp;
	<input type="radio" id="rec2020" name="color"><label for="rec2020">Rec2020</label>
  </div>
  <div class="row" style="margin-bottom: 5px;">
    <button id="run" disabled>Merge HDR</button>
    <button id="runHalf" disabled>HDR (½ Res)</button>
    <button id="runQuarter" disabled>HDR (¼ Res)</button>
    <button id="saveHdr" disabled style="margin-left: 20px;">Download .HDR</button>
  </div>
  <div class="row">
    <label>Preview EV: <input id="previewExp" type="number" min="-10" max="10" step="0.5" value="1.0" title="Exposure for preview" style="width: 100px;"></label>
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
const SUN_BLUR_LARGE = 63;
const CLIPPED_THRESH = 0.9;    // test threshold in linear (post-blur)
const CLIPPED_COUNT  = 1000;    // number of clipped pixels to consider "has clipped sun"

/* ===================== Helpers / UI ===================== */
const $ = sel => document.querySelector(sel);
const logEl = $('#log');

const MAX_LOG_LINES = 8;
function logLine(msg, cls = '') {
  const line = document.createElement('div');
  if (cls) line.className = cls;
  line.textContent = msg;
  logEl.appendChild(line);

  // Keep at most MAX_LOG_LINES
  while (logEl.children.length > MAX_LOG_LINES) {
    logEl.removeChild(logEl.firstChild);
  }

  // Always scroll to bottom
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


function gaussianBlurFloatRGB_fastApprox(src, w, h, ksize, opts = {}) {
  // --- optional very fast path: downsample → blur → upsample ---
  const down = Math.max(1, Math.min(4, (opts.downsample|0) || 1));
  if (down > 1) {
    const wd = Math.max(1, (w/down)|0), hd = Math.max(1, (h/down)|0);
    const small = new Float32Array(wd*hd*3);
    // box downsample (simple average of down×down block)
    boxDownsampleRGB(src, w, h, small, wd, hd, down);
    const blurredSmall = gaussianBlurFloatRGB_fastApprox(small, wd, hd, ksize, { inPlace:false });
    const up = new Float32Array(w*h*3);
    bilinearUpsampleRGB(blurredSmall, wd, hd, up, w, h);
    if (opts.inPlace) { src.set(up); return src; }
    return up;
  }

  // --- main 3× box approximation ---
  ksize = Math.max(3, ksize|0);
  if ((ksize & 1) === 0) ksize += 1;   // force odd
  const sigma = (ksize - 1) / 6;       // Gaussian equivalent
  const radii = boxesForGauss(sigma, 3); // [r1,r2,r3]
  const total = w*h*3;

  const bufA = new Float32Array(total); // intermediate
  const bufB = new Float32Array(total); // intermediate / output

  // copy src → bufA
  bufA.set(src);

  for (let pass=0; pass<3; pass++) {
    const r = Math.max(1, radii[pass]);

    // Horizontal pass: bufA → bufB
    boxBlurH_RGB(bufA, bufB, w, h, r);

    // Vertical pass: bufB → bufA (ping-pong)
    boxBlurV_RGB(bufB, bufA, w, h, r);
  }

  if (opts.inPlace) { src.set(bufA); return src; }
  return bufA;

  // -------- helpers --------

  function boxesForGauss(sigma, n) {
    // Compute n box widths approximating Gaussian(sigma)
    const ideal = Math.sqrt((12*sigma*sigma/n)+1); // ideal width
    let wl = Math.floor(ideal);
    if ((wl & 1) === 0) wl -= 1;
    const wu = wl + 2;
    const m = Math.round((12*sigma*sigma - n*wl*wl - 4*n*wl - 3*n)/(-4*wl - 4));
    const sizes = Array.from({length:n}, (_,i)=> i < m ? wl : wu);
    return sizes.map(s => (s-1)>>1); // radii
  }

  // Horizontal box blur (replicate at row edges)
  function boxBlurH_RGB(src, dst, W, H, r) {
    const norm = 1 / (2*r + 1);
    for (let y=0; y<H; y++) {
      // initialize sums at x=0
      let sr=0, sg=0, sb=0;
      for (let k=-r; k<=r; k++) {
        const xx = clamp(0 + k, 0, W-1);
        const p = (y*W + xx)*3;
        sr += src[p]; sg += src[p+1]; sb += src[p+2];
      }
      let q = (y*W + 0)*3;
      dst[q]   = sr * norm;
      dst[q+1] = sg * norm;
      dst[q+2] = sb * norm;

      for (let x=1; x<W; x++) {
        const addX = clamp(x + r, 0, W-1);
        const subX = clamp(x - 1 - r, 0, W-1);
        const pa = (y*W + addX)*3;
        const ps = (y*W + subX)*3;
        sr += src[pa]   - src[ps];
        sg += src[pa+1] - src[ps+1];
        sb += src[pa+2] - src[ps+2];

        q = (y*W + x)*3;
        dst[q]   = sr * norm;
        dst[q+1] = sg * norm;
        dst[q+2] = sb * norm;
      }
    }
  }

  // Vertical box blur (replicate at column edges)
  function boxBlurV_RGB(src, dst, W, H, r) {
    const norm = 1 / (2*r + 1);
    for (let x=0; x<W; x++) {
      // initialize sums at y=0
      let sr=0, sg=0, sb=0;
      for (let k=-r; k<=r; k++) {
        const yy = clamp(0 + k, 0, H-1);
        const p = (yy*W + x)*3;
        sr += src[p]; sg += src[p+1]; sb += src[p+2];
      }
      let q = (0*W + x)*3;
      dst[q]   = sr * norm;
      dst[q+1] = sg * norm;
      dst[q+2] = sb * norm;

      for (let y=1; y<H; y++) {
        const addY = clamp(y + r, 0, H-1);
        const subY = clamp(y - 1 - r, 0, H-1);
        const pa = (addY*W + x)*3;
        const ps = (subY*W + x)*3;
        sr += src[pa]   - src[ps];
        sg += src[pa+1] - src[ps+1];
        sb += src[pa+2] - src[ps+2];

        q = (y*W + x)*3;
        dst[q]   = sr * norm;
        dst[q+1] = sg * norm;
        dst[q+2] = sb * norm;
      }
    }
  }

  function clamp(v, lo, hi){ return v < lo ? lo : (v > hi ? hi : v); }
}

// Average-pooling downsample by integer factor (2 or 4 recommended)
function boxDownsampleRGB(src, w, h, dst, wd, hd, factor) {
  const area = factor*factor;
  for (let yd=0; yd<hd; yd++) {
    for (let xd=0; xd<wd; xd++) {
      let sr=0, sg=0, sb=0;
      const x0 = xd*factor, y0 = yd*factor;
      for (let yy=0; yy<factor; yy++) {
        const y = Math.min(h-1, y0+yy);
        for (let xx=0; xx<factor; xx++) {
          const x = Math.min(w-1, x0+xx);
          const p = (y*w + x)*3;
          sr += src[p]; sg += src[p+1]; sb += src[p+2];
        }
      }
      const q = (yd*wd + xd)*3;
      dst[q]   = sr/area;
      dst[q+1] = sg/area;
      dst[q+2] = sb/area;
    }
  }
}

// Bilinear upsample back to full res
function bilinearUpsampleRGB(src, sw, sh, dst, dw, dh) {
  for (let y=0; y<dh; y++) {
    const v = (y*(sh-1))/(dh-1);
    const y0 = Math.floor(v), y1 = Math.min(sh-1, y0+1);
    const fy = v - y0;
    for (let x=0; x<dw; x++) {
      const u = (x*(sw-1))/(dw-1);
      const x0 = Math.floor(u), x1 = Math.min(sw-1, x0+1);
      const fx = u - x0;

      const p00 = (y0*sw + x0)*3;
      const p01 = (y0*sw + x1)*3;
      const p10 = (y1*sw + x0)*3;
      const p11 = (y1*sw + x1)*3;

      const q = (y*dw + x)*3;

      for (let c=0;c<3;c++){
        const a = src[p00+c]*(1-fx) + src[p01+c]*fx;
        const b = src[p10+c]*(1-fx) + src[p11+c]*fx;
        dst[q+c] = a*(1-fy) + b*fy;
      }
    }
  }
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
async function tonemap_filmic(hdr, ev=1.0) {
  const {w,h,data} = hdr;
  const out = new Uint8ClampedArray(w*h*4);
  //const A=0.22, B=0.30, C=0.10, D=0.20, E=0.01, F=0.30, W=11.2;  // too contrasty
  const A=0.2, B=0.30, C=0.10, D=0.05, E=0.0, F=0.10, W=20;  // lower contrast
  const whiteScale = ((W*(A*W+C*B)+D*E)/(W*(A*W+B)+D*F)) - (E/F);
  function rnd(i){ let x = i ^ (i>>>17); x ^= x<<13; x ^= x>>>7; x ^= x>>>17; return ((x>>>8)&0xFF)/255; }

  const exposure = Math.pow(2.0, ev);

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



async function encodeRadianceHDR_RGBE(hdr, onProgress) 
{
  const { w, h, data } = hdr;
  const yieldMs = 500;
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

  for (let y = 0; y < h; y++) 
  {
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
    const now = performance.now();
    if (now - lastYield > yieldMs) {
      if (onProgress) onProgress(((y + 1) / h) * 100);
      lastYield = now;
      await new Promise(r => requestAnimationFrame(r));
    }

  }
  
  
  return new Blob(chunks, { type: "image/vnd.radiance" });
}




/**
 * Apply a 3x3 color matrix to an interleaved Float32Array RGB image.
 * 
 * @param {Float32Array} lin - linear RGB data, length = w*h*3
 * @param {...number} m - 9 numbers for 3x3 color matrix
 * @example
 * colorMatrix(lin,
 *   1.693359, -0.60742,  -0.08594,
 *  -0.18945,  1.521484, -0.33203,
 *   0.046875, -0.67773,  1.630859);
 */
function colorMatrix(lin,
  m00, m01, m02,
  m10, m11, m12,
  m20, m21, m22)
{
  const n = lin.length;
  for (let i = 0; i < n; i += 3) {
    const r = lin[i];
    const g = lin[i + 1];
    const b = lin[i + 2];
    lin[i    ] = r*m00 + g*m01 + b*m02;
    lin[i + 1] = r*m10 + g*m11 + b*m12;
    lin[i + 2] = r*m20 + g*m21 + b*m22;
  }
}


function getColorTempSun(lin, w, h, sun_x, sun_y) {
  let rBias = 0.0, gBias = 0.0, bBias = 0.0;
  sun_x = sun_x & 0xffff;
  sun_y = sun_y & 0xffff;
  
  let angle,radius;
  let rmax = w/90.0;
  let rstep = rmax / 50.0;
  let x = sun_x;
  let y = sun_y;
  let total = 0;
  
  //console.log("sun pos:", sun_x, sun_y);
  
  for(angle=0.0;angle<6.28; angle+=0.025)
  {
	  let xstep = Math.cos(angle);
	  let ystep = Math.sin(angle);
	  for(radius = rstep;radius<rmax; radius+=rstep)
	  {
		x = (sun_x + radius * xstep) & 0x7ffff;
		y = (sun_y + radius * ystep) & 0x7ffff;
		
		
		let i = (y*w + x)*3;
		let r = lin[i];
		let g = lin[i + 1];
		let b = lin[i + 2];
		
		if(r<0.9 && g<0.9 && b<0.9)
		{
			rBias += r;
			gBias += g;
			bBias += b;
			total ++;
			//console.log("per:", radius/rmax *100.0);
			break;
		}
	  }
  }
  
  if(total)
  {
	  rBias /= total;
	  gBias /= total;
	  bBias /= total;
  }
  else
  {
	  rBias = 1.0;
	  gBias = 1.0;
	  bBias = 1.0;
  }
  
  //console.log("RGB:", rBias, gBias, bBias, total);
  
  // Small sanity clamp to avoid extreme tints
  const clamp = (v) => Math.min(4, Math.max(0.25, v));
  return [clamp(rBias), gBias, clamp(bBias)];
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

  let shift = 0;
  if(scale <= 0.5) shift++; 
  if(scale <= 0.25) shift++;

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
	
	if(true === document.getElementById("rec709").checked)
		colorMatrix( lin,
		1.693, -0.607, -0.086,
		-0.189,  1.522, -0.333,
		0.047, -0.678,  1.631);
	else
		colorMatrix( lin,
		 1.00199602,  0.09096836, -0.09296437,
		-0.05627738,  1.34989477, -0.29361737,
		 0.05320917, -0.48320693,  1.42999776);

    let t = sortedExpos[i];

    // ---------- Short-exposure "sun" logic (unchanged behavior, now at scaled size) ----------
    if (t < SHORT_EXPOSURE_T) 
	{
      // Detect clipped sun on a blurred copy (first pass blur)
      let blurForSun = gaussianBlurFloatRGB_fastApprox(lin, w, h, SUN_BLUR_LARGE>>shift);
      //let blurForSun = gaussianBlurFloatRGB(lin, w, h, SUN_BLUR_LARGE>>shift);
      let clippedCount = 0;
      for (let p = 0; p < blurForSun.length; p++) if (blurForSun[p] > CLIPPED_THRESH) clippedCount++;
      // Scale count to approx native 7680×3840 reference if you use that heuristic
      clippedCount /= (scale*scale);
      const hasClippedSun = clippedCount > CLIPPED_COUNT;
      logLine(`Sun clipped? ${hasClippedSun} (count=${Math.round(clippedCount)})`, hasClippedSun ? 'warn' : 'muted');
	  setPerFile(5);
	  await nextFrame();
		
      if (hasClippedSun) 
      {
        // Find bbox of bright region
        let minx = w, maxx = 0, miny = h, maxy = 0;
        for (let yy = 0; yy < h; yy++) {
          for (let xx = 0; xx < w; xx++) {
            const p = (yy * w + xx) * 3;
            const r = blurForSun[p], g = blurForSun[p + 1], b = blurForSun[p + 2];
            if (r > CLIPPED_THRESH || g > CLIPPED_THRESH || b > CLIPPED_THRESH) {
              if (minx > xx) minx = xx;
              if (maxx < xx) maxx = xx;
              if (miny > yy) miny = yy;
              if (maxy < yy) maxy = yy;
            }
          }
        }
		let sun_x = (maxx+minx)/2;
		let sun_y = (maxy+miny)/2;
		
		const [rBias, gBias, bBias] = getColorTempSun(lin, w, h, sun_x, sun_y);
		
		//console.log("rBias:", rBias);
		//console.log("gBias:", gBias);
		//console.log("bBias:", bBias);
		
		//console.log("near minx maxx: ", minx, maxx);
		//console.log("near miny maxy: ", miny, maxy);
        // pad ROI a bit; clamp to image
        minx = Math.max(0, minx - 64*scale);
        miny = Math.max(0, miny - 64*scale);
        maxx = Math.min(w - 1, maxx + 64*scale);
        maxy = Math.min(h - 1, maxy + 64*scale);

        // First soften (ROI blur; x2/y2 exclusive → pass max+1)
        gaussianBlurROI(lin, w, minx, miny, maxx, maxy, SUN_BLUR1>>shift);
		setPerFile(15);
		await nextFrame();
	  
		let sun_diameter = 0.53 * w / 360.0; //0.53 degrees average 
		let erp_scale = 1.0;
		if(sun_y < h/2)
		{
			let angle = (sun_y * 90.0) / (h*0.5);
			if(angle < 5) angle = 5;
			let radians = angle * 3.14159265 / 180.0;
			erp_scale = Math.sin(radians);
		}
		let sun_radius_squared = sun_diameter*erp_scale*0.5*sun_diameter*0.5;
		let count = 0;
		let count2 = 0;
		//console.log("sun_diameter: ", sun_diameter);
		//console.log("sun_x sun_y: ", sun_x, sun_y);
		//console.log("minx maxx: ", minx, maxx);
		//console.log("miny maxy: ", miny, maxy);
		for (let yy = miny; yy <= maxy; yy++) 
		{
          for (let xx = minx; xx <= maxx; xx++) 
		  {
			const p = (yy * w + xx) * 3;
			const r = lin[p], g = lin[p + 1], b = lin[p + 2];
			if (r > CLIPPED_THRESH || g > CLIPPED_THRESH || b > CLIPPED_THRESH)
			{
				const radius_squared = ((yy-sun_y)*(yy-sun_y) + (xx-sun_x)*erp_scale*(xx-sun_x)*erp_scale);
				let alpha = (sun_radius_squared - radius_squared)/scale;
				
				if(alpha > 1.0) alpha = 1.0;
				else if(alpha < 0.0) alpha = 0.0;
				lin[p] += lin[p]*3200.0*rBias*alpha;
				lin[p + 1] += lin[p + 1]*3200.0*gBias*alpha;
				lin[p + 2] += lin[p + 2]*3200.0*bBias*alpha;
				
				if(alpha > 0.0) count++;
				count2++;
			}
          }
        }
		
        //gaussianBlurROI(lin, w, minx, miny, maxx, maxy, SUN_BLUR1>>shift);
        linearImages.push({ w, h, data: lin.slice(0) });
        expandedTimes.push(t);
		setPerFile(25);
		await nextFrame();

        gaussianBlurROI(lin, w, minx, miny, maxx, maxy, SUN_BLUR1>>shift);
        for (let p = 0; p < lin.length; p++) lin[p] /= 16.0;
        t /= 16.0;
        linearImages.push({ w, h, data: lin.slice(0) });
        expandedTimes.push(t);
        logLine(`Synthetic B push: t=${t}`, 'muted');
		setPerFile(50);
		await nextFrame();

        gaussianBlurROI(lin, w, minx, miny, maxx, maxy, SUN_BLUR1>>shift);
        for (let p = 0; p < lin.length; p++) lin[p] /= 16.0;
        t /= 16.0;
        linearImages.push({ w, h, data: lin.slice(0) });
        expandedTimes.push(t);
        logLine(`Synthetic C push: t=${t}`, 'muted');
		setPerFile(75);
		await nextFrame();

        gaussianBlurROI(lin, w, minx, miny, maxx, maxy, SUN_BLUR1>>shift);
        for (let p = 0; p < lin.length; p++) lin[p] /= 16.0;
        t /= 16.0;
        linearImages.push({ w, h, data: lin.slice(0) });
        expandedTimes.push(t);
        logLine(`Synthetic D push: t=${t}`, 'muted');
		setPerFile(100);
		await nextFrame();
      }
	  else
	  {
		linearImages.push({ w, h, data: lin.slice(0) });
		expandedTimes.push(t);
	  }
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


let last_hdr = 0;

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
	
	let fixed = removeShadowSpecklesHDR(hdr, {
	  shadowCut: 0.10, // treat below ~10% as "shadow" in scene-linear
	  rel: 0.25,
	  madK: 6.0,
	  madFloorFrac: 0.03,
	  allowCluster: true,
	  soft: 1.2,
	  pct: 0.95
	});
	logLine(`Speckle attenuated: ${fixed} px`, fixed ? 'ok' : 'muted');
    await nextFrame();

    setStage('Tone-mapping…');
    setOverall(85);
	last_hdr = hdr;
    const ldr = await tonemap_filmic(last_hdr, previewExposure);
    drawToCanvas(ldr, $('#preview'));
    await nextFrame();

    setStage('Preparing downloads…');
    setOverall(92);
    $('#saveHdr').disabled = false;
    $('#saveHdr').onclick = async () => {
      try {

        const blob = await encodeRadianceHDR_RGBE(
          hdr,
          pct => setPerFile(pct)    // progress bar
        );
        
        let name_extension = "";
        if(scale < 0.3)
             name_extension  = "-2K";
        else if(scale < 0.6)
             name_extension  = "-4K";
        else
             name_extension  = "-8K";
        
        const a = document.createElement('a');
        a.href = URL.createObjectURL(blob);
        a.download = baseName + name_extension + '.hdr';   // <— use shortest exposure basename
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



async function runPreview() {
  try {
    if(last_hdr != 0)
	{
		setStage('Tone-mapping…');
		const previewExposure = parseFloat($('#previewExp').value || '2.0');
		const ldr = await tonemap_filmic(last_hdr, previewExposure);
		drawToCanvas(ldr, $('#preview'));
		await nextFrame();
		setStage('Done');
		await nextFrame();
	}
  } catch (err) {
    setStage('Error');
    setOverall(100);
    logLine(`❌ ${err.message || err}`, 'err');
    console.error(err);
  }
}

function hasJpegs(input) {
  try {
	  const files = Array.from(input.files || []);
	  // allow .jpg/.jpeg and MIME image/jpeg
	  return files.some(f =>
		f.type === 'image/jpeg' ||
		/\.jpe?g$/i.test(f.name)
	  );
  } catch (err) {
	return false;
  }
  return false;
}

function updateMergeButtons() {
  const enabled = true;//hasJpegs($('files'));
  if(document.getElementById('run') !== null)
  {
	  $('run').disabled = !enabled;
	  $('runHalf').disabled = !enabled;
	  $('runQuarter').disabled = !enabled;
	  // if you also have a Save button that should stay disabled until merge:
	  const save = document.getElementById('saveHdr');
	  if (save) save.disabled = true;
	}
}

let cmd = " ";
let cmd2 = " ";
let once = true;

function makeQR() 
{
  if(once === true)
  {
    qrcode = new QRCode(document.getElementById("qrcode"), 
    {
      text : cmd,
      width : 540,
      height : 540,
      correctLevel : QRCode.CorrectLevel.M
    });
	
	document.getElementById("qrtext").textContent  = cmd;
	
    qrcode2 = new QRCode(document.getElementById("qrcode2"), 
    {
      text : cmd2,
      width : 540,
      height : 540,
      correctLevel : QRCode.CorrectLevel.M
    });
	
	document.getElementById("qrtext2").textContent  = cmd2;
	
    once = false;
  }
}

async function updateQRs()
{
	var delay = 0;
	if(document.getElementById("delay") !== null)
	{
		delay = parseInt(document.getElementById("delay").value);
		document.getElementById("delaytext").innerHTML = delay;
	}
	
	if(document.getElementById("lname").checked === true)
	{
		if(document.getElementById("moon").checked === true)
		{
			if(delay > 0)
				cmd = String.raw`*HDRI="!Z1=CecFi1x0=Bz!N==zB!R-6` + "!" + delay + "B" + String.raw`$BASE='H$C_'$GAMA=2.2=A81920!N<A0.1=A0.1$EXPQ=A!N!S=A/4>A0.05!R-33$EXPQ=0=C+1=C%99!R-100"`;
			else
				cmd = String.raw`*HDRI="!Z1=CecFi1x0=Bz!N==zB!R-6$BASE='H$C_'$GAMA=2.2=A81920!N<A0.1=A0.1$EXPQ=A!N!S=A/4>A0.05!R-33$EXPQ=0=C+1=C%99!R-97"`;
			//!Z1=Ct:ScFi1x0=Bz!N==zB!R-6$BASE='H$C_'$GAMA=2.2=A81920!N<A0.1=A0.11$EXPQ=A!N!S=A/4>A0.05!R55$EXPQ=0=C+1=C%99!R-97
		} else {
			if(delay > 0)
				cmd = String.raw`*HDRI="!Z1=CecFi1x0=Bz!N==zB!R-6` + "!" + delay + "B" + String.raw`$BASE='H$C_'$GAMA=2.2=A81920!N$EXPQ=A!N!S=A/4>A2!R-20$EXPQ=0=C+1=C%99!R-87"`;
			else
				cmd = String.raw`*HDRI="!Z1=CecFi1x0=Bz!N==zB!R-6$BASE='H$C_'$GAMA=2.2=A81920!N$EXPQ=A!N!S=A/4>A2!R-20$EXPQ=0=C+1=C%99!R-84"`;
			//!Z1=Ct:ScFi1x0=S0.25=Bz!N==zB!R-6$BASE='H$C_'$GAMA=2.2=A81920!N$EXPQ=A!N!S=A/4>A2!R-20$EXPQ=0=C+1=C%99!R-84
		}
		
		cmd2 = String.raw`*HDRi="!Z0$EXPQ=0$GAMA=0$BASE=''"mPN$PRES="16,HDRI"`;
	}
	else
	{
		if(document.getElementById("moon").checked === true)
		{
			if(delay > 0)
				cmd = String.raw`*HDRI="!Z1cFi1x0=Bz!N==zB!R-6` + "!" + delay + "B" + String.raw`$GAMA=2.2=A81920!N<A0.1=A0.1$EXPQ=A!N!S=A/4>A0.05!R-33$EXPQ=0!R-76"`;
			else
				cmd = String.raw`*HDRI="!Z1cFi1x0=Bz!N==zB!R-6$GAMA=2.2=A81920!N<A0.1=A0.1$EXPQ=A!N!S=A/4>A0.05!R-33$EXPQ=0!R-76"`;

			//!Z1cFi1x0=Bz!N==zB!R-6$GAMA=2.2=A81920!N<A0.1=A0.11$EXPQ=A!N!S=A/4>A0.05!R-33$EXPQ=0!R-76
		} else {
			if(delay > 0)
				cmd = String.raw`*HDRI="!Z1cFi1x0=Bz!N==zB!R-6` + "!" + delay + "B" + String.raw`$GAMA=2.2=A81920!N$EXPQ=A!N!S=A/4>A2!R-20$EXPQ=0!R-51"`;
			else
				cmd = String.raw`*HDRI="!Z1cFi1x0=Bz!N==zB!R-6$GAMA=2.2=A81920!N$EXPQ=A!N!S=A/4>A2!R-20$EXPQ=0!R-48"`;
			//!Z1cFi1x0=Bz!N==zB!R-6$GAMA=2.2=A81920!N$EXPQ=A!N!S=A/4>A2!R-20$EXPQ=0!R-45
		}
		
		cmd2 = String.raw`*HDRi="!Z0$EXPQ=0$GAMA=0"mPN$PRES="16,HDRI"`;
	}
	//console.log(cmd);
	document.getElementById("qrtext").textContent = cmd;
	document.getElementById("qrtext2").textContent = cmd2;
	
	qrcode.clear(); 
	qrcode.makeCode(cmd);
	qrcode2.clear(); 
	qrcode2.makeCode(cmd2);
}

window.addEventListener('DOMContentLoaded', () => {
  const filesInput = document.getElementById('files');
  const runBtn = document.getElementById('run');
  const runHalfBtn = document.getElementById('runHalf');
  const runQuaterBtn = document.getElementById('runQuarter');

  function hasJpegs(input) {
    const files = Array.from(input.files || []);
    return files.some(f =>
      f.type === 'image/jpeg' || /\.jpe?g$/i.test(f.name)
    );
  }

  function updateMergeButtons() {
    const enabled = hasJpegs(filesInput);
    runBtn.disabled = !enabled;
    runHalfBtn.disabled = !enabled;
    runQuaterBtn.disabled = !enabled;
  }

  filesInput.addEventListener('change', updateMergeButtons);
  updateMergeButtons(); // initialize
});


$('#run').addEventListener('click', async () => {
  await runPipeline(1.0);  // full res
});

$('#runHalf').addEventListener('click', async () => {
  await runPipeline(0.5);  // half res
});

$('#runQuarter').addEventListener('click', async () => {
  await runPipeline(0.25);  // half res
});

$('#previewExp').addEventListener('change', async () => {
  await runPreview(); 
});

$('#lname').addEventListener('change', async () => {
  await updateQRs(); 
});
$('#moon').addEventListener('change', async () => {
  await updateQRs(); 
});

$('#delay').addEventListener('input', async () => {
  await updateQRs(); 
});


makeQR();
updateQRs();

</script>
