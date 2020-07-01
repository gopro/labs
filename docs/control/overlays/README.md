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

# Add an Overlay to Video

This is more for security applications like a dash cam setup, or education environments where student projects are pre-labeled, rather than for creative applications, as it will modify the video image with text that can't be removed.

If either horizontal or vertical size is zero, the size will be computed automatically.
 
Overlay vertical size <input type="range" style="width: 300px;" id="vsize" name="vsize" min="0" max="200" value="20"><label for="vsize"></label> <b id="vstext">40</b>

Overlay horizontal size <input type="range" style="width: 300px;" id="hsize" name="hsize" min="0" max="200" value="0"><label for="hsize"></label> <b id="hstext">0</b>

Offset from the edge <input type="range" style="width: 300px;" id="offset" name="offset" min="10" max="150" value="10"><label for="offset"></label> <b id="offtext">10</b>

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

  &nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="am1" name="addmeta" value="'GPS53%1.2f'm/s"> <label for="am1">Add speed in m/s (requires GPS)</label><br>
  &nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="am2" name="addmeta" value="'GPS50%1.6f', 'GPS51%1.6f'"> <label for="am2">Add GPS Location</label><br>
  &nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="am3" name="addmeta" value="ISO:'ISOE%d'"> <label for="am3">Sensor ISO</label><br>
  &nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="am4" name="addmeta" value="" checked> <label for="am4">none</label><br>
 
**Any end message here:**  <input type="text" id="endmsg" value=""><br>

**Screen Placement** <br>
  &nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="sp1" name="placement" value="TL"> <label for="sp1">Top Left    </label>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <input type="radio" id="sp2" name="placement" value="TC"> <label for="sp2">Top Center  </label>&nbsp;&nbsp;&nbsp;&nbsp;
  <input type="radio" id="sp3" name="placement" value="TR"> <label for="sp3">Top Right   </label><br>
  &nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="sp4" name="placement" value="ML"> <label for="sp4">Mid Left    </label>&nbsp;
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <input type="radio" id="sp5" name="placement" value="MR"> <label for="sp5">Mid Right   </label><br>
  &nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="sp6" name="placement" value="BL"> <label for="sp6">Lower Left  </label>&nbsp;
  <input type="radio" id="b7" name="placement" value="BC"> <label for="sp7">Lower Center</label>&nbsp;
  <input type="radio" id="sp8" name="placement" value="BR" checked> <label for="sp8">Lower Right </label>&nbsp;<br>
  
  
**GPS On or Off** <br>
 
  &nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" id="gps" name="gps"> <label for="gps">Using GPS</label><br>

<center>
<div id="qrcode"></div>
<br>
</center>


Make the overlay permanently active: **Are you sure? (Risky)**  <input type="checkbox" id="permanent" name="permanent"> <label for="permanent">Permanent Overlay</label><br>

QR Command: <b id="qrtext">time</b><br>

Cool Tips:
- Metadata overlays work great with live-streaming.  This was its original intended function. 
- Overlays can be changed mid capture, it is one of the few modes that QR Code reading is active while recording. Example use: When live streaming an endurance auto-race, you can change the driver name on the overlay during driver change pit-stops. 
- A range (not all) of GoPro metadata can be displayed in their stored units, so speed is in meters/sec, not MPH. For more technical information on [GoPro's GPMF Metadata](https://gopro.github.io/gpmf-parser/) and other metadata you can display.

Known Issues:
- not working correctly in 4K50 and 4K60 video modes and Timelapse 4K.
- does not update the time and metadata when used with motion detection triggered captures.
- Metadata can take a second before it updates after capture start.
- Permanent overlays require the clearing of older settings. If your using either Owner or Large Chapters modifications, they will need to be added after the overlay.     
		
## ver 1.06
[BACK](..)

<script>
var once = true;
var qrcode;
var cmd = "";

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
  if(document.getElementById("startmsg") !== null)
  {
    var mtype = "o";
	var openb = "\[";
	var closeb = "\]";
	var pos = dcmd("","sp");
	
   

	cmd = "";
	
	 if(document.getElementById("permanent").checked === true)
	 {
		cmd = "!RESET";
		mtype = "!";
     }

	
    if(document.getElementById("gps").checked === true)
    {
		if(document.getElementById("permanent").checked === true)
		{
			cmd = cmd + "g1!MLFIN=\"0\"";
		}
		else
		{
			cmd = cmd + "g1oMLFIN=0";
		}		
	}
	else
	{
		cmd = cmd + "g0";
	}
	
    cmd = cmd + mtype + "MBRNO=" + document.getElementById("offset").value + mtype + "MBURN=\"(" + document.getElementById("hsize").value + "," + document.getElementById("vsize").value + ")" + document.getElementById("startmsg").value + openb + pos + document.getElementById("addtime").value + document.getElementById("adddate").value;
	cmd = dcmd(cmd, "am");
	cmd = cmd + closeb + document.getElementById("endmsg").value + "\"";
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
  document.getElementById("qrtext").innerHTML = cmd;
  var t = setTimeout(timeLoop, 50);
}

function myReloadFunction() {
  location.reload();
}

makeQR();
timeLoop();
</script>
