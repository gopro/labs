# GoPro Labs Command Language

## Setting Commands

All QR Codes are simple text strings, alphanumeric characters to describe settings and actions for your GoPro camera. It is fairly easy to learn, 
so you can create you own custom commands. Here is an example command to set video at 4K 60fps with some Protune customization: `mVr4p60x-.5cFw55`. 
Breaking-down how that command works, firstly all GoPro QR settings commands are separated with lowercase characters, so this command is interpreted 
in these groups mV, r4, p60, x-.5, cF and then w55. No space or other delimiters are used. This is what each command group means:

* `mV` - is shorthand for mode Video - this is the same a swiping the camera to use video mode.
* `r4` - set resolution to 4K (16:9), r4T (for 4K 4:3) and r4X (for HERO11-13s 8:7) 
* `p60` - set the frame rate to 60 fps 
* `x-.5` - exposure compensation is set to -0.5
* `cF` - color Flat
* `w55` - white balance to 5500K
  
Any of these can be used on their own, or in a different order, however the order can have meaning. If the camera was currently in a photo mode, 
and you set the Protunes settings first, then switched to video, any Protune changes would be to the photo preset, the video will have whatever Protune 
settings you had previously. The individual commands within a QR code are performed in order, just like you would when change settings using the camera menus and touchscreen.

## Option Commands

Just like settings, these alter camera options, not the settings used in a preset. Examples like beep volume and screen brightness. It turns out there are a lot of these. 
While each setting command is a single lowercase character, it can be followed by a number of either uppercase or numbers for the parameters. Option commands, starting with `o` 
can stack many parameter in one command. This is a single options command `oV1B4D2` which translates to Volume - 10%, Brightness 40%, and LEDs rear only. The same command can be 
written as `oV1oB4oD2`, three separate option commands, but as storage in a QR code is limited so options can be stacked for more efficiency, this is also why spaces are not 
used between commands. The only places for using spaces is within quotes, like for preset names or printing messages to the screen.

## The Full List of Settings and Option Commands

### Mode commands: 
 * `mV` - mode Video
 * `mVL` - mode Video Looping (\*)
 * `mP` - mode Photo
 * `mT` - mode Timelapse video (\*\*)
 * `mTP` - mode Timelapse Photo (\*\*)
 * `mTW` - mode TimeWarp
 * `mPB` - mode Photo Burst 
 * `mPN` - mode Photo Night
 * `mNL` - mode Night-Lapse Video (\*\*)
 * `mNP` - mode Night-Lapse Photo (\*\*)
 * `mL` - mode Live-Burst Photo (HERO10 only)
 * `mST` - mode Star Trails (HERO11-13 only)
 * `mLP` - mode Light Painting (HERO11-13 only)
 * `mLT` - mode Vehicle Lights (HERO11-13 only)
 
<b>\* Video Looping:</b> You need to create this preset on camera, before this command will select it.<br>
<b>\*\* Time/Night-Lapse modes:</b> The camera defaults to having presets for only one time-lapse mode and one night-lapse mode, yet both modes have two configurations (video or photo.) For all QR Code mode commands to work, a preset is needed for every mode you wish to use. e.g. If you only have a preset for night-lapse video (NLV), the QR command for NLV will work, but will not for night-lapse photo (NLP). To solve this, create a new preset for NLP, and both video and photo night-lapse commands will work. Not all modes are available on every camera. 
 
### Defaults modes (on power up): 
 * `dL` - last used mode, the camera will boot up to last mode used before shutdown
 * `dV` - last used Video mode, the camera will boot into video mode
 * `dP` - last used Photo mode, the camera will boot into photo mode
 * `dT` - last used Timelapse mode, the camera will boot into Timelapse mode, like TimeWarp or Night Lapse etc.
  
### Resolutions: 
Resolutions are also in the format rX(Y) - where X is the first character of the resolution, and the optional Y is aspect ratio, T - Tall 4:3, X - eXtreme 8:7, nothing is 16:9
 * `r1` or `r10` or `r1080`  - 1920x1080
 * `r1T` or `r14` or `r1440`  - 1920x1440
 * `r1V` - 1080x1920 HD Vertical Video (H13)
 * `r2` or `r27` - for 2.7K 16x9
 * `r2T` or `r27T` - for 2.7K Tall the 4x3 mode
 * `r3` - 3K 360° for GoPro MAX
 * `r4` - 4k 16x9
 * `r4T` - 4k Tall, the 4:3 mode
 * `r4X` - 4k eXtreme, the 8:7 mode (H11-13)
 * `r4S` - 4k Square, the 1:1 mode using Ultra Wide (H13)
 * `r4V` - 2160x3840 4K Vertical Video (H13)
 * `r5` - 5.3k for HERO and 5.6K 360° for GoPro MAX
 * `r5T` - 5k Tall, the 4:3 mode (H10)
 * `r5X` - 5k eXtreme, the 8:7 mode (H11-13)
 
### Frame rates: 
 * `p24` - 24 fps
 * `p25` - 25 fps
 * `p30` - 30 fps
 * `p50` - 50 fps
 * `p60` - 60 fps
 * `p100` - 100 fps
 * `p120` - 120 fps
 * `p200` - 200 fps
 * `p240` - 240 fps
 * (only supports existing frame rates, so p65 or p1000 will be ignored.)
  
### Timelapse and NightLapse frame rates: 
 * `p2` (0.5s or 2Hz/2p capture)
 * `p1` (1s interval)
 * `p.2` (2s interval) 
 * `p.5` (5s interval) 
 * `p.10` (10s interval) 
 * `p.30` (30s interval) 
 * `p.60` (1 min interval) 
 * `p.120` (2 min interval) 
 * `p.300` (5 min interval) 
 * `p.1800` (30 min interval) 
 * `p.3600` (1 hour interval) 
 * (only supports existing frame rates, so p.1234 will be ignored.)

### Lens - FOV: 
 * `fN` - Narrow (older models)
 * `fM` - Medium (older models)
 * `fW` - Wide
 * `fL` - Linear
 * `fS` - Superview 
 * `fV` - HyperView (H11-13)
 * `fH` - Horizonal Level + Linear (H9-13)
 * `fX` - SuperMax Wide (Max Lens Mod)
 
### Audio (Raw controls): 
 * `aL` - Low Processing
 * `aM` - Medium Processing
 * `aH` - High Processing

### Bitrate: 
 * `b0` - Standard Bitrate
 * `b1` - High Bitrate

### Color: 
 * `cF` - Color Flat
 * `cG` - Color Vibrant (old GoPro Color)
 * `cN` - Color Natural (H10-13)

### Depth (H11/12 only): 
 * `d0` or `d8` - 8-bit color
 * `d1` or `d10` - 10-bit color

### EIS (Hypersmooth control): 
 * `e0` - Off     
 * `e1` or just `e` - On
 * `e2` - High
 * `e3` - Boost
 * `e4` - Auto 
 
### Exposure Lock: 
 * `eL0` - Off     
 * `eL1` - On
 * `eL2` to `eL9` -  Lock after 2 to 9 seconds.

### Hindsight (Video modes H9-13): 
 * `hS0` - Off     
 * `hS1` - On 15s window
 * `hS2` - On 30s window
 * `hS5` - Experimental Labs H11-13 - 5s window

### White Balance (only this WB settings): 
 * `wA` - Auto White Balance
 * `w23` - 2300K White balance
 * `w28` - 2800K 
 * `w32` - 3200K 
 * `w40` - 4000K 
 * `w45` - 4500K 
 * `w50` - 5000K 
 * `w55` - 5500K 
 * `w60` - 6000K 
 * `w65` - 6500K 
 * `wN` - Native White Balance

### ISO Minimum and Maximum (set to together with format i(max)M(min)):
(All cameras and Older Labs):<br>
 * `i1M1` - 100 ISO Max & Min
 * `i2M1` - 200 ISO Max with 100 ISO Min
 * `i4M1` - 400 ISO Max with 100 ISO Min
 * `i8M1` - 800 ISO Max with 100 ISO Min
 * `i16M2` - 1600 ISO Max with 200 ISO Min
 * `i16M4` - 1600 ISO Max with 400 ISO Min
 * `i16M8` - 1600 ISO Max with 800 ISO Min
 * `i32M1`  - 3200 ISO Mac with 100 ISO Min
 * `i64M16` - 6400 ISO Mac with 1600 ISO Min
 * `i1S180` - 100 ISO Max with a 180 degree shutter angle
 * `i16S22` - 1600 ISO Max with a 22 degree shutter angle
 * `i1S0` - 100 ISO Max with an **Automatic** shutter angle<br>
