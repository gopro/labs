# Dive Mode

<script src="../../jquery.min.js"></script>
<script src="../../qrcode_canvas.js"></script>
<script src="../../html2canvas.min.js"></script>
<style>
        #qrcode{
            width: 100%;
        }
        div{
            width: 100%;
            display: inline-block;
        }
</style>

Corrects Hypersmooth stabilization so that is it optimized for underwater, improving footage stability and quality. 

## Dive Mode controls
 
<input type="checkbox" id="divemd" name="divemd" checked><label for="divemd">Enable dive mode</label><br>
<input type="checkbox" id="wblock" name="wblock" checked><label for="wblock">White Balance lock upon capture start</label><br>

Or use automatic White Balance:
<br>WBDV=1

<i>White Balance DiVe improvements. Rather than WARM for improving diving white balance, which effects WB the same at all depths, WBDV is more automatic – as the scene get more blue, the more the red channel is gain up.</i>

<input type="checkbox" id="wbdvmode" name="wbdvmode"><label for="wbdvmode">White Balance Dive Improvements</label><br>

<input type="checkbox" id="wgamut" name="wgamut" checked><label for="wgamut">Wide gamut colorspace (same a GPLog) for all video modes</label><br>
<input type="checkbox" id="preset" name="preset" checked><label for="preset">Make this as a new preset</label><br>

<b>Video Settings:</b>&nbsp;&nbsp;
  <input type="radio" id="videoh" name="videores" checked> <label  for="videoh">5K 16:9</label>&nbsp;&nbsp;
  <input type="radio" id="videov" name="videores"> <label for="videov">5K 8:7</label>&nbsp;&nbsp;

There is no need to use GPS underwater<br>HERO13 only!<br>
<b>GPS:</b>&nbsp;&nbsp;
<input type="checkbox" id="gpsoff" name="gpsoff" checked> <label for="gpson">OFF<sup>13</sup></label>&nbsp;&nbsp;

Disable audio track<br>
<b>Audio:</b>&nbsp;&nbsp;
<input type="checkbox" id="audoff" name="audoff" checked> <label for="audoff">OFF</label>&nbsp;&nbsp;


<input type="checkbox" id="permanent" name="permanent"><label for="permanent">If not a preset, make this permanent setting</label><br>

<div id="qrcode_txt" style="width: 360px">
 <center>
  <canvas id="qr-canvas" width="360" height="360" style="image-rendering: pixelated;"></canvas>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext"></em><br>
  <b><font color="#005CAC">Dive Mode</font></b>
 </center>
</div>
<button id="copyImg">Copy Image to Clipboard</button>
<br>
<br>
Share this QR Code as a URL: <small id="urltext"></small><br>
<button id="copyBtn">Copy URL to Clipboard</button>

        
## Background
Dive mode optimizes the Hypersmooth stabilization for underwater. It might be no surprise, but HyperSmooth is designed for the camera operation above the water's surface, 
underwater there is typically less camera shake, and HS is still 70% effective at removing shake. This hack adapts HS to use the refractive index (RI) of water 
(defaults to 1.335, good for fresh and command salt water), to remove closer to 100% of unwanted shake.<br>

The option for the wider color gamut offers Native like color space (way more colors supported), while support enabling auto whitebalance, or user controlled whitebalance (Kelvin settings, not recommend for diving as there are above water settings.) 
With WIDE off (0 - the default), the camera saturates color to the Rec709 gamut (basically sRGB), so some extreme real-world color saturations are clipped by the limits of the color gamut. With WIDE=1, the gamut 
is sensor native, wider than Rec709, wider than Rec2020, just what the sensor sees.<br>

The option for white balance lock, it auto white balances until the capture starts. This is useful as white balance can change greating when diving, this make post correction more straight forward.<br>

**Compatibility:** Labs enabled HERO12-13
        
updated: May 29, 2025

[More features](..) for Labs enabled cameras

[BACK](..)

<script>
var once = true;
var qrcode;
var cmd = "oC15dTmNLeA";
var clipcopy = "";
var lasttimecmd = "";
var changed = true;

let qrCanvas, qrCtx;

