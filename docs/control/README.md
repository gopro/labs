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
* **HERO7/8/9/10/MAX** - Start capture only when traveling fast with [**GPS Speed Triggers**](./speedtrigger) 
* **HERO7/8/9/10/MAX** - Use the [**USB Power Trigger**](./usb) to start and stop the camera (pseudo dash-cam mode)
* **HERO9/10/Bones** - Start capture using [**Sound Pressure Level Trigger**](./spltrigger)

### Extended Time-lapse Features 
* Start a 24-hour long time-lapse or greater with [**Extra Long Time-lapses**](./longtimelapse)
* Use your GoPro to time-lapse [**Construction Projects**](./construction)
* Schedule your camera to automatically [**Time-lapse Sunsets and Sunrises**](./solartimelapse)
* **HERO9/10/Bones** - Daily Time-lapse with [**auto upload**](./dailytl) (GoPro Subscription required)

### Video Alteration Features
* **HERO8/9/10/MAX/Bones** - Set the [**Max Shutter Angle**](./maxshut) for control over stabilization in low light
* **HERO8/9/MAX** - Add text like Date and Time with [**Video 'Burn-in' Overlays**](./overlays)
* **HERO8/9** Set the [**Exposure Lock**](./explock) via QR Code
* **HERO9** - Add a logo or any small image to your video with [**Logo Overlays**](./logo)

### Miscellaneous Features
* **HERO7/8/9/10/MAX** - Enable [**Archive Mode**](./archive), a video only capture mode for loaned cameras 
* **HERO8/9/10/Bones** - Configure your camera for [**Live-streaming**](./rtmp) via QR Code
* **HERO9/10** - Sync multiple cameras' timecode via [**GPS Time Synchronization**](./gpssync)
* **HERO8/9/10/MAX/Bones** - Experiment with larger chapter sizes with [**12 GB Chapters**](./chapters)
* **HERO8/9/10/MAX/Bones** - Multi-camera users, label you media with [**Altered File Naming**](./basename)
* **HERO9/10** - Timecode Support via [**LTC**](./ltc) over audio line-in using Media Mod 
* **HERO10** - Support for Adobe Premiere Pro™ style [**Proxy Files**](./proxies) 
* **HERO9** - Enable media [**encryption**](./encrypt) for increased security
* <span style="color:steelblue">**UPDATED**</span> Many more [**extensions**](./extensions) via QR Code

### Metadata Extraction
* **All GPMF Enabled Cameras** - [**Read metadata**](./metadata) stored within headers of most GoPro media files.

## Forum Discussions 

Please join the [**GoPro Labs Discussion**](https://community.gopro.com/s/gopro-labs)

## The Commands Under The Hood 

On QR Control Instructions page, one of the first demo QR Code was surfing example, using 1440p and 60fps with some custom Protune settings. The QR Code used this command string: **mVr1440p60tw55x.5**. While some of that seems like 1440p60, here is a full breakdown of how that command works:

* **mV** - is shorthand for mode Video - this is the same a swiping the camera to use video mode.
* **r1440** - set resolution to 1440 - same as using the LCD to set 1440p
* **p60** - set fps to 60 
* **t** - Protune on
* **w55** - white balance to 5500K
* **x.5** - exposure compensation is set to 0.5
  
Any of these can be used on their own, or in different order, however the order can have meaning.  If I enable protune with a ‘t’ command, while in the Photo mode, then switched to video, the video will be in whatever mode setting you had previously. The individual commands within a QR Code are performed in order, just like you would when using the touch LCD.

All setting commands start with a lowercase character, followed by either uppercase or numbers for the parameters, the next lowercase character is the next setting command. Below are some additional setting commands with their range of parameters.

## The Full List of [**Settings Commands**](./settings)

## The Full List of [**Action Commands**](./actions)

Subset of commands for the [**HERO 5 Session**](./session5). Limit to camera settings, date & time, scheduled captures and ownership information.


### ver 1.24
updated: Apr 19, 2022


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