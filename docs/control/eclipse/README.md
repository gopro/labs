# Eclipse Timelapse Planner

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


Shooting a solar eclipse is tricky. The first issue is the sheer change in dynamic range from full sun to when it's fully covered by the moon, 
the light level can vary up to 12 stops. 12 stops, the light halving in brightness 12 times, would be the difference in shooting with 1/1000 shutter to a 4 second exposure. 
This example data was from a solar eclipse measured in Australia in 2023 (thanks to Matt Parker's data from [**Stand-up Maths**](https://youtu.be/IuUMxNfDfFY?si=iytXca2frHqOakOB&t=945) - the whole video is a worth watch.)

![stops.png](stops.png)

The light levels change very slowly initially, but incredibly rapidly as the totality approaches. The first 90 minutes, the light drops only 3-4 stops, you will notice the light 
feels odd after 90 minutes, but your camera will have compensated so much to make it mostly unnoticeable. We can improve on the default camera behavior using Labs firmware.

## GoPro Night Lapse
A stock GoPro has a great night-lapse feature designed for day to night to day transitions, keeping a good exposure throughout, yet this exposure logic is not ideal for a solar 
eclipse before and after the totality (it is fine during totality.) None of the time-lapse modes on GoPro have an exposure lock option, but with a potential 12-stop change, locking the 
shutter 1/1000 and ISO at 100 (or exposing correctly at C1) will result in a mostly black image at C2. So we still need some of the autoexposure goodness, but with some constraints 
so that the light drop is more visibly dramatic.  

## GoPro Labs Firmware

### Extension - EXPS
Things to try with GoPro Labs. ```oMEXPS=1``` this will display ISO and shutter for your current shooting mode. Test with time-lapse or night-lapse, recording to see the exposure 
for different light levels. Practice well before the eclipse. This feature requires the latest Labs firmware on HERO12 and HERO11 to view exposure during a timelapse 
(it works only in video modes on older releases.)  

![EXPS.png](EXPS.png)

Note: The exposure settings for preview can be different than when recording, so experiment while capturing a timelapse.  


### Extension - EXPX
Once you see the shutter behavior with Labs extension above, we can now consider setting an upper limit to the shutter with ```oMEXPX=<your maximum shutter time>```.  
Below are extracted frames from two simultaneous Night Lapse captures of the sunset, one with the shutter limited to 1/50th of a second.

![NightCompare.png](NightCompare.png)

Limiting the ISO to 100 is also our recommendation for shooting the eclipse, as we estimate that from full daylight to totality, the shutter will range from around 1/1600th to 2.5 seconds at 100 ISO. 
Fitting nicely within Night Lapse with a 4-second interval, with an Auto shutter.  

It is tricky to capture both the massive drop in light, and the drama of totality, in a single timelapse capture. If possible, this is best achieved with multiple cameras, 
editing and blending the results in post.

#### Type 1 - Capture mostly optimized for the totality
Night Lapse ISO 100, 4s interval, Shutter Auto and starting about 15 minutes before the totality, running until 15 minutes after. 
Resulting in a ~17 second timelapse, 2 seconds in totality (if a 4-minute totality.)  

#### Type 2 - Capture optimized for the drop in brightness
Timelapse ISO 100, 10s interval, starting an hour before totality. Limiting the shutter to say 1/30th of a second 
(this is your creative choice.) At 1/30, the last 5-6 stops of teh eclipse will be more dramatically show the light impact upon the landscape. Resulting in a ~25 second timelapse, ~1 second in totality.

Note: Timelapse stock (not Night Lapse) is limited to a maximum of 1/8 second exposures, combined with ISO maximum of 100, this is a good option without Labs firmware. 
This is what I used in 2017. However, the now only the last 3-4 stops will show a dramatic light change, and this is in the last minute before and after totality, 
and with a 10s interval, you will only get about six frames of the light drop in the timelapse (quarter second at playback speed.)  Using the 1/30th limit, the estimated 
length of the light drop-off will double in the final timelapse.  

#### Type 3 - Super optimized for the totality
Night Lapse ISO Max 800, Auto interval, Shutter Auto, Labs shutter limited to 1s, and starting about 2 minutes 
before the totality, run until 2+ minutes after. Auto shutter with Auto interval is a special mode in Night Lapse, in this mode it will take frames as fast as possible, 
giving you more frames in the totality. When it is bright, this is ~3fps, when it is dark Labs firmware can limit the exposure time to 1fps. If you have 4 minutes of totality, 
this 8-minute timelapse will result in ~32s playback time, with 4 seconds in the totality. Optional, you could limit the exposure to half a second for up to 8 seconds in totality.

#### Type 4 - Combining 2 & 3
For those who want to experiment further, Labs firmware allows you to script the camera, so that certain modes or actions can be performed at particular moments. 
The problem is we haven’t had a prior eclipse to practice on. The very experimental script would be to run type 2) capture until the totality, then switch to type 3), automatically 
creating two separate video timelapses. 

## Eclipse Time-lapse QR Code

