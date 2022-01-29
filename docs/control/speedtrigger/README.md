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

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Start Speed** <input type="range" style="width: 300px;" id="snstvty" name="snstvty" min="1" max="162" value="6"><label for="snstvty"></label>&nbsp;&nbsp;<b id="snstvtytext"></b> km/h (<b id="snstvtymph"></b> mph)<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**End Speed** <input type="range" style="width: 300px;" id="esnstvty" name="esnstvty" min="0" max="162" value="0"><label for="esnstvty"></label>&nbsp;&nbsp;<b id="esnstvtytext"></b> km/h (<b id="esnstvtymph"></b> mph) (0 = off or speed threshold)<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Hold Time** <input type="range" style="width: 300px;" id="hold" name="hold" min="0" max="120" value="5"><label for="hold"></label>&nbsp;&nbsp;<b id="holdtext"></b> seconds, to continue recording after speed is below the threshold.<br> 

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" id="repeat" name="repeat" checked> 
<label for="repeat">Repeat speed triggered capture.</label><br>

Note: you will have to manually set the mode in which you capture.  The detector can be combined with the Hindsight feature on HERO9 or 10. 
 

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
Share this QR Code as a URL: <b id="urltext"></b><br>
<button id="copyBtn">Copy URL to Clipboard</button>

**Compatibility:** Labs enabled HERO7, HERO8, HERO9, HERO10 and MAX 
        
## ver 1.02
[Learn more](..) on QR Control

<script>
var once = true;
var qrcode;
var cmd = "oC";
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
	clipcopy = "https://gopro.github.io/labs/control/set/?cmd=" + cmd;
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
