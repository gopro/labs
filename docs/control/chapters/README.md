# Larger Chapter Support

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

GoPro cameras normally split long recordings into 4GB segments, we call these chapters. These 4GB (32-bit) MP4 files are the most compatible, yet larger 64-bit MP4 files are becoming more common. If you have an SD Card that is at least 64GBytes, you can increase your chapter size to 12GB with this control below. 

<input type="checkbox" id="lchptrs" name="lchptrs" checked> 
<label for="lchptrs">Enable Large Chapters</label><br>

<div id="qrcode_txt" style="width: 360px">
  <center>
  <div id="qrcode"></div><br>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext"></em><br>
  <b><font color="#005CAC">Large Chapters <em id="status"></em></font></b>
  </center>
</div>
<button id="copyImg">Copy Image to Clipboard</button>
<br>
<br>
Share this QR Code as a URL: <small id="urltext"></small><br>
<button id="copyBtn">Copy URL to Clipboard</button>

**Warning:** Larger chapters may not work everywhere in the ecosystem, even **the HERO8 an HERO9 cameras will not playback or USB transfer files larger than 4GB** in this current firmware. Yet the files are valid and accessible using a SD Card reader, and have been tested to work in many tools. So this one of the more experimental features, so please test before committing to this new workflow.  Support for HERO8, HERO9, HERO10 and MAX cameras.

**Known Issue:** Larger chapters will not be enabled when using QuikCapture. QuikCapture starts recording before the Labs service starts, resulting in perfectly fine, but only 4GB chapters. 

**Compatibility:** Labs enabled HERO8, HERO9, HERO10, MAX and BONES (Standard on HERO11/12)

## Optional: Joining Chapters After Capture
 
Whether you are using the larger chapter feature or not, you may still end up with more than one file for very long video captures. Tools like ReelSteady can only operate one file at a time, so here is a solution for merging chapters so that they operate as a valid GoPro MP4 of any length, with all the needed metadata.

### Easy Solution:

Try [ReelSteady-Joiner](https://github.com/rubegartor/ReelSteady-Joiner/releases)

### Techie Solution:

Steps involved:
- install ffmpeg: https://www.ffmpeg.org/ 
- download [udtacopy.zip](https://github.com/gopro/labs/tree/master/docs/control/chapters/bin/udtacopy.zip) (source [code](https://github.com/gopro/labs/tree/master/docs/control/chapters/src))
- Unzip and grab the version best for your computer (Mac, Win or Linux) and copy it a folder somewhere (within your executable path).
- Create a text file with a list of GoPro files that need to be concatenated. E.g. [filelist.txt](https://github.com/gopro/labs/tree/master/docs/control/chapters/src/filelist.txt)
- Start a terminal and run the following commands:

>ffmpeg -y -f concat -i **your_path_to/filelist.txt** -c copy -map 0:0 -map 0:1 -map 0:3 **your_output_path/final.mp4**
>
>udtacopy **your_path_to/the_first_GoPro_file.MP4** **your_output_path/final.mp4**

The resulting final.mp4 will be a complete GoPro file will all required metadata.

### .360 support changes

>ffmpeg -y -f concat -i **your_path_to/filelist.txt** -c copy -map 0:0 -map 0:1 -map 0:3 -map 0:5 **your_output_path/final.mp4**
>
>udtacopy **your_path_to/the_first_GoPro_file.360** **your_output_path/final.mp4**
>
>rename **your_output_path/final.mp4** **your_output_path/final.360**

The resulting final.360 will be a complete GoPro file will all required metadata.

 
## ver 1.11
updated: Sept 14, 2022

[More features](..) for Labs enabled cameras

<script>
var once = true;
var qrcode;
var stts = "";
var cmd = "";
var clipcopy = "";
var lasttimecmd = "";
var changed = true;

function makeQR() 
{	
  if(once === true)
  {
    qrcode = new QRCode(document.getElementById("qrcode"), 
    {
      text : "!M64BT=1",
      width : 360,
      height : 360,
      correctLevel : QRCode.CorrectLevel.M
    });
    once = false;
  }
}

function timeLoop()
{
  stts = "Disabled";
  cmd = "!M64BT=0";
  if(document.getElementById("lchptrs") !== null)
  {
    if(document.getElementById("lchptrs").checked === true)
    { 
	  stts = "Enabled";
      cmd = "!M64BT=1";
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
	document.getElementById("status").innerHTML = stts;
	document.getElementById("qrtext").innerHTML = cmd;
	clipcopy = "https://gopro.github.io/labs/control/set/?cmd=" + cmd + "&title=Large%20Chapter%20Control";
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
