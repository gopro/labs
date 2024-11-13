# GoPro Labs Command Language

## Setting Commands

All QR Codes are simple text strings, alphanumeric characters to describe settings and actions for your GoPro camera. It is fairly easy to learn, 
so you can create you own custom commands. Here is an example command to set video at 4K 60fps with some Protune customization: **mVr4p60x-.5cFw55**. 
Breaking-down how that command works, firstly all GoPro QR settings commands are separated with lowercase characters, so this command is interpreted 
in these groups mV r4 p60 x-.5 cF w55. This is what each command group means:

* **mV** - is shorthand for mode Video - this is the same a swiping the camera to use video mode.
* **r4** - set resolution to 4K (16:9), r4T (for 4K 4:3) and r4X (for HERO11-13s 8:7) 
* **p60** - set the frame rate to 60 fps 
* **x-.5** - exposure compensation is set to -0.5
* **cF** - color Flat
* **w55** - white balance to 5500K
  
Any of these can be used on their own, or in a different order, however the order can have meaning. If the camera was currently in a photo mode, 
and you set the Protunes settings first, then switched to video, any Protune changes would be to the photo preset, the video will have whatever Protune 
settings you had previously. The individual commands within a QR code are performed in order, just like you would when using the touchscreen.

## Option Commands

Just like settings, these alter camera options, not the settings used in a preset. Examples like beep volume and screen brightness. It turns out there are a lot of these. 
While each setting command is a single lowercase character, it can be followed by a number of either uppercase or numbers for the parameters. Option commands, starting with **o** 
can stack many parameter in one command. This is a single options command **oV1B4D2** which translates to Volume - 10%, Brightness 40%, and LEDs rear only. The same command can be 
written as **oV1oB4oD2**, three separate option commands, but as storage in a QR code is limited so options can be stacked for more efficiency, this is also why spaces are not 
used between commands.

## The Full List of Settings and Option Commands

### Mode commands: 
 * **mV** - mode Video
 * **mVL** - mode Video Looping (\*)
 * **mP** - mode Photo
 * **mT** - mode Timelapse video (\*\*)
 * **mTP** - mode Timelapse Photo (\*\*)
 * **mTW** - mode TimeWarp
 * **mPB** - mode Photo Burst 
 * **mPN** - mode Photo Night
 * **mNL** - mode Night-Lapse Video (\*\*)
 * **mNP** - mode Night-Lapse Photo (\*\*)
 * **mL** - mode Live-Burst Photo (HERO10 only)
 * **mST** - mode Star Trails (HERO11-13 only)
 * **mLP** - mode Light Painting (HERO11-13 only)
 * **mLT** - mode Vehicle Lights (HERO11-13 only)
 
<b>\* Video Looping:</b> You need to create this preset on camera, before this command will select it.<br>
<b>\*\* Time/Night-Lapse modes:</b> The camera defaults to having presets for only one time-lapse mode and one night-lapse mode, yet both modes have two configurations (video or photo.) For all QR Code mode commands to work, a preset is needed for every mode you wish to use. e.g. If you only have a preset for night-lapse video (NLV), the QR command for NLV will work, but will not for night-lapse photo (NLP). To solve this, create a new preset for NLP, and both video and photo night-lapse commands will work.
 
### Defaults modes (on power up): 
 * **dL** - last used mode
 * **dV** - last used Video mode
 * **dP** - last used Photo mode
 * **dT** - last used Timelapse mode
  
### Resolutions: 
Resolutions are also in the format rX(Y) - where X is the first character of the resolution, and the optional Y is aspect ratio, T - Tall 4:3, X - eXtreme 8:7, nothing is 16:9
 * **r1** or **r10** or **r1080**  - 1920x1080
 * **r1T** or **r14** or **r1440**  - 1920x1440
 * **r1V** - 1080x1920 HD Vertical Video (H13)
 * **r2** or **r27** - for 2.7K 16x9
 * **r2T** or **r27T** - for 2.7K Tall the 4x3 mode
 * **r3** - 3K 360° for GoPro MAX
 * **r4** - 4k 16x9
 * **r4T** - 4k Tall, the 4:3 mode
 * **r4X** - 4k eXtreme, the 8:7 mode (H11-13)
 * **r4S** - 4k Square, the 1:1 mode using Ultra Wide (H13)
 * **r4V** - 2160x3840 4K Vertical Video (H13)
 * **r5** - 5.3k for HERO and 5.6K 360° for GoPro MAX
 * **r5T** - 5k Tall, the 4:3 mode (H10)
 * **r5X** - 5k eXtreme, the 8:7 mode (H11-13)
 
### Frame rates: 
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
  
### Timelapse and NightLapse frame rates: 
 * **p2** (0.5s or 2Hz/2p capture)
 * **p1** (1s interval)
 * **p.2** (2s interval) 
 * **p.5** (5s interval) 
 * **p.10** through **p.3600** (10s to 60m interval)

### Lens - FOV: 
 * **fN** - Narrow (older models)
 * **fM** - Medium (older models)
 * **fW** - Wide
 * **fL** - Linear
 * **fS** - Superview 
 * **fV** - HyperView (H11-13)
 * **fH** - Horizonal Level + Linear (H9-13)
 * **fX** - SuperMax Wide (Max Lens Mod)
 
### Audio (Raw controls): 
 * **aL** - Low Processing
 * **aM** - Medium Processing
 * **aH** - High Processing

### Bitrate: 
 * **b0** - Standard Bitrate
 * **b1** - High Bitrate

### Color: 
 * **cF** - Color Flat
 * **cG** - Color Vibrant (old GoPro Color)
 * **cN** - Color Natural (H10-13)

### Depth (H11/12 only): 
 * **d0** or **d8** - 8-bit color
 * **d1** or **d10** - 10-bit color

