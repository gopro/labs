# GoPro Labs Firmware Release Notes 

Only the more recent releases are documented below. This a general list of Labs enhancements on top on the mainline firmware updates. Changes to mainline firmware are not listed.

## HERO12 Black 

### 1.12.70 - Sept 29, 2023
- Fixed !MWAKE=2 booting without battery (some source may require !MTUSB=1)
- Fixed bricking bug when a user error sets SPED to be permanent
- Fixed the exposure error when mxing WIDE and WBLK features
- Fixed NR01=1 so that the noise reduction is fully off
- Fixed BITL to support Kb/s (oMBITL=4500) and Mb/s (oMBITL=5)
- Fixed 24HZ=1 not seting the sensor to 24.0Hz
- Fixed w++ and w-- white up and down control


### 1.10.70 - Sept 13, 2023
- Almost all Labs features from HERO11, (known excptions DAUD and DLRV aren't supported.)
- Adding mH for selecting HDR 
- Adding mL for selecting Log
- Adding mS for selecting Standard (switch Log or HDR off)
- Adding oX2 for selecting Max Lens Mod 2.0
- Adding l1, l2, l3 for selecting, trails length short, long and infinite.
- Enhanced support for the new Blockly visual scripting tool [https://gopro.github.io/labs/build/](https://gopro.github.io/labs/build/)


## HERO11 Black 

### 2.12.70 - Aug 10, 2023
- Added !MFAST=1 for fewer Labs notifications on boot.
- Added !MBERS=2 for disabling ERS only when Hypersmooth is off.
- Added !MBITL=6 controlling the livestream maximum bitrate (up to 8Mbit/s).
- Added oMEXPQ=value for an fixed exposure time of 1/value.  Same as oMEXPN=100oMEXPX=100, so a simplification only.
- Enhanced EXPQ,EXPN,EXPX and EXPT to work on timelapse video and photo 
- Restored Overlays and Logos to Livestream feeds (use only small logos and overlays for reliability)
- Fixed motion detection so would scan the full image in TimeWarp mode (was only scanning middle 50%.)
- Fixed Overlays use AM/PM now correctly use 12 hour time
- Fixed using of Math functions in saved scripts.
- Fixed setting bitrate (BITR) lower with multiple captures. 
- Fixed very long captures using motion detection or similar repeating events.
- Fixed GPS time SYNC=1 to update the year.
- Improved support for external power with internal battery, wake alarm events.
- General performance improvement to Labs processing.
- Support for the new Blockly visual scripting tool [https://gopro.github.io/labs/build/](https://gopro.github.io/labs/build/)


### 2.10.70 - Mar 15, 2023
- Fixed DLRV to support multiple captures
- Fixed short DSPL interfering with delayed start
- Fixed a common failure in upload in repeating scripts (command !U)
- Fixed a new issue with delay start like !20N, shutting down before the full command was executed.
- Fixed the bitrate control (BITR), to be compatible with Hindsight.
- Fixed !Mwxyz=-value, permanent metadata stores weren't supporting negative values.
- Fixed Proxy files/folders to work with base file-name changes.
- Added support for QR code scanning will HDMI is connected (the window is narrower, qr code need to be more centered.)
- Added hS5 < 5 sec hindsight and hS10 < 10 second hindsight. (both extra-experimental.)
- Added shortcut cut options oSAx, oSBx, oSCx, oSDx
- Added WIDE (flat color wider gamut, like wN with white balance controls), 2020 (color primaries), MTRX (color matrix) extensions.
- Added new condition commands. Previous only >HH:MMcommand or <HH:MMcommand, meaning if(current_time>HH:MM) or if(current_time<HH:MM) respectivily. Now >x and/or <x can be used to test camera states, where 'x' is the camera state to test:
  * a accelerationValue - >a100     if(acceleration > V) Cmd1  e.g. >a100"accleration\n>100mg" numbers are in milli-gs (1000 is 1 unit of gravity.)
  * b battery level test
  * c coord distance test
  * d GPS DOP - <d800 - if(DOP then then 800)
  * e random <e50 - 50% true  <e90  - 90% true.
  * g gyroValue - >gValue  if(gryo > Value) Cmd1  e.g. >g15"gyro > 15dps" numbers are in degrees per second.
  * k speedValue - if(gps Speed > Value) Cmd1  e.g. >k45"speed > 45km/h" numbers are in km/h.
  * l loopNumValue - <lValueCMD if(loop_count < Value) CMD e.g. <l45!R, this is the loop count for !R repeat, since last QR scan or boot.
  * m motionValue - <mValueCMD if(motion < Value) CMD e.g. >m5!S+60E!R, this look of motion, and record for 60seconds when detected.
  * p soundpressureValue - in dB
  * i isoValue - ISO ranging from 100 to 6400
  * r recording - >rCMD1~CMD2 if(Recording) then CMD1 else CMD2
  * r:C remote Contented - >rCCMD1~CMD2 if(RC_Connected) then CMD1 else CMD2
  * r:A remote App Contented - >rACMD1~CMD2 if(App_Connected) then CMD1 else CMD2
  * s shutterValue - 1/Value for shutter speed
  * t:X timedate - >tXValueCMD - where X: Y-Year M-Month D-Day H-Hour N-miNute S-second W-day_of_the_Week B-seconds_since_Boot Q-seconds_since_Qrcode
  * u USB stage - >uCmd1~Cmd2 or <uCmd3 expand to if(power is on USB) Cmd1 else Cmd2  or  if(no power on USB) cmd.  e.g. >u"Power On"~"Power Off"
  * y mode button count from scan start
  * z shutter button count from scan start
- Added button muting control !Zx  !Z3-mute shutter and mode buttons, !Z2-mute only mode, !Z1-mute only shutter. !Z0-unmutes both.
- Added a random delay option 'e' e.g. !eS (start random within an hour) or !e10E (end random within 10 seconds) or !e60N (NOP wait for random up to 60seconds.)
- Added crude super of macro (near focus) lenses, with e.g. oMMACR=-0.1,0.2,... (add the distortion prescription for the added lens.)
- Added oC1 - Auto Off 1 minute  oC0 - Auto Off default length
- Added a "Labs Processing" message for any background looping scripts.
- Added PMSG="your message" to customize the processing message.  Good for naming background scripts, like "gryo trigger".
- Added support for variables in QR scripts, =A10, =A^2, =A$BITR and !$AS!$BE etc.
- Added TimeWarp actions !T - start TW (if not yet) or toggle (real-time/slomo mode)
- Added TimeWarp speed change !TS or !TR - if recording, do into Slomo or Real-time (interchangable)
- Added TimeWarp speed change !TN or !TT - if recording, switch back to normal TimeWarp (interchangable)
- Added Bleep and LED blink control, could be useful in scripts prodicing user feedback !B - Blink once, !B0 - Beep Once, !B1 - both once, !B2 - both twice
- Restored 64BT=x where x is the number of MB.
- Enhanced PRXY=4 for DaVinci style proxies. [more info](https://gopro.github.io/labs/control/proxies/)
- Enhanced front screen histogram includes ISO and Shutter speeds (automatically.)

### 2.01.70 - Dec 14, 2022
- Added EVBS=x for EV Comp Bias, global for all video modes that also works with Live-Stream and web-cam, and can be changed during capture if QRDR=1 is set.
- Added FRNT=1 display most LCD Labs message on the Front screen.
- Added AUDS=1 display the approximate audio levels in dB SPL
- Added oE1 thru oE5  - External microphone type selector, for MediaMod or the mic adaptor
   * 1 - standard
   * 2 - standard plus
   * 3 - powered
   * 4 - powered plus
   * 5 - line_in
- Enhanced Faster Live-Stream start and reliability via QR code
- Enhanced QR code decoder was improved
- Enhanced !MPRXY=x  so that 1- moves LRVs, 2 - moves THMs, 3 moves both in the proxies folder.
- Enhanced xV EV compensation can again support the range -6 to 6 (menus are still limited to -2 to 2)  e.g. -x3 or -x-4

### 1.20.70 - Nov 8, 2022
- All the features and fixes of HERO11 Labs 1.10.70
- Added oTZx  e.g -7 or oTZ-420  -7 hour or -420 minutes timezone offset
- Added oDT or oTD1 for daylight savings on or oDT0 for off
- Added !Dx wait for GPS lock with a DOP less than x, then sync time. For time only locks !D is fine. 
   If GPS is off it will be switch on temporarily for this command, then off again.
- Added oMEXPS=1 - exposure settings display
- Added oMEXPX=x and oMEXPN=n - exposure shutter speed mi(n) and ma(x). e.g. oMEXPX=48 (for 1/48) and oMEXPN=500 (for 1/500) 
- Added oMLOGB=base,[offset] - Logbase control for more flattened 10-bit  e.g. cFoMLOGB=1000
- Added oMNR01=x - x is Noise Reduction level 1-100 (100 is normal)
- Added oMGUID=aspect,aspect,... - on screen framing guides, up to 8, e.g. oMGUID=2.35,1.777
- Added oMLEVL=size - on screen spirit level sizes 1-9. e.g. oMLEVL=3
- Added oHSTP=x,y,s - histogram position and size (used with oMHIST=x), negative x position will render it to the front LCD.
- Improved !M64BT=x x is the size in 100MB. e.g. !M64BT=20 for 2GB chapters. 
- Fixed - GPS Speed trigger, now using the new GPS chip
- Fixed - GPS Clock Sync, now using timezones, so it is awesome!
- Fixed - Motion Detection with masks
- Fixed - fH0/fH for select Linear+horizon lock 

### 1.10.70 - Sept 14, 2022
- All the features and fixes of HERO10 Labs 1.46.76
- New Commands:
- d1 or d10 - 10-bit Depth
- d0 or d8 - 8-bit Depth
- mST - Star Trails 
- mLP - Light Painting
- mLT - Vehicle Lights
- mE - mode Easy
- mPR - mode Pro
- e4 - autoBoost
- r5X - 5K 8:7 (r5T - 5K 4:3, r4 - 5K 16:9)
- r4X - 4K 8:7
- i0 - ISO Auto, other i1 thru i64 for ISO Max 100 thru 6400 
- Bug Fix for metadata in video overlays 


## HERO11 Black Mini

### 2.30.70 - May 19, 2023
- Added !MFAST=1 for fewer Labs notifications on boot.
- Added !MBERS=2 for disabling ERS only when Hypersmooth is off.
- Added oMEXPQ=value for an fixed exposure time of 1/value. Same as oMEXPN=100oMEXPM=100, so a simplification only.
- Enhanced EXPQ,EXPN,EXPX and EXPT to work on timelapse video
- Restored Overlays and Logos to Livestream feeds (use only small logos and overlays for reliability)
- Fixed motion detection so would scan the full image in TimeWarp mode (was only scanning middle 50%.)
- Fixed Overlays use AM/PM now correctly use 12 hour time
- Fixed using of Math funcitons is save scripts.

### 2.20.70 - Mar 31, 2023
- Update to new command language with variable support (matching HERO11 2.10.70.)
- Added !Cx where x is GBs to make sure is clear.  If more than x is available, no files are removed. x is limited to half SD size. Deletes the oldest media first. Ideal for dashcam applications.
- Added !X to exit a running script. >l99!X!S!2R <- loop for 99 times, then exit. 

### 2.10.70 - Feb 1, 2023
- Fixed DLRV to support multiple captures
- Fixed short DSPL interfering with delayed start 
- Fixed a common failure in upload in repeating scripts (command !U)
- Fixed a new issue with delay start like !20N, shutting down before the full command was executed.
- Fixed !Mwxyz=-value, permanent metadata stores weren't supporting negative values. 
- Added GCMP=1 to disable gyro compensated exposure.
- Added WIDE=1 flat color wider gamut, like wN with white balance controls
- Added MTRX=a,b,c,d,e,f,g,h,i. This is the RGB to YUV matrix, new ways to mess up your video. e.g. For an B/W effect in camera oMMTRX=50,175,25,0,0,0,0,0,0
- Added WBLK=1 or wL white balance lock immediately upon capture, allowing auto white balance in dive footage, where good white balance can be tricky.
- Added new condition commands. Previous only >HH:MMcommand or <HH:MMcommand, meaning if(current_time>HH:MM) or if(current_time<HH:MM) respectivily
  Now >x and/or <x can be used to test camera states, where 'x' is the camera state to test:
   * **u** USB stage - >uCmd1~Cmd2 or <uCmd3 expand to if(power is on USB) Cmd1 else Cmd2  or  if(no power on USB) cmd.  e.g. >u"Power On"~"Power Off"
   * **r** recording 
   * **a** accelerationValue - >a100     if(acceleration > V) Cmd1  e.g. >a100"accleration\n>100mg" numbers are in milli-gs (1000 is 1 unit of gravity.) 
   * **d** GPS DOP - <d800 - if(DOP then then 800)
   * **e** random <e50 - 50% true  <e90  - 90% true. 
   * **g** gyroValue - >gValue  if(gryo > Value) Cmd1  e.g. >g15"gyro > 15dps" numbers are in degrees per second.
   * **k** speedValue - if(gps Speed > Value) Cmd1  e.g. >k45"speed > 45km/h" numbers are in km/h.
   * **p** soundpressureValue - in dB
   * **i** isoValue - ISO ranging from 100 to 6400
   * **s** shutterValue - 1/Value for shutter speed
- Added a random delay option 'e' e.g. !eS (start random within an hour) or !e10E (end random within 10 seconds) or !e60N (NOP wait for random up to 60seconds.)
- Added crude super of macro (near focus) lenses, with e.g. oMMACR=-0.1,0.2,... (add the distortion prescription for the added lens.)
- Added oC1 - Auto Off 1 minute  oC0 - Auto Off default length
- Restored 64BT=x where x is the number of MB.
- Enhanced PRXY=4 for DaVinci style proxies.


### 2.00.70 - Jan 5, 2023
- Added EVBS=x for EV Comp Bias, global for all video modes that also works with Live-Stream and web-cam, and can be changed during capture if QRDR=1 is set.
- Added AUDS=1 display the approximate audio levels in dB SPL
- Enhanced Faster Live-Stream start and reliability via QR code
- Enhanced !MPRXY=x  so that 1- moves LRVs, 2 - moves THMs, 3 moves both in the proxies folder.
- Enhanced xV EV compensation can again support the range -6 to 6 (menus are still limited to -2 to 2)  e.g. -x3 or -x-4
- Fixed DLRV=1, so that disabling LRVs can work for more than two captures.

### 1.10.70 - Nov 8, 2022
- All the features and fixes of HERO11 Labs 1.20.70, minus on-screen and GPS features.


## MAX

### 2.00.75 - Apr 27, 2023
- Updates to the new Labs script language recently released for HERO11 Black and Mini. This allows for If-This-Then-That camera for customize 
   camera triggers using a good range of system properties like: acceleration and gyroscope levels, battery level, GPS distance 
   and precision, camera speed, loop count, scene motion and recording and USB status.
- Added support for BITR command for enhanced bitrate control. 360 HEVC can be increased from 60 up to 100Mb/s (90Mb/s good for most SD media) 
- Added support for WAKE command, for auto boot the camera upon USB power.
- Added support for small logo overlays in 360 (and color bars for testing)
- improvements to motion detection 
- improvements to histogram
- many smaller bug fixes for Labs


### 2.00.71 - January 2021
 - The first Labs release for MAX


## HERO10 Black 

### 1.50.70 - Dec, 2022
- Added EVBS=x for EV Comp Bias, global for all video modes that also works with Live-Stream and web-cam, and can be changed during capture if QRDR=1 is set.
- Added FRNT=1 display most LCD Labs message on the Front screen.
- Added AUDS=1 display the approximate audio levels in dB SPL
- Added oE1 thru oE5  - External microphone type selector, for MediaMod or the mic adaptor
   * 1 - standard
   * 2 - standard plus
   * 3 - powered
   * 4 - powered plus
   * 5 - line_in
- Enhanced Faster Live-Stream start and reliability via QR code
- Enhanced !MPRXY=x  so that 1- moves LRVs, 2 - moves THMs, 3 moves both in the proxies folder.
- Enhanced xV EV compensation can again support the range -6 to 6 (menus are still limited to -2 to 2)  e.g. -x3 or -x-4

### 1.46.70 - July, 2022
 - improved active feature reporting (show active and non-one values.)
 - improved video overlay, removing the 30 frame delay
 - suppress RTC clock nagging (it will get the date time wrong if you leave out the battery to long.) Use !MBYPS=1
 - Fixed all the triggers so that they don't require the !MQRDR=1 workaround.
 - Fixed requiring the LCD active for Audio, IMU and GPS triggers.
 - Fixed !MWAKE=2 wake on power command.

### 1.42.70 - June, 2022
 - Added !M**HSTO**=x minutes - controlling the length of the Hindsight timeout, changing from the default for 15 minutes. e.g. !MHSTO=60 for a 60 minute Hindsight timeout.
 - Added !M**IWFR**=1 Increased Write FRequency to support for higher precision file recoveries (defaulted on with !MBITR=x also).  
 - Added rate control for slow SD media (activated using either !MBITR=x or !MIWFR=1), allowing for potentially improved capture reliability with older media or at higher bitrates.
 - Added Trust USB !M**TUSB**=1 to allow power from USB with unknown current (assumes USB is 2A source.)
 - Added support for text and graphics overlay. Limited as is will only work up to 4k30, 2.7Kp60 and 1080p120.   
 - Enhanced SPL trigger levels now reported to the qrlog.txt file.
 - Enhanced, upon boot the LCD will repeat any permanent Labs modification you might have active.
 - Fixed for rare crash when waking the LCD during a Night Lapse video capture.

### 1.40.70 - April, 2022
 - Added default Last Used preset (dL), match the camera menus
 - Added Commands for Max Lens Mod, so you can now request horizon leveling.
 - Added Command for Audio Auto selection (aA), rather than just Wind and Stereo. 
 - Added missing Photo burst modes (Auto bA,  b25N1, b30N10)
 - Added missing Superphoto and HDR modes  (rS and rH).
 - Added command to enhance timecode precision !MTCAL=offset in ms  
 - Added commend to make LRVs file Premiere Pro formated proxy files !MPRXY=1.
 - Enhanced setting time via QR Code higher precision for timecode sync.
 - Enhanced the default timecode precision with using QR code to set timecode
 - Fixed t0 Protune Reset, doesn't erase ISO min/max values from metadata
 - Fixed fN -  will not select a Narrow FOV Lens, rather than just zooming in on a Wide lens.
 - Fixed NightLapse Auto exposure
 - Fixed hS1 (15s) and HS2 (30s), hindsight length selection.
 - Fixed Language selection (Voice and user interface.)
 - Fixed Battery level reporting at 80% if you start in TimeLapse or Photo modes on some cameras.
 
### 1.30.71 - Feburary, 2022
 - Added MLM support for Photos
 - Added Command for selecting Live Burst
 - Added oM**DLRV**=1 disable LRV
 - Added oM**DAUD**=1 disable audio
 - Added oM**BITH**=x bitrate control for H264 encodes (LRVs typically), BITR is for HEVC (MP4s typically)
 - Added WiFi band switching commands oW2 - 2.4GHz and oW5 - 5GHz
 - Fixed Photo FOV support
 - Fixed for Beep Levels below 70%
 - Fixed BITR so that only the MP4 is increased
 - Fixed Long timelapse with Battery and External power (the recommend configuration for this firmware)
 - Fixed metadata storage for change variable length data (change OWNR info, could erase data.)
 - Enhanced !M**WAKE**=2 - wake on power option to bypass any delay.txt (improves robustness for extra long timelapses.)
 - Enhanced - removed all first boot UI notifications for naked cameras
 - Enhanced logging got IMU triggers
 - Enhanced extra long time-lapses with improved handling of RTC errors 
 
### 1.20.70 - December, 2021
 - Added oM**BITR**=x bitrate control for increasing video quality (typical max for a good SD card is 180mbs)
 - Added !M**24HZ**=1 set all the 24p video mode to run at the film standard of 24.0, rather than the broadcast standard of 23.976.
 - Naked camera support (FPV community), firmware updates within the orginal battery, and other optimizations.
 
### 1.10.70 - October, 2021
 - Labs features on Launch firmware.
 - The first few HERO10 Labs releases were mostly going for HERO9 Labs parity 
 
 
## HERO9 Black

### 1.42.70 - June, 2022
 - Added !M**HSTO**=x minutes - controlling the length of the Hindsight timeout, changing from the default for 15 minutes. e.g. !MHSTO=60 for a 60 minute Hindsight timeout.
 - Enhanced SPL trigger levels now reported to the qrlog.txt file.
 - Enhanced, upon boot the LCD will repeat any permanent Labs modification you might have active.
 - minor bug fixes

### 1.70.70 - May 2022
 - Added Max Lens Mod support for Photos
 - Added Command for selecting Live Burst
 - Added WiFi band switching commands oW2 - 2.4GHz and oW5 - 5GHz
 - Added default Last Used preset (dL), match the camera menus
 - Added Commands for Max Lens Mod, so you can now request horizon leveling.
 - Added Command for Audio Auto selection (aA), rather than just Wind and Stereo.
 - Added missing Photo burst modes (Auto bA,  b25N1, b30N10)
 - Added missing Superphoto and HDR modes  (rS and rH).
 - Added command to enhance timecode precision !MTCAL=offset in ms
 - Added commend to make LRVs file Premiere Pro formated proxy files !MPRXY=1.
 - Enhanced setting time via QR Code higher precision for timecode sync.
 - Enhanced logging got IMU triggers
 - Enhanced extra long time-lapses with improved handling of RTC errors
 - Fixed Photo FOV support
 - Fixed for Beep Levels below 70%
 - Fixed metadata storage for change variable length data (change OWNR info, could erase data.)
 - Fixed t0 Protune Reset, doesn't erase ISO min/max values from metadata
 - Fixed fN to selecting a Narrow FOV Lens, rather than just zooming in on a Wide lens.
 - Fixed NightLapse Auto exposure
 - Fixed hS1 (15s) and HS2 (30s), hindsight length selection.
 - Fixed Language selection (Voice and user interface.)

### 1.60.70 - June 2021

### 1.50.72 - January 2021


## HERO8 Black

### 2.51.75 - July 2022
 - Added command to enhance timecode precision !MTCAL=offset in ms
 - Added logo overlays (like HERO9 & 10)
 - Added !MWAKE=2, auto boot on power, either from USB or battery insert.
 - Fixed fN will now correctly select a Narrow FOV Lens.
 - Fixed Language selection (Voice and user interface.)
 - improved active feature reporting (show active and non-one values.)
 - Support for naked cameras with factory resets and firmware updates
 - Sync with the latest QR Code command language with HERO9 & 10

### 2.50.71 - January 2021
 - Mostly bug fixes.

### 1.70.75 - June 2020
 - The very first Labs release for any GoPro camera
 

## HERO7 Black

### 1.90.71 - January 2021
 - The only Labs release for HERO7
 

## HERO5 Session

### 2.70.71 - January 2021
 - The only Labs release for HERO5 Session



updated: Sept  29, 2023

[Learn more](..) on QR Control
