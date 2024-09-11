# Very Long Time-lapses with Larger Intervals

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

The Labs' firmware allows for much longer time-lapses, on the internal battery alone, by powering off the camera between photos (sorry no video mode time-lapse.) It also supports intervals beyond 60 seconds. A fully charged HERO8 can take around 400 photos, which you can spread over several hours or several days for long form time-lapse.

Example Time-lapses tested:
* 400+ photos over a 24 hour time-lapse. 
* 340+ photos over a 10-day time-lapse. 
* 150+ photos over a 40-day time-lapse.

As the camera is off between frames, it is also possible to periodically change the battery for extremely long time-laspes without interrupting the time-lapse in progress. Simply replace the battery, power on the camera, the time-lapse will automatically continue.

HERO12-13 Users: Due to improved reliability, effeciency and Enduro battery, HERO12-13 can achieve ~40% greater capture times. A test requesting for 24 hours capture, 3.6 minute interval, a HERO12 captured 627 images over nearly 38 hours.

## Time-lapse Calculator

Number of days <input type="range" style="width: 300px;" id="tldays" name="tldays" min="0" max="50" value="0"><label for="tldays"></label> <b id="daystext"></b>

Number of hours <input type="range" style="width: 300px;" id="tlhours" name="tlhours" min="0" max="48" value="24"><label for="tlhours"></label> <b id="hourstext"></b>

Maximum estimated frames: <b id="framestext">0</b> for  <b id="playtext">0</b> seconds of playback at 30fps. Capture time estimate <b id="captext">0</b> hours with an interval of <b id="intervaltext">0</b> minutes.

<div id="qrcode_txt" style="width: 360px">
 <center>
  <div id="qrcode"></div><br>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext"></em><br>
  <b><font color="#005CAC">Extra Long Timelapse</font></b>
 </center>
</div>
<button id="copyImg">Copy Image to Clipboard</button>
<br>
<br>
Share this QR Code as a URL: <small id="urltext"></small><br>
<button id="copyBtn">Copy URL to Clipboard</button>

## Extending Time-lapse Duration

Simply replacing the battery is the easiest solution for long captures. After the battery is replaced, power on the camera so that the time-lapse can continue. You might want to set and forget for a multi-week or multi-month time-lapse, for this A/C powering the camera via USB is the best. With continuous power supplied, the battery should be removed, and the camera should run for a very long time (only SD card storage limitations.) You might be tempted to use a Lithium Ion USB powerbank, however they typically do not work well (see below for solutions.) They are designed to quickly recharge a smartphone, and when they think power is no longer needed, they shut-off. For this reason they get you far shorter captures than you would expect. If you want to try a USB powerbank, you must remove the GoPro battery for good results. For long captures away from the power grid, the best solution is a small 12V 18+Ah sealed lead acid battery and attached a non-smart (doesn't shut off) USB regulator. With the right photo interval, this configuration could last a year on a single charge.      
		
## Solutions for Using External Lithium Ion USB Batteries

As stated above, most Lithium Ion USB power-banks will shut-off early, even when the camera still needs the power. A select few USB battery sources include an "always on feature" designed for time-lapse projects.  Example:[voltaicsystems.com/v50](https://voltaicsystems.com/v50/) This one can even solar recharge the battery at the same time.

The second option is a USB keep alive device that prevents your USB power bank from shutting down.  Examples: from [sotabeams.co.uk](https://www.sotabeams.co.uk/usb-battery-pack-keep-alive-load/) and from [tindie.com](https://www.tindie.com/products/overz/smart-power-bank-keep-alive/)

Compatibility: Labs enabled HERO5 Session, HERO7-13, MAX and BONES 

updated: September 10, 2024

[More features](..) for Labs enabled cameras

<script>
var once = true;
var qrcode;
var cmd = "!60SQ!1R";
var clipcopy = "";
var lasttimecmd = "";
var changed = true;

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

function timeLoop()
{
  if(document.getElementById("tldays") !== null)
  {
	var tld = parseInt(document.getElementById("tldays").value);
	var totalh = tld*24;
	var tlh = parseInt(document.getElementById("tlhours").value);
	totalh += tlh;
	var frms = 406 - (6/24)*totalh;
	var playsecs = 10 * frms / 30;
	var interval = ( ( (tld * 24) + tlh) * 3600 / frms) - 15; 
	
	playsecs = Math.round(playsecs); playsecs = playsecs / 10;
	frms = Math.round(frms);
	
	if(interval < 1) interval = 1;
	interval = Math.round(interval);
	
	document.getElementById("daystext").innerHTML = tld;
	document.getElementById("hourstext").innerHTML = tlh;
	document.getElementById("framestext").innerHTML = frms;
	document.getElementById("playtext").innerHTML = playsecs;	
	document.getElementById("captext").innerHTML = Math.round(((interval+15)*frms/360))/10;	
	document.getElementById("intervaltext").innerHTML = Math.round((interval+15)/6)/10;	
	
	cmd = "!" + interval + "NQmPN!S!1R";
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
	clipcopy = "https://gopro.github.io/labs/control/set/?cmd=" + cmd + "&title=Extra%20Long%20Timelapse";
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