### EIS (Hypersmooth control): 
 * **e0** - Off     
 * **e1** or just **e* - On
 * **e2** - High
 * **e3** - Boost
 * **e4** - Auto 
 
### Exposure Lock: 
 * **eL0** - Off     
 * **eL1** - On
 * **eL2 - eL9** -  Lock after 2 to 9 seconds.

### Hindsight (Video modes H9-13): 
 * **hS0** - Off     
 * **hS1** - On 15s window
 * **hS2** - On 30s window
 * **hS5** - Experimental Labs H11-13 - 5s window

### White Balance: 
 * **wA** - Auto White Balance
 * **w23** - 2300K White balance
 * **w28**, **w32**, **w40**, **w45**  - 2800K, 3200K, 4000K, 4500K
 * **w50**, **w55**, **w60**, **w65**  - 5000K, 5500K, 6000K, 6500K
 * **wN** - Native White Balance (sensor raw)

### ISO Minimum and Maximum (set to together with format i(max)M(min)):
(All cameras and Older Labs):<br>
 * **i1M1** - 100 ISO Max & Min
 * **i2M1** - 200 ISO Max with 100 ISO Min
 * **i16M8** - 1600 ISO Max with 800 ISO Min
 * **i32M1**  - 3200 ISO Mac with 100 ISO Min
 * **i64M16** - 6400 ISO Mac with 1600 ISO Min
 * **i1S180** - 100 ISO Max with a 180 degree shutter angle
 * **i16S22** - 1600 ISO Max with a 22 degree shutter angle
 * **i1S0** - 100 ISO Max with an **Automatic** shutter angle<br>

Note: Angles between 22 and 1 degrees are supported. Experiment for higher shutter speeds. You will need a good amount of light and/or a higher ISO.

### EV Compensation: 
 * **x0** - EV 0 default
 * **x-.5** - EV -0.5
 * **x.5** - EV +0.5
 * **x-1** - EV -1.0
 * **x1** - EV +1.0
 * **x-1.5** - EV -1.5
 * **x1.5** - EV +1.5
 * **x-2** - EV -2.0 
 * **x2** - EV +2.0<br>
 on some cameras models you can extend this to +/-6 EV (beyond the range the camera menu supports).
 * **x-5** - EV -5.0
 * **x3** - EV +3.0
 
### Sharpness: 
 * **sL** - Low
 * **sM** - Medium
 * **sH** - High
 
### Night Photo exposure time: 
 * **eA** - Auto exposure
 * **e2** - 2 second shutter
 * **…** 
 * **e30** - 30 second shutter

### GoPro MAX Shooting Modes
 * **mH** - mode Hero
 * **mHF** - mode Hero Front
 * **mHR** - mode Hero Rear
 * **m3** - mode 360°
 * **m3F** - mode 360° front on LCD
 * **m3R** - mode 360° rear on LCD
 * **mF** - mode monitor Front lens
 * **mR** - mode monitor Rear lens

### Feature with off and on commands:
 * GPS Active: **g0** or **gO** - off, **g** or **g1** - on 
 * Quick Capture: **q0** or **qO** - off, **q** or **q1** - on 
 * Voice Commands: **v0** or **vO** - off, **v** or **v1** - on

### Option (‘o’) commands:
 * Brightness of the LCDs - **oB0** … **oB9** - (100%)
 * Camera Auto Off - **oC0** - Never, **oC1** - 1min, **oC5** - 5min, **oC15** - 15min, **oC30** - 30min
 * LCDs off now - **oDO**
 * LED control - **oD0** - all off, **oD2** - some on, **oD4** - all on
 * Extern Audio options - **oE1** - Standard Mic, **oE2** - Standard+ Mic, **oE3** - Powered Mic, **oE4** - Powered+ Mic, **oE5** - Line In (HERO10-13)
 * Front Screen control - **oFxy** - (see list below)
 * GPS Options (HERO11 v2.1) - **oG0** - off, **oG1** - on
 * Language - **oL**x - **0** English USA, **01** English UK, **02** English Aus, **03** English India, **1** German, **2** French, **3** Italian, **4** Spanish, **5** Chinese, **6** Japanese, **7** Korean, **8** Portuaguese, **9** Russian, **91** Swedish
 * Noise Reduction control (HERO13) - **oN0** High/Default (less noise/detail),  **oN1** Medium,  **oN2** Low (more noise/detail),  
 * Quick Capture (HERO11 v2.1) - **oQ0** - off, **oQ1** - on
 * Rotation, Camera Orientation - **oR0** - Auto, **oR1** - Up, **oR2** - Down, **oR2** - Left, **oR3** - Right
 * Screen Auto Off - **oS0** - Never, **oS1** - 1min ... **oS3** - 3min
 * Shortcut Menu on LCD - **oSA**x - Upper Left, **oSB**x - Lower Left, **oSC**x - Upper Right, **oSD**x - Lower Right, **oSR** - reset. Where x is in the list below.
 * Time and date - **oT**yymmddhhmmss.sss
 * Time, daylight savings - **oTD1** for daylight savings on or **oTD0** for off
 * Timezone (H11-13) - **oTZ-7** or **oTZ-420** e.g. -7 hour or -420 minutes timezone offset
 * Volume of Beeps - **oV0** - Mute, **oV1** ... **oV9** (min through max.)
 * Volume Control - **oVC0** - off, **oVC1** - on
 * WiFi Connection - **oW0** - off, **oW1** - on
 * Max Lens Mod -  **oX0** - disabled, **oX1** - MLM original enabled, **oX2** - MLM 2.0 enanled
 * Denoise - **oN0** - High/default, **oN1** - Medium, **oN2** - Low.

### GoPro HERO9-13 Front Screen option commands
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
 
