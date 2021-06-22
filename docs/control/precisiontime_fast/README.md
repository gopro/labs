# Precision Date and Time (Local Time + 0.1%)

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

Simply point your Labs enabled camera at this animated QR Code, to set your date and time very accurately to local time. This is particularly useful for multi-camera shoots, as it helps synchronize the timecode between cameras. As the camera's internal clock will drift slowly over time, use this QR Code just before your multi-camera shoot for the best synchronization. 

<center>
<div id="qrcode"></div>
<br>
</center>
QR Command: <b id="qrtext"></b>

## ver 1.0
[BACK](..)

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
  var yy,mm,dd,h,m,s,f;
  var ms;
  
  today = new Date();
  yy = today.getFullYear() - 2000;
  mm = today.getMonth() + 1;
  dd = today.getDate();
  h = today.getHours();
  m = today.getMinutes();
  s = today.getSeconds();
  ms = today.getMilliseconds();
  
  f = (ms/1000) + s + m*60 + h*3600;
  f = f * 1001;
  f = f / 1000;

  h = Math.floor(f / 3600);
  f -= h * 3600;
  m = Math.floor(f / 60);
  f -= m * 60;
  s = Math.floor(f);
  f -= s;
  ms = f * 1000.0;    
  
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
