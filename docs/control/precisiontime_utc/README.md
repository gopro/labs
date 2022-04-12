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

Compatibility: Labs enabled HERO5 Session, HERO7, HERO8, HERO9, HERO10, MAX and BONES 
        
## ver 1.03
updated: Apr 12, 2022

[Learn more](..) on QR Control

<script>
var once = true;
var qrcode;
var cmd = "";

function makeQR() {	
  if(once === true)
  {
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
  ms = Math.floor(ms / 10); // hundredths
  ms = padTime(ms);

  cmd = "oT" + yy + mm + dd + h + m + s + "." + ms;
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
