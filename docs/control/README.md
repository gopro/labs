# QR Control

<script src="../jquery.min.js"></script>
<script src="../qrcodeborder.js"></script>
<style>
        #qrcode{
            width: 100%;
        }
        div{
            width: 100%;
            display: inline-block;
        }
</style>

### Configuration Commands for All Labs Enabled Cameras
* Set camera modes with the [**Customizable QR Code Creator**](./custom) and here optimized for [**Bones**](../bones)
and as a mobile app:<br>
[![google play](google-play-823.png)](https://play.google.com/store/apps/details?id=com.miscdata.qrcontrol)
[![apple app store](apple-store-823.png)](https://apps.apple.com/us/app/gopro-app/id1518134202)
* Set Precision [**Local Date and Time**](./precisiontime) or [**UTC Time**](./precisiontime_utc) or
* <div id="qrcode">Set Local Time:</div>
* Personalize your cameras with [**Owner Information**](./owner)

### Capture Triggers 
* Use the image sensor for [**Motion Detection**](./motion), capturing only scenes with motion
* Capture using [**IMU Motion Triggers**](./imutrigger) for detecting camera movement
* **HERO7-11/MAX** - Start capture only when traveling fast with [**GPS Speed Triggers**](./speedtrigger) 
* **HERO7-11/MAX** - Use the [**USB Power Trigger**](./usb) to start and stop the camera (pseudo dash-cam mode)
* **HERO9-11/Bones** - Start capture using [**Sound Pressure Level Trigger**](./spltrigger)

### Extended Time-lapse Features 
* Start a 24-hour long time-lapse or greater with [**Extra Long Time-lapses**](./longtimelapse)
* **HERO8-11/Bones** - [**Daily Time-lapse**](./dailytl) with optional upload
* Schedule your camera to automatically [**Time-lapse Sunsets and Sunrises**](./solartimelapse)
* **Depricated** - This style is less reliable than the above types [**Daily Long Time-lapses**](./construction)

### Video Alteration Features
* **HERO8-11/MAX/Bones** - Set the [**Max Shutter Angle**](./maxshut) for control over stabilization in low light
* **HERO8-11/MAX** - Add text like Date and Time with [**Video 'Burn-in' Overlays**](./overlays)
* **HERO8-11** - Add a logo or any small image to your video with [**Logo Overlays**](./logo)

### Miscellaneous Features
* **HERO7-11/MAX** - Enable [**Archive Mode**](./archive), a video only capture mode for loaned cameras 
* **HERO8-11/Bones** - Configure your camera for [**Live-streaming**](./rtmp) via QR Code
* **HERO9-11** - Sync multiple cameras' timecode via [**GPS Time Synchronization**](./gpssync)
* **HERO8-10/MAX/Bones** - Enable larger chapter sizes [**12 GB Chapters**](./chapters). Standard on HERO11
* **HERO8-11/MAX/Bones** - Multi-camera users, label you media with [**Altered File Naming**](./basename)
* **HERO9-11** - Timecode Support via [**LTC**](./ltc) over audio line-in using Media Mod 
* **HERO10-11** - Support for Adobe Premiere Pro™ and DaVinci style [**Proxy Files**](./proxies) 
* **HERO9** - Experimental on camera real-time [**Media Encryption**](./encrypt) during capture
* **ALL** - <span style="color:steelblue">**UPDATED**</span> Dozens more [**extensions**](./extensions) via QR Code

### Metadata Extraction
* **ALL** - [**Read metadata**](./metadata) stored within headers of most GoPro media files.

<!--
### Features Phased Out
If we don't see feedback on features it may not get ported to the next camera. If you are using a Labs feature, please provide feedback.
* **HERO8/9** Set the [**Exposure Lock**](./explock) via QR Code
* **HERO9** - Enable media [**encryption**](./encrypt) for increased security
* Subset of commands for the [**HERO 5 Session**](./session5). Limit to camera settings, date & time, scheduled captures and ownership information. -->

## Forum Discussions and Feedback 
* For GoPro Labs discussions, feature requests, and help: [**Labs Discussion on GitHub**](https://github.com/gopro/labs/discussions)
* For obmissions or errors within these Pages: [**GitHib Labs Issues**](https://github.com/gopro/labs/issues)

## Firmware Release Notes 
An incomplete set of [**Release Notes**](./notes) 

## The Commands Under The Hood 
Technical information on the [**Labs command language**](./tech)

## GoPro Labs
[**Labs start on GitHub**](https://gopro.github.io/labs).

updated: April 7, 2023


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
  


  cmd = "oT" + yy + mm + dd + h + m + s;
  qrcode.clear(); 
  qrcode.makeCode(cmd);
 
  var t = setTimeout(timeLoop, 500);
}

function myReloadFunction() {
  location.reload();
}

makeQR();
timeLoop();

</script>