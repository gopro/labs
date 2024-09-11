# Daily Long Time-lapses

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

An extension of [Extra Long Time-lapses](../longtimelapse) feature, just performed during particular hours, to extend your battery life and reduce the number of images you will assemble into a time-lapse.  Remember to set your camera's [clock](../precisiontime) before using this QR Code.

## Daytime Time-lapse Calculator

Start Time <input type="range" style="width: 300px;" id="tlstrt" name="tlstrt" min="1" max="143" value="48"><label for="tlstrt"></label> <b id="starttext"></b>

End Time <input type="range" style="width: 300px;" id="tlend" name="tlend" min="1" max="143" value="54"><label for="tlend"></label> <b id="endtext"></b>

Number of photos per day <input type="range" style="width: 300px;" id="tlday" name="tlday" min="10" max="300" value="60"><label for="tlday"></label> <b id="perdaytext"></b>

<!-- <input type="checkbox" id="setdatetime" name="setdatetime" checked> 
<label for="setdatetime">Automatically update the camera date and time</label><br>
-->

Estimated runtime per charged battery: <b id="daystext">0</b> days

<div id="qrcode_txt" style="width: 360px">
  <center>
  <div id="qrcode"></div><br>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext"></em><br>
  <b><font color="#005CAC">Daily Timelapse</font></b>
  </center>
</div>
<button id="copyImg">Copy Image to Clipboard</button>
<br>
<br>
Share this QR Code as a URL: <small id="urltext"></small><br>
<button id="copyBtn">Copy URL to Clipboard</button>
        
## Warning

This type of timelapse, booting the camera for every image, is less reliable than using [Daily-Timelapse](../dailytl). 	
		
## Extending Time-lapse Duration

Simply replacing the battery is the easiest solution for long captures. After the battery is replaced, power on the camera so that the time-lapse can continue. You might want to set and forget for a multi-week or multi-month time-lapse, for this A/C powering the camera via USB is the best. With continuous power supplied, the battery should be removed, and the camera should run for a very long time (only SD card storage limitations.) You might be tempted to use a Lithium Ion USB powerbank, however they typically do not work well (see below for solutions.) They are designed to quickly recharge a smartphone, and when they think power is no longer needed, they shut-off. For this reason they get you far shorter captures than you would expect. If you want to try a USB powerbank, you must remove the GoPro battery for good results. For long captures away from the power grid, the best solution is a small 12V 18+Ah sealed lead acid battery and attached a non-smart (doesn't shut off) USB regulator. With the right photo interval, this configuration could last a year on a single charge.   
		
## Solutions for Using External Lithium Ion USB Batteries

As stated above, most Lithium Ion USB power-banks will shut-off early, even when the camera still needs the power. A select few USB battery sources include an "always on feature" designed for time-lapse projects.  Example:[voltaicsystems.com/v50](https://voltaicsystems.com/v50/) This one can even solar recharge the battery at the same time.

The second option is a USB keep alive device that prevents your USB power bank from shutting down.  Examples: from [sotabeams.co.uk](https://www.sotabeams.co.uk/usb-battery-pack-keep-alive-load/) and from [tindie.com](https://www.tindie.com/products/overz/smart-power-bank-keep-alive/)

**Compatibility:** Labs enabled HERO5 Session, HERO7-13, MAX and BONES 
        
updated: September 10, 2024

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


function timeLoop()
{
  if(document.getElementById("tlstrt") !== null)
  {
	var start = parseInt(document.getElementById("tlstrt").value);
	var startmins = start*10;
	var end = parseInt(document.getElementById("tlend").value);
	var endmins = startmins + end*10;
	if(endmins>1430) endmins = 1430;
	var perday = parseInt(document.getElementById("tlday").value);
	
	var restarthourstime = Math.trunc(startmins / 60);
	var restartminstime = startmins - restarthourstime * 60;
	
	var starthourstime = Math.trunc((startmins-1) / 60);
	var startminstime = (startmins-1) - starthourstime * 60;	
	
	var endhourstime = Math.trunc(endmins / 60);
	var endminstime = endmins - endhourstime * 60;
	
	document.getElementById("perdaytext").innerHTML = perday;	
	
	var rtxt = pad(restarthourstime, 2) + ":" + pad(restartminstime, 2);
	var stxt = pad(starthourstime, 2) + ":" + pad(startminstime, 2);
	var etxt = pad(endhourstime, 2) + ":" + pad(endminstime, 2);
	
	document.getElementById("starttext").innerHTML = rtxt;
	document.getElementById("endtext").innerHTML = etxt;
	
	var d = 406 / perday;
	var dd = (406 - d * 6) / perday;
		
	dd *= 10;
	dd = Math.trunc(dd) / 10;
	
	document.getElementById("daystext").innerHTML = dd;
		
	var interval = Math.trunc(((endmins - startmins)*60 / perday) - 15);
	if(interval < 30) interval = 30;
	
	cmd = "mPdP>" + stxt + "<" + etxt + "!" + interval + "SQ~" + "!" + rtxt + "S!1R";
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
	clipcopy = "https://gopro.github.io/labs/control/set/?cmd=" + cmd + "&title=Daily%20Timelapse";
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