Note: Angles between 22 and 1 degrees are supported. Experiment for higher shutter speeds. You will need a good amount of light and/or a higher ISO.  Only ISOs of 100, 200, 400, 800, 1600, 3200 and 6400 are support (although not all modes support the full range.)

### EV Compensation: 
 * `x0` - EV 0 default
 * `x-.5` - EV -0.5
 * `x.5` - EV +0.5
 * `x-1` - EV -1.0
 * `x1` - EV +1.0
 * `x-1.5` - EV -1.5
 * `x1.5` - EV +1.5
 * `x-2` - EV -2.0 
 * `x2` - EV +2.0<br>
 on some cameras models you can extend this to +/-6 EV (beyond the range the camera menu supports).
 * `x-5` - EV -5.0
 * `x3` - EV +3.0
 
### Sharpness: 
 * `sL` - Low
 * `sM` - Medium
 * `sH` - High
 
### Night Photo exposure time: 
 * `eA` - Auto exposure
 * `e2` - 2s shutter
 * `e5` - 5s shutter
 * `e10` - 10s shutter
 * `e15` - 15s shutter
 * `e20` - 20s shutter 
 * `e30` - 30s shutter

### GoPro MAX/360 Shooting Modes:
 * `mH` - mode Hero
 * `mHF` - mode Hero Front
 * `mHR` - mode Hero Rear
 * `m3` - mode 360°
 * `m3F` - mode 360° front on LCD
 * `m3R` - mode 360° rear on LCD
 * `mF` - mode monitor Front lens
 * `mR` - mode monitor Rear lens
 
### GPS Active:
 - `g0` or `gO`: GPS off
 - `g1` or `g`: GPS on
 
### Touch Active (H13/MAX2 only):
 - `tE`: Touch screen input enabled
 - `tD`: Touch screen input disabled
 
### Quick Capture:
 - `q0` or `qO` : off
 - `q1` or `q1` : on
 
### Voice Commands:
 - `v0` or `vO`: off
 - `v1` or `v1`: on
 
### Option (‘o’) commands:
#### Brightness of the LCDs: 
 - `oB0`: LCD brightness 0%
 - `oB1`: LCD 10%
 - `oB4`: LCD 40%
 - `oB7`: LCD 70%
 - `oB9`: LCD 100%
#### Camera Auto Off Timer to preserve battery:
 - `oC0`: Never auto off
 - `oC1`: 1 min auto off
 - `oC5`: 5 min auto off
 - `oC15`: 15 min auto off
 - `oC30`: 30 min auto off
#### Turn all the LCD screens off:
 - `oDO`: turn the LCDS off now
#### LED tally lights to show when the camera is recording:
 - `oD0`: all LEDs off
 - `oD2`: some LEDs on
 - `oD4`: all LEDs on
#### Protune Noise Reduction control (HERO13 only):
 - `oN0`: High
 - `oN1`: Medium 
 - `oN2`: Low
#### Rotation, Camera Orientation:
 - `oR0`: Auto orientation 
 - `oR1`: Up 
 - `oR2`: Down
 - `oR2`: Left
 - `oR3`: Right 
#### Screen Auto Off:
 - `oS0`: LCD screens never timeout
 - `oS1`: 1 min timeout
 - `oS3`: 3 min timeout
#### Volume of Beeps:
 - `oV0`: Muted
 - `oV1`: 10% volume
 - `oV3`: 30% volume
 - `oV7`: 70% volume
 - `oV9`: maximum volume
#### Wireless/WiFi Connections:
 - `oW0`: Wireless off 
 - `oW1`: Wireless on
#### Front LCD controls:
 - `oF0` front LCD off
 - `oFU` UI info only
 - `oFF` Full image
 - `oFC` Cropped image
 - `oFN` Never turn off
 - `oFM` Match rear screen
 - `oF1` off in 1 minute
 - `oF2` off in 2 mins
 - `oF3` off in 3 mins
 - `oF5` off in 5 mins
#### External Audio options (via Media Mod):
 - `oE1` - Standard Mic
 - `oE2` - Standard+ Mic
 - `oE3` - Powered Mic
 - `oE4` - Powered+ Mic
 - `oE5` - Line In (HERO10-13)
#### Language:
 - `oL0` - English USA
 - `oL01` - English UK
 - `oL02` - English Aus
 - `oL03` - English India
 - `oL1` - German
 - `oL2` - French
 - `oL3` - Italian
 - `oL4` - Spanish
 - `oL5` - Chinese
 - `oL6` - Japanese
 - `oL7` - Korean
 - `oL8` - Portuaguese
 - `oL9` - Russian
 - `oL91` - Swedish
#### Time and date:
 **oT**yymmddhhmmss.sss for precision date and time e.g. `oT241208174033.556` for 2024 December 8, at 5:40:33.556pm 
 - `oTD1` for daylight savings on 
 - `oTD0` for daylight savings off
 - `oTZ-7` or `oTZ-420` e.g. -7 hour or -420 minutes timezone offset
 - `oTZ6` or `oTZ360` e.g. 6 hour or 360 minutes timezone offset
 Shortcut Menu Types (to be used with oSA, oSB, oSC and oSD):
 * **oSAx** - Top Left Shortcut x is from the table below e.g. `oSA1` zoom is the top left
 * **oSBx** - Bottom Left Shortcut x is from the table below  `oSB5` ISO is the bottom left
 * **oSCx** - Top Right Shortcut x is from the table below  `oSC27` Hindsight is the top right
 * **oSDx** - Bottom Right Shortcut x is from the table below  `oSD6` shutter is the bottom right

| Shortcut Menu Feature                                                        |
|------------------|----------------|-------------------|----------------------|
|0 - clear shortcut|8  - burst rate |15 - ISO max       |24 - horizon control  |
|1 - zoom          |9  - duration   |16 - mic type      |25 - speed ramp       |
|2 - fov           |10 - color      |18 - raw audio     |26 - scheduled capture|
|3 - slowmo        |11 - EV comp    |19 - sharpness     |27 - hindsight        |
|5 - white balance |12 - hypersmooth|20 - timer         |28 - 10-bit           |
|6 - shutter       |13 - interval   |21 - timewarp speed|29 - nightphoto       |
|7 - bit rate      |14 - ISO min    |23 - wind noise    |30 - trail length     |

### HERO11-13 UX modes: (limited, best to use the camera menu)
- `mE` - mode Easy
- `mPR` - mode Pro

### Print Messages ###
Anything within quotes that is not being store in an FourCC metadata field will be printed to the screen for one second.
- "Hello World" - prints the Hello World message.
- "Set Video\nMode"mV - prints Set Video Mode over two lines, and set the mode to video with the `mV` command.
- "Current mode $v" - $v is one of the system variable (see below), v display the camera current mode.
- "Temperature\n $p:T C" - $p:T system variable for processor Temperature (see below), prints text "Temperature" on a new line value of the temp in C.

