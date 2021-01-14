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

# Extensions and Other Smaller Additions

After the release of the the first Labs firmware for HERO8, we heard the feedback and added features wherever possible. Some of the more major features got their own page, the rest are documented in this collection.

## Miscellaneous Metadata controls. 

All metadata QR commands are written in the form oM**wxzy**=value(s) or !M**wxzy**=value(s) -- where the four character code (4CC) **wxzy** is under your control, along with the data it stores. The **!M** version will permanently store the metadata, and the **oM** will store it for only this power-on session. Metadata is available to flag your files for special uses, or just to label the [camera owner](./owner). Some particular 4CCs will also change camera behavior and/or enable features. Here is a list of additional metadata driven controls: 

- **LLTZ=latt,long,timezone** for those want to use Sunset/Sunrise timelapse without waiting for GPS lock, or for when you are shooting a sunset timelapse from indoors. The metadata is used to store your GPS Location and timezone e.g. !MLLTZ=33.126,-117.327,-8.0  In this case you must used the !M command, permanent storage, as solar event timers will shutdown the camera.
- **QRDR=1** - detect QR Codes while recording.  Normally this feature is disabled to ensure the lowest computing load impact, so not enabling this is the safest. However, it is needed for some cool ideas, like changing a video burnin message in the middle of a live-stream, or changing its exposure with BIAS (see below.) This also allows you to end a capture via a QR Code (command: !E). oMQRDR=0 will disable it.
- **BIAS=ev_value** - This is a crude EV compensation for modes that don’t have Protune settings, like Live-stream. e.g. oMBIAS=2.0 (do not make this permanent as it can impact all video modes.) 
- **HNDL=x**, where x is 1 to 31, setting the camera ID for a camera. This is for rare scenarios where multiple cameras see the same QR Code, and you only want particular cameras to respond. This combined with **hZ** command where Z is the bit mask for which cameras will follow the command.
	- e.g.   h6mP!S  ← this command will only run on cameras with IDs 2 and 3.
    - e.g.   h1mVh2mPB ← set camera 1 to mode Video and camera 2 to Photo Burst.
- **DSPL=time**, this will control the amount of time messages are displayed. For users who want there own information displayed longer. The default is 1 second.  DISP=1 thru 9 is in seconds.  DISP = 10 thru 9999 is in milliseconds.  So for much faster messages set DISP to 100. Set this before setting the owner information, as metadata commands are processed in the order they are stored. 
- **DSPC=value**, this sets that contrast for which messages are displayed.  Contrast is from 0 - transparent text background, to 6 - opaque black background
- **HIST=x** - Displays a histogram with contrast from 1 to 11. e.g. try setting HIST to 5. HIST=0 will disable it.
- **LAPS=1** turns on the burn-in laptime, a hackathon designed for live-streaming auto races. LAPS=0 will disable it.
	- **BRNP=”xx”**  this the burnin position TL, TR, BL, BR (default) - T-Top L-Left B-Bottom R-Right, e.g. oMBRNP="TR"
	- **LFIN=latt,long** GPS location for the Lap Line (finish line), used to compute the lap times. e.g. !MLFIN=36.586221,-121.756818 The finish line at Laguna Seca. You need a high degree of GPS precision for this to work correctly.
	- **LSRT=”hh:mm”** - Lap times starting at time HH:MM, so you can put in the race start time.
	- **LDVR=”Driver Name”** - displays "Driver", with the name you provide
	- **LRDR=”Rider Name”** - displays "Rider", with the name you provide
	- **LRUN=”Runner Name”** - displays "Runner", with the name you provide
        

<input type="checkbox" id="perm" name="perm"> 
<label for="perm">Make metadata Premanent (are you sure?)</label><br>
Metadata Four CC: <input type="text" id="addcmd" value="">  e.g. BIAS, HIST etc.<br>
Metadata Value(s): <input type="text" id="addvalue" value="">  e.g. 2.0 or "Joe Blogg", strings in quotes, numbers comma separated.

<center>
<div id="qrcode"></div>
<br>
</center>
QR Command: <b id="qrtext">command</b><br>


## Alternative Exposure Controls. 

- EV adjustments. While you can just see an EV value you can now use x++ to increase from the current EV and x-&nbsp;- to decrease. This might be useful for dive application, as you can't change EV while under water 

- White Balance adjustments, with w++ and w-&nbsp;- will increase or decrease white balance.
 Again for dive users.

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
	if(document.getElementById("addcmd").value.length !== 4)
		cmd = "Metadata 4CCs must be\\nfour characters long";
	else if(document.getElementById("addvalue").value.length === 0)
		cmd = "Metadata requires\\nvalid data";
	if(document.getElementById("addcmd").value.length === 4 && document.getElementById("addvalue").value.length > 0)
	{
		cmd = "oM";
		if(document.getElementById("perm") !== null)
		{
			if(document.getElementById("perm").checked === true)
			{
				cmd = "!M"
			}
		}
		cmd = cmd + document.getElementById("addcmd").value + "=" + document.getElementById("addvalue").value;
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
