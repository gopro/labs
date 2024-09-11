# Add an Overlay to Video

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

This is more for security applications like a dash cam setup, or education environments where student projects are pre-labeled, rather than for creative applications, as it will modify the video image with text that can't be removed.

If either horizontal or vertical size is zero, the size will be computed automatically.
 
Overlay vertical size <input type="range" style="width: 300px;" id="vsize" name="vsize" min="0" max="200" value="20"><label for="vsize"></label> <b id="vstext">40</b><br>
Overlay horizontal size <input type="range" style="width: 300px;" id="hsize" name="hsize" min="0" max="200" value="0"><label for="hsize"></label> <b id="hstext">0</b><br>
Offset from the edge <input type="range" style="width: 300px;" id="offset" name="offset" min="10" max="150" value="10"><label for="offset"></label> <b id="offtext">10</b><br>
Limit display time <input type="range" style="width: 200px;" id="brnt" name="brnt" min="0" max="149" value="0"><label for="brnt"></label> <b id="brnttxt">unlimited</b>

Note: All text box support **\n** for a new line.

**Any start message here:** <input type="text" id="startmsg" value=""><br>

**Add Time with format**  <input type="text" id="addtime" value="HH:MM:SSaa "> Remove by emptying this field.

 * HH - Hour
 * MM - Minute
 * SS - Second
 * aa - am/pm (also switches off 24 hour time)
 * AA - AM/PM (also switches off 24 hour time)

**Add Date with format**  <input type="text" id="adddate" value="mm-dd-yyyy "> Remove by emptying this field.

 * yy - year in two digit format
 * yyyy - year in four digit format
 * mm - month (1-12)
 * dd - day (1-31)
 
**Display Metadata (experimental)** 

  &nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="am1" name="addmeta" value="'GPS53%1.2f'm/s"> <label for="am1">Add speed in m/s *</label><br>
  &nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="am2" name="addmeta" value="'GPS50%1.6f', 'GPS51%1.6f'"> <label for="am2">Add GPS Location *</label><br>
  &nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="am3" name="addmeta" value="ISO:'ISOE%d'"> <label for="am3">Sensor ISO</label><br>
  &nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="am4" name="addmeta" value="" checked> <label for="am4">none</label><br>
  
  Note: * These features require the GPS to be enabled. If combined with Livestreaming, you will need to record a local copy for these features to display correctly.
  
**Any end message here:**  <input type="text" id="endmsg" value=""><br>

**Screen Placement** <br>
  &nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="sp1" name="placement" value="TL"> <label for="sp1">Top Left    </label>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <input type="radio" id="sp2" name="placement" value="TC"> <label for="sp2">Top Center  </label>&nbsp;&nbsp;&nbsp;&nbsp;
  <input type="radio" id="sp3" name="placement" value="TR"> <label for="sp3">Top Right   </label><br>
  &nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="sp4" name="placement" value="ML"> <label for="sp4">Mid Left    </label>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <input type="radio" id="sp5" name="placement" value="MR"> <label for="sp5">Mid Right   </label><br>
  &nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="sp6" name="placement" value="BL"> <label for="sp6">Lower Left  </label>&nbsp;
  <input type="radio" id="sp7" name="placement" value="BC"> <label for="sp7">Lower Center</label>&nbsp;
  <input type="radio" id="sp8" name="placement" value="BR" checked> <label for="sp8">Lower Right </label>&nbsp;<br>
  
  
**GPS On or Off** <br>
 
  &nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" id="gps" name="gps"> <label for="gps">Using GPS</label><br>


<div id="qrcode_txt" style="width: 360px">
 <center>
  <div id="qrcode"></div><br>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext"></em><br>
  <b><font color="#005CAC">Overlays</font></b>
 </center>
</div>
<button id="copyImg">Copy Image to Clipboard</button>
<br>
<br>
Share this QR Code as a URL: <small id="urltext"></small><br>
<button id="copyBtn">Copy URL to Clipboard</button>


