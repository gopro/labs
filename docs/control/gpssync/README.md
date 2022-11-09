# GPS Time Synchronization

<script src="../../jquery.min.js"></script>
<script src="../../qrcodeborder.js"></script>
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

If you are shooting with multiple GoPro **HERO9/10/11** cameras, enable this feature. 

## How it works

This improves the timecode track precision. While this works best outdoors with a clear GPS signal, it is harmless to have active in all shooting locations and modes. If there is a good GPS signal, the camera’s internal clock will be precisely updated, but only minute and second fields (on HERO9 and HERO10.) On older cameras it will not update the hour or day, as it preserves your current timezone offset, so this doesn’t remove the need for initial setup for time and date. On HERO11, the camera has a timezone control, so GPS time can be used fully. This feature updates the MP4s timecode track at the end of capture, so it a good GPS time occurs after the capture begins, the timecode will be accurate. In tools like Adobe Premiere Pro, multiple camera angles can be synchronized using timecode. In limited testing, sync is typically within a frame or two, but your precision my vary.

<input type="checkbox" id="gsync" name="gsync" checked> 
<label for="gsync">Enable GPS Time Sync</label><br>

<div id="qrcode_txt" style="width: 360px">
  <center>
  <div id="qrcode"></div><br>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext"></em><br>
  <b><font color="#005CAC">GPS Camera Sync</font></b>
  </center>
</div>
<button id="copyImg">Copy Image to Clipboard</button>
<br>
<br>
Share this QR Code as a URL: <small id="urltext"></small><br>
<button id="copyBtn">Copy URL to Clipboard</button>

## Time-of-day Timecode for 24, 25 and 30p Modes

<iframe src="https://www.shadertoy.com/embed/ts3BW7?gui=false&paused=false" frameborder="0" style="height: 400px; width: 700px; "></iframe>

Note: it is correct for 23.976 and 29.97 Non-drop timecode to it be 0.1% behind 25.0 timecode.

<br> 

**Compatibility:** Labs enabled HERO9, HERO10 and HERO11
        
## ver 1.07
updated: Nov 8, 2022<br>

[More features](..) for Labs enabled cameras

<script>
var once = true;
var qrcode;
var cmd = "";
var clipcopy = "";
var lasttimecmd = "";
var changed = true;

function makeQR() 
{	
  if(once === true)
  {
    qrcode = new QRCode(document.getElementById("qrcode"), 
    {
      text : "!MSYNC=1",
      width : 360,
      height : 360,
      correctLevel : QRCode.CorrectLevel.M
    });
    once = false;
  }
}

function timeLoop()
{
  cmd = "!MSYNC=0";
  if(document.getElementById("gsync") !== null)
  {
    if(document.getElementById("gsync").checked === true)
    {
      cmd = "!MSYNC=1";
    }
  }

  qrcode.clear(); 
  qrcode.makeCode(cmd);
  
  
  if(cmd != lasttimecmd)
  {
	changed = true;
	lasttimecmd = cmd;
  }
	
  if(changed === true)
  {
	document.getElementById("qrtext").innerHTML = cmd;
	clipcopy = "https://gopro.github.io/labs/control/set/?cmd=" + cmd + "&title=GPS%20Camera%20Sync";
	document.getElementById("urltext").innerHTML = clipcopy;
	changed = false;
  }
  
  var t = setTimeout(timeLoop, 50);
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
