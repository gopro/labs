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
<div id="qrcode"></div>
<br>
</center>
QR Command: <b id="qrtext"></b>

**Compatibility:** Labs enabled HERO5 Session, HERO7, HERO8, HERO9, HERO10, HERO11, MAX and BONES 
        
updated: April 24, 2023

[Learn more](..) on QR Control

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

function isDST(d) {
    let jan = new Date(d.getFullYear(), 0, 1).getTimezoneOffset();
    let jul = new Date(d.getFullYear(), 6, 1).getTimezoneOffset();
    return Math.max(jan, jul) === d.getTimezoneOffset();    
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
  h = padTime(h);
  m = padTime(m);
  s = padTime(s);
  ms = Math.floor(ms / 10); // hundredths
  ms = padTime(ms);
  
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
 
  var t = setTimeout(timeLoop, 30);
}

function myReloadFunction() {
  location.reload();
}

makeQR();
setTZ();
timeLoop();

</script>
