<script src="../../qrcodeborder.js"></script>
<style>
        #qrcode{
            height: 380px;
            width: 380px;
            margin: 0px;
        }
        div{
            height: 380px;
            width: 380px;
            margin: 0px;
            display: inline-block;
        }
</style>

## Full List the Settings Commands
Mode commands: 
 * **mV** - mode Video
 * **mP** - mode Photo
 * **mT** - mode Timelapse video
 * **mTW** - mode TimeWarp
 * **mPB** - mode Burst Photo 
 * **mPN** - mode Photo Night
 * **mNL** - mode Night-Lapse
 
Defaults modes (on power up): 
 * **dV** - last used Video mode
 * **dP** - last used Photo mode
 * **dT** - last used Timelapse mode
  
Resolutions: 
 * **r1080** - 1920x1080
 * **r1440** - 1920x1440
 * **r27** - for 2.7K 16x9
 * **r27T** - for 2.7K Tall the 4x3 mode
 * **r4** - for 4k 16x9
 * **r4T** - for 4k Tall the 4x3 mode

Frame rates: 
 * NTSC, 60Hz Anti-flicker
 * **p24** - 24 fps
 * **p30** - 30 fps
 * **p60** - 60 fps
 * **p120** - 120 fps
 * **p240** - 240 fps
 * PAL, 50Hz Anti-flicker
 * **p25** - 25 fps
 * **p50** - 50 fps
 * **p100** - 100 fps
 * **p200** - 200 fps
 * (only supports existing frame rates, so p65 or p1000 will be ignored.)

Note: Switching between PAL (25,50) and NTSC (30,60) frame rates has to be done on camera.

Time-lapse frame rates: 
 * **p2** (0.5s or 2Hz/2p capture)
 * **p1** (1s interval)
 * **p.2** (2s interval) 
 * **p.5** (5s interval) 
 * **p.10** through **p.60** (10 to 60s interval)

NightLapse frame rates: 
 * **p.120** through **p.1800** (2 minutes to 60 minute interval)

Color: 
 * **cF** - Color Flat
 * **cG** - Color GoPro

White Balance: 
 * **wA** - Auto White Balance
 * **w23** - 2300K While balance
 * **w28**, **w32**, **w40**, **w45**  - 2800K, 3200K, 4000K, 4500K
 * **w50**, **w55**, **w60**, **w65**  - 5000K, 5500K, 6000K, 6500K
 * **wN** - Native White Balance (sensor raw)

ISO Minimum and Maximum (set to together with format i(max)M(min)): 
 * **i1M1** - 100 ISO Max & Min
 * **i2M1** - 200 ISO Max with 100 ISO Min
 * **i16M8** - 1600 ISO Max with 800 ISO Min
 * **i32M1**  - 3200 ISO Mac with 100 ISO Min
 * **i64M16**  - 6400 ISO Mac with 1600 ISO Min

ISO Maximum and Shutter Lock (set to together format i(max)S(angle)): 
 * **i1S180** - 100 ISO Max with a 180 degree shutter angle
 * **i8S90** - 800 ISO Max with a 90 degree shutter angle
 * **i4S45** - 400 ISO Max with a 45 degree shutter angle
 * **i16S22** - 1600 ISO Max with a 22 degree shutter angle
 * **i1S22** - 100 ISO Max with a 22 degree shutter angle
 * **i1S0** - 100 ISO Max with an **Automatic** shutter angle
 * Angles between 22 and 1 degrees do have limited support. Experiment for higher shutter speeds.  You will need a good amount of light and/or a higher ISO.

EV Compensation: 
 * **x0** - EV 0 default
 * **x-.5** - EV -0.5
 * **x.5** - EV +0.5
 * **x-1** - EV -1.0
 * **x1** - EV +1.0
 * **x-1.5** - EV -1.5
 * **x1.5** - EV +1.5
 * **x-2** - EV -2.0 
 * **x2** - EV +2.0
 
Sharpness: 
 * **sL** - Low
 * **sM** - Medium
 * **sH** - High
 
Night Photo exposure time: 
 * **eA** - Auto exposure
 * **e2** - 2 second shutter
 * **…** 
 * **e30** - 30 second shutter

Feature with off and on commands:

- EIS (Hypersmooth stabilization): **e0** - off, **e** or **e1** - on
- GPS Active: **g0** - off, **g** or **g1** - on
- Quick Capture: **q0** - off, **q** or **q1** - on
- Voice Commands: **v0** - off, **v** or **v1** - on

Same further option (‘o’) commands

- Camera Auto Off - **oC** - Never, **oC5** - 5min ... **oC30** - 30min
- Screen Brightness - **oB0** … **oB9** - (100%)
- Screen Auto Off - **oS** - Never, **oC1** - 1min ... **oC3** - 3min
- Camera Orientation - **oR0** - Auto, **oR1** - Up, **oR2** - Down
- WiFi Connection - **oW0** - off, **oW1** - on
- LED control - **oD** - all off, **oD2** - some on, **oD4** - all on
- Beep Volume - **oV0** - Mute, **oV1** ... **oV9** (min through max.)


# Experiment Here
## Typing-in Your Custom Mode:

<div id="qrcode"></div>
Custom Mode: <input type="text" id="tryit" value=""><br>


## ver 1.01
[BACK](..)


<script>
var once = true;
var qrcode;
var cmd = "";

function makeQR() {	
  if(once == true)
  {
    qrcode = new QRCode(document.getElementById("qrcode"), 
    {
      text : "\"Try It\"",
      width : 400,
      height : 400,
      correctLevel : QRCode.CorrectLevel.M
    });
    once = false;
  }
}

function timeLoop()
{
  if(document.getElementById("tryit") != null)
  {
    cmd = document.getElementById("tryit").value;
	if(cmd.length == 0)
	{
		cmd = "\"Try It\"";
	}
  }
  else
  {
    cmd = "\"Try It\"";
  }

  qrcode.clear(); 
  qrcode.makeCode(cmd);
  var t = setTimeout(timeLoop, 50);
}

function myReloadFunction() {
  location.reload();
}

makeQR();
timeLoop();

</script>
