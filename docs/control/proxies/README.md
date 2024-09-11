# Proxy File Support

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

Decoding 4K and 5K HEVC Video can be very demanding on video tools. To speed up the editing workflow, a common solution is to transcode high resolution files into proxies.
With this Labs extension enabled, the camera automatically produces Adobe Premiere Pro™ or DaVinci style proxy files, saving you the time consuming transcoding step. 
Normally a camera will encode a LRV (Low Res Video) for every MP4 using this standard directory structure:<br>
<pre>   DCIM/100GOPRO/GX013784.MP4
   DCIM/100GOPRO/GL013784.LRV
   DCIM/100GOPRO/GX013785.MP4
   DCIM/100GOPRO/GL013785.LRV</pre>
When Proxies are enabled, the LRV files will be created with names that are ready for the NLE use, greatly speeding up professional workflows. The new folder structure is:<br>
<div id="prem">
<pre>   DCIM/100GOPRO/GX013784.MP4
   DCIM/100GOPRO/GX013785.MP4
   DCIM/100GOPRO/Proxies/GX013784_Proxy.MP4
   DCIM/100GOPRO/Proxies/GX013785_Proxy.MP4</pre>
</div>
<div id="davi">
<pre>   DCIM/100GOPRO/GX013784.MP4
   DCIM/100GOPRO/GX013785.MP4
   DCIM/100GOPRO/Proxy/GX013784.MP4
   DCIM/100GOPRO/Proxy/GX013785.MP4</pre>
</div>

Proxies can be used directly from the SD card (when mounted on your PC or Mac), or can be transfered with the MP4s to local storage for the fastest editing experience.

<input type="checkbox" id="proxies" name="proxies" checked> <label for="proxies">Enable Proxies</label><br>

<input type="checkbox" id="davinci" name="davinci"> <label for="davinci">DaVinci style</label> (HERO11-13 only - Default off is Premiere Pro style)<br> 

<div id="qrcode_txt" style="width: 360px">
  <center>
  <div id="qrcode"></div><br>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext"></em><br>
  <b><font color="#005CAC">Proxies <em id="status"></em></font></b>
  </center>
</div>
<button id="copyImg">Copy Image to Clipboard</button>
<br>
<br>
Share this QR Code as a URL: <small id="urltext"></small><br>
<button id="copyBtn">Copy URL to Clipboard</button>

**Warning:** When this feature is enabled, the lack of LRVs will mean the Quik App will not be able to preview video on the camera. However, this will not prevent the full resolution transfer, or on camera playback.

**Compatibility:** Labs enabled HERO10 (Premiere Pro only), HERO11-13 (Both NLEs)

updated: September 10, 2024

[More features](..) for Labs enabled cameras

<script>
var once = true;
var qrcode;
var cmd = "";
var stts = "";
var clipcopy = "";
var lasttimecmd = "";
var changed = true;



function dset(label, on) {
		var settings = document.getElementById(label);
		if(on === true)
		{
			if (settings.style.display === 'none') 
				settings.style.display = 'block';
		}
		else
		{
			settings.style.display = 'none';
		}
}


function makeQR() 
{	
  if(once === true)
  {
    qrcode = new QRCode(document.getElementById("qrcode"), 
    {
      text : "!M64BT=1",
      width : 360,
      height : 360,
      correctLevel : QRCode.CorrectLevel.M
    });
	dset("davi", false);
	dset("prem", true);
    once = false;
  }
}

function timeLoop()
{
  stts = "Disabled";
  cmd = "!MPRXY=0";
  if(document.getElementById("proxies") !== null)
  {
    if(document.getElementById("proxies").checked === true)
    {
	  stts = "Enabled";
	  if(document.getElementById("davinci").checked === true)
	  {
        cmd = "!MPRXY=4";
		dset("davi", true);
		dset("prem", false);
	  }
	  else
	  {
        cmd = "!MPRXY=1";
		dset("davi", false);
		dset("prem", true);
	  }
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
	document.getElementById("status").innerHTML = stts;
	document.getElementById("qrtext").innerHTML = cmd;
	clipcopy = "https://gopro.github.io/labs/control/set/?cmd=" + cmd + "&title=Large%20Chapter%20Control";
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
