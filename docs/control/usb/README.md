# USB Power Trigger

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

The camera can use the switching on of USB power to boot the camera, and auto capture upon boot.

End capture after <input type="range" style="width: 200px;" id="tlendsec" name="tlendsec" min="0" max="60" value="2"><label for="tlendsec"></label>&nbsp;&nbsp;<b id="secsendtext"></b> seconds after USB power is off.

**Note:** A battery is required, as the camera needs close captured video when power is removed. Unfortunately this means your battery will eventually discharge, so it is best to have a spare battery if you intended to used this feature as a dedicated dash-cam.  

<input type="checkbox" id="enablenew" name="enablenew" checked> 
<label for="enablenew">Enable for newer Cameras: MAX, HERO10, 11, 11Mini & 12</label><br>

<div id="newer">
Once scanned, power off the camera. Now the camera will start with USB power, end capture and shutdown with USB power off. You can temporarily cancel any capture with the shutter button, power on with USB power, full manual camera control is restored.<br>
<br>
<input type="checkbox" id="usefast" name="usefast"> 
<label for="usefast">Enable a faster Labs boot.</label><br>  
<input type="checkbox" id="disablenew" name="disablenew"> 
<label for="disablenew">Disable the USB trigger.</label><br>   
</div>

<div id="qrcode_txt" style="width: 360px">
 <center>
  <div id="qrcode"></div><br>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext"></em><br>
  <b><font color="#005CAC">USB Power Trigger</font></b>
 </center>
</div>
<button id="copyImg">Copy Image to Clipboard</button>
<br>
<br>
Share this QR Code as a URL: <small id="urltext"></small><br>
<button id="copyBtn">Copy URL to Clipboard</button>
        
**Compatibility:** Labs enabled HERO7 (limited), HERO8, HERO9, HERO10, HERO11, 11Mini, HERO12 and MAX         

## BACKGROUND

The Script above was developed using Blocky and visual coding tool configured for Labs scripts.

![ScriptDemo+XML.png](ScriptDemo+XML.png)

If you save the above PNG image (of the script), and load that into [**Visual Script Tool**](https://gopro.github.io/labs/build/) via the "Import image", you can enhance it further. 

![importImage.png](importImage.png)

updated: August 1, 2024

[More features](..) for Labs enabled cameras

<script>
var once = true;
var qrcode;
var cmd = "oC15dTmNLeA";
var clipcopy = "";
var lasttimecmd = "";
var changed = true;

function dset(label, on) {
		var settings = document.getElementById(label);
		if(on === true)
		{
			if (settings.style.display === 'none') 
				settings.style.display = 'block';
		}
		else
		{
			settings.style.display = 'none';
		}
}


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

function checkTime(i) {
    if (i < 10) {i = "0" + i;}  // add zero in front of numbers < 10
    return i;
}

function timeLoop()
{
  if(document.getElementById("tlendsec") !== null)
  {
	cmd = "";
				
	var secs = 0;	
		
	var endsecs = parseInt(document.getElementById("tlendsec").value);
	endsecs *= 5;
	if(endsecs == 0) endsecs = 1; 
	document.getElementById("secsendtext").innerHTML = endsecs;	
	
	if(secs > 0)
		cmd = cmd + "!u" + secs + "N";
	else
		cmd = cmd + "!uN";
		
	cmd = cmd + "!S";
	
	if(endsecs > 0)
		cmd = cmd + "!u" + endsecs + "E";	
	else
		cmd = cmd + "!uE";
    
	cmd = cmd + "!R";
	
    if(document.getElementById("enablenew") !== null)
    {
      if(document.getElementById("enablenew").checked === true)
      {
		dset("newer",true);
		if(document.getElementById("disablenew").checked === true)
		{
			if(document.getElementById("usefast").checked === true)
			{
				cmd = "*WAKE=0*FAST=0*BOOT=0";
			}
			else
			{
				cmd = "*WAKE=0*BOOT=0";
			}
		}
		else
		{
			//*WAKE=2*BOOT="!Lbt"!SAVEbt=<u0!X<r0!S>u0=At:B<u0>r0=Bt:B+=B-A>B9>r0!E+!1N+!1O<r0!X!R10
			
			if(document.getElementById("usefast").checked === true)
			{
				cmd = "*FAST=1";
			}
			else
			{
				cmd = "*FAST=0";
			}
			cmd = cmd + "*WAKE=2*BOOT=\"!Lbt\"!SAVEbt=";
			cmd = cmd + "<u0!X";
			cmd = cmd + "<r0!S";
			cmd = cmd + ">u0=At:B";
			cmd = cmd + "<u0>r0=Bt:B+=B-A"
			cmd = cmd + ">B" + endsecs;
			cmd = cmd + ">r0!E+!1N+!1O";
			cmd = cmd + "<r0!X!R10";
		}
      }
	  else
	  {
	  	dset("newer",false);
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
	document.getElementById("qrtext").innerHTML = cmd.replace(/</g, '&lt;');
	clipcopy = "https://gopro.github.io/labs/control/set/?cmd=" + encodeURIComponent(cmd) + "&title=USB%20Power%20Trigger";
	document.getElementById("urltext").innerHTML = clipcopy;
	changed = false;
  }
	
  var t = setTimeout(timeLoop, 50);
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
