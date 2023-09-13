# Maximum Shutter Angle

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

## More control over low-light stabilization.

<div id="ptSHUT">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Maximum Shutter Angle:</b>&nbsp;&nbsp;
  <input type="radio" id="shut1" name="shut" value="MEXPT=0"> <label for="shut1">360&deg;(default) </label>&nbsp;&nbsp;
  <input type="radio" id="shut2" name="shut" value="MEXPT=1" > <label for="shut2">180&deg; </label>&nbsp;&nbsp;
  <input type="radio" id="shut3" name="shut" value="MEXPT=2" > <label for="shut3">90&deg; </label>&nbsp;&nbsp;
  <input type="radio" id="shut4" name="shut" value="MEXPT=3" checked> <label for="shut4">45&deg; </label>&nbsp;&nbsp;
  <input type="radio" id="shut5" name="shut" value="MEXPT=4" > <label for="shut5">22.5&deg; </label>&nbsp;&nbsp;
  <input type="radio" id="shut6" name="shut" value="MEXPT=5" > <label for="shut6">11.25&deg; </label>&nbsp;&nbsp;
 </div>

<div id="ptISO">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>ISO Max:</b>&nbsp;&nbsp;
  <input type="radio" id="iso1" name="iso" value="i1M1" > <label for="iso1">100 </label>&nbsp;&nbsp;
  <input type="radio" id="iso2" name="iso" value="i2M1" > <label for="iso2">200 </label>&nbsp;&nbsp;
  <input type="radio" id="iso3" name="iso" value="i4M1" > <label for="iso3">400 </label>&nbsp;&nbsp;
  <input type="radio" id="iso4" name="iso" value="i8M1" > <label for="iso4">800 </label>&nbsp;&nbsp;
  <input type="radio" id="iso5" name="iso" value="i16M1" checked> <label for="iso5">1600 (default) </label>&nbsp;&nbsp;
  <input type="radio" id="iso6" name="iso" value="i32M1"> <label for="iso6">3200 </label>&nbsp;&nbsp;
  <input type="radio" id="iso7" name="iso" value="i64M1"> <label for="iso7">6400 </label>&nbsp;&nbsp;
 </div>
 
<input type="checkbox" id="permanent" name="permanent" checked> 
<label for="permanent">Make this setting survive a power off</label><br>

<div id="qrcode_txt" style="width: 360px">
 <center>
  <div id="qrcode"></div><br>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext"></em><br>
  <b><font color="#005CAC">Maximum Shutter Angle</font></b>
 </center>
</div>
<button id="copyImg">Copy Image to Clipboard</button>
<br>
<br>
Share this QR Code as a URL: <small id="urltext"></small><br>
<button id="copyBtn">Copy URL to Clipboard</button>

        
## Background
Shutter Angle describes the amount of potential motion blur in the image, it is a nice way to describe shutter speed independent of the video frame rate. A maximum shutter angle of 360&deg; means the blur can capture all the motion from one video frame to the next, e.g. 24p with a 360&deg; will expose for 1/24th of a second,  at 120p with the same angle exposes for 1/120th of a second. In low light, the camera will typically expose longer, increasing the shutter angle, resulting in more motion blur. 

Stabilization benefits from a smaller shutter angle, yet other factors of image quality benefit from more light. With this feature the trade-off is more under your control.  In the standard camera firmware you can set a Maximum ISO to a lower value, this forces the camera to use larger shutter angles (more blur) and there is no reverse operation.  While ISO Min can be used in some situations, you might be trading off quality (more noise) when you don't need to (outside, daylight.)  Shutter Angle Maximum is the missing control and it still works with ISO Min set to 100. This is ideal for shoots that needs the best stabilization and when it maybe going in and out of lower-light situations. examples: mountain biking through dense forest, or drone flights that go in and out of a building.  

Default exposure might result in these behaviors (shooting 24p, ISO Min 100, ISO Max 1600 - defaults)<br>
**Sunny outdoors:** the camera might shoot 1/1500th shutter (5.76&deg;), ISO 100<br> 
**Indoors:** the camera might shoot 1/96th shutter (90&deg;), ISO 1600 (so-so stabilization)<br>
**Dark indoors:** the camera might shoot 1/24th shutter (360&deg;), ISO 1600 (poor stabilization)<br>

For good stabilization you might select 45&deg; for your maximum shutter angle, with Protune ISO Min 100 and ISO Max 3200. Don't be afraid of increasing the ISO Maximum, it is only used when needed.   

Auto exposure might result in these behaviors (shooting 24p) <br>
**Sunny outdoors:** the camera might shoot 1/1500th shutter (5.76&deg;), ISO 100<br>
**Indoors:** the camera might shoot 1/192th shutter (45&deg;), ISO 3200 (good stabilization)<br> 
**Dark indoors:** the camera might shoot 1/192th shutter (45&deg;), ISO 3200  (good stabilization, but is a little darker)<br>

**Compatibility:** Labs enabled HERO7, HERO8, HERO9, HERO10, HERO11, HERO12, MAX and BONES 
        
updated: Sept 13, 2023

[More features](..) for Labs enabled cameras

[BACK](..)

<script>
var once = true;
var qrcode;
var cmd = "oC15dTmNLeA";
var clipcopy = "";
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

function checkTime(i) {
    if (i < 10) {i = "0" + i;}  // add zero in front of numbers < 10
    return i;
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
  
  cmd = dcmd("mVt","iso"); //iso
  cmd = cmd + type + dcmd("","shut"); //shutter angle
  
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
	clipcopy = "https://gopro.github.io/labs/control/set/?cmd=" + cmd + "&title=Maximum%20Shutter%20Angle";
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
