# Precision Date and Time (UTC)

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

Simply point your Labs enabled camera at this animated QR Code, to set your date and time very accurately to UTC time. This is particularly useful for multi-camera shoots, as it helps synchronize the timecode between cameras. As the camera's internal clock will drift slowly over time, use this QR Code just before your multi-camera shoot for the best synchronization. 

<center>
<div id="qrcode"></div>
<br>
</center>
QR Command: <b id="qrtext"></b>

Compatibility: Labs enabled HERO5 Session, HERO7-13, MAX and BONES 
        
updated: September 10, 2024

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
function timeLoop()
{
  var today;
  var yy,mm,dd,h,m,s;
  var ms;
  
  today = new Date();
  yy = today.getUTCFullYear() - 2000;
  mm = today.getUTCMonth() + 1;
  dd = today.getUTCDate();
  h = today.getUTCHours();
  m = today.getUTCMinutes();
  s = today.getUTCSeconds();
  ms = today.getUTCMilliseconds();
  yy = padTime(yy);
  mm = padTime(mm);
  dd = padTime(dd);
  h = padTime(h);
  m = padTime(m);
  s = padTime(s);
  //ms = Math.floor(ms / 10); // hundredths
  ms = padTime1000(ms);

  cmd = "oT" + yy + mm + dd + h + m + s + "." + ms + "oTI" + id;
  qrcode.clear(); 
  qrcode.makeCode(cmd);
  document.getElementById("qrtext").innerHTML = cmd;
 
  var t = setTimeout(timeLoop, 30);
}

function myReloadFunction() {
  location.reload();
}

makeQR();
timeLoop();

</script>
