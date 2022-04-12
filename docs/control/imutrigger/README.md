# IMU Detection to Start and Stop Captures

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

While the motion detection feature looks for changes in the image, this is only looking for motion of the camera itself. The Inertial measurement unit (IMU), has a gyroscope and accelerometer for measuring rotation and linear acceleration, this can now be used to start and stop captures.  Example: Drone use, only capture while in flight, automatically stop recording when motion stops.

## Customize IMU Detected Capture


<div id="dtIMU">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Sensor:</b>&nbsp;&nbsp;
  <input type="radio" id="imu1" name="imu" value="G" > <label for="GYRO">GYRO </label>&nbsp;&nbsp;
  <input type="radio" id="imu2" name="imu" value="A" > <label for="ACCL">ACCL </label>&nbsp;&nbsp;
  <input type="radio" id="imu3" name="imu" value="I" checked> <label for="BOTH">BOTH</label>
</div>

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Start Sensitivity** <input type="range" style="width: 180px;" id="snstvty" name="snstvty" min="1" max="9" value="6"><label for="snstvty"></label>&nbsp;&nbsp;<b id="snstvtytext"></b><br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**End Sensitivity** <input type="range" style="width: 180px;" id="esnstvty" name="esnstvty" min="0" max="9" value="0"><label for="snstvty"></label>&nbsp;&nbsp;<b id="esnstvtytext"></b><br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Start Delay** <input type="range" style="width: 180px;" id="delay" name="delay" min="0" max="9" value="1"><label for="delay"></label>&nbsp;&nbsp;<b id="delaytext"></b> seconds<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Hold Time** <input type="range" style="width: 180px;" id="hold" name="hold" min="0" max="60" value="5"><label for="hold"></label>&nbsp;&nbsp;<b id="holdtext"></b> seconds<br> 

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" id="repeat" name="repeat" checked> 
<label for="repeat">Repeat IMU triggered capture.</label><br>

Notes: 
- Sensitivity range: 1-low to 9-high - see table below
- you will have to manually set the mode in which you capture.  The detector can be combined with the Hindsight feature on HERO9. 
 
 
<div id="qrcode_txt1" style="width: 360px">
  <center>
  <div id="qrcode1"></div><br>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext1"></em><br>
  <b><font color="#005CAC">IMU Trigger</font></b>
  </center>
</div>
<button id="copyImg1">Copy Image to Clipboard</button>
<br>
<br>
Share this QR Code as a URL: <small id="urltext1"></small><br>
<button id="copyBtn1">Copy URL to Clipboard</button>


<div id="qrcode_txt2" style="width: 360px">
  <center>
  <div id="qrcode2"></div><br>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext2"></em><br>
  <b><font color="#005CAC">Drone Boot Command and Trigger</font></b>
  </center>
</div>
<button id="copyImg2">Copy Image to Clipboard</button>
<br>
<br>
Share this QR Code as a URL: <small id="urltext2"></small><br>
<button id="copyBtn2">Copy URL to Clipboard</button>


## Using as a Boot Command - Drone Applications 

Now that starting and stopping your GoPro's capture is solved, you also don't want to have to remember to run the script each flight. For a camera dedicated for drone usage (or similar) you can set QR commands that run automatically on boot. This command uses the IMU trigger settings, makes them a boot command (saved to the current SD card,) and enables QR detection while the IMU Trigger is running. Now power-up the drone and power on your GoPro (in some setups this is automatic,) the camera will be ready in seconds. If the drone is stationary, you can use QR Codes to change shooting modes before the flight, or set date and time for cameras that have been without a battery. Once the drone is moving, start and stop capture is automatic. For drone use try a start sensitivity of 4, and end sensitivity of 8, so that an average launch starts the capture, and only rotors off will stop the capture.

## Sensitivity

| Sensitivity | GYRO degrees per second  | ACCL units gravity | Example Camera Activity |
|-------------|--------------------------|--------------------|-------------------------|
| 1           | 360dps                   | 1.0g               | Throwing the camera     |
| 2           | 180dps                   | 0.5g               | Jumps                   |
| 3           | 90dps                    | 0.25g              | most hand-held movement |
| 4           | 45dps                    | 0.125g             | ..                      |
| 5           | 24dps                    | 0.064g             | any hand movement       |
| 6           | 15dps                    | 0.032g             | ..                      |
| 7           | 8dps                     | 0.016g             | ..                      |
| 8           | 4dps                     | 0.008g             | tiny movement           |
| 9           | 2dps                     | 0.004g             | small tremor            |

