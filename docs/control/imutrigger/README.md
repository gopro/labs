<script src="../../jquery.min.js"></script>
<script src="../../qrcodeborder.js"></script>
<style>
        #qrcode{
            width: 100%;
        }
        div{
            width: 100%;
            display: inline-block;
        }
</style>

# IMU (Camera Motion) Detection to Start and Stop Captures

While the motion detection feature looks for changes in the image, this is only looking for motion of the camera itself. The Inertial measurement unit (IMU), has a gyroscope and accelerometer for measuring rotation and linear acceleration, this can now be used to start and stop captures.  Example: Drone use, only capture while in flight, automatically stop recording when motion stops.

## Customize IMU Detected Capture


<div id="dtIMU">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Sensor selection:</b>&nbsp;&nbsp;
  <input type="radio" id="imu1" name="imu" value="G" > <label for="GYRO">GYRO </label>&nbsp;&nbsp;
  <input type="radio" id="imu2" name="imu" value="A" > <label for="ACCL">ACCL </label>&nbsp;&nbsp;
  <input type="radio" id="imu3" name="imu" value="I" checked> <label for="BOTH">BOTH (default)</label>
</div>

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Start Sensitivity** <input type="range" id="snstvty" name="snstvty" min="1" max="9" value="6"><label for="snstvty"></label>&nbsp;&nbsp;<b id="snstvtytext"></b> (1-low to 9-high)<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**End Sensitivity** <input type="range" id="esnstvty" name="esnstvty" min="0" max="9" value="0"><label for="snstvty"></label>&nbsp;&nbsp;<b id="esnstvtytext"></b> (0 - off, 1-low to 9-high)<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Start Delay** <input type="range" id="delay" name="delay" min="0" max="60" value="4"><label for="delay"></label>&nbsp;&nbsp;<b id="delaytext"></b> seconds before reading sensors.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Hold Time** <input type="range" id="hold" name="hold" min="0" max="60" value="5"><label for="hold"></label>&nbsp;&nbsp;<b id="holdtext"></b> seconds, to continue recording after motion has stopped.<br> 

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" id="repeat" name="repeat" checked> 
<label for="repeat">Repeat IMU triggered capture.</label><br>

Note: you will have to manually set the mode in which you capture.  The detector can be combined with the Hindsight feature on HERO9. 
 
<center>
<div id="qrcode"></div>
<br>
</center>

QR Command: <b id="qrtext">time</b><br>

## Sensitivity

| Sensitivity | GYRO degrees per second  | ACCL units gravity | Activity               |
|-------------|--------------------------|--------------------|------------------------|
| 1           | 360dps                   | 1.0g               | Throwing the camera    |
| 2           | 180dps                   | 0.5g               | Jumps                  |
| 3           | 90dps                    | 0.25g              | most handheld movement |
| 4           | 45dps                    | 0.125g             | ..                     |
| 5           | 24dps                    | 0.064g             | any hand movement      |
| 6           | 15dps                    | 0.032g             | ..                     |
| 7           | 8dps                     | 0.016g             | ..                     |
| 8           | 4dps                     | 0.008g             | tiny movement          |
| 9           | 2dps                     | 0.004g             | small tremor           |

## On Screen Feedback

![Feedback](feedback.jpg)

## ver 1.00
[BACK](..)

<script>
var once = true;
var qrcode;
var cmd = "oC";
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
	
	var esnstvty = parseInt(document.getElementById("esnstvty").value);	
	document.getElementById("esnstvtytext").innerHTML = esnstvty;	
		
	var delay = parseInt(document.getElementById("delay").value);	
	document.getElementById("delaytext").innerHTML = delay;	
	
	var hold = parseInt(document.getElementById("hold").value);	
	document.getElementById("holdtext").innerHTML = hold;	
		
	cmd = dcmd("!S","imu"); //shutter angle
	cmd = cmd + snstvty;
	
	if(esnstvty > 0) cmd = cmd + "-" + esnstvty;
	if(delay > 0) cmd = cmd + 'D' + delay;
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
	changed = false;
  }
  
  var t = setTimeout(timeLoop, 100);
}

function myReloadFunction() {
  location.reload();
}

makeQR();
timeLoop();


</script>
