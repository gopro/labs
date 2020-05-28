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

# Video Motion Detection to Start and Stop Captures

While your GoPro camera is not equipped with ultra sonic or another motion sensor, it does have a very high resolution image sensor that is active even when the camera is not recording. So simply using the main imaging engine, the experimental motion detection feature uses the differences between video frames to detect when to start and stop recording. This means your camera should be mounted so that it is not moving, so that only subject moves will trigger the capture. Motion detection can be use to capture video of a shy animal in the wild or simply reduce any video captures to only the moments with activity.

## Custom Motion Capture

Sensitivity <input type="range" id="snstvty" name="snstvty" min="1" max="9" value="3"><label for="snstvty"></label>&nbsp;&nbsp;<b id="snstvtytext"></b> (1-low to 9-very high)<br>
Start Delay <input type="range" id="delay" name="delay" min="0" max="60" value="4"><label for="delay"></label>&nbsp;&nbsp;<b id="delaytext"></b> seconds to get yourself out of the way.<br>
Motion mask for <input type="range" id="mask" name="mask" min="0" max="20" value="0"><label for="mask"></label>&nbsp;&nbsp;<b id="masktext"></b> seconds, to avoid falsely detecting constantly moving objects like a ceiling fan, or winds blowing leaves.<br> 
Hold time for <input type="range" id="hold" name="hold" min="0" max="60" value="5"><label for="hold"></label>&nbsp;&nbsp;<b id="holdtext"></b> seconds, to continue recording after motion has stopped.<br> 

<input type="checkbox" id="repeat" name="repeat" checked> 
<label for="repeat">Repeat motion capture.</label><br>

Note: you will have to manually set the mode in which you capture.  Motion detection works is in video, TimeWarp and Timelapse Video modes. 
 
<center>
<div id="qrcode"></div>
<br>
</center>

QR Command: <b id="qrtext">time</b><br>

## After Capture - Finding Your Snow Leopard (or Backyard Dog)

After a couple of hours of repeated motion capture, you are still likely to have many false positives, resulting in more MP4 files than you need. We have a solution to help you narrow down to the best shots. For each capture start, the camera will create a JPEG showing where the motion was detected. So if you are looking for a ground animal and a bird flies by, the detection would show a patch in the sky. The JPEG is stored in the MISC folder, with a matching file number to the MP4 created. Sometimes it is faster to scan these JPEGs to find the videos you want?

![GL013585.jpg](GL013585.jpg)

The file **MISC\GL013585.jpg** matches capture in **DCIM\100GOPRO\GH013585.MP4**. The cross-hatched boxes show where the motion was detected. 

        
## ver 1.0
[BACK](..)

<script>
var once = true;
var qrcode;
var cmd = "oC";

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
		
	var delay = parseInt(document.getElementById("delay").value);	
	document.getElementById("delaytext").innerHTML = delay;	
	
	var mask = parseInt(document.getElementById("mask").value);	
	document.getElementById("masktext").innerHTML = mask;	
	
	var hold = parseInt(document.getElementById("hold").value);	
	document.getElementById("holdtext").innerHTML = hold;	
		
	cmd = "oC" + "!SM" + snstvty;	
	if(delay > 0) cmd = cmd + 'D' + delay;
	if(mask > 0) cmd = cmd + 'M' + mask;
	if(hold > 0) cmd = cmd + 'H' + hold;	
	
    if(document.getElementById("repeat") != null)
    {
      if(document.getElementById("repeat").checked == true)
      {
        cmd = cmd + "!R";
      }
    }
  }
  
  qrcode.clear(); 
  qrcode.makeCode(cmd);
  document.getElementById("qrtext").innerHTML = cmd;
  var t = setTimeout(timeLoop, 100);
}

function myReloadFunction() {
  location.reload();
}

makeQR();
timeLoop();


</script>
