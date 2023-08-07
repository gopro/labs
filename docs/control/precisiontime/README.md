# Precision Date and Time (Local)

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


**Timezone** <input type="range" id="tzid" name="tzid" min="-48" max="56" value="0" style="width: 300px;"><label for="tzid"></label>&nbsp;&nbsp;<b id="tztext"></b> hour <b id="tzmin"></b> minute<br>

**Daylight Saving Time** <input type="checkbox" id="tdid" name="tdid"> <label for="tdid">Active</label><br>

Simply point your Labs enabled camera at this animated QR Code, to set your date and time very accurately to local time. This is particularly useful for multi-camera shoots, as it helps synchronize the timecode between cameras. As the camera's internal clock will drift slowly over time, use this QR Code just before your multi-camera shoot for the best synchronization. 

<center>
<div id="qrcode"></div><br>
TC 24: <b id="tctext24"></b><br>
TC 25: <b id="tctext25"></b><br>
NDF 30: <b id="tctext30"></b>   DF 30: <b id="dftext30"></b><br>
TC 50: <b id="tctext50"></b><br>
NDF 60: <b id="tctext60"></b>   DF 60: <b id="dftext60"></b><br>
</center>
QR Command: <b id="qrtext"></b>

**Compatibility:** Labs enabled HERO5 Session, HERO7, HERO8, HERO9, HERO10, HERO11, MAX and BONES 
        
updated: Aug 5, 2023

[Learn more](..) back to QR Controls

<script>
var once = true;
var qrcode;
var cmd = "";
var id = 0;


function id5() {  // 5 characters, so up to 17-bit ID
  return ([1111]+1).replace(/1/g, c =>
    (c ^ crypto.getRandomValues(new Uint8Array(1))[0] % 10 >> c / 4).toString()
  );
}

function getMachineId() 
{
    let machineId = localStorage.getItem('MachineId');
    if (!machineId) {
    	//machineId = crypto.randomUUID();
        machineId = id5();
        localStorage.setItem('MachineId', machineId);
    }
    return machineId;
}

function isDaylightSavingTime(date) {
  // Get the time zone offset for the given date
  const timezoneOffsetMinutes = date.getTimezoneOffset();

  // Get the standard time zone offset for the same date but in January (non-DST period)
  const januaryOffsetMinutes = new Date(date.getFullYear(), 0, 1).getTimezoneOffset();

  // If the current offset is greater than the standard offset, it is DST
  return timezoneOffsetMinutes < januaryOffsetMinutes;
}

function isDST(date) {
  // Get the time zone offset for the given date
  const timezoneOffsetMinutes = date.getTimezoneOffset();

  // Get the standard time zone offset for the same date but in January (non-DST period)
  const januaryOffsetMinutes = new Date(date.getFullYear(), 0, 1).getTimezoneOffset();

  // If the current offset is greater than the standard offset, it is DST
  return timezoneOffsetMinutes < januaryOffsetMinutes;
}

function setTZ() {	
  var today = new Date();
  var tz,td = 0;  
  tz = today.getTimezoneOffset();
  
  if(isDST(today))
     td = 1;
  
  if(document.getElementById("tzid") !== null)
  {
	document.getElementById("tzid").value = -tz/15;	
	
	var h = Math.trunc(tz/60);
	var m = tz - h*60;
	document.getElementById("tztext").innerHTML = -h;	
	document.getElementById("tzmin").innerHTML = -m;	
  }
  
  
  if(document.getElementById("tdid") !== null)
  {
	if(td) {
		document.getElementById("tdid").checked = true;
	}
  }
}

function makeQR() {	
  if(once === true)
  {
  	id = getMachineId();  // 5 character 10-base, so up to 17-bit ID
    qrcode = new QRCode(document.getElementById("qrcode"), 
    {
      text : "oT0",
      width : 360,
      height : 360,
      correctLevel : QRCode.CorrectLevel.M
    });
    once = false;
  }
}
function padTime(i) {
  if (i < 10) {i = "0" + i;}  // add zero in front of numbers < 10
  return i;
}
function padTime1000(i) {
  if (i >= 10 && i < 100) {i = "0" + i;}  // add zero in front of numbers < 100
  else if (i < 10) {i = "00" + i;}  // add zero in front of numbers < 10
  return i;
}


