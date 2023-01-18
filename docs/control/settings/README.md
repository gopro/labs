## Full List the Settings Commands

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

Mode commands: 
 * **mV** - mode Video
 * **mP** - mode Photo
 * **mT** - mode Timelapse video (\*)
 * **mTP** - mode Timelapse Photo (\*)
 * **mTW** - mode TimeWarp
 * **mPB** - mode Photo Burst 
 * **mPN** - mode Photo Night
 * **mNL** - mode Night-Lapse Video (\*)
 * **mNP** - mode Night-Lapse Photo (\*)
 * **mL** - mode Live-Burst Photo (HERO10/11 only)
 * **mST** - mode Star Trails (HERO11 only)
 * **mLP** - mode Light Painting (HERO11 only)
 * **mLT** - mode Vechical Lights (HERO11 only)
 
<b>\* Time/Night-Lapse modes:</b> The camera defaults to having presets for only one time-lapse mode and one night-lapse mode, yet both modes have two configurations (video or photo.) For all QR Code mode commands to work, a preset is needed for every mode you wish to use. e.g. If you only have a preset for night-lapse video (NLV), the QR command for NLV will work, but will not for night-lapse photo (NLP). To solve this, create a new preset for NLP, and both video and photo night-lapse commands will work.
 
Defaults modes (on power up): 
 * **dL** - last used mode
 * **dV** - last used Video mode
 * **dP** - last used Photo mode
 * **dT** - last used Timelapse mode
  
Resolutions: 
 * **r1080** - 1920x1080
 * **r1440** - 1920x1440
 * **r27** - for 2.7K 16x9
 * **r27T** - for 2.7K Tall the 4x3 mode
 * **r3** - 3K 360° for GoPro MAX
 * **r4** - 4k 16x9
 * **r4T** - 4k Tall, the 4x3 mode
 * **r4X** - 4k Extreme, the 8x7 mode (H11)
 * **r5** - 5k for HERO5 and 5K 360° for GoPro MAX
 * **r5T** - 5k Tall, the 4x3 mode
 * **r5X** - 5k Extreme, the 8x7 mode (H11)
 
Frame rates: 
 * **p24** - 24 fps
 * **p25** - 25 fps
 * **p30** - 30 fps
 * **p50** - 50 fps
 * **p60** - 60 fps
 * **p100** - 100 fps
 * **p120** - 120 fps
 * **p200** - 200 fps
 * **p240** - 240 fps
 * (only supports existing frame rates, so p65 or p1000 will be ignored.)
  
Time-lapse frame rates: 
 * **p2** (0.5s or 2Hz/2p capture)
 * **p1** (1s interval)
 * **p.2** (2s interval) 
 * **p.5** (5s interval) 
 * **p.10** through **p.60** (10 to 60s interval)

NightLapse frame rates: 
 * **p.120** through **p.1800** (2 minutes to 60 minute interval)

Lens - FOV: 
 * **fN** - Narrow
 * **fM** - Medium
 * **fW** - Wide
 * **fX** - SuperMax Wide (Max Lens Mod)
 * **fH** - Horizonal Level + Linear (H9/10/11)
 * **fV** - HyperView (H11)
 
Audio (Raw controls): 
 * **aL** - Low Processing
 * **aM** - Medium Processing
 * **aH** - High Processing

Bitrate: 
 * **b0** - Standard Bitrate
 * **b1** - High Bitrate

Color: 
 * **cF** - Color Flat
 * **cG** - Color Vibrant
 * **cN** - Color Natural (H10/11)

Depth (H11 only): 
 * **d0** or **d8** - 8-bit color
 * **d1** or **d10** - 10-bit color

EIS (Hypersmooth control): 
 * **e0** - Off     
 * **e1** - On
 * **e2** - High
 * **e3** - Boost
 * **e4** - Auto 

White Balance: 
 * **wA** - Auto White Balance
 * **w23** - 2300K White balance
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
 * **x2** - EV +2.0<br>
 on some cameras models you can extend this to larger amounts (beyond the range the camera menu supports).
 * **x-5** - EV -5.0
 * **x3** - EV +3.0
 
Sharpness: 
 * **sL** - Low
 * **sM** - Medium
 * **sH** - High
 
Night Photo exposure time: 
 * **eA** - Auto exposure
 * **e2** - 2 second shutter
 * **…** 
 * **e30** - 30 second shutter