## On Screen Feedback

![Feedback](feedback.jpg)

**Compatibility:** Labs enabled HERO7, HERO8, HERO9, HERO10 and MAX 


## ver 1.15
[More features](..) for Labs enabled cameras

<script>
var once = true;
var qrcode1;
var qrcode2;
var clipcopy1 = "";
var clipcopy2 = "";
var cmd1 = "";
var cmd2 = "";
var lasttimecmd1 = "";
var lasttimecmd2 = "";
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

function makeQR() 
{	
  if(once === true)
  {
    qrcode1 = new QRCode(document.getElementById("qrcode1"), 
    {
      text : "\"Hello\"",
      width : 360,
      height : 360,
      correctLevel : QRCode.CorrectLevel.M
    });
	
	
    qrcode2 = new QRCode(document.getElementById("qrcode2"), 
    {
      text : "\"World\"",
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
	
	var esnstvty = parseInt(document.getElementById("esnstvty").value);	
	document.getElementById("esnstvtytext").innerHTML = esnstvty;	
		
	var delay = parseInt(document.getElementById("delay").value);	
	document.getElementById("delaytext").innerHTML = delay;	
	
	var hold = parseInt(document.getElementById("hold").value);	
	document.getElementById("holdtext").innerHTML = hold;	
		
	cmd1 = dcmd("!S","imu"); 
	cmd1 = cmd1 + snstvty;
	
	cmd2 = "!MQRDR=1!MBOOT=\"!Ldrone\"!SAVEdrone=";
	cmd2 = cmd2 + dcmd("!S","imu"); 
	cmd2 = cmd2 + snstvty;
	
	if(esnstvty > 0) cmd1 = cmd1 + "-" + esnstvty;
	if(delay > 0) cmd1 = cmd1 + 'D' + delay;
	if(hold > 0) cmd1 = cmd1 + 'H' + hold;	
	
	if(esnstvty > 0) cmd2 = cmd2 + "-" + esnstvty;
	if(delay > 0) cmd2 = cmd2 + 'D' + delay;
	if(hold > 0) cmd2 = cmd2 + 'H' + hold;	
	
    if(document.getElementById("repeat") !== null)
    {
      if(document.getElementById("repeat").checked === true)
      {
        cmd1 = cmd1 + "!R";
        cmd2 = cmd2 + "!R";
      }
    }
  }
  
  qrcode1.clear(); 
  qrcode1.makeCode(cmd1);
  
  qrcode2.clear(); 
  qrcode2.makeCode(cmd2);
  
  if(cmd1 != lasttimecmd1)
  {
	changed = true;
	lasttimecmd1 = cmd1;
  }
  if(cmd2 != lasttimecmd2)
  {
	changed = true;
	lasttimecmd2 = cmd2;
  }
	
  if(changed === true)
  {
	document.getElementById("qrtext1").innerHTML = cmd1;
	clipcopy1 = "https://gopro.github.io/labs/control/set/?cmd=" + cmd1 + "&title=IMU%20Trigger";	
	document.getElementById("urltext1").innerHTML = clipcopy1;
	
	document.getElementById("qrtext2").innerHTML = cmd2;
	clipcopy2 = "https://gopro.github.io/labs/control/set/?cmd=" + cmd2 + "&title=Drone%20Boot%20Command%20and%20Trigger";	
	document.getElementById("urltext2").innerHTML = clipcopy2;
	
	changed = false;
  }
  
  var t = setTimeout(timeLoop, 100);
}

function myReloadFunction() {
  location.reload();
}


async function copyImageToClipboard(id) {
    html2canvas(document.querySelector(id)).then(canvas => canvas.toBlob(blob => navigator.clipboard.write([new ClipboardItem({'image/png': blob})])));
}
async function copyTextToClipboard(text) {
	try {
		await navigator.clipboard.writeText(text);
	} catch(err) {
		alert('Error in copying text: ', err);
	}
}

function setupButtons() {	
    document.getElementById("copyBtn1").onclick = function() { 
        copyTextToClipboard(clipcopy1);
	};
    document.getElementById("copyImg1").onclick = function() { 
        copyImageToClipboard("#qrcode_txt1");
	};
    document.getElementById("copyBtn2").onclick = function() { 
        copyTextToClipboard(clipcopy2);
	};
    document.getElementById("copyImg2").onclick = function() { 
        copyImageToClipboard("#qrcode_txt2");
	};
}

makeQR();
setupButtons();
timeLoop();


</script>