function nonDropframeToDropframe(timecode, fps) {
	// Extract hours, minutes, seconds, and frames from the timecode
	const [hours, minutes, seconds, frames] = timecode.split(':').map(Number);

	// Calculate the total number of frames
	const totalFrames = hours * 3600 * fps + minutes * 60 * fps + seconds * fps + frames;

	var i=0,h=0,m=0,s=0,f=0;
	
	for(i=0;i<totalFrames-fps;)
	{
		i += fps-f;
		f += fps-f;
		
		if(f<fps-1)
		{
			f++;	
		}
		else
		{ 
			f = 0;
			s++;
			
			if(Math.trunc(m/10)*10 != m && s == 60)
			{
			    // drop frame every minute except every 10 minutes
			    if(fps == 60)
			    	f = 4;
			    else
			        f = 2;
			}
			if(s == 60) 
			{
				s = 0;
				m++;
				if(m == 60)
				{
					m = 0;
					h++;
				}
			}
		} 
	}
	
	
	for(; i<totalFrames; i++)
	{
		if(f<fps-1)
		{
			f++;	
		}
		else
		{ 
			f = 0;
			s++;
			
			if(Math.trunc(m/10)*10 != m && s == 60)
			{
			    // drop frame every minute except every 10 minutes
			    if(fps == 60)
			    	f = 4;
			    else
			        f = 2;
			}
			if(s == 60) 
			{
				s = 0;
				m++;
				if(m == 60)
				{
					m = 0;
					h++;
				}
			}
		} 
	}

	// Format the dropframe timecode
	const dropframeTimecode = padTime(h)+":"+padTime(m)+":"+padTime(s)+";"+padTime(f);

	return dropframeTimecode;
}

function timeLoop()
{
  var today;
  var yy,mm,dd,h,m,s;
  var ms,tz;
  
  today = new Date();
  yy = today.getFullYear() - 2000;
  mm = today.getMonth() + 1;
  dd = today.getDate();
  h = today.getHours();
  m = today.getMinutes();
  s = today.getSeconds();
  ms = today.getMilliseconds();
  yy = padTime(yy);
  mm = padTime(mm);
  dd = padTime(dd);
  
  var tmilli = (ms/1000) + s + (m * 60) + (h * 60 * 60);
  tmilli /= 1.001; //29.97 vs 30.0
  var fixtmilli = tmilli;
  
  h = padTime(h);
  m = padTime(m);
  s = padTime(s);
  //ms = Math.floor(ms / 10); // hundredths
  ms = padTime1000(ms);
  
  if(document.getElementById("tzid") !== null)
  {
	tz = parseInt(document.getElementById("tzid").value) * 15;	

	var H = Math.trunc(tz/60);
	var M = tz - H*60;
	document.getElementById("tztext").innerHTML = H;	
	document.getElementById("tzmin").innerHTML = M;	
	
	if(Math.trunc(tz/60) == tz/60)
		tz = tz/60;  // only need hours when precise.
  }

  var td = 0;
  if(document.getElementById("tdid") !== null) 
  {
	if(document.getElementById("tdid").checked) {
		td = 1;
	}
  }

  cmd = "oT" + yy + mm + dd + h + m + s + "." + ms + "oTD" + td + "oTZ" + tz + "oTI" + id;
  qrcode.clear(); 
  qrcode.makeCode(cmd);
  document.getElementById("qrtext").innerHTML = cmd;
  
  var tc25 = h + ":" + m + ":" + s + ":" + padTime(Math.trunc(ms * 25 / 1000));
  var tc50 = h + ":" + m + ":" + s + ":" + padTime(Math.trunc(ms * 50 / 1000));
   
  h = Math.trunc(tmilli / (60 * 60));  tmilli -= h * (60 * 60);
  m = Math.trunc(tmilli / (60 ));  tmilli -= m * (60);
  s = Math.trunc(tmilli);  tmilli -= s;
  ms = Math.trunc(tmilli * 1000);
  
  h = padTime(h);
  m = padTime(m);
  s = padTime(s);
   
  var tc24 = h + ":" + m + ":" + s + ":" + padTime(Math.trunc(ms * 24 / 1000));
  var tc30 = h + ":" + m + ":" + s + ":" + padTime(Math.trunc(ms * 30 / 1000));
  var tc60 = h + ":" + m + ":" + s + ":" + padTime(Math.trunc(ms * 60 / 1000));
 
  var df30 = nonDropframeToDropframe(tc30, 30);
  var df60 = nonDropframeToDropframe(tc60, 60);
 
  document.getElementById("tctext24").innerHTML = tc24;  
  document.getElementById("tctext25").innerHTML = tc25;  
  document.getElementById("tctext30").innerHTML = tc30;  
  document.getElementById("dftext30").innerHTML = df30;  
  document.getElementById("tctext50").innerHTML = tc50;  
  document.getElementById("tctext60").innerHTML = tc60;
  document.getElementById("dftext60").innerHTML = df60;
   
  var t = setTimeout(timeLoop, 10);
}

function myReloadFunction() {
  location.reload();
}

makeQR();
setTZ();
timeLoop();

</script>