## Action and Conditional Commands
Now you know how to set up your camera with QR commands, the fun really begins with Actions and Conditionals. Actions are starting `!S` or ending a capture `!E`, manual upload `!U`, 
beginning a live stream `!G`. As these actions are typically just pressing a button or camera menu, these actions can be enhanced based on time. e.g. `!08:00S`, which will sleep 
the camera until 8am, and then start capture (in the camera's default mode.) We can also do an conditional capture based on time. e.g. `>06:00<19:00mV~mNL!S` with this command, if the 
time is greater than 6am and less than 7pm, set mode Video, else set mode NightLaspe, then start.  You can start pre-programming actions with QR codes.

### The Full List of Actions
* **!**time**Bx** - <sup>H11-13</sup> Beeps and Blinks, `!B` - Blink once, `!B0` - Beep once, `!B1` - Blink+Beep once, `!B2` - Blink+Beep twice
* **!**time**Cx** - <sup>H10-13</sup> Up to x GBs to make sure is clear on the SD card. e.g `!C16` - clears up to 16GB. If more than x is available, no files are removed. x is limited to half SD size. Deletes the oldest media first. 
* **!**time**C or CA-CZ** - <sup>H13</sup>Clear location distance for system variables c, c:A thru c:Z
* **!**time**Dx** - <sup>H10-11</sup> !Dx wait for GPS lock with a DOP less than x, then sync time. For time only locks `!D` is fine. For high precsion try `!D10` 
* **!**time**E** - End at <time> if in hh:mm form, or after n seconds. e.g. `!20:00E` - End at 8pm or `!120E` - End after 2 minutes (120s).
* **!**time**Fx** - Frame Grab (LCD) at <time> - 'x' grab next x Labs messages. e.g. `!F` frame grab now or !F3 frame grab teh next 3 Labs events
* **!**time**G(S or M or L)(C)** - Start Live-streaming, e.g. `!GS` - start at 480p, `!GM` - start at 720p, `!GL` - 1080p, optional `C` for capture a local file like `!GLC`
* **!**time**N** - No Action until exact <time>, useful if you just need a pause. e.g. `!11:30N` - Pause (Sleep) until 11:30am or `!90N` - Sleep for 90s.
* **!**time**NQ** - No Action until at approximately <time> (more power efficient). e.g. `!09:50NQ` - Pause (Sleep) until approximately 9:50am or `!180NQ` - Sleep for approx 180s.
* **!**time**O** - Off, shutdown the camera. e.g. `!O` Off now or `!5O` Off in 5 seconds. Never use this in a script (talking to you ChatGPT) if you script is repeating, as this stops everything. 
* **!**time**OR** - shutdown and restart the camera. e.g. `!OR` Off and restart now or `!2O` Off in 2 seconds, then restart
* **!**time**R** - Repeat the whole command. e.g. `!1R` repeat the whole command in 1 second or `!08:00R` repeat at 8am.
* **!**time**RQ** - Repeat Quickly at approximately <time> (more power efficient). e.g. `!08:00RQ` repeat the whole command at approximately 8am.
* **!**time**Rx** - <sup>H11-13</sup> Repeat the command starting at position x (i.e. a goto command). e.g. `!R5` repeat start at command character 5. 
* **!**time**S** - Start at exactly <time> if in hh:mm form, or after n seconds. e.g. `!20:00S` - Start at 8pm or `!5S` Start in 5 seconds.
* **!**time**SQ** - Start Quickly at approximately <time> if in hh:mm form, or after n seconds. !timeSQ commands are a bit more power efficient than !timeS. e.g. `!18:00SQ` - Start at approx 6pm or `!60SQ` Start in 60 seconds approximately.
* **!**time**TR** - <sup>H11-13</sup>  `!TR`- switch active TimeWarp to Realtime (or slow motion)
* **!**time**TN** - <sup>H11-13</sup>  `!TN` - switch active TimeWarp to Normal (speed-up timelapse mode)
* **!**time**U** - `!U` Attempt a network contention and Upload now <sup>9/10/11/12/13</sup>.
* **!**time**W** - Connect to a network, requires JOIN metadata to have been previous stored <sup>9/10/11</sup>.
* **!**time**X** - `!X` exist script now <sup>H10-13/MAX</sup>. 
* **!**time**Zx** - <sup>H10-13</sup> `!Z3` - mute both buttons, `!Z2` - mute only mode, `!Z1` - mute only shutter, `!Z0` - unmutes both

### Capture Triggers (Classic method)
* **!**time**SMs-t** - Start Motion detection with start sensitivity 's' and stop sensitivity 't' -- 't' field is optional. e.g. `!SM5` start with motion detection a level 5 sensitivity. 
* **!**time**SMsDdMmHh** - Start Motion detection with sensitivity 's', Delay of 'd', Mask of 'm' and Hold for 'h' seconds (D,M and H fields are all optional.) e.g. `!SM3D1H5` start with motion detection a level 3 sensitivity, delay 1s and hold for 5s. 
* **!**time**SKs-t** - Start Speed capture at threshold 's' km/h and stop at 't' km/h -- 't' field is optional.  e.g. `!SK45-30` start with speed 45kmph, end with speed 30kmph 
* **!**time**SKsHh** - Start Speed capture at threshold 's' km/h and Hold for 'h' seconds (H fields are all optional.)  e.g. `!SK30H15` start with speed 30kmph and hold for 15s. 
* **!**time**SAs-tDdHh** - Accelerometer Trigger e.g. `!SA5` start with accelerometer sensitivity 5 
* **!**time**SGs-tDdHh** - Gyro Trigger e.g. `!SG3` start with gyro sensitivity 3 
* **!**time**SIs-tDdHh** - IMU Trigger (both Accelerometer and Gyro) e.g. `!SI7` start with IMU sensitivity 7 
* **!**time**SDs-tDdHh** - Speed Pressure Level  (SPL) Trigger, 's' and 't' values are in dB. e.g. `!SD90` start with SPL of 90dB

### more examples:
* `!S` - start now  
* `!07:00S` - start at precisely 7am, the camera will shutdown and sleep until 7am.  
* `!300SQ` - start in approximately 300 seconds, it will shutdown and sleep for ~300s.  
* `!N` - short pause around 500ms.  
* `!2N` - pause for seconds 2s.
* `!20N` - pause for seconds 20s. Any pause for greater than 9 seconds will shutdown and sleep the camera.  
* `!60E` - end after 60 seconds (End commands are not used for photos.)
* `!2R` - repeat after 2 seconds
* `!s-01:00S` - start one hour before sunset, the camera will shutdown and sleep until one hour before sunset.  
* `!nS` - start at true noon.
* `!s1200E` - end 1200 seconds after sunset
* `!r-600S` - start 600 seconds before sunrise
* `!17:00W!GLC` - start Live-streaming 1080p at 5pm, saving a local copy

### New timing commands (HERO13 2.04.70 or later):
There is a new interval time representation. Previously sleep alarms were absolute times, e.g. !10:00N or just pauses relative to now: e.g. !600N. 
But users have been requesting photos on the hour or similar, which was harder to do as commands like !3600N would drift a few seconds with each call.
e.g. commands like !60R - sleeps for ~60 seconds, but this will drift over time, 10:00:00, 10:01:04, 10:02:07...<br>
Now you can use:<br>
!00;01R sleeps until the next clock minute, no drift: 10:00:00, 10:01:00, 10:02:00...<br>
!00;05R sleeps until the next clock 5 minute: so 10:00, 10:05, 10:10, 10:15...<br>
!01;00R sleeps until the next hour so 10:00, 11:00, 12:00...<br>
<br>
A daily command to shoot precisely hourly between 8am and 6pm simplifies to:<br>
!01;00NmP!S!1N>18:00!08:00R!R<br>
<br>
This was added for a second reason, as with no drift, you now know when your camera might be busy (for cameras in remote places.) 
This supports a more significant change: the ability to use Quik and Labs scripts at the same time. Previously any sleep command would shutdown BLE and 
all wireless services, while this does help with power/battery life, the second reason it would prevent Quik breaking a running script. 
Now Labs is aware is was woken via BLE, and the behavior now supports a Quik connection, control and data off load, then the script will 
continue when you press camera off from within Quik. If you are using the new clock relative sleeps, Quik download time will not likely 
mess up your interval on your timelapses.<br>

### Storing metadata (Permanent, survives power off)
#### Old style (old cameras up to HERO9, supported by all models)
* **!M**fourcc**=<courier>"string"</courier>**
* **!M**fourcc**=Number metadata** (comma separated)

#### New style (support HERO10 onward)
* **\***fourcc**=<courier>"string"</courier>**
* **\***fourcc**=Number metadata**  (comma separated)

#### Example for display the owner’s name
* `*OWNR="Joe Bloggs"`  - Within the quotes spaces are allowed.
* `*OWNR="Jill Bloggs\n(555)-252-5555"`  - the addition of "\n" allows for a new line.
* `*OWNS="Jill and Joes\n(555)-252-5555\njandj@yahoo.com"`  - multi-line example

Note: All strings must use <courier>"</courier> (ASCII 34) and not the <courier>”</courier> (148) character.  

All tags between **OWNA** and **OWNZ** will be displayed and stored in **GoPro-owner.txt**.

All tags between **OWNa** and **OWNz** will be only stored in the **GoPro-owner.txt**

Any four character code can be used for store other information. You can also store numeric data examples: 
* `*CAMR=53` - metadata CAMR will be 53 
* `*ABCD=45.234` - metadata ABCD will be floating point 45.234
* `*UNIT=-1723` - metadata UNIT will be -1723 
* `*LLTZ=32.707,-117.1576,-7` - set camera location (GPS off) with Latt/Long/TimeZone 

### Storing Temporarily Metadata (until power off)<br>
#### Old style (old cameras up to HERO9)
* **oM**fourcc**&#61;<courier>"string"</courier>**  
* **oM**fourcc**=Number metadata** (comma separated)

#### Storing Temporarily Metadata (New style - HERO10 onward)
* **$**fourcc**&#61;<courier>"string"</courier>**  
* **$**fourcc**=Number metadata** (comma separated)

Any four character code can be used for store other information. This data will be temporarily stored
* `$CAMA=53` - metadata CAMA will be 53 
* `$AAAA=45.234` - metadata ABCD will be floating point 45.234
* `$UNTS=-1723` - metadata UNIT will be -1723 
* `$LLTZ=32.707,-117.1576,-7` - set camera location (GPS off) with Latt/Long/TimeZone 

### Metadata extraction
All metadata in stored in a GPMF format with the MP4, 360 or JPG files, this is an open source, so if it free to integrated within any third party tool. 
The above global metadata can be extracted with this [**demo web tool**](../metadata)

### Some Four Character Codes are reserved for feature extensions
* **24HZ** H10-13/M2: enable film standard 24.0 frame, rather than the default broadcast standard 23.976. The existing 24p mode(s) will have the new frame rate when this is enabled, all other video modes are unaffected. Input Data: 1-enable, 0-disable. e.g. `*24HZ=1`
* **64BT** H8-10/M1-2: 12GB Chapter sizes on HERO8/9/10 and MAX cameras (default on H11+), 64GB chapters on MAX2. Note: Will not be active for QuickCaptures. Input Data: 1-enable, 0-disable WARNING: Larger chapters will not playback on camera or support USB transfers, but are compatible with desktop tools. Permanent required. e.g. `*64BT=1`
* **64BT** H11-13/M2: These camera default to 12GB Chapter sizes, but support larger. Note: Will not be active for QuickCaptures. Input Data: x-size in MBs, 0-disable. Permanent required. e.g. `*64BT=32000` for 32GB chapters.
* **ALLI** M2 only: Like 24HZ, this also makes 29.97 -> 30.0 and 59.94 -> 60.0. All integer frame frames. e.g. *ALLI=1
* **ARCH** H8-13/M1-2: Archive mode: an ultra simplified video camera mode for novices documenting critical events, where you don’t want the camera mode modified. Either button will start and stop video capture. Input Data: 1-enable, 0-disable WARNING: only removable via the disable command. Permanent required. e.g. `*ARCH=1`
* **AUDS** H10-13: Audio Level: displays the current estimate of the sound pressure level in dB. Input Data: 1-enable, 0-disable. e.g. `$AUDS=1`
* **B001** thru **B999** M2 only: preset friendly B001 to B999 for bitrate control e.g. B180 in a preset name will be 180mbs
* **BASE** H8-13/M1-2: Base file name change, adding to beginning of the filename. Input: H10-13 supports wildcards within [ ]: like [yyyy-mm-dd] or [HH-MM-SS]  e.g. A-[yyyymmddHHMMSS] WARNING: GoPro App and cloud will not support renamed files. e.g. `*BASE="CamA-[yy-mm-dd]"`
* **BERS** H10-13: Bypass ERS compensation, extremely rare usecases. Input Data: 0-display, 1-enable, 2-enable only with EIS off e.g. `*BERS=2`
* **BIAS** H9 only (new cameras use EVBS): Bias is like EV Compensation, but it can only be used after recording has began. It is a hack designed to tweak exposure during a livestream or webcam session. Input Data: Number of stops between -6 and 6, supports half stops like 3.5.
* **BITR** H10-13/M1-2: set the compression in Mb/s for the Protune High Bitrate setting. Normally this would be around 100Mb/s, however higher (or lower) rates may be achieved with newer SD Cards.Input Data: MB/s from 2 to 200. e.g. `*BITR=180`
* **BITH** H10-12: set the compression for LRVs in Mb/s. Normally this would be around 4Mb/s, however higher (or lower) rates may be achieved with newer SD Cards. Input Data: MB/s from 1 to 100. 
* **BITL** H11-13: controlling the livestream maximum bitrate (up to 8Mbit/s). Input Data: MB/s from 1 to 8.
* **BOOT** H7-13/M1-2: Boot command can be dangerous, but a safe way to use them is to store the script on the SD Card. So the boot command would be `*BOOT="!Lbt"` which attempts to load a file bt from the MISC folder of the SD card. So creating boot command should always use the formatting `*BOOT="!Lbt"!SAVEbt="your script"` e.g. `*BOOT="!Lbt"!SAVEbt=!12:00NmP!S!1R`
* **BURN** H8-13/M1: Add date, time and other burn-in text to your video. Input Format (0,height)[yyyy-mm-dd HH:MM:SSaa] examples:   (0,30)Local Time: [HH:MMaa]   (0,26)Local Time: [HH:MM:SSAA]   (0,40)©[yyyy]\ XYZ Inc.   (0,24)Shoot Date [yy/mm/dd]
* **BRNP** H8-13/M1: The burn-in position for overlays or LOGO display. Input Data (select 1 of 8): TL, TC, TR, ML,BL, BC, and BR\nT-Top B-Bottom C-Center L-Left and R-Right.
* **BRNT** H8-13/M1: The overlays or LOGO display time in seconds. e.g. BRNT=0.016 will display the logo or text overlays only on the first frame. Input Data: 0 is unlimited, or 0.01 to 3600 seconds.
* **BRNX** H8-13/M1: Offset the overlays or LOGO display with X,Y pixel coordinates. Input Data: x,y pixel coordinates.e.g. 120,40
* **BYPS** H11-13/M1-2: Bypass common pop-ups, such as resetting the time and date. Remember to set time and date if you remove the battery. Input Data: 1 to bypass, 0 for normal notifications. e.g. `*BYPS=1`
* **CBAR** H9-13: enable a small 75% saturated color bars for video tools evaluation. Most cameras limit overlays to 4K30, 2.7Kp60 or lower. Input Data: 1 to enable, 0 to disable
* **COOL** H12-13/M2: offset white balance for the blue channel. $COOL=40 will add 40% more gain to the blue channel.
* **DAMP** H10-13/M2: Control over the auto-exposure damping. Setting the DAMP to 1 is the default, setting to 10 would slow the camera’s exposure adjustments 10X.Input Data: 0.1 to 10000. e.g. `$DAMP=10`
* **DAUD** H10-13: Disable Audio in video captures, all MP4 files will have no audio track. Application: high bit-rate drones video.Input Data: 1 to disable audio, 0 to re-enable
* **DBGL** H8-13/M1-2: Enables more debug logging. Labs saves it logs to the SD card under MISC/qrlog.txt. Using this extension increases the details and logged events. e.g. To see more logging from boot up use `*DBGL=1`
* **DIST** H13/M2: Time-Lapse Video Distance, x is a GPS travel distance between exposures in meters, rather than time for an in-camera computed timelapse. So `$DIST=5` will set a 5 meter interval for TLV. One exception is when x=1, 10 meters will be used, 1 meter is too noisy (GPS errors.) So this feature is good for 2 meters of larger. For shorter distances or a higher speed, you the new TLV sample rate for 4Hz (p4), for the best distance precision. e.g. `mTr5Xp4$DIST=5`
* **DIVE** H12-13: Optimizing the Hypersmooth stabilization for underwater. It might be no surprise, but HyperSmooth is designed for the camera operation above the water's surface, underwater there is typically less camera shake, and HS is still 70% effective at removing shake. The hack adapts HS to use the refractive index (RI) of water (defaults to 1.335, good for fresh and command salt water), to remove closer to 100% of unwanted shake. Note: if you know your area's RI is significantly different, use DIVE=r, where r can be 1.3 to 1.45 is supported. e.g. `$DIVE=1` for most underwater captures. To create a dive preset use `mV$PRES="14,DIVE"mV`
* **DLRV** H10-11: Disable LRV file creation. Application: high bit-rate drones video. Input Data: 1 to disable LRVs, 0 to re-enable. e.g. `*DLRV=1` to permanently disable LRV files.
* **DPTS** M2 only: stitch depth change smoother, 1 - fast, 15 - smooth. 360 experimental.
* **DPTP** M2 only: stitch depth change speed, 1 - slow, 7 - fast (like DPTS with a different implementation). 360 experimental.
* **DPTL** M2 only: stitch depth lock stitch after x seconds, 1 - immediate, 2-99 - seconds, 100-99999 - milliseconds. 360 experimental.
* **DSPC** H7-13/M1-2: Labs text display contrast. Set the background opacity for Labs text on the LCD. Input Data: Number from 0-transparent to 6-completely opaque.
* **DSPL** H7-13/M1-2: Labs text display length. How long to display each Labs message, like owner information (OWNR). The default is 1 second. Input Data: Number from 1-9 seconds or 10-9999 milliseconds.
* **ENCR** H9 only: Experimental media encryption, using a password to prevent playback by non-authorized users. As the QR Code with the password is not encrypted, do not print or save the QR code image.Enable by using password between 4 and 16 characters. Disable with an empty password.
* **DECR** H9 only: Decryption of media encryption with ENCR.  Warning: If the passwords do not match, the data is doubly encrypted, there is no recovery of the data. Be careful. This operation is slow, USB power or have a full battery.Input a matching password
* **EVBS** H10-13/M1-2: This is an EV compensation value that works with webcam and livestreaming, it can be changed live (with QRDR=1) and it is global, adding the any existing EV control in your presets.Input Data: range -4 to 4.
* **EXPQ** H11-13/M1-2: Min and Max Shutter speed, 1/x format. Input Data: 24 to 8000, representing 1/24 and 1/8000s, 0 to disable. e.g. `$EXPQ=120`
* **EXPS** H11-13/M1-2: Video exposure values: ISO and Shutter speed, rendered to the LCD. Handy for those using ND Filters. Input Data: 1 to enable, 0 to disable (2 smoother rendering.) 
* **EXPX** H10-13/M1-2: Max Shutter speed (shortest exposure time), 1/x format. EXPX is a good control to set the look for stabilization in lower light. Input Data: 24 to 8000, representing 1/24 and 1/8000s, 0 to disable. e.g. `$EXPX=120`
* **EXPN** H10-13/M1-2: Min Shutter speed (longest exposure time), 1/x format. EXPN is a good to ensure you have motion blur, you may need ND filters. Input Data: 24 to 8000, representing 1/24 and 1/8000s, 0 to disable.  e.g. `$EXPN=240`
* **EXPT** H7-13/M1-2: Video Exposure Control through Maximum Shutter Angle for video modes. Can improve stabilization in low light. Input Data: Number 0 through 5 stops.  0-360° (camera default), 1-180°, 2-90°, 3-45°, 4-22.5° etc.
* **FAST** H10-13/M1-2: Faster and fewer Labs notifications on boot. Input Data: 1-enable, 0-disable. e.g. `*FAST=1`
* **FEAT** H10-13/M1-2: Displays Labs enabled Features for x seconds. Input Data: x-seconds.  e.g. `$FEAT=4`
* **GAIN** H9-13: Digitally gain up the audio. e.g. \$GAIN=12, increase audio by 12dB. Will likely reduce the dynamic range.Input Data: 0-48 in dB.
* **GAMA** M2 only: Gamma control for easier HDRI work, gamma equivalent of LOGB. e.g. $GAMA=2.2 for standard 2.2 gamma curve.
* **GCMP** H11-13/M1-2: Disable Gryo Compensated Exposure.  When GoPro camera modes, it normally uses a faster shutter for improved stabilization, this control disables this feature.Input Data: 1 to disable gyro comp, 0 - default
* **GPSL** H13/M2: enable continous GPS location logging, even when not capturing, so the capture can log more of you path and adventures, simply have the camera on. Path is saved by day into MISC/GPS-yy-mm-dd.gpmf file. GPSL=1 logs everything, GPSL=x will only log movement great than x meters from the last stored location. e.g. $GPSL=10 to log evert meters.
* **GUID** H11-13/M1-2: On screen guides lines for output aspect ratios. e.g. \$GUID=2.35, set shooting guides for cinescope. Input Data: List of aspect ratios (up to 8) as real numbers, so 16:9 is 1.778 and 9:16 is 0.5625.  e.g. `$GUID=1.778,0.5625`
* **GUIC** H11-13/M1-2: Color/brightness of guides lines. Input Data: List of guide brightness (up to 8).  e.g. `$GUIC=10,255`
* **HDMI** H8-13: Media Mod users can change the output default from Gallery, to clean monitoring with no overlays, or monitoring live video with On Screen Display overlays. Input Data: 0-Galley, 1-Clean Video, 2-Video+OSD e.g. `*HDMI=1`
* **HIST** H7-13/M1-2: Enable a histogram with with a range of contrast options. Input Data: Number 1 to 11 enables the histogram with contrast 1 through 11, 0 will disable it. e.g. `$HIST=5`
* **HSTP** H11-13/M1-2, not Mini: Histogram position and size. A negative position will place the histogram on the front LCD. Input Data: x,y,size as percentages. e.g. `$HSTP=16,8,44`
* **HNDL** H7-13/M1-2: Set the camera ID to limit which cameras to respond to a QR Code. Used with the hZ command, where Z is the bit mask for which cameras will follow the command. Input Data: ID Number from 1-31. Usage: h6mP!S ← runs on cameras with IDs 2 or 3.
* **HSTO** H9-13: Number minutes controlling the length of the Hindsight timeout, changing from the default for 15 minutes. Input Data: minutes from 5-1440. e.g. `*HSTO=180`
* **IFRM** M2 only: Change the HEVC compression to use I-Frame only (experimental) e.g. *IFRM=1
* **IWFR** H10-11: Increased Write FRequency to support for higher precision file recoveries (defaulted on with *BITR=x bitrate changes). This hack increases the rate in which video data is flushed to the SD Card, improving the recoverability for footage. Great for FPV users.
* **JOIN** H7-13/M2: Setup storing your WiFi network credentials.Input Data: String in the format your_ssid:your_passphase e.g. HomeWiFi:Pass1234
* **LBAR** H9-13: enable a small luma sweep for video tools evaluation. Most cameras limit overlays to 4K30, 2.7Kp60 or lower. Input Data: 1 to enable, 0 to disable
* **LEVL** H11-13/M1-2: enable on-screen spirit level. Input Data: 1-9 sets the size of the level, 0 to disable.  e.g. `*LEVL=5`
* **LLTZ** H7-13/M1-2: Manual location: using Sunset/Sunrise triggers without waiting for a GPS lock. Input Data: numbers in the format latitude,longitude,timezone e.g. `$LLTZ=33.126,-117.327,-8.0`
* **LOGB** H11-13/M2: Extremely advanced users. Change the Log base for very flat encoding. Color Flat is Log base 113. Math:out = log(in*(base-1)+1)/log(b). Should be combined with Flat and 10-bit settings. Input Data: base,[offset]e.g. 200,-128 or 400. e.g. $LOGB=400 for GPLog equivalent
* **LOGO** H9-13: Activate a small logo (under 64K pixels) to render within the video. There must be a PNG file stored on the SD card in the MISC folder. Most cameras limit overlays to 4K30, 2.7Kp60 or lower. Input Data: String e.g. Logo.PNG for the name of your image
* **LOWL** M2 only: Low Light more, working the same as GCMP, this will bias towards a longer shutter for lower noise, but will less stabilization. e.g. *LOWL=1
* **MUTE** H9-13: Mute one or more channels of audio. e.g. \$MUTE=15 mutes all channels, for a single channel use 1 = first, 2 = second, 4 = third and 8 = fourth channelInput Data: 0-15, the value is binary mask.
* **NR01** H11-13/M2: Noise reduction control, for advanced user intending noise reduction in post. Likely needs a higher BITR. Input Data: 1-100, is the default full denoise processing in camera. 1 - leaves the most noise. 0 - disables e.g. `$NR01=1` for maximum noise (denoise off)
* **NR02** thru **NR09** M2 only: preset friendly NR01 to NR99 for noise reduction percentage e.g. NR25 in a preset name will be 25% noise reduction.
* **OLTC** H12-13: Offset for LTC timecode in frames, enabling calibration you are seeing any offset..Input Data: x - frames.
* **OWNR** H7-13/M1-2: Display Owner information. This written into every MP4 and JPGs metadata, and MISC/GoPro-owner.txt file.Input Data: String up to 64 characters using '\\n' for a newline. Permanent required.
* **OWNr** H7-13/M1-2: Owner information, not displayed. This written into metadata, and MISC/GoPro-owner.txt file.Input Data: String up to 64 characters using '\\n' for a newline. Permanent required.
* **PMSG** H11-13/M1-2: Message to display during a Labs looping script, so you know the camera is running something custom. Input Data: Any label less than 20 characters, or empty to disable.
* **PRES** H12-13/M2: Create a new preset with custom name and icon. Input Data: Icon number 0 thru 32, preset name up to 15 characters. e.g. `$PRES="14,Scuba"` On HERO12 and 13, present name that use FourCC commands with enable those command only when the user selects that preset.  e.g. `$PRES="14,DIVE WBLK"` creates a preset called "DIVE WBLK" that enables the DIVE and WBLK extensions. Note: While oMPRES and $PRES are using "temporary" metadata style commands, the preset created is not temporary, it will remain until the user removes it.
* **PRXY** H10-13: Store LRV files as NLE ready proxies. Normally a camera will encode an LRV (Low Res Video) for every MP4, with this enabled LRVs are made MP4s within a subfolder. Input Data: 1-move LRVs, 2-move THMs, 3-both, (v2.1) 4-No _Proxy name. 0-disable
* **QRDR** H7-13/M1-2: Detect QR Codes while recording and during Quik previews. This also enables Labs BOOT commands to work with QuikCapture in recent models. Can be used for changing a video burn-in message in the middle of a live-stream. This also allows you to end a capture via a QR Code (command: !E).  Input Data: 1-enable, 0-disable
* **RLTC** H12-13: Read LTC timecode from audio inputsInput Data: 1-Enable, 0-Disable.  e.g. `*RLTC=1`
* **RTMP** H8-13: RTMP Address to livestream to. Combined with JOIN Metadata, use `!W!GLC` to start a 1080p livestream. Input Data: String of the RTMP URL, e.g. rtmp://live.twitch.tv/app/live_1234567. Permanent required.
* **SHMX** H8-9 & MAX: Photo shutter maximum exposure time: this is similar Maximum Shutter Angle (EXPT), except it applies to Photos. e.g. SHMX=1000 would set 1/1000th of a second as the longest shutter time. Input Data: 30-2000.
* **SOLO** H9-13: Use only one channel of audio. e.g. `$SOLO=1` use only channel 1, `$SOLO=4` use only channel 4.Input Data: 0-4, the value is a channel number.
* **SPED** H8-13/M1-2: SD Card Speed Test. Data rates should have minimums above 120Mb/s is you want to reliably capture the high bitrate modes.Input Data: 1-9, number of times to run the test.
* **STOP** H12-13: A Stop Motion extension where is STOP=x the number for frames to store per shutter press. This modify timelapse video. It is recommend to make a stop motion preset with this command `mT$PRES="0,STOP"mTr5Xp4` Works great with the remote. Mode button ends capture. 
* **SYNC** H9-11,13/M1-2: GPS time/timecode sync. With a good GPS signal, the camera’s internal clock will be precisely updated to the millisecond. It will not update the hour or date, preserving your current timezone offset. Input Data: 1-enable, 0-disable. Permanent required. e.g. `*SYNC=1`
* **TCAL** H9-13: Timecode CALibration, help to increase the precision of setting timecode via QR Code. The milliseconds can be positive or negative as needed.
* **TONE** H10-13/M2: Tone-mapping controls. Input Data:   0 - current defaults   1 - global tone-mapping only   2 - both tone-mapping   3 - disable all tone-mapping
* **TUSB** H10-13/M2: Trust USB power. Some USB power sources may report less than they are capable. This modification assumes the USB Power source is 2A minimum, and disables the testing. If you use TUSB with an inadequate power source, expect capture failures. e.g. `*TUSB=1`
* **WAKE** H9-13/M1-2: Conditional wake on any power addition. Inserting a battery or the connection of USB power, will boot up the camera to continue a script after a power failure.  Input Data: 1-wake if there is a delay action pending, 2-wake on power, 0-disable  e.g. `*WAKE=2`
* **WARM** H12-13/M1-2: offset white balance for the red channel. WARM is good to use with DIVE, so you can improve the red respond for deeper dives. `$WARM=50` will add 50% more gain to the red channel.  
* **WBDV** H13 only: White Balance DiVe improvements. Rather than WARM for improving diving white balance, which effects WB the same at all depths, WBDV is more automatic – as the scene gets more blue, the more the red channel is gained up. Currently $WBDV=1 is uses =2.33,4.0 internally (gaining red 4x after red gain hits 2.33), so you can try tuning this yourself e.g. `$WBDV=2.4,3.0`
* **WBLK** H11-13/M2: White balance Lock upon capture. Allows the convenience of auto white balance, without the risk of WB change during capture. Input Data: 1-enable WB Lock, 0-disable
* **WIDE** H11-13/M2: A wide gamut color profile, this supports all in-camera white balancing. Like using white balance Native, without as much post color work. Input Data: 1-enable WIDE gamut, 0-disable e.g. `$WIDE=1`
* **ZONE** H9-13/M1-2: Set the time zone for use with SYNC. Input Data: time zone offset in minutes.

Note: MAX has around H11 Labs capabilities. 

## Macro support (since March, '24)
Added support for macros, or crude scripting subroutines. This expands the potential complexity for QR scripting, as the entire script is no longer limited to 255 characters. 
It would be possible to run scripts nearing ~1.2KB. Note: recursion is supported, macros can call other macros, and can call themselves.

Macros are saved in string FourCCs:
* **$**fourcc**&#61;<courier>"custom Labs commands"</courier>**  (temporary)
* **\***fourcc**&#61;<courier>"custom Labs commands"</courier>**  (permanent)

Example: This macro calculates the Light Value and stores the result in variable **E**<br>
`LVAL="=Ii=Ss=I/100=S/I=E6.25=E*S=E#2"`

 e.g. `*SUBA="mVr4p60'60p'!S!2E!1N"` Note: Use single quotes for text within double quotes.

In a separate QR Code will call LVAL and display the result<br>
`^LVAL"Current LV $E"`

Note: for Macros that print output use single quotes for text within.
`DPLV="^LVAL'current LV $E'"`

### Macros in Presets (Powerful)

Presets names enabling features like DIVE and HIST work fine, but you can't name a preset $EXPN=120. However you can do this, create macros. 
For Presets you need two macros, one for selecting the preset, and another for leaving the preset. 

Set up macro: `*STUF="$EXPN=120$GCMP=1$BITR=180"`

Restore macro (lowercase last character):  `*STUf="$EXPN=0$GCMP=0$BITR=0"`

Name have a preset call "STUF", e.g. `$PRES="0,STUF"`

When the preset is selected it runs `$EXPN=120$GCMP=1$BITR=180`, and when you select another preset it first runs `$EXPN=0$GCMP=0$BITR=0`.

### Macros in Presets running scripts (Crazy Powerful)

Set up a script macro: `*RUNN="=A+1$PMSG='$A looping'!R"`

Set up a shutdown script macro: `*RUNn="$PMSG='done'"`  (can't be empty)

Name have a preset call "RUNN", e.g. `$PRES="0,RUNN"`

Now the script will automatically run with the selection of this preset.

## Reset Actions ##

* `!RESET!1OR` - erase all your permanent metadata (anything that used !Mxxxx command.) Then Reboot. (requires user confirmation.)
* `!FORMAT` <sup>H10-13</sup> for SD formatting via QR Code (requires user confirmation.)
* `!FRESET` <sup>H10-13</sup> Factory reset, erase everything, except QR code metadata (requires user confirmation.)
* `!PRESET` <sup>H10-13</sup> Presets reset, restore the default presets (requires user confirmation.)
* `!WRESET` <sup>H10-13</sup> WiFi Credentials reset, erase all your BLE and WiFi configurations (requires user confirmation.)

## Scripting

The geek factor is highest in this section.  This is close to a Turing-complete language, you can get many interesting capture control jobs done.  There are save and load commands, additive metadata and clock time conditionals

* **!SAVEname=script**  e.g. `!SAVEdaily=dPmP!12:00S!Ldaily` - a save script called ‘daily’ that repeatedly shots one photo every day at noon. 
* **!Lname**  e.g. `!LnightLapse` - load and run a script called nightLapse
* **<courier>"any text"</courier>** e.g. `mV"Video Mode"!S!5E!4NmP"Photo Mode"!S!5R` - this will display <courier>"Video Mode"<courier> and <courier>"Photo Mode"</courier> when switch to those modes.  

### Conditionals Based on Time

**\<** , **>** and **==** characters are used to indicate a conditional: less than, greater than equal, and equal (**==** Since March 2024 firmware)

`<08:45!S` is equivalent to 

> if(current_time < 8:45) <br>
> &nbsp;&nbsp;&nbsp;   Start

`>18:30!R` is equivalent to 

> if(current_time >= 18:30) <br>
> &nbsp;&nbsp;&nbsp;  Repeat

`==10:10!R` is equivalent to
> if(current_time == 10:10) <br>
> &nbsp;&nbsp;&nbsp;  Repeat


The if condition defaults to effecting only the one command after the condition

`<08:45!S"Hello World"` is equivalent to:

> if(current_time < 8:45) <br>
> &nbsp;&nbsp;&nbsp;   Start<br>
> print <courier>"Hello World"</courier>
	
The start will happen if the condition is true, but the print message occurs whether true or false.  To make the print also part of the true state you can use **+** between the joined commands.

`<08:45!S+"Hello World"` is equivalent to

> if(current_time < 8:45) <br>
> {<br>
> &nbsp;&nbsp;&nbsp;    Start <br>
> &nbsp;&nbsp;&nbsp;    print <courier>"Hello World"</courier> <br>
> }

These can be stacked too, e.g. `<08:45!S+"Hello World"+!60E` is equivalent to

> if(current_time < 8:45) <br>
> {<br>
> &nbsp;&nbsp;&nbsp;    Start <br>
> &nbsp;&nbsp;&nbsp;    print <courier>"Hello World"</courier> <br>
> &nbsp;&nbsp;&nbsp;    After 60 seconds End the capture <br>
> }

Conditions support **else** statements using the **~** character after the last 'true' command

`<08:45!S+"Hello World"+!60E~!08:44N!R` is equivalent to

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


Conditionals themselves can be stacked like `>09:15<10:00!S` is equivalent to 

> if(current_time >= 9:15) <br>
> &nbsp;&nbsp;&nbsp; if(current_time <= 10:00) <br>
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Start<br>
	
However the else can only be applied to the last condition. `>09:15<10:00!S+"Hello World"+!60E~!09:30N!R` is equivalent to

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

### Conditionals Based on Camera Status (HERO10 or newer)

Now \>xValue and/or \<xValue and/or ==xValue can be used to test camera states, where 'x' is the camera state to test, and Value the amount to test against. Again Labs uses the `>` symbol to mean greater-than-equals ('>=' is other languages), `<` for less-than, and `==` for equal to:<br>
* **a** accelerationValue - **\>aValue**CMD if(acceleration \>= Value) then CMD, units in Gs  e.g. `>a0.5"half g"`
* **a:X** x_accel_value  - **\=Xa:X>XValue**CMD if(acceleration \>= Value) then CMD, units in Gs  e.g. `=Xa:X>X0.5"X half g"`
* **a:Y** y_accel_value  - **\=Ya:Y>YValue**CMD if(acceleration \>= Value) then CMD, units in Gs  e.g. `=Ya:X>Y0.5"Y half g"`
* **a:Z** z_accel_value  - **\=Za:Z>ZValue**CMD if(acceleration \>= Value) then CMD, units in Gs  e.g. `=Za:X>Z0.5"Z half g"`
* **b** batteryLevel - **\>bValue**CMD if(battery \>= Value) then CMD, units in percentage  e.g. `<b10"Battery less than 10%"`
* **b:T** batteryTemperature<sup>H13</sup> - **\>bValue**CMD if(battery \>= Value) then CMD, units in degrees C  e.g. `>b:T70"Battery Hot"`
* **c** coordDistance - **\>cDist**CMD  then CMD, units in meters, compare distance from initial GPS location  e.g. `>c10"moved 10m"`
* **c:X** coord[A-Z]Distance - **\>c:XDist**CMD There are up to 26 pre-stored GPS locations oMFRMA=latt,long thru oMFRMZ. If nothing is store in FRMx, it will initialize with the current location. Reset a location with $FRMx=0,0 it will reinit with the current location.
* **d** GPS DOP - **\<dValue**CMD - if(DOP \< Value) then CMD, units in 100x DOP. GPS location precision.   e.g. `<d500"GPS precision high"`
* **e** random - **\<eValue**CMD \<e50 - 50% true \<e90 - 90% true.    e.g. `<e50"Heads"~"Tails"`
* **f** (H12/H13) SD full? Remaining space on SD card in GB (or -1.0 for no SD) - **\>fValue**CMD \>f4 - more than 4GB left e.g. `<f4"SD card warning"`
* **f:U** (H12/H13) GB Used? Used space on SD card in GB (or -1.0 for no SD) - **\>f:UValue**CMD \>f:U32 - more than 32GB used e.g. `>f:U32"32GB used"`
* **g** gyroValue - **\>gValue**CMD if(gryo \>= Value) CMD, numbers are in degrees per second.
* **g:X** x_accel_value  - **\=Xg:X>XValue**CMD if(gryo \>= Value) then CMD, units in Gs  e.g. `=Xa:X>X0.5"X half g"`
* **g:Y** y_accel_value  - **\=Yg:Y>YValue**CMD if(gryo \>= Value) then CMD, units in Gs  e.g. `=Ya:X>Y0.5"Y half g"`
* **g:Z** z_accel_value  - **\=Zg:Z>ZValue**CMD if(gryo \>= Value) then CMD, units in Gs  e.g. `=Za:X>Z0.5"Z half g"`
* **h** heightValue - **\>hValue**CMD if(height \>= Value) CMD, numbers are in meters above sealevel.
* **i** isoValue - **\>iValue**CMD - testing ISO where ISO ranges from 100 to 6400
* **k** speedValue - **\>kValue**CMD if(gps Speed \>= Value) CMD e.g. >k45!S, numbers are in km/h.
* **l** loop_countValue - **\<lValue**CMD if(loop_count \< Value) CMD e.g. \<l45!R, this is the loop count for !R repeat, since last QR scan or boot.
* **m** motionValue - **\<mValue**CMD if(motion \< Value) CMD Motion value is a percentage of pixels moving  e.g. >m5!S+60E!R, this look of motion greater than 5%, and record for 60seconds when detected.
* **m:X** motion[A-Z]Value - <m:A through <m:Z adjusts the sensitivity of the detector, the above is the equivalent <m:J.  'A' is very low sensitivity, only large pixel changes detected, 'Z' tiniest change detected. 
* **n** network Connect - if false it returns -1, otherwise it returns the string length of the SSID
* **n:L** networkLivestreaming - if false it returns -1, 1.0 if currently livestreaming
* **p** soundpressureValue - **\>pValue**CMD if(spl \>= Value) CMD, numbers are in dB
* **p:T** processorTempValue<sup>H13</sup> - **\>p:TValue**CMD if(processorTemp \> Value) then CMD, units in degrees C
* **r** recording, 1 for true, -1 for false, - **\>r0**CMD1~CMD2 if(Recording > 0) then CMD1 else CMD2 
* **r:C** remote Connected, 1 for true, -1 for false, - **\>r:C0**CMD1~CMD2 if(RC_Connected) then CMD1 else CMD2 
* **r:A** remote App Connected with Live Preview, 1 for true, -1 for false, - **\>r:A0**CMD1~CMD2 if(App_Connected) then CMD1 else CMD2 
* **s** shutterValue - **\>sValue**CMD - testing shutter, where 1/Value is used for shutter speed
* **t:Y** time Year (e.g. 2025) e.g. \<t:Y2025"You clock is wrong"
* **t:M** time Month (1 thru 12)
* **t:D** time Day (1 thru 31)
* **t:H** time Hour (0 thru 23)
* **t:N** time miNutes (0 thru 59) e.g. \>t:N55!U - auto upload at the end of the hour, i.e. xx:55 or greater
* **t:S** time Seconds (0 thru 59) 
* **t:W** time day_of_the_Week (0-Sunday, 1-Monday,... thru 6-Saturday) e.g. =Tt:W>T1<T6"Week Day"
* **t:B** time in seconds since the camera Boot
* **t:Q** time in seconds since scanning the QR code
* **t:R** time is seconds for the current recording
* **u** USB power - **\>u0**CMD1~CMD2 if(power is on USB) then CMD1 else CMD2
* **v** Current Camera Mode - **==vValue**CMD video=12, TLV=13, Looping Video=15, Photo=16, Night Photo=18, Burst Photo=19, etc. Example: ==v12!S  will start recording video if in Video Mode. ==v16!S will take a photo if in Photo Mode.
* **y** mode_pressesValue - **\>y0**CMD1~CMD2 if(mode_presses > 0) then CMD1 else CMD2
* **z** shutter_pressesValue - **\>z0**CMD1~CMD2 if(shutter_presses > 0) then CMD1 else CMD2

### Assignments, Variables and Math

QR Command scripts can include variables and operation on them. Why? Fun maybe? More power, for sure! A complete program in a QR Code.

As 'a' to 'z' and system system fields, 'A' to 'Z' are the variable can contain any floating point number. This new variables are all initialized to zero, 
and can be tested with the '<' and '>' conditionals. To make them non-zero, they can be assign with and '=' command. Just like with conditions and action, 
the '=' character is the command delimiter and comes first.  

`=A5`  is the command variable A = 5.

`=P3.14159265` assigns Pi to variable P.  

Now math can be used to modify your variables.

* `=A+1.4` adds in form A = A + 1.4
* `=D-2` subtraction D = D - 2  (note: assignments of negative numbers aren't support, but subtracting is. So `=D0=D-2` would initialize D to be -2, although =D0 is unnecessary as all variable are initialize to zero at boot.)
* `=A*P` multiply A = A * P
* `=E/7` divide E = E &#47; 7
* `=H^A` raised to a power H = H ^ A
* `=F^0.5` raised to a power F = sqrt(F)
* `=B%10` modulus  B = B % 10 
* `=G#2` Log base N  G = log(G)/log(2) 
* `=J&6` Bitwise AND like  J = (float)((int)J & 6) 
* `=K|3` Bitwise OR K = (float)((int)K &#124; 3) 
* `=Tt:W=T%6>T1"week day"~"weekend"` This is a week day vs Weekend detector

There should be a prize if some can come up with a practical use for all of these ;)

So if thought the above is crazy, it gets weirder.

* `=B$BITR`  load the contents of the BITR (bitrate) hack into variable B, otherwise store zero.  So you can test if a feature is enabled.
* `=Tt:W` load the day of the week into variable T
* `=Di` load the current ISO value into variable D
* `$EVBS=E`  store the current into EV Bias hack, so you can make a variable mess with your exposure (potentially mid capture.)
* `*VARC=C`  permanently store the current variable C into metadata field VarC, so this can be read back on next boot.  
* `!$AR`  delay an action (like !R) with a variable amount of time, e.g. `=A$VARA<A1=A1=A*2*VARA=A!$AR` this will loop forever, doubling the sleep time with each interation
 
### Example command requests

#### 1) Use a GoPro as a crude light meter, and report the output as an Exposure Value, then make capture decision based on that EV value.

Info on [exposure value](https://en.wikipedia.org/wiki/Exposure_value) shows to math as:
EV = logbase2 (f-number^2/(time x gain_above_base_iso))  is the formula for EV<br>

As a QR command: `=E6.25=Gi=G*0.01=E/G=E*s=E#2"Exposure value $E"!R`<br>

Command steps explained:
> E=6.25<br>
> G=ISO value<br>
> G=G&#42;0.01<br>
> E=E/G<br>
> E=E&#42;shutter value (1/s)<br>
> E=log(E)/log(2)<br>
> print E<br>
> repeat<br>

#### 2) Shoot a construction timelapse only Monday thru friday from 9am to 5pm with a 10 minute interval, shutting down the camera between images to extend battery.

`=Tt:W=T%6>T1>09:00<17:00mP+!S+!2N+!600RQ!09:00R`
 
Step-by-step explanation:<br>
`=Tt:W` - Loads the current day of the week into variable T. (Sunday = 0, Monday =1,... Saturday = 6)<br>
`=T%6` - Computes T % 6 (modulus), which distinguishes weekdays (1-5) from Sunday and Saturday (now both 0). <br>
`>T1>09:00<17:00` - Conditional stack:<br>
&nbsp;&nbsp;&nbsp;`>T1` - True if it's a week day (T >= 1)<br>
&nbsp;&nbsp;&nbsp;`>09:00<17:00` - True if current time is between 9:00 AM and 5:00 PM<br>
`mP+!S+!2N+!600RQ` - If the condition is met:<br>
&nbsp;&nbsp;&nbsp;`mP` - Switch to Photo mode<br>
&nbsp;&nbsp;&nbsp;`!S` - Take a photo immediately<br>
&nbsp;&nbsp;&nbsp;`!2N` - Wait 2 seconds<br>
&nbsp;&nbsp;&nbsp;`!600RQ` - Repeat the entire script every ~10 minutes (600 seconds) using the power-efficient quick repeat<br>
`!09:00R` - Repeat the entire script at exactly 09:00 AM daily<br>

#### 3) Take a photo every 30 minutes from 6am to 6pm every day

`>06:00<18:00mP+!S+!2N+!1800RQ!06:00R`
 
Step-by-step explanation:<br>
`>06:00<18:00` - This sets a conditional time window. The commands that follow will only run if the current time is after 6:00 AM and before 6:00 PM.
&nbsp;&nbsp;&nbsp;`mP` - Switches the camera to Photo mode.
&nbsp;&nbsp;&nbsp;`+!S` - Starts capture, in this case, takes a photo. The + means it is bundled with the time condition—this only happens during the valid time window.
&nbsp;&nbsp;&nbsp;`+!2N` - A 2-second pause after taking the photo, bundled with the same time condition.
&nbsp;&nbsp;&nbsp;`+!1800RQ` - Instructs the camera to sleep for approximately 1800 seconds (30 minutes), then repeat the script (power-efficient wake). Again, bundled with the same time condition using +.
`!06:00R` - Daily repeat at exactly 6:00 AM, ensuring the script runs every day starting from this time.


### Prohibited Action Rule
Never use !O, !xO, or any form of shutdown (!O, !5O, !20:00O) in a repeating script using !RQ, !R, or time-based loops.

Shutdown stops the camera entirely and halts all future scheduled events.

Use !xN (sleep) instead for power-saving pauses that still allow repeat execution.

Example BAD: 
>08:00<18:00mP+!S+!5O+!1800RQ!08:00R  ❌ This halts the script after first execution

Example GOOD:
>08:00<18:00mP+!S+!2N+!1800RQ!08:00R  ✅ This sleeps and repeats correctly


### Prohibited Formatting Rule
Never use ! followed by any lowercase character, e.g. !mP is not a valid commmand.  

If asked: take a photo and repeat every 10 minutes
 
Example BAD: 
!mP!S!2N!600R  ❌ This is meaningless as ! is using for action commands and there are not lowercase actions.

Example GOOD:
mP!S!2N!600R  ✅ This sets the mode to Photo, takes a photo, sleeps 10 minutes and repeats


### Prohibited Photo Script Behavior
Never use !xE to end an action following !S if you are using single Photo mode. Photos do not have an end action. End actions are for video modes and timelapse modes.  

If asked: starting at 5am take a photo and shut off 5 seconds later, then repeat every half hour until 6pm, repeat each day

Example BAD: 
<05:00>18:00!05:00NmP!S!5E!1800R  ❌ The !5E is meaningless as the photo that is taking with !S is completes immediately

Example GOOD:
<05:00>18:00!05:00NmP!S!5N!1800R  ✅ The !5N adds a pause have the !S that takes the photo


## Troubleshooting

You can try to ask the [Labs ChatBot](https://bit.ly/chat_gp_labs) help with commands. A when really stuck ask ask a human within the [Labs discussion forum](https://github.com/gopro/labs/discussions)


updated: October 7, 2025

[Learn more](..) on QR Control
