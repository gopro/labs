# Larger Chapter Support

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

GoPro cameras normally split long recordings into 4GB segments, we call these chapters. These 4GB (32-bit) MP4 files are the most compatible, yet larger 64-bit MP4 files are becoming more common. If you have an SD Card that is at least 64GBytes, you can increase your chapter size to 12GB with this control below. 

<input type="checkbox" id="lchptrs" name="lchptrs" checked> 
<label for="lchptrs">Enable Large Chapters</label><br>
<center>
<div id="qrcode"></div>
<br>
</center>
QR Command: <b id="qrtext">command</b><br>

**Warning:** Larger chapters may not work everywhere in the ecosystem, even **the camera will not playback or USB transfer files larger than 4GB** in this current firmware. Yet the files are valid and accessible using a SD Card reader, and have been tested to work in many tools. So this one of the more experimental features, so please test before committing to this new workflow.  Support for HERO8, HERO9 and MAX cameras.

**Known Issue:** Larger chapters will not be enabled when using QuikCapture. QuikCapture starts recording before the Labs service starts, resulting in perfectly fine, but only 4GB chapters. 

<br> 
        
Compatibility: Labs enabled HERO8, HERO9 and MAX 
        
## ver 1.04
[Learn more](..) on QR Control

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
  cmd = "!M64BT=0";
  if(document.getElementById("lchptrs") !== null)
  {
    if(document.getElementById("lchptrs").checked === true)
    {
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
