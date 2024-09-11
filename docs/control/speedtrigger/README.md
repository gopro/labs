# GPS Speed Triggered Start and Stop Captures

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

The GPS feature in your GoPro provides speed information in addition to location, this speed can be used as a threshold to start and stop a capture.  Example: A track day, you only want to capture once you are driving at speed.

## Customize Speed Triggered Capture

**Start Speed** <input type="range" style="width: 300px;" id="snstvty" name="snstvty" min="1" max="162" value="6"><label for="snstvty"></label>&nbsp;&nbsp;<b id="snstvtytext"></b> km/h (<b id="snstvtymph"></b> mph)<br>
**End Speed** <input type="range" style="width: 300px;" id="esnstvty" name="esnstvty" min="0" max="162" value="0"><label for="esnstvty"></label>&nbsp;&nbsp;<b id="esnstvtytext"></b> km/h (<b id="esnstvtymph"></b> mph) (0 = off or speed threshold)<br>
**Hold Time** <input type="range" style="width: 300px;" id="hold" name="hold" min="0" max="120" value="5"><label for="hold"></label>&nbsp;&nbsp;<b id="holdtext"></b> seconds, to continue recording after speed is below the threshold.<br> 

**HERO10 Note:** For GPS triggers to work on HERO10, the LCD must remain on. For extended captures set the LCD brightness to low.  

<input type="checkbox" id="camoff" name="camoff"> 
<label for="camoff">Disable auto power off</label><br>

<input type="checkbox" id="h10lcd" name="h10lcd"> 
<label for="h10lcd">Set LCD brightness to low (10%)</label><br>

<input type="checkbox" id="h10lcdon" name="h10lcdon"> 
<label for="h10lcdon">Leave LCD on</label> (Required on HERO10)<br>

<input type="checkbox" id="repeat" name="repeat" checked> 
<label for="repeat">Repeat speed triggered capture.</label><br>

Note: you will have to manually set the mode in which you capture.  The detector can be combined with the Hindsight feature on HERO9/10/11 & 13. 
 

<div id="qrcode_txt" style="width: 360px">
 <center>
  <div id="qrcode"></div><br>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext"></em><br>
  <b><font color="#005CAC">Speed Trigger</font></b>
 </center>
</div>
<button id="copyImg">Copy Image to Clipboard</button>
<br>
<br>
Share this QR Code as a URL: <small id="urltext"></small><br>
<button id="copyBtn">Copy URL to Clipboard</button>

**Compatibility:** Labs enabled HERO7-11, HERO13 and MAX 

updated: September 10, 2024

[More features](..) for Labs enabled cameras

<script>
var once = true;
var qrcode;
var cmd = "oC";
var clipcopy = "";
var lasttimecmd = "";
var changed = true;
var h10lcdlow = "oB1";
var h10lcdon = "oS";

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
  if(document.getElementById("snstvty") !== null)
  {
	var snstvty = parseInt(document.getElementById("snstvty").value);	
	document.getElementById("snstvtytext").innerHTML = snstvty;
	
	var smph = Math.trunc(snstvty * 0.6213712 * 10)/10.0;	
	document.getElementById("snstvtymph").innerHTML = smph;
	
	var esnstvty = parseInt(document.getElementById("esnstvty").value);	
	document.getElementById("esnstvtytext").innerHTML = esnstvty;	
	
	var emph = Math.trunc(esnstvty * 0.6213712 * 10)/10.0;	
	document.getElementById("esnstvtymph").innerHTML = emph;
			
	//var delay = parseInt(document.getElementById("delay").value);	
	//document.getElementById("delaytext").innerHTML = delay;	
	
	var hold = parseInt(document.getElementById("hold").value);	
	document.getElementById("holdtext").innerHTML = hold;	
		
	cmd = "!SK" + snstvty;
	
	if(esnstvty > 0 && esnstvty != snstvty) cmd = cmd + "-" + esnstvty;
	//if(delay > 0) cmd = cmd + 'D' + delay;
	if(hold > 0) cmd = cmd + 'H' + hold;	
	
    if(document.getElementById("repeat") !== null)
    {
      if(document.getElementById("repeat").checked === true)
      {
        cmd = cmd + "!R";
      }
    }
	
    // Auto off
    if(document.getElementById("camoff") != null && document.getElementById("camoff").checked) {
        cmd = "oC" + cmd;
    }
    // Hero10 LCD set to low
    if(document.getElementById("h10lcd") != null && document.getElementById("h10lcd").checked) {
        cmd = h10lcdlow + cmd;
    }
    // Hero10 LCD timeout to Never
    if(document.getElementById("h10lcdon") != null && document.getElementById("h10lcdon").checked) {
        cmd = h10lcdon + cmd;
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
	clipcopy = "https://gopro.github.io/labs/control/set/?cmd=" + cmd + "&title=Speed%20Trigger";
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
