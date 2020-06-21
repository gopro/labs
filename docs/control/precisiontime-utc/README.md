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

# Precision Date and Time in UTC

Similar to its sibling, [Precision Date and Time](../precisiontime), but this set your camera to UTC time, as current Gopro firmware does not support timezone nor DST, and setting your Gopro to UTC time [will fix](https://community.gopro.com/t5/Cameras/Time-zone-set-incorrectly/td-p/265136) time problem with any Photo/Video manager, including Google Photo.

Simply point your Labs enabled camera at this animated QR Code, to set your date and time very accurately. This is particularly useful for multi-camera shoots, as it helps synchronize the timecode between cameras. As the camera's internal clock will drift slowly over time, use this QR Code just before your multi-camera shoot for the best synchronization. 

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

function padTrim2Digits(i) {
  if (i < 10) {
    return "0" + i;
  }
  return ("" + i).substr(-2);
}

function timeLoop()
{
  
  const today = new Date();
  const year = today.getUTCFullYear();
  const month = today.getUTCMonth() + 1;
  const day = today.getUTCDate();
  const hour = today.getUTCHours();
  const minute = today.getUTCMinutes();
  const second = today.getUTCSeconds();
  const milliseconds = today.getUTCMilliseconds();
  const centisecond = Math.floor(milliseconds / 10);

  cmd = "oT" + padTrim2Digits(year) + padTrim2Digits(month) + padTrim2Digits(day) + padTrim2Digits(hour) + padTrim2Digits(minute) + padTrim2Digits(second) + "." + padTrim2Digits(centisecond);

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
