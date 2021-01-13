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

# GPS Time Synchronization

If you are shooting with multiple GoPro **HERO9** cameras, enable this feature. 

## How it works

This improves the timecode track precision. While this works best outdoors with a clear GPS signal, it is harmless to have active in all shooting locations and modes. If there is a good GPS signal, the camera’s internal clock will be precisely updated, but only minute and second fields. It will not update the hour or day, as it preserves your current timezone offset, so this doesn’t remove the need for initial setup for time and date. This feature updates the MP4s timecode track at the end of capture, so it a good GPS time occurs after the capture begins, the timecode will be accurate. In tools like Adobe Premiere Pro, multiple camera angles can be synchronized using timecode. In limited testing, sync is typically within a frame or two, but your precision my vary.

<input type="checkbox" id="gsync" name="gsync" checked> 
<label for="gsync">Enable GPS Time Sync</label><br>
<center>
<div id="qrcode"></div>
<br>
</center>
QR Command: <b id="qrtext">command</b><br>

## Time-of-day Timecode for 24, 25 and 30p Modes

<iframe src="https://www.shadertoy.com/embed/ts3BW7?gui=false&paused=false" frameborder="0" style="height: 400px; width: 700px; "></iframe>

Note: it is correct for 23.976 and 29.97 Non-drop timecode to it be 0.1% behind 25.0 timecode.

<br> 
        
## ver 1.00
[BACK](..)

<script>
var once = true;
var qrcode;
var cmd = "";
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
	changed = false;
  }
  
  var t = setTimeout(timeLoop, 50);
}

function myReloadFunction() {
  location.reload();
}

makeQR();
timeLoop();

</script>