Make the overlay permanently active: **Are you sure? (Risky)**  <input type="checkbox" id="permanent" name="permanent"> <label for="permanent">Permanent Overlay</label> <input type="checkbox" id="erase" name="erase"> <label for="erase">Erase</label><br>

QR Command: <b id="qrtext">time</b><br>

Cool Tips:
- Metadata overlays work great with live-streaming.  This was its original intended function. 
- Overlays can be changed mid capture, it is one of the few modes that QR Code reading is defaulted to active while recording. Example use: When live streaming an endurance auto-race, you can change the driver name on the overlay during driver change pit-stops. 
- A range (not all) of GoPro metadata can be displayed in their stored units, so speed is in meters/sec, not MPH. For more technical information on [GoPro's GPMF Metadata](https://gopro.github.io/gpmf-parser/) and other metadata you can display.

Known Issues:
- HERO10-13 support is limited to video modes 4K 16:9 up to 30, 2.7K up to 60 and 1080p up to 120fps, in 8-bit only. 
- Metadata can take a second before it updates after capture start.

**Compatibility:** Labs enabled HERO8-13 and MAX 
        
updated: September 10, 2024

[Learn more](..) on QR Control

<script>
var once = true;
var qrcode;
var cmd = "";
var clipcopy = "";
var lasttimecmd = "";
var changed = true;

function dcmd(cmd, id) {
    var x;
    var i;
	if(document.getElementById(id) !== null)
	{
		x = document.getElementById(id).checked;
		if( x === true)
			cmd = cmd + document.getElementById(id).value;
	}
	else
	{
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
      text : "oMBURN=\"\"",
      width : 360,
      height : 360,
      correctLevel : QRCode.CorrectLevel.M
    });
    once = false;
  }
}

function timeLoop()
{
  if(document.getElementById("startmsg") !== null)
  {
    var mtype = "o";
	var openb = "\[";
	var closeb = "\]";
	var pos = dcmd("","sp");
	
   
	cmd = "";
	
	if(document.getElementById("permanent").checked === true)
	{
	//	cmd = "!RESET!30NQ";
		mtype = "!";
    }
	
    if(document.getElementById("gps").checked === true)
    {
		cmd = cmd + "g1" + mtype + "MLFIN=0";	
	}
	else
	{
		cmd = cmd + "g0";
	}
	
	{
		var tm = document.getElementById("brnt").value; 
		
		if(tm == 0) 
		{
			s = 0;
			document.getElementById("brnttxt").innerHTML = "unlimited";
		}
		else if (tm < 30)
		{
			s = Math.trunc(100*tm/30)/100;
			document.getElementById("brnttxt").innerHTML = s + " secs";
		}
		else if (tm < 90)
		{
			s = tm-29;
			document.getElementById("brnttxt").innerHTML = s + " secs";
		}
		else
		{
			s = (tm-89)*60;
			document.getElementById("brnttxt").innerHTML = (tm-89) + " mins";
		}
		
		if(s != 0)
			cmd = cmd + mtype + "MBRNT=" + s;
	}
	
    cmd = cmd + mtype + "MBRNO=" + document.getElementById("offset").value + mtype + "MBURN=\"(" + document.getElementById("hsize").value + "," + document.getElementById("vsize").value + ")" + document.getElementById("startmsg").value + openb + pos + document.getElementById("addtime").value + document.getElementById("adddate").value;
	cmd = dcmd(cmd, "am");
	cmd = cmd + closeb + document.getElementById("endmsg").value + "\"";
	
	if(document.getElementById("erase").checked === true)
	{
		cmd = mtype + "MBURN=\"\"";
	}
  }
  else
  {
    cmd = "oMBURN=\"\"";
  }

  if(document.getElementById("hsize") !== null)
  {
	var h = document.getElementById("hsize").value;
	var v = document.getElementById("vsize").value;
	var o = document.getElementById("offset").value;
 
	document.getElementById("hstext").innerHTML = h;
	document.getElementById("vstext").innerHTML = v;
	document.getElementById("offtext").innerHTML = o;
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
	clipcopy = "https://gopro.github.io/labs/control/set/?cmd=" + cmd + "&title=Overlays";	
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