GoPro MAX Shooting Modes
 * **mH** - mode Hero
 * **mHF** - mode Hero Front
 * **mHR** - mode Hero Rear
 * **m3** - mode 360°
 * **m3F** - mode 360° front on LCD
 * **m3R** - mode 360° rear on LCD
 * **mF** - mode monitor Front lens
 * **mR** - mode monitor Rear lens

Feature with off and on commands:
- EIS (Hypersmooth stabilization): **e0** - off, **e** or **e1** - on, **e2** - High, **e3** Boost, **e4** Auto (H11)
- GPS Active: **g0** - off, **g** or **g1** - on
- Quick Capture: **q0** - off, **q** or **q1** - on
- Voice Commands: **v0** - off, **v** or **v1** - on

Option (‘o’) commands:
- Brightness of the LCDs - **oB0** … **oB9** - (100%)
- Camera Auto Off - **oC** - Never, **oC0** - default, **oC1** - 1min, **oC5** - 5min, **oC15** - 15min, **oC30** - 30min
- LCDs off now - **oDO**
- LED control - **oD** - all off, **oD2** - some on, **oD4** - all on
- Extern Audio options - **oE1** - Standard Mic, **oE2** - Standard+ Mic, **oE3** - Powered Mic, **oE4** - Powered+ Mic, **oE5** - Line In (HERO10/11 only)
- Front Screen control - **oFxy** - (see list below)
- Language - **oL**x - **0** English USA, **01** English UK, **02** English Aus, **03** English India, **1** German, **2** French, **3** Italian, **4** Spanish, **5** Chinese, **6** Japanese, **7** Korean, **8** Portuaguese, **9** Russian, **91** Swedish
- Rotation, Camera Orientation - **oR0** - Auto, **oR1** - Up, **oR2** - Down
- Screen Auto Off - **oS** - Never, **oS1** - 1min ... **oS3** - 3min
- Shortcut Menu on LCD - **oSA**x - Upper Left, **oSB**x - Lower Left, **oSC**x - Upper Right, **oSD**x - Lower Right, **oSR** - reset. Where x is in the list below.
- Time and date - **oT**yymmddhhmmss.sss
- Time, daylight savings - **oTD** or **oTD1** for daylight savings on or **oDT0** for off
- Timezone (H11) - **oTZ-7** or **oTZ-420** e.g. -7 hour or -420 minutes timezone offset
- Volume of Beps - **oV0** - Mute, **oV1** ... **oV9** (min through max.)
- WiFi Connection - **oW0** - off, **oW1** - on
- Max Lens Mod -  **oX0** - disabled, **oX1** - enabled

GoPro HERO9/10/11 Front Screen option commands
 * **oF0 or oFO** - turn the front LCD off
 * **oFU** - UI interface mode info only
 * **oFF** - Full image (image is letterboxed)
 * **oFC** - Cropped image (filling the front LCD)
 * **oFN** - Never turn off
 * **oFM** - Match rear screen on/off behavior
 * **oF1** - turn off after 1 minute
 * **oF2** - turn off after 2 minutes
 * **oF3** - turn off after 3 minutes
 * **oF5** - turn off after 5 minutes
 
Shortcut Menu Types (to be used with oSA, oSB, oSC and oSD)  (coming soon)

| Feature      | value  | Feature      | value  |Feature      | value  |Feature      | value  |
|--------------|--------|--------------|--------|-------------|--------|-------------|--------|
|clear shortcut|0|burst rate |8 |ISO max       |15|horizon control  |24|
|zoom          |1|duration   |9 |mic type      |16|speed ramp       |25|
|fov           |2|color      |10|raw audio     |18|scheduled capture|26|
|slowmo        |3|EV comp    |11|sharpness     |19|hindsight        |27|
|white balance |5|hypersmooth|12|timer         |20|10-bit           |28|
|shutter       |6|interval   |13|timewarp speed|21|nightphoto       |29|
|bit rate      |7|ISO min    |14|wind noise    |23|trail length     |30|


HERO11 UX modes:
- **mE** - mode Easy
- **mPR** - mode Pro

# Experiment Here
## Typing-in Your Custom Mode:

<div id="qrcode"></div>
Custom Mode: <input type="text" id="tryit" value=""><br>


updated: Jan 18, 2023

[Learn more](..) on QR Control


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