Find 2024 eclipse times [**for your location**](https://nso.edu/for-public/eclipse-map-2024/)

<div id="eTYPE"><b>Capture Type:</b><br>
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="type1" name="type" value="1" checked> <label for="type1">Type 1 - 4s Night Lapse starting 15 minutes before totality</label><br>
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="type2" name="type" value="2" > <label for="type2">Type 2 - 10s Time Lapse, exposure limited, starting 1 hour before totality</label><br>
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="type3" name="type" value="3" > <label for="type3">Type 3 - Super optimized 1-3fps Night Lapse, start 2 minutes before totality</label><br>
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="type4" name="type" value="4" > <label for="type4">Type 4 - Experimental - switching between type 2 and 3</label>
</div>

Totality Start Time: <input type="range" style="width: 600px;" id="tlstrt" name="tlstrt" min="1" max="480" value="200"><label for="tlstrt"></label> <b id="starttext"></b>

Totality Length: <input type="range" style="width: 300px;" id="tlend" name="tlend" min="1" max="5" value="4"><label for="tlend"></label> <b id="lentext"></b> minutes &nbsp;&nbsp; Totality End Time: <b id="endtext"></b>
 
<div id="qrcode_txt" style="width: 360px">
  <center>
  <div id="qrcode"></div><br>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext"></em><br>
  <b><font color="#005CAC">Eclipse Timelapse</font></b>
  </center>
</div>
<br>
Share this QR Code as a URL: <small id="urltext"></small><br>
<button id="copyBtn">Copy URL to Clipboard</button>
      
**Compatibility:** Labs enabled HERO11 and HERO12 (likely some support with older Labs enoubled cameras, please test.) 

updated: March 19, 2024

[More features](..) for Labs enabled cameras

<script>
var once = true;
var qrcode;
var cmd = "mPdP!60SQ!1R";
var clipcopy = "";
var lasttimecmd = "";
var changed = false;

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

function pad(num, size) {
    var s = num+"";
    while (s.length < size) s = "0" + s;
    return s;
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


function dval(id) {
    var x;
	var val = "";
	{
		for (i = 1; i < 15; i++) { 
			var newid = id+i;
			if(document.getElementById(newid) !== null)
			{
				x = document.getElementById(newid).checked;
				if( x === true)
					val = document.getElementById(newid).value;
			}
		}
	}
	return val;
}




function timeLoop()
{
  if(document.getElementById("tlstrt") !== null)
  {
	var start = parseInt(document.getElementById("tlstrt").value);
	var startmins = start + 600;
	var caplen = parseInt(document.getElementById("tlend").value);
	var endmins = startmins + caplen;
	if(endmins >= 1440)
		endmins -= 1440;
		
	var starthourstime;
	var startminstime;	
	var endhourstime;
	var endminstime;
		
	starthourstime = Math.trunc(startmins / 60);
	startminstime = startmins - starthourstime * 60;	
	
	endhourstime = Math.trunc(endmins / 60);
	endminstime = endmins - endhourstime * 60;
		
	var stxt = pad(starthourstime, 2) + ":" + pad(startminstime, 2);
	var etxt = pad(endhourstime, 2) + ":" + pad(endminstime, 2);

	var type = dcmd("","type"); 
	if(type == "1")
	{
		startmins -= 15;
		starthourstime = Math.trunc(startmins / 60);
		startminstime = startmins - starthourstime * 60;	
		
		endmins += 15;
		endhourstime = Math.trunc(endmins / 60);
		endminstime = endmins - endhourstime * 60;
		
		var stime = pad(starthourstime, 2) + ":" + pad(startminstime, 2);
		var etime = pad(endhourstime, 2) + ":" + pad(endminstime, 2);
	
		cmd = "\"Type1\"" + "!" + stime + "N" + "!S!" + etime + "E";
	} 
	else if(type == "2")
	{
		startmins -= 60;
		starthourstime = Math.trunc(startmins / 60);
		startminstime = startmins - starthourstime * 60;	
		
		endmins += 60;
		endhourstime = Math.trunc(endmins / 60);
		endminstime = endmins - endhourstime * 60;
		
		var stime = pad(starthourstime, 2) + ":" + pad(startminstime, 2);
		var etime = pad(endhourstime, 2) + ":" + pad(endminstime, 2);
	
		cmd = "\"Type2\"" + "!" + stime + "N" + "!S!" + etime + "E";
	} 
	else if(type == "3")
	{
		startmins -= 2;
		starthourstime = Math.trunc(startmins / 60);
		startminstime = startmins - starthourstime * 60;	
		
		endmins += 2;
		endhourstime = Math.trunc(endmins / 60);
		endminstime = endmins - endhourstime * 60;
		
		var stime = pad(starthourstime, 2) + ":" + pad(startminstime, 2);
		var etime = pad(endhourstime, 2) + ":" + pad(endminstime, 2);
	
		cmd = "\"Type3\"" + "!" + stime + "N" + "!S!" + etime + "E";
	}
	else	
	{
		startmins -= 60;
		starthourstime = Math.trunc(startmins / 60);
		startminstime = startmins - starthourstime * 60;	
		
		endmins += 15;
		endhourstime = Math.trunc(endmins / 60);
		endminstime = endmins - endhourstime * 60;
		
		var stime = pad(starthourstime, 2) + ":" + pad(startminstime, 2);
		var etime = pad(endhourstime, 2) + ":" + pad(endminstime, 2);
	
		cmd = "\"Type4\"" + "!" + stime + "N" + "!S!" + etime + "E";
	}
	
	document.getElementById("starttext").innerHTML = stxt;
	document.getElementById("endtext").innerHTML = etxt;
	document.getElementById("lentext").innerHTML = caplen;
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
	clipcopy = "https://gopro.github.io/labs/control/set/?cmd=" + cmd + "&title=Eclipse%20Timelapse";
	document.getElementById("urltext").innerHTML = clipcopy;
	changed = false;
  }
  
  var t = setTimeout(timeLoop, 100);
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
}

makeQR();
setupButtons();
timeLoop();

</script>
