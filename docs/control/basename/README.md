# Altered File Naming via QR Code

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

Your GoPro will typically name your files something like GOPR3606.JPG and GH013607.MP4. If you format your media, and factory reset your camera, you can change the file counter back to zero, but otherwise, you have no control over the file name, until this Labs hack. This is intended for high volume multiple camera production, where simply naming the source media differently will ease post production. 

**WARNING:** The GoPro App and GoPro cloud services will not support these renamed files. In addition, the camera's automatic file repair will not know to repair these files (see Manual File Recovery below), so only use this feature if you aren't putting cameras in extreme danger (where power could be randomly disconnected.) 

Your base filename here: <input type="text" id="addname" value=""> (only a-z, A-Z, 0-9, and +-_(),.)<br> 
Up to eight characters. e.g. "CAMERA06"<br> 

**HERO10 - Only:** You can added date and time to the filename (Note: make sure your clock is set correctly).  The date and time shortcuts must be within the **[ ]** characters, these are the wildcards:
 - **yyyy** - Year in format: 2021
 - **yy** - Year in to digit format: 21
 - **mm** - Month
 - **dd** - Day of Month
 - **HH** - Hour
 - **MM** - Minute
 - **SS** - Second
 
Formatting examples: 
 - CamA-[yyyymmddHHMMSS]-
 - [yy-mm-dd_HH.MM.SS]-HERO10-

Note: Unfortunately filenames can't contain common date/time delimiters, only +-_(),. allowed.

<br>
Your filenames will be in the format: <b id="newnameMP4">nameGH013607.MP4</b> and <b id="newnameJPG">nameGOPR3607.JPEG</b><br>

<div id="qrcode_txt" style="width: 360px">
  <center>
  <div id="qrcode"></div><br>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext"></em><br>
  <b><font color="#005CAC">Base Filename Change</font></b>
  </center>
</div>

<input type="checkbox" id="permanent" name="permanent"> <label for="permanent">Make this name change permanent</label><br>
Can be restored by setting the basename to nothing.

<button id="copyImg">Copy Image to Clipboard</button>
<br>
<br>
Share this QR Code as a URL: <small id="urltext"></small><br>
<button id="copyBtn">Copy URL to Clipboard</button>


## Useful Tip - Manual File Recovery 
 
So you have a corrupted/unclosed GoPro file. You crashed your drone, and the battery was disconnected before the file was closed, or you ran your car wheel over a recording GoPro, crushing it. If your SD Card survived, the file is likely recoverable using another GoPro. 

1. You need any working GoPro camera, although the same model and firmware version is advised. If you're using Labs Firmware and are using Altered file naming (this page's Labs feature), reset the filenaming to the default. 

2. Copy the file you want to repair to your PC

3. With a working GoPro, record for 10+ seconds then pull the power or battery, while still recording. You want an intentionally unclosed file. The camera will remember it needs to repair only this file

4. Add that SD Card to your PC directly (not via camera USB)

5. Copy the filename of the last MP4 captured. e.g. "GX010358.MP4"

6. Delete this dummy file from the SD Card

7. Add your previous corrupted (unclosed) file to the SD card, and rename it to the copied name. e.g. If your filename was "Drone03_GX010201.MP4", or just "GH010330.MP4", rename it to "GX010358.MP4" (your last MP4 filename)

8. Insert the SD Card with your corrupted file back into the working GoPro camera

9. Power on the camera, and the "last" file will be repaired

10. Once the camera completes the file repair process, you can eject the SD Card and backup and play the now repaired file


**Compatibility:** Labs enabled HERO8, HERO9, HERO10, MAX and BONES 
        
## ver 1.15
updated: June 5, 2022

[More features](..) for Labs enabled cameras

<script>
var once = true;
var qrcode;
var clipcopy = "";
var cmd = "";
var lasttimecmd = "";
var changed = true;
var number = 1;

function makeQR() 
{	
  if(once === true)
  {
    qrcode = new QRCode(document.getElementById("qrcode"), 
    {
      text : "!MOWNR=\"\"",
      width : 360,
      height : 360,
      correctLevel : QRCode.CorrectLevel.M
    });
    once = false;
  }
}

function pad(num, size) {
    var s = num+"";
    while (s.length < size) s = "0" + s;
    return s;
}

function filter(txt)
{
	var desired;
	desired = txt.replace('{', '');
	desired = desired.replace('}', '');
	desired = desired.replace('\[', '{');
	desired = desired.replace(']', '}');
	desired = desired.replace(/[^a-zA-Z0-9-_+(){},.]/gi, '');
	desired = desired.replace('{', '\[');
	desired = desired.replace('}', ']');
	return desired;
}

function timeLoop()
{
  var type = "o";
	
  if(document.getElementById("permanent") !== null)
  {
	if(document.getElementById("permanent").checked === true)
	{
		type = "!";
	}
  }
		
  if(document.getElementById("addname") !== null)
  {
    cmd = type + "MBASE=\"" + filter(document.getElementById("addname").value) + "\"";
  }
  else
  {
    cmd = type + "MBASE=\"\"";
  }

  if(document.getElementById("newnameMP4") !== null)
  {
	var MP4 = filter(document.getElementById("addname").value) + "GH01" + pad(number,4) + ".MP4";
	var JPG = filter(document.getElementById("addname").value) + "GOPR" + pad(number,4) + ".JPG";
 
	number++;
	if(number > 9999) 
	{
	  number = 1;
	}
	
	document.getElementById("newnameMP4").innerHTML = MP4;
	document.getElementById("newnameJPG").innerHTML = JPG;
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
	clipcopy = "https://gopro.github.io/labs/control/set/?cmd=" + cmd + "&title=Base%20Filename%20Change";
	document.getElementById("urltext").innerHTML = clipcopy;
	changed = false;
  }
  
  var t = setTimeout(timeLoop, 250);
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
