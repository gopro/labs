# Stop Motion Mode

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

A Stop Motion extension where only a single frames is stored per shutter press. Once the Stop motion has started, on the LCD the there is ghost of the previous frame, "onion skinning" to help with character position and speed of movement. This modify timelapse video, so the new preset is under timelapse. 

<video width="640" height="360" controls loop autoplay>
  <source src="stopmotionvideo.mp4" type="video/mp4">
</video>

## Stop Motion controls
 
<input type="checkbox" id="stopmt" name="stopmt" checked><label for="stopmt">Enable Stop Motion</label><br>
<input type="checkbox" id="preset" name="preset" checked><label for="preset">Make this as a new preset (best)</label><br>
<input type="checkbox" id="permanent" name="permanent"><label for="permanent">If not a present, make this permanent setting (risky)</label><br>
<input type="checkbox" id="tall" name="tall"><label for="tall">Use 8:7 (not 16:9)</label><br>
<input type="checkbox" id="use5K" name="use5K"><label for="use5K">Use 5.3K (not 4K)</label><br>
<input type="checkbox" id="linear" name="linear"><label for="linear">Use Linear (not Wide)</label><br>

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

        
![StopMotionPreset.jpg](StopMotionPreset.jpg)

Your new Preset will look like this.  The "???" is normal, as the frame rate is undefined, controlled by your shutter presses.


**Compatibility:** Labs enabled HERO12-13
        
updated: May 30, 2025

[More features](..) for Labs enabled cameras

[BACK](..)

<script>
var once = true;
var qrcode;
var cmd = "mTr5Xp4";
var mode = "r5X"
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
	if(document.getElementById("use5K").checked === true)
	{
		mode = "r5";
	}
	else
	{
		mode = "r4"
	}
	
	if(document.getElementById("tall").checked === true)
	{
		mode = mode + "X";
	}
	
	if(document.getElementById("linear").checked === true)
	{
		mode = mode + "fL";
	}
	else
	{
		mode = mode + "fW";
	}
  }

  if(document.getElementById("preset") !== null)
  {
	if(document.getElementById("preset").checked === true)
	{
		cmd = "mT$PRES=\"18,STOP\"mT!N" + mode + "p4";
	}
	else
	{ 
  	  if(document.getElementById("permanent").checked === true)
	  {
		cmd = "mT" + mode + "p4*STOP=1";
	  }
	  else
	  {
		cmd = "mT" + mode + "p4$STOP=1";
	  }
	}
    if(document.getElementById("stopmt").checked === false)
	{ 
		if(document.getElementById("permanent").checked === true)
		{
			cmd = "*STOP=0";
		}
		else
		{
			cmd = "$STOP=0";
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
