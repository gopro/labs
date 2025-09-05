# Dual Fisheye → 360° Maximum Effective Resolution

<style>
  h1 { font-size: 20px; margin: 0 0 12px; }
  label { display: block; margin: 10px 0 4px; }
  input, select { padding: 8px; width: 220px; }
  .num { font-variant-numeric: tabular-nums; }
  small { color: #666; }
  code { background: #f2f2f2; padding: 1px 4px; border-radius: 4px; }
  .presets { margin: 14px 0 4px; display: flex; gap: 10px; flex-wrap: wrap; display: none; }
  .preset-btn { padding: 8px 12px; border: 1px solid #ccc; border-radius: 8px; background: #f8f8f8; cursor: pointer; }
  .preset-btn.active { border-color: #4a7; background: #e9fff1; }
</style>

<p>
  The maximum effective resolution of the 360° image is calculated by measuring the 180° line (diameter) of active pixels. The region of active pixels can be measured by looking at objects at large distances, but visible in both fisheye lenses.
  These distant objects indicate how much resolution is in the sphere and how much is used as overlap (for stitching) between the lenses. Overlap pixels are a must for stitching, but do not contribute to final output resolution.<br>
  Measure any dual fisheye camera system using this <a href="https://gopro.com/en/us/news/beyond-counting-pixels--defining-resolution-in-spherical">technique.</a><br>
  <small>size180 = min(width, height) × (180 / FOV). Then ERP = (2×size180) × (size180) and EAC face = size180 / 2.</small>
</p>

<div id="presetbuttons" class="presets">
  Camera Presets: 
  <button id="preset-xam" class="preset-btn" type="button" title="cam1">Camera 1</button>
  <button id="preset-lam" class="preset-btn" type="button" title="cam2">Camera 2</button>
  <button id="preset-bam" class="preset-btn" type="button" title="cam3">Camera 3</button>
</div>

<div id="secrets">
	<input type="password" id="password" placeholder="Password">
	<button onclick="unlock()">Unlock</button>
	<div id="error"></div>
</div>
  
<div>
  <div>
    Fisheye width and height (px): <input type="range" style="width: 200px;vertical-align: middle;" id="vsize" name="vsize" min="1920" max="4400" value="3840" step="8">
    <input id="w" type="number" style="width: 100px;" min="1920" max="4400" value="3840" step="8">
  </div>
  <div>
    Percentage active pixels (% of total diameter):  <input type="range" style="width: 200px;vertical-align: middle;" id="pcrop" name="pcrop" min="70" max="100" value="90" step="0.2">
    <input id="crop" type="number" style="width: 100px;" value="90" min="70" max="100" step="0.2">
  </div>

  <br>
  <div>
    <canvas id="myCanvas" width="1024" height="512"></canvas>
  </div>
</div>

<div class="out" id="out"></div>

<script src="https://cdnjs.cloudflare.com/ajax/libs/crypto-js/4.2.0/crypto-js.min.js"></script>
<script>
function roundTo(x, mult) { return Math.round(x / mult) * mult; }
function fmt(x, d=2) { return Number.isFinite(x) ? x.toFixed(d) : '—'; }

var last_w = 0;
var last_crop = 0;

var cam1 = 95.0;
var cam2 = 93.0;
var cam3 = 94.0;

var max_res = 4400;
var cam1_res = 3840;

var show_eac = 0;

function setInputs(w, crop) {
  const wEl = document.getElementById('w');
  const vEl = document.getElementById('vsize');
  const cEl = document.getElementById('crop');
  const pEl = document.getElementById('pcrop');

  vEl.value = w;
  wEl.value = w;
  pEl.value = crop;
  cEl.value = crop;

  last_w = w;
  last_crop = crop;
}

function markActivePreset() {
  const w = Number(document.getElementById('w').value);
  const crop = Number(document.getElementById('crop').value);

  const presets = [
    { id: 'preset-xam', w: cam1_res, crop: cam1},
    { id: 'preset-lam', w: 3840, crop: cam2 },
    { id: 'preset-bam', w: 3840, crop: cam3 },
  ];

  presets.forEach(p => {
    const btn = document.getElementById(p.id);
    const active = (w === p.w && Math.abs(crop - p.crop) < 0.001);
    btn.classList.toggle('active', active);
  });
}

function setPreset(name) {
  if (name === 'XAM') { show_eac = 1; setInputs(cam1_res, cam1); }
  else if (name === 'LAM') { show_eac = 0; setInputs(3840, cam2); }
  else if (name === 'BAM') { show_eac = 0; setInputs(3840, cam3); }
  last_w = 0;
  last_crop = 0;
  calc();
}

function bindPresets() {
  document.getElementById('preset-xam').addEventListener('click', () => setPreset('XAM'));
  document.getElementById('preset-lam').addEventListener('click', () => setPreset('LAM'));
  document.getElementById('preset-bam').addEventListener('click', () => setPreset('BAM'));
}

function drawTextAlongArc(ctx, text, x, y, radius, startAngle, fsize) {
  ctx.save();
  ctx.translate(x, y);
  ctx.rotate(startAngle * Math.PI / 180);

  ctx.font = fsize + "px Courier New";
  ctx.fillStyle = "white";  
  ctx.textAlign = "center";

  const angleStep = 0.4 * Math.PI / (text.length - 1); // spread across 180°

  for (let i = 0; i < text.length; i++) {
    ctx.save();
    ctx.rotate(i * angleStep - (Math.PI / 2));
    ctx.fillText(text[i], 0, -radius); // inward offset for readability
    ctx.restore();
  }

  ctx.restore();
}

function drawLine(ctx, x, y, x2, y2, wid) {
  ctx.beginPath();
  ctx.moveTo(x, y);   // left edge
  ctx.lineTo(x2, y2);   // right edge
  ctx.strokeStyle = "white";
  ctx.lineWidth = wid;
  ctx.stroke();
}

function drawArrow(ctx, x, y, x2, y2, wid) {
  // Draw main line
  drawLine(ctx, x, y, x2, y2, wid);

  // Draw arrowhead
  const headlen = wid*5; // length of arrowhead
  const angle = Math.atan2(y2 - y, x2 - x);

  ctx.beginPath();
  ctx.moveTo(x2, y2);
  ctx.lineTo(x2 - headlen * Math.cos(angle - Math.PI / 6),
             y2 - headlen * Math.sin(angle - Math.PI / 6));
  ctx.moveTo(x2, y2);
  ctx.lineTo(x2 - headlen * Math.cos(angle + Math.PI / 6),
             y2 - headlen * Math.sin(angle + Math.PI / 6));
  ctx.strokeStyle = "white";
  ctx.lineWidth = wid;
  ctx.stroke();
}

function drawText(ctx, text, x, y, size, angle)
{
  var fontsize = size + "px Arial";
  ctx.rotate(angle * Math.PI / 180); // rotate in radians
  ctx.font = fontsize;
  ctx.fillStyle = "white";
  ctx.fillText(text, x, y);
}
  


function calc() {
  var w = Number(document.getElementById('vsize').value);

  if (w == last_w) {
    w = Number(document.getElementById('w').value);
    if (w >= 2880 && w <= max_res) {
      document.getElementById('vsize').value = w;
      last_w = w;
    }
  } else {
    document.getElementById('w').value = w;
    last_w = w;
  }
  const h = w;

  var crop = Number(document.getElementById('pcrop').value);
  if (crop == last_crop) {
    crop = Number(document.getElementById('crop').value);
    if (crop >= 70 && crop <= 100) {
      document.getElementById('pcrop').value = crop;
      last_crop = crop;
    }
  } else {
    document.getElementById('crop').value = crop;
    last_crop = crop;
  }

  const out = document.getElementById('out');

  if (!(w>0 && h>0 && crop>0)) {
    out.innerHTML = 'Enter positive numbers.';
    return;
  }

  const crp = crop / 100;
  const scale = w/max_res;
  const edge_scale = 1-0.5*(1-scale);
  const base = Math.min(w, h);
  const size180_raw = base * crp;
  const size180_r = Math.round(size180_raw);
  const size180_rm = roundTo(size180_raw, 8);

  const erpW_rm = size180_rm * 2;
  const erpH_rm = size180_rm;
  const erpK_rm = fmt(erpW_rm/960, 2);

  const eacF_rm       = size180_rm / 2;
  const eacF_overlap  = 4*48;

  const canvas = document.getElementById("myCanvas");
  const ctx = canvas.getContext("2d");

  var cw =  canvas.width;
  var ch =  canvas.height;
  
  var cx1 = cw/2 - cw/4*scale;
  var cx2 = cw/2 + cw/4*scale;
  var cy = ch/2;

  ctx.fillStyle = "rgba(20,20,20,255)";
  ctx.fillRect(0, 0, cw, ch);
  ctx.fillStyle = "black";
  ctx.fillRect(cw*0.5*(1-scale), ch*0.5*(1-scale), cw*scale, ch*scale);

  ctx.textAlign = "center";
  ctx.textBaseline = "middle";
  drawText(ctx, "unused black pixels", cw/2, ch*edge_scale-9, 14*scale, 0);

  ctx.beginPath();
  ctx.arc(cx1, cy, 1.1*cx1*scale, 0, Math.PI * 2);
  var gradient = ctx.createRadialGradient(cx1, cy, cy * 0.96*scale, cx1, cy, cy * 1.04*scale);
  gradient.addColorStop(0, "red");          // center solid
  gradient.addColorStop(1, "rgba(255,0,0,0)"); // edge transparent
  ctx.fillStyle = gradient;
  //ctx.fillStyle = "red";
  ctx.fill();

  ctx.beginPath();
  ctx.arc(cx2, cy, 1.1*cx1*scale, 0, Math.PI * 2);
  gradient = ctx.createRadialGradient(cx2, cy, cy * 0.96*scale, cx2, cy, cy * 1.04*scale);
  gradient.addColorStop(0, "red");          // center solid
  gradient.addColorStop(1, "rgba(255,0,0,0)"); // edge transparent
  ctx.fillStyle = gradient;
  ctx.fill();

  drawTextAlongArc(ctx, "overlap pixels (for stitching)", cx1, cy, (cy+10)*crp*scale, 55, 16*scale)
  drawTextAlongArc(ctx, "overlap pixels (for stitching)", cx2, cy, (cy+10)*crp*scale, 55, 16*scale)  


  ctx.beginPath();
  ctx.arc(cx1, cy, cy*crp*scale, 0, Math.PI * 2);
  ctx.fillStyle = "green";
  ctx.fill();

  ctx.beginPath();
  ctx.arc(cx2, cy, cy*crp*scale, 0, Math.PI * 2);
  ctx.fillStyle = "green";
  ctx.fill();

  drawArrow(ctx, cx1, cy, cx1-cy*crp*scale, cy, 3*scale);
  drawArrow(ctx, cx1, cy, cx1+cy*crp*scale, cy, 3*scale);
  drawArrow(ctx, cx2, cy, cx2-cy*crp*scale, cy, 3*scale);
  drawArrow(ctx, cx2, cy, cx2+cy*crp*scale, cy, 3*scale);
  
  drawText(ctx, "180° Active Pixels", cx1, cy-14*scale, 30*scale, 0);
  drawText(ctx, "180° Active Pixels", cx2, cy-14*scale, 30*scale, 0);
  
  drawText(ctx, "Front", cx1, cy-54*scale, 24*scale, 0);
  drawText(ctx, "Back", cx2, cy-54*scale, 24*scale, 0);
  
  var respix = erpH_rm + "px";
  drawText(ctx, respix, cx1, cy+15*scale, 18*scale, 0);
  drawText(ctx, respix, cx2, cy+15*scale, 18*scale, 0);

  var txt = erpK_rm + "K";
  drawText(ctx, txt, cx1, cy+65*scale, 40*scale, 0);
  drawText(ctx, txt, cx2, cy+65*scale, 40*scale, 0);
  
  var src = w + " x " + h;
  drawText(ctx, src, 50*scale+cw*(1-edge_scale), 15*scale+ch*(1-edge_scale), 16*scale, 0);
  drawText(ctx, src, -50*scale+cw*edge_scale, 15*scale+ch*(1-edge_scale), 16*scale, 0);
 
	var group1 = `
		<p><strong>Inputs</strong>: width=${w}, height=${h}, crop=${crop}%</p>

		<p><strong>180° dimensions:</strong><br>
		  180° Fisheye Size: <b class="num">${size180_rm}</b> × <b class="num">${size180_rm}</b>
		</p>

		<p><strong>ERP that matches this sampling</strong> (W × H = 2×size180 × size180)<br>
		  ERP Full Size: <b class="num">${eacF_rm*4}</b> × <b class="num">${eacF_rm*2}</b><br>
		  Maximum marketing resolution for the sphere: <b class="num">${erpK_rm}K</b><br>
		</p>
		`;
	
	var group2 = `
		<div id="eac"><strong>GoPro MAX/MAX2 cameras use EAC 360° format</strong><br>
		  EAC Face Size: <b class="num">${eacF_rm}</b> × <b class="num">${eacF_rm}</b><br>
		  EAC Full Size 3x2: <b class="num">${eacF_rm*3}</b> × <b class="num">${eacF_rm*2}</b><br>
		  EAC Full Size 3x2 + blending overlap : <b class="num">${eacF_rm*3+ eacF_overlap}</b> × <b class="num">${eacF_rm*2}</b>
		</p></div>
	`;

	var group3 = `<p>
		<small>Terms: <br>
		<b>ERP</b> (Equirectangular Projection) - ERP is a flat‑image format for 360° images that maps the sphere onto a rectangle with a 2:1 aspect ratio. Because of the way the math works, the top and bottom poles are stretched, just like on most world maps.<br>	
		`;
	var group4 = `<b>EAC</b> (Equiangular Cubemap) - EAC is 360° format that stores the image as six square faces of a cube, just like a traditional cubemap use in video gaming, but each face is laid out so that every pixel covers exactly the same angular width and height. This “equal‑angle” layout keeps distortion low at the poles and gives a more uniform resolution across the whole sphere, which is why it’s more efficient for 360° video storage.<br>
		`;
	
	var group5 = `<br>
		Assumptions: <br>
		Resolution calculations are for perfectly ideal fisheye lenses. 
		In practice, real lens have distortion curves, which add or subtract resolution for different parts of the image. 
		However, the average resolution for the sphere can not exceed the maximum resolution calculated here.<br>
		<br>
		GoPro, HERO, MAX and their respective logos are trademarks or registered trademarks of GoPro, Inc. in the United States and other countries. Other trademarks are the property of their respective owners.
		</small>
		</p>
	  `;
	  
    if(show_eac)
    {
		out.innerHTML = group1 + group2 + group3 + group4 + group5;
	} 
	else
	{
		out.innerHTML = group1 + group3 + group5;
	}

  markActivePreset();
}

const ciphertext = "U2FsdGVkX18Xv+4p6Lt2Lx8hjaj2YYvrLiShf+eZ47lAmAieRDxCz0RDNU4qPUWGdVxb9VFXuqBLBdRvFddPXffGpl+us6f//y06xF+TPEt8BwOG9krb2Olg2dBVhUfP";

function parseCSV(input) {
  return input.split(",").map(item => item.trim());
}

function parseCSVwithNumbers(input) {
  return input.split(",").map(item => {
    item = item.trim();
    return isNaN(item) ? item : Number(item);
  });
}

function unlock() {
  const pw = document.getElementById('password').value;
  try {
	const bytes = CryptoJS.AES.decrypt(ciphertext, pw);
	const plaintext = bytes.toString(CryptoJS.enc.Utf8);
	if (!plaintext) 
	{
		throw new Error("Wrong password");
	}
	
	let parsed = parseCSVwithNumbers(plaintext);
	max_res = cam1_res = parsed[0];
	cam1 = parsed[1];
	cam2 = parsed[2];
	cam3 = parsed[3];
	
	document.getElementById('preset-xam').innerText = parsed[4];
	document.getElementById('preset-lam').innerText = parsed[5];
	document.getElementById('preset-bam').innerText = parsed[6];
	
	setPreset("XAM");
	
	document.getElementById("secrets").style.display = "none";
	document.getElementById("presetbuttons").style.display = "block";
	document.getElementById("eac").style.display = "block";
  } catch (e) {
	//document.getElementById('error').innerText = CryptoJS.AES.encrypt("This is the secret message!", "password").toString();
	document.getElementById('error').innerText = "Invalid password. Try again.";
  }
}


let frameCount = 0;
function animate() {
  if (frameCount % 10 === 0) {
    calc();
  }
  requestAnimationFrame(animate);
}

['w','vsize','pcrop','crop'].forEach(id => {
  document.getElementById(id).addEventListener('input', calc);
});
bindPresets();
calc();

animate();

</script>