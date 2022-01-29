# Daily Time-lapse Video and Upload

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

If your camera is already configured (via the Quik App) to enable auto upload to the GoPro cloud, you can use this daily timelapse to automatically sync each day. Requires a GoPro Subscription. Ideal for daily documentation for a construction or sunsize/sunsets.

Note: it is best to set your camera’s date and time before using this QR Code for improved precision.

## Time-lapse Settings

<b>Type:</b>&nbsp;&nbsp;
  <input type="radio" id="nltlv1" name="nltlv" value="mT" checked> <label for="nltlv1">TimeLapse Video</label>&nbsp;&nbsp;
  <input type="radio" id="nltlv2" name="nltlv" value="mNL"> <label for="nltlv2">NightLapse Video</label>&nbsp;&nbsp;
  <input type="radio" id="nltlv3" name="nltlv" value=""> <label for="nltlv3">not set</label>
 
<b>Lens:</b>&nbsp;&nbsp;
  <input type="radio" id="tlvf1" name="tlvf" value="fW"> <label for="tlvf1">Wide </label>&nbsp;&nbsp;
  <input type="radio" id="tlvf2" name="tlvf" value="fL"> <label for="tlvf2">Linear </label>&nbsp;&nbsp;
  <input type="radio" id="tlvf3" name="tlvf" value="" checked> <label for="tlvf3">not set</label>
 
<b>Interval:</b>&nbsp;&nbsp;
  <input type="radio" id="fpslapse1" name="fpslapse" value="p.2">  <label for="fpslapse1">2s  </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse2" name="fpslapse" value="p.5">  <label for="fpslapse2">5s  </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse3" name="fpslapse" value="p.10"> <label for="fpslapse3">10s </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse4" name="fpslapse" value="p.30"> <label for="fpslapse4">30s </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse5" name="fpslapse" value="p.60" checked> <label for="fpslapse5">60s </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse6" name="fpslapse" value="p.120" > <label for="fpslapse6">2min </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse7" name="fpslapse" value="p.300" > <label for="fpslapse7">5min </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse8" name="fpslapse" value="p.1800"> <label for="fpslapse8">30min </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse9" name="fpslapse" value="p.3600"> <label for="fpslapse9">60min </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse9" name="fpslapse" value=""> <label for="fpslapse10">not set </label>
 
## Time-lapse Capture Time

Start Time: <input type="range" style="width: 300px;" id="tlstrt" name="tlstrt" min="1" max="143" value="48"><label for="tlstrt"></label> <b id="starttext"></b>

Capture Length: <input type="range" style="width: 240px;" id="tlend" name="tlend" min="1" max="960" value="240"><label for="tlend"></label> <b id="lentext"></b> minutes &nbsp;&nbsp; End Time: <b id="endtext"></b>

<input type="checkbox" id="upld" name="upld" checked> 
<label for="upld">Upload at the end of each capture</label><br>

Daily playback length (at 30fps): <b id="length"></b> seconds
 
<div id="qrcode_txt" style="width: 360px">
  <center>
  <div id="qrcode"></div><br>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext"></em><br>
  <b><font color="#005CAC">Daily Timelapse and Upload</font></b>
  </center>
</div>
<button id="copyImg">Copy Image to Clipboard</button>
<br>
<br>
Share this QR Code as a URL: <small id="urltext"></small><br>
<button id="copyBtn">Copy URL to Clipboard</button>
      
## Solutions for extra long captures

A/C powering the camera via USB is the best. With continuous power supplied, remove the internal battery (charging can reset the wake timer), and the camera should run for a very long time (only SD card storage limitations.) You might be tempted to use a Lithium Ion USB powerbank, however they typically do not work well. They are designed to quickly recharge a smartphone, and when they think power is no longer needed, they shut-off. A select few USB battery sources include an "always on feature" designed for time-lapse projects. Example:[voltaicsystems.com/v50](https://voltaicsystems.com/v50/) This one can even solar recharge the battery at the same time. The second option is add a USB keep alive device that prevents your USB power bank from shutting down. Examples: from [sotabeams.co.uk](https://www.sotabeams.co.uk/usb-battery-pack-keep-alive-load/) and from [tindie.com](https://www.tindie.com/products/overz/smart-power-bank-keep-alive/)
	
**Compatibility:** Labs enabled HERO9/10 only
        
## ver 1.02
[More features](..) for Labs enabled cameras

<script>
var once = true;
var qrcode;
var cmd = "mPdP!60SQ!1R";
var clipcopy = "";
var lasttimecmd = "";
var changed = false;

function makeQR() 
{	
  if(once === true)
  {
    qrcode = new QRCode(document.getElementById("qrcode"), 
    {
      text : "!oMBURN=\"\"",
      width : 360,
      height : 360,
      correctLevel : QRCode.CorrectLevel.M
    });
    once = false;
  }
}

function checkTime(i) {
    if (i < 10) {i = "0" + i;}  // add zero in front of numbers < 10
    return i;
}

function pad(num, size) {
    var s = num+"";
    while (s.length < size) s = "0" + s;
    return s;
}


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


function dval(id) {
    var x;
	var val = "";
	{
		for (i = 1; i < 15; i++) { 
			var newid = id+i;
			if(document.getElementById(newid) !== null)
			{
				x = document.getElementById(newid).checked;
				if( x === true)
					val = document.getElementById(newid).value;
			}
		}
	}
	return val;
}




function timeLoop()
{
  if(document.getElementById("tlstrt") !== null)
  {
	var start = parseInt(document.getElementById("tlstrt").value);
	var startmins = start*10;
	var caplen = parseInt(document.getElementById("tlend").value);
	caplen = Math.trunc(caplen*caplen/960);
	if(caplen < 1) caplen = 1;
	var endmins = startmins + caplen;
	if(endmins >= 1440)
		endmins -= 1440;
		
	var starthourstime = Math.trunc(startmins / 60);
	var startminstime = startmins - starthourstime * 60;	
	
	var endhourstime = Math.trunc(endmins / 60);
	var endminstime = endmins - endhourstime * 60;
		
	var stxt = pad(starthourstime, 2) + ":" + pad(startminstime, 2);
	var etxt = pad(endhourstime, 2) + ":" + pad(endminstime, 2);
	
	document.getElementById("starttext").innerHTML = stxt;
	document.getElementById("endtext").innerHTML = etxt;
	document.getElementById("lentext").innerHTML = caplen;
	
	var spftxt = dval("fpslapse");
	var spf = spftxt.slice(2);
	var fsecs = ((caplen*60) / parseInt(spf)) / 30;	
	var secs10 =  fsecs * 10;
	var secs = Math.trunc(secs10) / 10;

	if(spf == "")
		document.getElementById("length").innerHTML = "unknown";
	else
		document.getElementById("length").innerHTML = secs;
		
	

	cmd = "";
	cmd = dcmd(cmd,"nltlv");
	cmd = dcmd(cmd,"tlvf");
	cmd = dcmd(cmd,"fpslapse");
	
	cmd = "!" + stxt + "N" + cmd + "!S!" + caplen*60 + "E";
	
	if(document.getElementById("upld") !== null)
	{
		if(document.getElementById("upld").checked === true)
		{
			cmd = cmd + "!U";
		}
	}
	cmd = cmd + "!1R";
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
	clipcopy = "https://gopro.github.io/labs/control/set/?cmd=" + cmd + "&title=Daily%20Timelapse%20and%20Upload";
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