function makeQR() {
  qrCanvas = document.getElementById("qr-canvas");
  qrCtx = qrCanvas.getContext("2d");
}

function renderQRToCanvas(data) {
  const qr = qrcode(0, 'M');  // Type number auto
  qr.addData(data);
  qr.make();

  const count = qr.getModuleCount();
  const size = qrCanvas.width;
  const tileSize = Math.floor(size / (count+2));
  
  qrCtx.clearRect(0, 0, size, size);
  for (let row = 0; row < count; row++) {
    for (let col = 0; col < count; col++) {
      qrCtx.fillStyle = qr.isDark(row, col) ? "#000" : "#fff";
      qrCtx.fillRect((col+1) * tileSize, (row+1) * tileSize, tileSize, tileSize);
    }
  }
}


function timeLoop() {
  // mutually exclusive: white balance dive improvements and white balance auto lock
  const wblock = document.getElementById("wblock");
  const wbdvmode = document.getElementById("wbdvmode");

  wblock.addEventListener("change", function() {
      if (this.checked) {
          wbdvmode.checked = false;
      }
  });

  wbdvmode.addEventListener("change", function() {
      if (this.checked) {
          wblock.checked = false;
      }
  });

  let cmd = "mV";
  
  if (document.getElementById("preset")?.checked) {
    cmd += "$PRES=\"14,DIVE"; // start of preset
    if (document.getElementById("wblock")?.checked) cmd += " WBLK";
    if (document.getElementById("wgamut")?.checked) cmd += " WIDE";
    if (document.getElementById("wbdvmode")?.checked) cmd += " WBDV";
    if (document.getElementById("audoff")?.checked) cmd += " MUTE";

    // r5X for 8:7
    const verticalVideo = document.getElementById("videov")?.checked ? "X" : ""
    cmd += "\"r5" + verticalVideo + "e1!NfW"; // quotations ends the preset
    
    if (document.getElementById("gpsoff")?.checked) {
      cmd += "g0"
    }
  } else {
  // $ == non permanent
  // * == permanent
    const makePermanent = document.getElementById("permanent")?.checked ? "*" : "$"; 
    
    if (document.getElementById("divemd")?.checked) {
      cmd += makePermanent + "DIVE=1";
      if (document.getElementById("wblock")?.checked) cmd += makePermanent + "WBLK=1";
      if (document.getElementById("wgamut")?.checked) cmd += makePermanent + "WIDE=1";
      if (document.getElementById("wbdvmode")?.checked) cmd += makePermanent + " WBDV=1";
      if (document.getElementById("audoff")?.checked) cmd += makePermanent + " MUTE=1";
      if (document.getElementById("gpsoff")?.checked) cmd += "g0"
    } else {
      cmd = makePermanent + "DIVE=0" + makePermanent + "WBLK=0" + makePermanent + "WIDE=0";
    }
  }
  
  renderQRToCanvas(cmd);
  
  if(cmd != lasttimecmd)
  {
  changed = true;
  lasttimecmd = cmd;
  }
  
  if(changed === true)
  {
  document.getElementById("qrtext").innerHTML = cmd;
  clipcopy = "https://gopro.github.io/labs/control/set/?cmd=" + cmd + "&title=Dive%20Mode";
  document.getElementById("urltext").innerHTML = clipcopy;
  changed = false;
  }
  
  var t = setTimeout(timeLoop, 100);
}

function myReloadFunction() {
  location.reload();
}


async function copyImageToClipboard() {
    html2canvas(document.querySelector("#qrcode_txt")).then(canvas => canvas.toBlob(blob => navigator.clipboard.write([new ClipboardItem({'image/png': blob})])));
}
async function copyTextToClipboard(text) {
  try {
    await navigator.clipboard.writeText(text);
  } catch(err) {
    alert('Error in copying text: ', err);
  }
}

function setupButtons() {	
    document.getElementById("copyBtn").onclick = function() { 
        copyTextToClipboard(clipcopy);
  };
    document.getElementById("copyImg").onclick = function() { 
        copyImageToClipboard();
  };
}

makeQR();
setupButtons();
timeLoop();


</script>
