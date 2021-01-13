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

# Archive Mode

An ultra simplified camera mode for novices documenting critical events, from weddings to protest marches, where you don't want the camera mode modified. Ever loan a camera to a friend to shoot video, and they bumped the mode button or LCD so that it was only shooting photos? Archive mode is intended to stop that, but making the camera video QuikCapture only, with either button starting or stopping the default video mode capture. The camera will inform the operator that the mode is limited, nothing can disable this mode other than the reversing QR Code. It will turn your GoPro into one button operation, press to start, press to stop. The operator can play or delete captures, or connect the GoPro to a smartphone, all media operations require the removal of the SD Card.

Set your video mode customization here: <input type="text" id="addcmd" value="">  e.g. **r4p24** Will set 4K at 24p as you default. You can make you own defaults video mode using the [**QR Control Customizer**](../custom), including Protune settings.

<input type="checkbox" id="arch" name="arch" checked> 
<label for="arch">Enable Archive Mode</label><br>
<center>
<div id="qrcode"></div>
<br>
</center>
QR Command: <b id="qrtext">command</b><br>

<br> 
        
## Disabling Archive Mode

Uncheck the above Archive mode checkbox, and scan the new code while the camera is recording.
		
		
## ver 1.00
[BACK](..)

<script>
var once = true;
var qrcode;
var cmd1 = "";
var cmd2 = "";
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
	cmd1 = "!E";
	cmd2 = "!MARCH=0\"Archive Mode\\nDisabled\\nShutting-down\"!O";
	if(document.getElementById("arch") !== null)
	{
		if(document.getElementById("arch").checked === true)
		{
			if(document.getElementById("addcmd") !== null)
			{
				cmd1 = cmd1 + "mVdVq1" + document.getElementById("addcmd").value;
			}
			cmd2 = "!MARCH=1\"Archive Mode\\nEnabled\\nShutting-down\"!O";
		}
	}
	
	cmd1 = cmd1 + cmd2;
	
	qrcode.clear(); 
	qrcode.makeCode(cmd1);

	if(cmd1 != lasttimecmd)
	{
		changed = true;
		lasttimecmd = cmd1;
	}

	if(changed === true)
	{
		document.getElementById("qrtext").innerHTML = cmd1;
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