### Shortcut Menu Types (to be used with oSA, oSB, oSC and oSD)
 * **oSAx** - Top Left Shortcut x is from the table below 
 * **oSBx** - Bottom Left Shortcut x is from the table below 
 * **oSCx** - Top Right Shortcut x is from the table below 
 * **oSDx** - Bottom Right Shortcut x is from the table below 

| Feature      | value  | Feature      | value  |Feature      | value  |Feature      | value  |
|--------------|--------|--------------|--------|-------------|--------|-------------|--------|
|clear shortcut|0|burst rate |8 |ISO max       |15|horizon control  |24|
|zoom          |1|duration   |9 |mic type      |16|speed ramp       |25|
|fov           |2|color      |10|raw audio     |18|scheduled capture|26|
|slowmo        |3|EV comp    |11|sharpness     |19|hindsight        |27|
|white balance |5|hypersmooth|12|timer         |20|10-bit           |28|
|shutter       |6|interval   |13|timewarp speed|21|nightphoto       |29|
|bit rate      |7|ISO min    |14|wind noise    |23|trail length     |30|

### HERO11-13 UX modes: (limited, best to use the camera menu)
- **mE** - mode Easy
- **mPR** - mode Pro


## Action and Conditional Commands
Now you know how to set up your camera with QR commands, the fun really begins with Actions and Conditionals. Actions are starting **!S** or ending a capture **!E**, manual upload **!U**, 
beginning a live stream **!G**. As these actions are typically just pressing a button or camera menu, these actions can be enhanced based on time. e.g. **!08:00S**, which will sleep 
the camera until 8am, and then start capture (in the camera's default mode.) We can also do an conditional capture based on time. e.g. **>06:00<19:00mV~mNL!S** with this command, if the 
time is greater than 6am and less than 7pm, set mode Video, else set mode NightLaspe, then start.  You can start pre-programming actions with QR codes.

### The Full List of Actions
* **!**time**Bx** - <sup>H11-13</sup> Beeps and Blinks, **!B** - Blink once, **!B0** - Beep once, **!B1** - Blink+Beep once, **!B2** - Blink+Beep twice
* **!**time**Cx** - <sup>H10-13</sup> Up to x GBs to make sure is clear on the SD card. e.f **!C16** - clears up to 16GB. If more than x is available, no files are removed. x is limited to half SD size. Deletes the oldest media first. 
* **!**time**C or CA-CZ** - <sup>H13</sup>Clear location distance for system variables c, c:A thru c:Z
* **!**time**Dx** - <sup>H10-11</sup> !Dx wait for GPS lock with a DOP less than x, then sync time. For time only locks !D is fine. 
* **!**time**E** - End at **time** if in hh:mm form, or after n seconds.
* **!**time**Fx** - Frame Grab (LCD) at **time** - 'x' grab next x Labs messages.
* **!**time**G(S or M or L)(C)** - Start Live-streaming, **S** - 480p, **M** - 720p, **L** - 1080p, optional **C** for capture a local file, requires a previously successful **!W** command <sup>8/9/10/11</sup>
* **!**time**N** - No Action until exact **time**, useful if you just need a pause.
* **!**time**NQ** - No Action until at approximately **time**.
* **!**time**O** - Off, shutdown the camera.
* **!**time**OR** - shutdown and restart the camera.
* **!**time**R** - Repeat the whole command.
* **!**time**Rx** - <sup>H11-13</sup> Repeat the command starting at position x (i.e. a goto command).
* **!**time**S** - Start at exactly **time** if in hh:mm form, or after n seconds. 
* **!**time**SQ** - Start Quickly at approximately **time** if in hh:mm form, or after n seconds.  
* **!**time**TR** - <sup>H11-13</sup>  **!TR* - switch active TimeWarp to Realtime (or slow motion)
* **!**time**TN** - <sup>H11-13</sup>  **!TN* - switch active TimeWarp to Normal (speed-up timelapse mode)
* **!**time**U** - Attempt a network contention and Upload <sup>9/10/11</sup>.
* **!**time**W** - Connect to a network, requires JOIN metadata to have been previous stored <sup>9/10/11</sup>.
* **!**time**X** - <sup>H10-13/MAX</sup> Exit script. 
* **!**time**Zx** - <sup>H10-13</sup> **!Z3** - mute both buttons, **!Z2** - mute only mode, **!Z1** - mute only shutter, **!Z0** - unmutes both

### Capture Triggers (Classic, invent your own below.)
* **!**time**SMs-t** - Start Motion detection with start sensitivity 's' and stop sensitivity 't' -- 't' field is optional.
* **!**time**SMsDdMmHh** - Start Motion detection with sensitivity 's', Delay of 'd', Mask of 'm' and Hold for 'h' seconds (D,M and H fields are all optional.)
* **!**time**SKs-t** - Start Speed capture at threshold 's' km/h and stop at 't' km/h -- 't' field is optional.
* **!**time**SKsHh** - Start Speed capture at threshold 's' km/h and Hold for 'h' seconds (H fields are all optional.)
* **!**time**SAs-tDdHh** - Accelerometer Trigger
* **!**time**SGs-tDdHh** - Gyro Trigger
* **!**time**SIs-tDdHh** - IMU Trigger (both Accelerometer and Gyro)
* **!**time**SDs-tDdHh** - Speed Pressure Level Trigger, 's' and 't' values are in dB.

### examples:
* **!S** - start now  
* **!07:00S** - start at precisely 7am  
* **!300SQ** - start in approximately 300 seconds.  
* **!60E** - end after 60 seconds (End commands are not used for photos.)
* **!2R** - repeat after 2 seconds
* **!s-01:00S** - start one hour before sunset
* **!nS** - start at true noon.
* **!s1200E** - end 1200 seconds after sunset
* **!r-600S** - start 600 seconds before sunrise
* **!17:00W!GLC** - start Live-streaming 1080p at 5pm, saving a local copy

### Storing metadata (Permanent, survives power off)
#### Old style (firmware released before March, '24)
* **!M**fourcc**=<courier>"string"</courier>**
* **!M**fourcc**=Number metadata** (comma separated)

#### New style (after March, '24)
* **\***fourcc**=<courier>"string"</courier>**
* **\***fourcc**=Number metadata**  (comma separated)

#### Example for display the owner’s name
**\*OWNR=<courier>"Joe Bloggs"</courier>**

Note: All strings must use <courier>"</courier> (ASCII 34) and not the <courier>”</courier> (148) character.  

All tags between **OWNA** and **OWNZ** will be displayed and stored in **GoPro-owner.txt**.

All tags between **OWNa** and **OWNz** will be only stored in the **GoPro-owner.txt**

Any four character code can be used for store other information. You can also store numeric data examples: 
* **\*CAMR=53** - metadata CAMR will be 53 
* **\*ABCD=45.234** - metadata ABCD will be floating point 45.234
* **\*UNIT=-1723** - metadata UNIT will be -1723 
* **\*LLTZ=32.707,-117.1576,-7** - set camera location (GPS off) with Latt/Long/TimeZone 

### Storing metadata (Temporarily, until power off)<br>
#### Old style (firmware released before March, '24)
* **oM**fourcc**&#61;<courier>"string"</courier>**  
* **oM**fourcc**=Number metadata** (comma separated)

#### New style (after March, '24)
* **$**fourcc**&#61;<courier>"string"</courier>**  
* **$**fourcc**=Number metadata** (comma separated)

### Metadata extraction
All metadata in stored in a GPMF format with the MP4, 360 or JPG files, this is an open source, so if it free to integrated within any third party tool. 
The above global metadata can be extracted with this [**demo web tool**](../metadata)

### Some Four Character Codes are reserved for feature extensions
* **24HZ** 10-13: enable film standard 24.0 frame, rather than the default broadcast standard 23.976. The existing 24p mode(s) will have the new frame rate when this is enabled, all other video modes are unaffected. Input Data: 1-enable, 0-disable",
* **64BT** H8-10/MAX: 12GB Chapter sizes on HERO8/9/10 and MAX cameras (default on H11.) Note: Will not be active for QuickCaptures. Input Data: 1-enable, 0-disable WARNING: Larger chapters will not playback on camera or support USB transfers, but are compatible with desktop tools. Permanent required.",
* **ARCH** H8-13/MAX: Archive mode: an ultra simplified video camera mode for novices documenting critical events, where you don’t want the camera mode modified. Either button will start and stop video capture. Input Data: 1-enable, 0-disable WARNING: only removable via the disable command. Permanent required.",
* **AUDS** H10-13: Audio Level: displays the current estimate of the sound pressure level in dB. Input Data: 1-enable, 0-disable.",
* **BASE** H8-10/MAX: Base file name change, adding to beginning of the filename. Input: H10-13 supports wildcards within [ ]: like [yyyy-mm-dd] or [HH-MM-SS]  e.g. A-[yyyymmddHHMMSS] WARNING: GoPro App and cloud will not support renamed files.",
* **BERS** H10-13: Bypass ERS compensation, extremely rare usecases. Input Data: 0-display, 1-enable, 2-enable only with EIS off",
* **BIAS** H9 only (new cameras use EVBS): Bias is like EV Compensation, but it can only be used after recording has began. It is a hack designed to tweak exposure during a livestream or webcam session. Input Data: Number of stops between -6 and 6, supports half stops like 3.5.",
* **BITR** H10-13: set the compression in Mb/s for the Protune High Bitrate setting. Normally this would be around 100Mb/s, however higher (or lower) rates may be achieved with newer SD Cards.Input Data: MB/s from 2 to 200.",
* **BITH** H10-13: set the compression for LRVs in Mb/s. Normally this would be around 4Mb/s, however higher (or lower) rates may be achieved with newer SD Cards. Input Data: MB/s from 1 to 100.",
* **BITL** H11-13: controlling the livestream maximum bitrate (up to 8Mbit/s). Input Data: MB/s from 1 to 8.",
* **BURN** H8-13/MAX: Add date, time and other burn-in text to your video. Input Format (0,height)[yyyy-mm-dd HH:MM:SSaa] examples:   (0,30)Local Time: [HH:MMaa]   (0,26)Local Time: [HH:MM:SSAA]   (0,40)©[yyyy]\ XYZ Inc.   (0,24)Shoot Date [yy/mm/dd]",
* **BRNP** H8-13/MAX: The burn-in position for overlays or LOGO display. Input Data (select 1 of 8): TL, TC, TR, ML,BL, BC, and BR\nT-Top B-Bottom C-Center L-Left and R-Right.",
* **BRNT** H8-13/MAX: The overlays or LOGO display time in seconds. e.g. BRNT=0.016 will display the logo or text overlays only on the first frame. Input Data: 0 is unlimited, or 0.01 to 3600 seconds.",
* **BRNX** H8-13/MAX: Offset the overlays or LOGO display with X,Y pixel coordinates. Input Data: x,y pixel coordinates.e.g. 120,40",
* **BYPS** "H11-13: Bypass common pop-ups, such as resetting the time and date. Remember to set time and date if you remove the battery. Input Data: 1 to bypass, 0 for normal notifications",
* **CBAR** H9-13: enable a small 75% saturated color bars for video tools evaluation. Most cameras limit overlays to 4K30, 2.7Kp60 or lower. Input Data: 1 to enable, 0 to disable",
* **DAMP** H10-13: Control over the auto-exposure damping. Setting the DAMP to 1 is the default, setting to 10 would slow the camera’s exposure adjustments 10X.Input Data: 0.1 to 10000",
* **DAUD** H10-13: Disable Audio in video captures, all MP4 files will have no audio track. Application: high bit-rate drones video.Input Data: 1 to disable audio, 0 to re-enable",
* **DLRV** H10-11: Disable LRV file creation. Application: high bit-rate drones video. Input Data: 1 to disable LRVs, 0 to re-enable",
* **DSPC** Labs text display contrast:  Set the background opacity for Labs text on the LCD. Input Data: Number from 0-transparent to 6-completely opaque.",
* **DSPL** Labs text display length: How long to display each Labs message, like owner information (OWNR). The default is 1 second. Input Data: Number from 1-9 seconds or 10-9999 milliseconds.",
* **ENCR** H9 only: Experimental media encryption, using a password to prevent playback by non-authorized users. As the QR Code with the password is not encrypted, do not print or save the QR code image.Enable by using password between 4 and 16 characters. Disable with an empty password.",
* **DECR** H9 only: Decryption of media encryption with ENCR.  Warning: If the passwords do not match, the data is doubly encrypted, there is no recovery of the data. Be careful. This operation is slow, USB power or have a full battery.Input a matching password",
* **EVBS** H10-13: This is an EV compensation value that works with webcam and livestreaming, it can be changed live (with QRDR=1) and it is global, adding the any existing EV control in your presets.Input Data: range -4 to 4.",
* **EXPQ** H11-13: Min and Max Shutter speed, 1/x format. Input Data: 24 to 8000, representing 1/24 and 1/8000s, 0 to disable",
* **EXPS** H11-13: Video exposure values: ISO and Shutter speed, rendered to the LCD. Handy for those using ND Filters. Input Data: 1 to enable, 0 to disable",
* **EXPX** H10-13: Max Shutter speed, 1/x format. Input Data: 24 to 8000, representing 1/24 and 1/8000s, 0 to disable",
* **EXPN** H10-13: Min Shutter speed, 1/x format. Input Data: 24 to 8000, representing 1/24 and 1/8000s, 0 to disable",
* **EXPT** Video Exposure Control through Maximum Shutter Angle for video modes. Can improve stabilization in low light. Input Data: Number 0 through 5 stops.  0-360° (camera default), 1-180°, 2-90°, 3-45°, 4-22.5° etc.",
* **FAST** Faster and fewer Labs notifications on boot. Input Data: 1-enable, 0-disable",
* **FEAT** H10-13/MAX: Displays Labs enabled Features for x seconds. Input Data: x-seconds",
* **GAIN** H9-13: Digitally gain up the audio. e.g. \$GAIN=12, increase audio by 12dB. Will likely reduce the dynamic range.Input Data: 0-48 in dB.",
* **GCMP** H11-13: Disable Gryo Compensated Exposure.  When GoPro camera modes, it normally uses a faster shutter for improved stabilization, this control disables this feature.Input Data: 1 to disable gyro comp, 0 - default",
* **GUID** H11-13: On screen guides lines for output aspect ratios. e.g. \$GUID=2.35, set shooting guides for cinescope. Input Data: List of aspect ratios (up to 8) as real numbers, so 16:9 is 1.778 and 9:16 is 0.5625.",
* **GUIC** H11-13: Color/brightness of guides lines. e.g. \$GUIC=10,255. Input Data: List of guide brightness (up to 8). e.g. 255,10",
* **HDMI** Media Mod users can change the output default from Gallery, to clean monitoring with no overlays, or monitoring live video with On Screen Display overlays. Input Data: 0-Galley, 1-Clean Video, 2-Video+OSD",
* **HIST** Enable a histogram with with a range of contrast options. Input Data: Number 1 to 11 enables the histogram with contrast 1 through 11, 0 will disable it.",
* **HSTP** H11-13, not Mini: Histogram position and size. A negative position will place the histogram on the front LCD. Input Data: x,y,size as percentages. e.g. 20,40,60",
* **HNDL** Set the camera ID to limit which cameras to respond to a QR Code. Used with the hZ command, where Z is the bit mask for which cameras will follow the command. Input Data: ID Number from 1-31. Usage: h6mP!S ← runs on cameras with IDs 2 or 3.",
* **HSTO** H9-13: Number minutes controlling the length of the Hindsight timeout, changing from the default for 15 minutes. Input Data: minutes from 5-1440.",
* **IWFR** H10-11: Increased Write FRequency to support for higher precision file recoveries (defaulted on with *BITR=x bitrate changes). This hack increases the rate in which video data is flushed to the SD Card, improving the recoverability for footage. Great for FPV users.",
* **JOIN** Setup storing your WiFi network credentials.Input Data: String in the format your_ssid:your_passphase e.g. HomeWiFi:Pass1234",
* **LBAR** H9-13: enable a small luma sweep for video tools evaluation. Most cameras limit overlays to 4K30, 2.7Kp60 or lower. Input Data: 1 to enable, 0 to disable",
* **LEVL** H11-13: enable on-screen spirit level. Input Data: 1-9 sets the size of the level, 0 to disable",
* **LLTZ** Manual location: using Sunset/Sunrise triggers without waiting for a GPS lock. Input Data: numbers in the format latitude,longitude,timezone e.g. 33.126,-117.327,-8.0",
* **LOGB** H11-13: Extremely advanced users. Change the Log base for very flat encoding. Color Flat is Log base 113. Math:out = log(in*(base-1)+1)/log(b). Should be combined with Flat and 10-bit settings. Input Data: base,[offset]e.g. 200,-128 or 400",
* **LOGO** H9-13: Activate a small logo (under 64K pixels) to render within the video. There must be a PNG file stored on the SD card in the MISC folder. Most cameras limit overlays to 4K30, 2.7Kp60 or lower. Input Data: String e.g. Logo.PNG for the name of your image",
* **MUTE** H9-13: Mute one or more channels of audio. e.g. \$MUTE=15 mutes all channels, for a single channel use 1 = first, 2 = second, 4 = third and 8 = fourth channelInput Data: 0-15, the value is binary mask.",
* **NR01** H11-13: Noise reduction control, for advanced user intending noise reduction in post. Likely needs a higher BITR. Input Data: 1-100, is the default full denoise processing in camera. 1 - leaves the most noise. 0 - disables",
* **OLTC** Offset for LTC timecode in frames, enabling calibration you are seeing any offset..Input Data: x - frames.",
* **OWNR** Display Owner information. This written into every MP4 and JPGs metadata, and MISC/GoPro-owner.txt file.Input Data: String up to 64 characters using '\\n' for a newline. Permanent required.",
* **OWNr** Owner information, not displayed. This written into metadata, and MISC/GoPro-owner.txt file.Input Data: String up to 64 characters using '\\n' for a newline. Permanent required.",
* **PMSG** H11-13: Message to display during a Labs looping script, so you know the camera is running something custom. Input Data: Any label less than 20 characters, or empty to disable.",
* **PRES** H12-13: Create a new preset with custom name and icon. Input Data: Icon number 0 thru 15, preset name up to 15 characters",
* **PRXY** H10-13: Store LRV files as NLE ready proxies. Normally a camera will encode an LRV (Low Res Video) for every MP4, with this enabled LRVs are made MP4s within a subfolder. Input Data: 1-move LRVs, 2-move THMs, 3-both, (v2.1) 4-No _Proxy name. 0-disable",
* **QRDR** Detect QR Codes while recording. Used for changing a video burn-in message in the middle of a live-stream. This also allows you to end a capture via a QR Code (command: !E).  Input Data: 1-enable, 0-disable",
* **RLTC** Read LTC timecode from audio inputsInput Data: 1-Enable, 0-Disable.",
* **RTMP** RTMP Address to livestream to. Combined with JOIN Metadata, use !W!GLC to start a 1080p livestream. Input Data: String of the RTMP URL, e.g. rtmp://live.twitch.tv/app/live_1234567. Permanent required.",
* **SHMX** H8-9 & MAX: Photo shutter maximum exposure time: this is similar Maximum Shutter Angle (EXPT), except it applies to Photos. e.g. SHMX=1000 would set 1/1000th of a second as the longest shutter time. Input Data: 30-2000.",
* **SOLO** H9-13: Use only one channel of audio. e.g. \$SOLO=1 use only channel 1, \$SOLO=4 use only channel 4.Input Data: 0-4, the value is a channel number.",
* **SPED** SD Card Speed Test. Data rates should have minimums above 120Mb/s is you want to reliably capture the high bitrate modes.Input Data: 1-9, number of times to run the test.",
* **SYNC** H9-11: GPS time/timecode sync. With a good GPS signal, the camera’s internal clock will be precisely updated to the millisecond. It will not update the hour or date, preserving your current timezone offset. Input Data: 1-enable, 0-disable. Permanent required.",
* **TCAL** H9-13: Timecode CALibration, help to increase the precision of setting timecode via QR Code. The milliseconds can be positive or negative as needed.",
* **TONE** H10-13: Tone-mapping controls. Input Data:   0 - current defaults   1 - global tone-mapping only   2 - both tone-mapping   3 - disable all tone-mapping",
* **TUSB** H10-13: Trust USB power. Some USB power sources may report less than they are capable. This modification assumes the USB Power source is 2A minimum, and disables the testing. If you use TUSB with an inadequate power source, expect capture failures.\n",
* **WAKE** H9-13: Conditional wake on any power addition. Inserting a battery or the connection of USB power, will boot up the camera to continue a script after a power failure.  Input Data: 1-wake if there is a delay action pending, 2-wake on power, 0-disable",
* **WBLK** H11-13: White balance Lock upon capture. Allows the convenience of auto white balance, without the risk of WB change during capture. Input Data: 1-enable WB Lock, 0-disable",
* **WIDE** H11-13: A wide gamut color profile, this supports all in-camera white balancing. Like using white balance Native, without as much post color work. Input Data: 1-enable WIDE gamut, 0-disable",
* **ZONE** H9-13: Set the time zone for use with SYNC. Input Data: time zone offset in minutes.

## Macro support (since March, '24)
Added support for macros, or crude scripting subroutines. This expands the potential complexity for QR scripting, as the entire script is no longer limited to 255 characters. 
It would be possible to run scripts nearing ~1.2KB. Note: recursion is supported, macros can call other macros, and can call themselves.

Macros are saved in string FourCCs:
* **$**fourcc**&#61;<courier>"custom Labs commands"</courier>**  (temporary)
* **\***fourcc**&#61;<courier>"custom Labs commands"</courier>**  (permanent)

Example: This macro calculates the Light Value and stores the result in variable **E**<br>
**\*LVAL=**<courier>"=Ii=Ss=I/100=S/I=E6.25=E*S=E#2"</courier>

 e.g. *SUBA="mVr4p60'60p'!S!2E!1N" Note: Use single quotes for text within double quotes.

In a separate QR Code will call LVAL and display the result<br>
**^LVAL**<courier>"Current LV $E"</courier>

Note: for Macros that print output use single quotes for text within.
**\*DPLV=**<courier>"^LVAL'current LV $E'"</courier>


## Reset Actions ##

* **!RESET!1OR** - erase all your permanent metadata (anything that used !Mxxxx command.) Then Reboot.  (requires user confirmation.)
* **!FORMAT**<sup>H10-13</sup> - for SD formatting via QR Code (requires user confirmation.)
* **!FRESET**<sup>H10-13</sup> - Factory reset, erase everything, except QR code metadata (requires user confirmation.)
* **!PRESET**<sup>H10-13</sup> - Presets reset, restore the default presets (requires user confirmation.)
* **!WRESET**<sup>H10-13</sup> - WiFi Credentials reset, erase all your BLE and WiFi configurations (requires user confirmation.)

## Scripting

The geek factor is highest in this section.  This is close to a Turing-complete language, you can get many interesting capture control jobs done.  There are save and load commands, additive metadata and clock time conditionals

* **!SAVEname=script**  e.g. !SAVEdaily=dPmP!12:00S!Ldaily - a save script called ‘daily’ that repeatedly shots one photo every day at noon. 
* **!Lname**  e.g. !LnightLapse - load and run a script called nightLapse
* **<courier>"any text"</courier>** e.g. mV<courier>"Video Mode"</courier>!S!5E!4NmP<courier>"Photo Mode"</courier>!S!5R - this will display <courier>"Video Mode"<courier> and <courier>"Photo Mode"</courier> when switch to those modes.  

### Conditionals Based on Time

**\<** , **>** and **==** characters are used to indicate a conditional: less than, greater than equal, and equal (**==** Since March 2024 firmware)

**\<08:45!S** is equivalent to 

> if(current_time < 8:45) <br>
> &nbsp;&nbsp;&nbsp;   Start

**>18:30!R** is equivalent to 

> if(current_time >= 18:30) <br>
> &nbsp;&nbsp;&nbsp;  Repeat

**==10:10!R** is equivalent to
> if(current_time == 10:10) <br>
> &nbsp;&nbsp;&nbsp;  Repeat


The if condition defaults to effecting only the one command after the condition

**\<08:45!S<courier>"Hello World"</courier>** is equivalent to:

> if(current_time < 8:45) <br>
> &nbsp;&nbsp;&nbsp;   Start<br>
> print <courier>"Hello World"</courier>
	
The start will happen if the condition is true, but the print message occurs whether true or false.  To make the print also part of the true state you can use **+** between the joined commands.

**\<08:45!S+<courier>"Hello World"</courier>** is equivalent to

> if(current_time < 8:45) <br>
> {<br>
> &nbsp;&nbsp;&nbsp;    Start <br>
> &nbsp;&nbsp;&nbsp;    print <courier>"Hello World"</courier> <br>
> }

These can be stacked too, e.g. **\<08:45!S+<courier>"Hello World"</courier>+!60E** is equivalent to

> if(current_time < 8:45) <br>
> {<br>
> &nbsp;&nbsp;&nbsp;    Start <br>
> &nbsp;&nbsp;&nbsp;    print <courier>"Hello World"</courier> <br>
> &nbsp;&nbsp;&nbsp;    After 60 seconds End the capture <br>
> }

Conditions support **else** statements using the **~** character after the last 'true' command

**\<08:45!S+<courier>"Hello World"</courier>+!60E~!08:44N!R** is equivalent to

> if(current_time < 8:45) <br>
> {<br>
> &nbsp;&nbsp;&nbsp;    Start <br>
> &nbsp;&nbsp;&nbsp;    print <courier>"Hello World"</courier> <br>
> &nbsp;&nbsp;&nbsp;    After 60 seconds End the capture <br>
> }<br>
> else<br>
> {<br>
> &nbsp;&nbsp;&nbsp;    Sleep until 8:44 the next day <br>
> }<br>
> Repeat


Conditionals themselves can be stacked like **\>09:15<10:00!S** is equivalent to 

> if(current_time >= 9:15) <br>
> &nbsp;&nbsp;&nbsp; if(current_time <= 10:00) <br>
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Start<br>
	
However the else can only be applied to the last condition. **\>09:15<10:00!S+<courier>"Hello World"</courier>+!60E~!09:30N!R** is equivalent to

> if(current_time >= 9:15) <br>
> {<br>
> &nbsp;&nbsp;&nbsp;	if(current_time <= 10:00) <br>
> &nbsp;&nbsp;&nbsp;	{<br>
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;		Start<br>
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;		print <courier>"Hello World"</courier><br>
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;		After 60 seconds End the capture<br>
> &nbsp;&nbsp;&nbsp;	}<br>
> &nbsp;&nbsp;&nbsp;	else<br>
> &nbsp;&nbsp;&nbsp;	{<br>
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;		Sleep until 9:30 the next day<br>
> &nbsp;&nbsp;&nbsp;	}<br>
> }<br>
> Repeat

The command language is kept simple, so it doesn't maintain a stack on the conditional nesting. 

### Conditionals Based on Camera Status (HERO11-13)

New conditional commands for 2023. Now \>xValue and/or \<xValue and/or ==xValue can be used to test camera states, where 'x' is the camera state to test, and Value the amount to test against:<br>
* **a** accelerationValue - **\>aValue**CMD if(acceleration \> Value) then CMD, units in Gs
* **b** batteryLevel - **\>bValue**CMD if(battery \> Value) then CMD, units in percentage
* **b:T** batteryTemperature<sup>H13</sup> - **\>bValue**CMD if(battery \> Value) then CMD, units in degrees C
* **c** coordDistance - **\>cDist**CMD  then CMD, units in meters, compare distance from initial GPS location
* **c:X** coord[A-Z]Distance - **\>c:XDist**CMD There are up to 26 pre-stored GPS locations oMFRMA=latt,long thru oMFRMZ. If nothing is store in FRMx, it will initialize with the current location. Reset a location with $FRMx=0,0 it will reinit with the current location.
* **d** GPS DOP - **\<dValue**CMD - if(DOP \< Value) then CMD, units in 100x DOP. GPS location precision.
* **e** random - **\<eValue**CMD \<e50 - 50% true \<e90 - 90% true.
* **g** gyroValue - **\>gValue**CMD if(gryo \> Value) CMD, numbers are in degrees per second.
* **h** heightValue - **\>hValue**CMD if(height \> Value) CMD, numbers are in meters above sealevel.
* **i** isoValue - **\>iValue**CMD - testing ISO where ISO ranges from 100 to 6400
* **k** speedValue - **\>kValue**CMD if(gps Speed \> Value) CMD e.g. >k45!S, numbers are in km/h.
* **l** loop_countValue - **\<lValue**CMD if(loop_count \< Value) CMD e.g. \<l45!R, this is the loop count for !R repeat, since last QR scan or boot.
* **m** motionValue - **\<mValue**CMD if(motion \< Value) CMD Motion value is a percentage of pixels moving  e.g. >m5!S+60E!R, this look of motion greater than 5%, and record for 60seconds when detected.
* **m:X** motion[A-Z]Value - <m:A through <m:Z adjusts the sensitivity of the detector, the above is the equivalent <m:J.  'A' is very low sensitivity, only large pixel changes detected, 'Z' tiniest change detected. 
* **n** network Connect - if false it returns -1, otherwise it returns the string length of the SSID
* **n:L** networkLivestreaming - if false it returns -1, 1.0 if currently livestreaming
* **p** soundpressureValue - **\>pValue**CMD if(spl \> Value) CMD, numbers are in dB
* **p:T** processorTempValue<sup>H13</sup> - **\>pValue**CMD if(processorTemp \> Value) then CMD, units in degrees C
* **r** recording - **\>r0**CMD1~CMD2 if(Recording > 0) then CMD1 else CMD2 
* **r:C** remote Connected - **\>r:C0**CMD1~CMD2 if(RC_Connected) then CMD1 else CMD2 
* **r:A** remote App Connected - **\>r:A0**CMD1~CMD2 if(App_Connected) then CMD1 else CMD2 
* **s** shutterValue - **\>sValue**CMD - testing shutter, where 1/Value is used for shutter speed
* **t:X** timedate - **\>t:XValue**CMD - where X Y-Year M-Month D-Day H-Hour N-miNute S-second W-day_of_the_Week B-seconds_since_Boot Q-seconds_since_Qrcode R-recording_time W-day_of_week
* **u** USB power - **\>u0**CMD1~CMD2 if(power is on USB) then CMD1 else CMD2
* **v** Current Camera Mode - **==vValue**CMD video=12, TLV=13, Looping Video=15, Photo=16, Night Photo=18, Burst Photo=19, etc. Example: ==v12!S  will start recording video if in Video Mode. ==v16!S will take a photo if in Photo Mode.
* **y** mode_pressesValue - **\>y0**CMD1~CMD2 if(mode_presses > 0) then CMD1 else CMD2
* **z** shutter_pressesValue - **\>z0**CMD1~CMD2 if(shutter_presses > 0) then CMD1 else CMD2

### Assignments, Variables and Math

QR Command scripts can include variables and operation on them. Why? Fun maybe? More power, for sure! A complete program in a QR Code.

As 'a' to 'z' and system system fields, 'A' to 'Z' are the variable can contain any floating point number. This new variables are all initialized to zero, 
and can be tested with the '<' and '>' conditionals. To make them non-zero, they can be assign with and '=' command. Just like with conditions and action, 
the '=' character is the command delimiter and comes first.  

**=A5**  is the command variable A = 5.

**=P3.14159265** assigns Pi to variable P.  

Now math can be used to modify your variables.

* **=A+1.4** adds in form A = A + 1.4
* **=D-2** subtraction D = D - 2  (note: assignments of negative numbers aren't support, but subtracting is. So **=D0=D-2** would initialize D to be -2, although =D0 is unnecessary as all variable are initialize to zero at boot.)
* **=A*P** multiply A = A * P
* **=E&#47;7** divide E = E &#47; 7
* **=H^A** raised to a power H = H ^ A
* **=F^0.5** raised to a power F = sqrt(F)
* **=B%10** modulus  B = B % 10 
* **=G#2** Log base N  G = log(G)/log(2) 
* **=J&6** Bitwise AND like  J = (float)((int)J & 6) 
* **=K&#124;3** Bitwise OR K = (float)((int)K &#124; 3) 

There should be a prize if some can come up with a practical use for all of these ;)

So if thought the above is crazy, it gets weirder.

* **=B$BITR**  load the contents of the BITR (bitrate) hack into variable B, otherwise store zero.  So you can test if a feature is enabled.
* **=Tt:W** load the day of the week into variable T
* **=Di** load the current ISO value into variable D
* **$EVBS=E**  store the current into EV Bias hack, so you can make a variable mess with your exposure (potentially mid capture.)
* **\*VarC=C**  permanently store the current variable C into metadata field VarC, so this can be read back on next boot.  
* **!$AR**  delay an action (like !R) with a variable amount of time, e.g. this will loop forever, doubling the sleep time with each interaction **=A$VARA<A1=A1=A*2!MVARA=A!$AR**

### Why Add Math to QR codes

You the user can have very particular shooting needs, this improves the robustness of Labs to cover a wider range of automatic captures. And is it cool. ;)

Say you want use a GoPro as a crude light meter, and report the output as an [exposure value](https://en.wikipedia.org/wiki/Exposure_value), then make capture decision based on that EV value.

EV = logbase2 (f-number^2/(time x gain_above_base_iso))  is the formula for EV<br>

As a QR command: **=E6.25=Gi=G&#42;0.01=E/G=E&#42;s=E#2<courier>"Exposure value $E"</courier>!R**<br>

Command steps explained:
> E=6.25<br>
> G=ISO value<br>
> G=G&#42;0.01<br>
> E=E/G<br>
> E=E&#42;shutter value (1/s)<br>
> E=log(E)/log(2)<br>
> print E<br>
> repeat<br>
 

updated: November 5, 2024

[Learn more](..) on QR Control
