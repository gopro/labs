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
<input type="checkbox" id="wgamut" name="wgamut" checked><label for="wgamut">Wide gamut colorspace (same a GPLog) for all video modes</label><br>
<input type="checkbox" id="preset" name="preset" checked><label for="preset">Make this as a new preset</label><br>
<input type="checkbox" id="permanent" name="permanent"><label for="permanent">If not a present, make this permanent setting</label><br>

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
Dive mode optimizes the Hypersmooth stabilization for underwater. It might be no surprise, but HyperSmooth is designed for the camera operation above the water’s surface, 
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

function dcmd(cmd, id) {
    var x;
	if(document.getElementById(id) !== null)
	{
		x = document.getElementById(id).checked;
		if( x === true)
			cmd = cmd + document.getElementById(id).value;
	}
	else
	{
	    var i;
		for (i = 1; i < 15; i++) { 
			var newid = id+i;
			if(document.getElementById(newid) !== null)
			{
				x = document.getElementById(newid).checked;
				if( x === true)
					cmd = cmd + document.getElementById(newid).value;
			}
		}
	}
	return cmd;
}

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

function checkTime(i) {
    if (i < 10) {i = "0" + i;}  // add zero in front of numbers < 10
    return i;
}

function timeLoop()
{
  if(document.getElementById("preset") !== null)
  {
	if(document.getElementById("preset").checked === true)
	{
		if(document.getElementById("wblock").checked === true)
		{
			if(document.getElementById("wgamut").checked === true)
			{
				cmd = "mV$PRES=\"14,DIVE WBLK WIDE\"r5e1!NfW";
			}
			else
			{
				cmd = "mV$PRES=\"14,DIVE WBLK\"r5e1!NfW";
			}
		}
		else
		{
			if(document.getElementById("wgamut").checked === true)
			{
				cmd = "mV$PRES=\"14,DIVE WIDE\"r5e1!NfW";
			}
			else
			{
				cmd = "mV$PRES=\"14,DIVE\"r5e1!NfW";
			}
		}
	}
	else
	{ 
  	  if(document.getElementById("permanent").checked === true)
	  {
		if(document.getElementById("wblock").checked === true)
		{
			if(document.getElementById("wgamut").checked === true)
			{
				cmd = "mV*DIVE=1*WBLK=1*WIDE=1";
			}
			else
			{
				cmd = "mV*DIVE=1*WBLK=1";
			}
		}
		else
		{
			if(document.getElementById("wgamut").checked === true)
			{
				cmd = "mV*DIVE=1*WIDE=1";
			}
			else
			{
				cmd = "mV*DIVE=1";
			}
		}
	  }
	  else
	  {
		if(document.getElementById("wblock").checked === true)
		{
			if(document.getElementById("wgamut").checked === true)
			{
				cmd = "mV$DIVE=1$WBLK=1$WIDE=1";
			}
			else
			{
				cmd = "mV$DIVE=1$WBLK=1";
			}
		}
		else
		{
			if(document.getElementById("wgamut").checked === true)
			{
				cmd = "mV$DIVE=1$WIDE=1";
			}
			else
			{
				cmd = "mV$DIVE=1";
			}
		}
	  }
	}
    if(document.getElementById("divemd").checked === false)
	{ 
		if(document.getElementById("permanent").checked === true)
		{
			cmd = "*DIVE=0*WBLK=0*WIDE=0";
		}
		else
		{
			cmd = "$DIVE=0$WBLK=0$WIDE=0";
		}
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
