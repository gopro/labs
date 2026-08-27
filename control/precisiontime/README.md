# Precision Date and Time (Local)

<script src="../../jquery.min.js"></script>
<script src="../../qrcode_canvas.js"></script>
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
<canvas id="qr-canvas" width="360" height="360" style="image-rendering: pixelated;"></canvas>
<br>
TC 24: <b id="tctext24"></b><br>
TC 25: <b id="tctext25"></b><br>
NDF 30: <b id="tctext30"></b>   DF 30: <b id="dftext30"></b><br>
TC 50: <b id="tctext50"></b><br>
NDF 60: <b id="tctext60"></b>   DF 60: <b id="dftext60"></b><br>
</center>
QR Command: <b id="qrtext"></b><br>
fps: <b id="fpstext"> Hz<br>

**Compatibility:** Labs enabled HERO5 Session, HERO7-13, MAX and BONES 
		
updated: May 16, 2025

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
  {
     td = 1;
     tz += 60;
  }
  
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

let qrCanvas, qrCtx;

function makeQR() {
  qrCanvas = document.getElementById("qr-canvas");
  qrCtx = qrCanvas.getContext("2d");
}

function renderQRToCanvas(data) {
  const qr = qrcode(0, 'M');  // Type number auto
  qr.addData(data);
  qr.make();

  const count = qr.getModuleCount();
  const size = qrCanvas.width;
  const tileSize = Math.floor(size / (count+2));
  
  qrCtx.clearRect(0, 0, size, size);
  for (let row = 0; row < count; row++) {
    for (let col = 0; col < count; col++) {
      qrCtx.fillStyle = qr.isDark(row, col) ? "#000" : "#fff";
      qrCtx.fillRect((col+1) * tileSize, (row+1) * tileSize, tileSize, tileSize);
    }
  }
}


function makeQROld() {	
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
			
			if(s == 60)
			{
				if(Math.trunc(m/10)*10 != m)
				{
					// drop frame every minute except every 10 minutes
					if(fps == 60)
						f = 4;
					else
						f = 2;
				}
				
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




function nonDropframeToDropframeFast(timecode, fps) {
	// Extract hours, minutes, seconds, and frames from the timecode
	const [hours, minutes, seconds, frames] = timecode.split(':').map(Number);

	// Calculate the total number of frames
	const totalFrames = hours * 3600 * fps + minutes * 60 * fps + seconds * fps + frames;

	var i=0,h=0,m=0,s=0,f=0;
	
	if(fps == 30 || fps == 60)
	{
		var mult = Math.trunc(fps/30);
		while(i+18000*mult <= totalFrames) /// every 10 minutes adds 18*mult frames 
		{
			i += 18000*mult
			f += 18*mult;
			m += 10;
		}
	
		while(f>=fps)
		{
			s++; f-=fps;
		}
		while(s>=60)
		{
			m++; s-=60;
		}
		while(m>=60)
		{
			h++; m-=60;
		}
	}

	for(;i<totalFrames-fps;)
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
			
			if(s == 60)
			{
				if(Math.trunc(m/10)*10 != m)
				{
					// drop frame every minute except every 10 minutes
					if(fps == 60)
						f = 4;
					else
						f = 2;
				}
				
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
			
			if(s == 60)
			{
				if(Math.trunc(m/10)*10 != m)
				{
					// drop frame every minute except every 10 minutes
					if(fps == 60)
						f = 4;
					else
						f = 2;
				}
				
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

function setText(id, value) {
  const el = document.getElementById(id);
  if (el && el.innerHTML !== value)
    el.innerHTML = value;
}


var starttime = 0;
var updates = 0;
var tlast = 0;
var fps = "1";

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
  
  var tnow = performance.now() / 1000;
  
  var tmilli = (ms/1000) + s + (m * 60) + (h * 60 * 60);
  tmilli /= 1.001; //29.97 vs 30.0
  var fixtmilli = tmilli;
  
  h = padTime(h);
  m = padTime(m);
  s = padTime(s);
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
  
  renderQRToCanvas(cmd);
  //qrcode.clear(); 
  //qrcode.makeCode(cmd);
  
  setText("qrtext", cmd);
  
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
 
  var df30 = nonDropframeToDropframeFast(tc30, 30);
  var df60 = nonDropframeToDropframeFast(tc60, 60);
 
  setText("tctext24", tc24);
  setText("tctext25", tc25);
  setText("tctext30", tc30);
  setText("dftext30", df30);
  setText("tctext50", tc50);
  setText("tctext60", tc60);
  setText("dftext60", df60);
  
  var tdelta = tnow - tlast;
  if(starttime == 0)
  {
    updates = 0;
    starttime = tnow;
  }
  else
  {
    updates = updates + 1;
    if(updates > 5)
      fps = updates / (tnow - starttime);
  }
  
  setText("fpstext", Math.trunc(fps*10)/10);
   
  if(updates > 400)
  {
    updates = 200;
    starttime += (tnow - starttime)/2;
  }
  if(tdelta > 0.2 && tlast > 0)
  {
    updates = 0;
	starttime = tnow;
  }
  tlast = tnow;
  
  requestAnimationFrame(timeLoop);
}

function myReloadFunction() {
  location.reload();
}

makeQR();
setTZ();
timeLoop();

</script>
