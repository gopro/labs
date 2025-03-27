# GoPro Labs Firmware Release Notes 

Only the more recent releases are documented below. This a general list of Labs enhancements on top on the mainline firmware updates. Changes to mainline firmware are not listed.


## HERO13 Black 

### 2.02.70 - March 27, 2025
- Added commands to enable and disable the touch screen (tE and tD). These will be usefil in script to prevent an accidental screen touch setting the wrong mode. 
- Added $EXPL=1, for exposure lock upon capture, just like the existing $WBLK=1 for white balance lock. 
- Added simplified script versions for exposure lock: eL <- Lock exposure, like wL <- Lock whitebalance, automatically upon capture. Disable with eL0 and wL0.
- Added support for Stop Motion via Quik, using the hilight tag button to add a frame.
- Improved Photo capture response times (removing the user timer animation, when run Labs scripts) 
- Improved command shell response times
- Fixed *BYPS=1 will now correctly suppress the Date/Time setup popup.
- Fixed Macros using temporary assignments *ALLD="$BITR=150$GCMP=1"
- Fixed a preset name with one FourCC and a following string is now support. e.g. "WBDV Wb for Dive"
- Fixed a conflict when using *FAST=1 the camera sometimes not reading BOOT commands.
- Fixed overlays rendering time before the date (was rendering time as 00:00:00)
- Fixed e4 to enable Auto Boost even with UltraWide or Max Lens Mod 2.0 attached.
- Fixed a rare wake late error, resulting in a 24 hour pause in longform timelapse. 

### 1.30.72 - December 13, 2024
- Added variable $f to determine how full the SD Card is. Returns -1 if the SD card is ejected, or storage remaining in GBytes. Use $f:U for storage used in GBytes. e.g. `$PMSG="$f GB"!R`
- Added support for printing the contents of fourCCs directly `"bitrate $BITR"` and `"Owner $OWNR"` are now supported.
- Fixed range time conditional in form >time<time(TRUE)~(FALSE) the else wasn't be processed.
- Fixed for scripts Photo follow by a sleep.
- Fixed WBDV red channel clipping (overflow).

### 1.30.70 - November 21, 2024
- Added WBDV - White Balance DiVe improvements. Rather than WARM for improving diving white balance, which effects WB the same at all depths, 
WBDV is more automatic -- as the scene get more blue, the more the red channel is gain up. Currently $WBDV=1 is uses =2.33,4.0 internally 
(gaining red 4x after red gain hits 2.33), so you can try tuning this yourself e.g. $WBDV=2.4,5.0
- Added SHEL - Using $SHEL=1 enables a command shell for Labs over a USB serial port. Every experimental, and looking for feedback. 
Connect to COM at 115200 8N1. All QR code command work, just type them. Used $ commands will report their data back to the shell, 
e.g. $BITR or $A or $p:T to read variables.
- Added OPNW - Open Network (allows of faster non-secure http:// vs https:// to be used with Open GoPro)
- Fixed supporting numbers in FourCC codes in Presets (e.g. preset named "DIVE 24HZ")
- Fixed d1 and d10 for 10-bit selection
- Fixed voice control enabling in Labs

### 1.20.70 - October 25, 2024
- Added *DRFT=1 for automatic clock drift fix.
- Added *DRFS=-11.3 for a fixed clock drift fix.
- Added mPp1 or p.5 for interval photo
- Fix for the TONE extension
- Fix for wake events under power
- Fix for ISO and SHUT LCD overlay position
- Fix for multiple day wake events e.g. !259200N for sleeping for 72 hours
- Fix for the !1R required in motion detection, now !R works again 
- Fix for *SYNC=1 and its impact on timecode

### 1.12.70 - September 24, 2024
- Added command oX10 to select Auto Detect for lens mods.
- Fixed LOGB with offsets less than -100, now LOGB=200,-128 works as intended.
- Fixed crash with creating presets through the menus.  If instability presists, reset the presets.

### 1.10.70 - September 10, 2024
- Added STOP=x A Stop Motion extension where is x the number for frames to store per shutter press. This modify timelapse video. It is recommend to make a stop motion preset with this command ```mT$PRES="0,STOP"mTr5Xp4``` Works great with the remote. Mode button ends capture. 
- Added ONIO=x Onion percentage used for Stop Motion where is x the precentage of transparency of the onion skin.  
- Added DIST=x Time-Lapse Video Distance, x is a GPS travel distance between exposures in meters, rather than time for an in-camera computed timelapse. So $DIST=5 will set a 5 meter interval for TLV. One exception is when x=1, 10 meters will be used, 1 meter is too noisy (GPS errors.) So this feature is good for 2 meters of larger. For shorter distances or a higher speed, you the new TLV sample rate for 4Hz (p4), for the best distance precision. e.g. mTr5Xp4$DIST=5
- Added DIVE=1 - optimizing the Hypersmooth stabilization for underwater. The water refractive index defaults to 1.335 (good for fresh and command salt water), if you know your area RI is significantly different DIVE=r where r can be 1.3 to 1.45 is supported.
- Added WARM=x and COOL=x to offset white balance.  WARM is good to use with DIVE, so you can improve the red respond for deeper dives. 
- Added RLTC=1 to enable LTC timecode reading from line-in audio 
- Added OLTC=x frame offset to LTC, enabling calibration you are seeing any offset.
- Added MMSK=time, for auto generating a mask for the new motion detector
- Added GOAL=x - 0 to 60 (or x) MPH speed timing. Not for precision timing, just for fun. Drive safe.
- Added GPSL=x to enabled continous GPS location logging, even when not capturing, so the capture can log more of you path and adventures. 
    Path is saved by day into MISC/GPS-yy-mm-dd.gpmf file. GPSL=1 logs everything, GPSL=x will only log movement great than x meter from the last stored location. 
- Added custom Labs setting within Preset names. e.g. ```*DIVE=1*BITR=160``` (standard formatting) or ```DIVE 24HZ``` or ```24HZ,DIVE,NR01``` (space or comma delimited). 
For advanced Labs users, preset names can call macros. Warning: don't put permanent settings or actions with presets, could brick your camera.
  * Safe example: 
  * ```*OVLY="$BURN='(0,20)[BRHH:MM:SSaa mm-dd-yyyy ]'"```   <- Enable overlay macro
  * ```*OVLy="$BURN=''"```   <- Disable overlay macro, required to disable when leaving/deselecting a preset
  * ```$PRES="0,OVLY"``` <- Now this OVLY preset will enable overlays for that preset alone.
  * as one cmd: ```*OVLY="$BURN='(0,20)[BRHH:MM:SSaa mm-dd-yyyy ]'"*OVLy="$BURN=''"$PRES="0,OVLY"```
- Added !A for appending frames for a new controlled video timelapse.  Stop motion, GPS interval Lapse etc.
- Added !C to Clear last GSP distance so command like this are simplier >c10!C+!A!R //(if distance > 10m) Clear()+Append() repeat;
- Added support for !R-x relative gotos. e.g. "Hello"!N!R-2 keep back 2 character before !R.
- Added command p.3 for 3s interval support
- Added command p4 for a custom 4fps Time-lapse Video interval (0.25s)
- Added 24.0 LTC Timecode support
- Added !SAVEfile=0 - to erase MISC/file
- Added oNx commands for Noise Reduction controls - oN0 - High/default, oN1 - Medium, oN2 - Low.
- Added script variables b:T - battery temperature, p:T - processor temperature
- Added mVB - mode Video Burst command
- Added oX0, oX2 to oX9 - Standard, MLM2.0, MLM2.5, Macro, future, ND4, ND8, ND16, ND32
- Added r4S - new Square 4K mode for the Ulta Wide lens mode (and MLM2.)
- Added variables a:X, a:Y, a:Z and g:X, g:Y, g:Z, for accelerometer and gyro single axis measurements 
- Added commands r1V and r4V, for 1080p and 4K vertical video modes.
- Improved the new style motion detection, faster and more precise.  System variable m is the percentage of the frame in motion. 
- Improved QR Scan will a Labs script is already running.
- Improved QR Sanning of complex codes in different lens modes. 
- Improved handling of utf-8 characters in QR Codes.
- Improved long form wake reliability
- Improved archive messages
- Improved AUDS, auto start voice control (required for SPL outside of video recording) 
- Fixed subroutine handling of !R repeats
- Fixed commands running too fast, occasionally missing steps or sleeps
- Fixed BOOT commands to only happen during boot, so that when scan in a new boot command, it will not run immediately
- Fixed attempted file I/O with SD Card removed.

## HERO12 Black 

### 2.32.70 - December 12, 2024
- Added variable $f to determine how full the SD Card is. Returns -1 if the SD card is ejected, or storage remaining in GBytes. Use $f:U for storage used in GBytes. e.g. `$PMSG="$f GB"!R`
- Added support for printing the contents of fourCCs directly `"bitrate $BITR"` and `"Owner $OWNR"` are now supported.
- Added SHEL - Using $SHEL=1 enables a command shell for Labs over a USB serial port. Every experimental, and looking for feedback. 
Connect to COM at 115200 8N1. All QR code command work, just type them. Used $ commands will report their data back to the shell, 
e.g. $BITR or $A or $p:T to read variables.
- Fixed range time conditional in form >time<time(TRUE)~(FALSE) the else wasn't be processed.
- Fixed for scripts Photo follow by a sleep.
- Fixed WBDV red channel clipping (overflow).
- Fixed voice control enabling in Labs


### 2.30.70 - November 13, 2024
- Added *DRFT=1 for automatic clock fix.
- Added *DRFS=-11.3 for a fixed clock fix.
- Added mPp1 or p.5 for interval photo
- Added STOP=x A Stop Motion extension where is x the number for frames to store per shutter press. This modify timelapse video. It is recommend to make a stop motion preset with this command ```mT$PRES="0,STOP"mTr5Xp4``` Works great with the remote. Mode button ends capture. 
- Added ONIO=x Onion percentage used for Stop Motion where is x the precentage of transparency of the onion skin.  
- Added DIVE=1 - optimizing the Hypersmooth stabilization for underwater. The water refractive index defaults to 1.335 (good for fresh and salt water), if you know your area RI is significantly different DIVE=r where r can be 1.3 to 1.45 is supported.
- Added WARM=x and COOL=x to offset white balance.  WARM is good to use with DIVE, so you can improve the red respond for deeper dives. 
- Added RLTC=1 to enable LTC timecode reading from line-in audio 
- Added OLTC=x frame offset to LTC, enabling calibration you are seeing any offset.
- Added MMSK=time, for auto generating a mask for the new motion detector
- Added GPSL=x to enabled continous GPS location logging, even when not capturing, so the capture can log more of you path and adventures. 
    Path is saved by day into MISC/GPS-yy-mm-dd.gpmf file. GPSL=1 logs everything, GPSL=x will only log movement great than x meter from the last stored location. 
- Added custom Labs setting within Preset names. e.g. *DIVE=1*BITR=160 (standard formatting) or DIVE 24HZ or 24HZ,DIVE,NR01 (space or comma delimited). 
    For advanced Labs users, preset names can call macros. Warning: don't put permanent settings or actions with presets, could brick your camera. 
- Added !A for appending frames for a new controlled video timelapse.  Stop motion, GPS interval Lapse etc.
- Added support for !R-x relative gotos. e.g. "Hello"!N!R-2 keep back 2 character before !R.
- Added command p.3 for 3s interval support
- Added command p4 for a custom 4fps Time-lapse Video interval (0.25s)
- Added 24.0 LTC Timecode support
- Added !SAVEfile=0 - to erase MISC/file
- Added oNx commands for Noise Reduction controls - oN0 - High/default, oN1 - Medium, oN2 - Low.
- Added script variables b:T - battery temperature, p:T - processor temperature
- Added mVB - mode Video Burst command
- Added variables a:X, a:Y, a:Z and g:X, g:Y, g:Z, for accelerometer and gyro single axis measurements 
- Added commands r1V and r4V, for 1080p and 4K vertical video modes.
- Improved the new style motion detection, faster and more precise.  System variable m is the percentage of the frame in motion. 
- Improved QR Scan will a Labs script is already running.
- Improved QR Sanning of complex codes in different lens modes. 
- Improved handling of utf-8 characters in QR Codes.
- Improved long form wake reliability
- Improved archive messages
- Improved AUDS, auto start voice control (required for SPL outside of video recording) 
- Fixed subroutine handling of !R repeats
- Fixed commands running too fast, occasionally missing steps or sleeps
- Fixed BOOT commands to only happen during boot, so that when scan in a new boot command, it will not run immediately
- Fixed attempted file I/O with SD Card removed.
- Fixed ISO and SHUT LCD overlay position
- Fixed multiple day wake events !259200N <- sleep for 72 hours.
- Fixed the !1R required in motion detection, now !R works again 
- Fixed DAUD which wasn't working on HERO12.

### 2.20.70 - March 28, 2024
- Added Macro Support
- Added $BITR=150 and *BITR=150 versions of oMBITR and !MBITR
- Fixed LEVL, broken in the last release
- Fixed protune setting incorrectly changing the color to Vibrant
- Enhanced $EXPS=1 to work in all modes (timelapse and photo)
- Enhanced $EXPS=1 to support shutter speeds longer than 1s

### 2.10.70 - Feb 8, 2024
- Fixed ```x++``` and ```x--``` EV up and down controls (handy for scuba)
- Enhancing processing speed for looping scripts about 10-15x faster.
   example code print to the loop speed: ```=Sl=Tt:Q=S/T=Ll=L%9<L1oMPMSG="loops $S/s"!R```
- Added support testing current camera mode, system variable 'v' will have the mode.
   e.g. Video=12, TLV=13, Looping Video=15, Photo=16, Night Photo=18, Burst Photo=19, etc.
   Display the current mode with with this command:  ```"mode $v"!R``` or fast/cleaner ```oMPMSG="mode $v"!R```
- Added precise variable testing with '=='. Previously only < for less_than and > for greater_than_equal were supported.
   e.g. command:   ```>10:10<11:00"do thing between 10:10 and 10:59"```
   now you can do: ```==10:10"do thing only at 10:10"```
   useful for mode testing: ```==v12"video mode, do thing only on video mode"```
   
 Known Issue: 24HZ=1 for 24.0 video, has conflict with Autoboost (captures will fail.)  Either turn off autoboost (standard HS works) or shoot 23.976.
   

### 2.00.70 - Dec 14, 2023
- Added FEAT - Display the Labs feature you have active, without have to reboot the camera. e.g. oMFEAT=4 <- display for 4 seconds.
- Added creating, naming and sharing presets oMPRES="1,MyPreset" 0-22 for icon selection, -1 for delete 
- Added FONT=1 Select the old fonts (if you only want the dot matrix font)
- Added GRAB=x screen grab x-frames, !F (grab now) and !F3 (grab next 3 Labs overlays) - frame grab the UI.  Useful for education and bug reporting
- Added font color for script messaging. e.g. try this QR Code ```"\1H\2e\3l\4l\5o \6W\7o\8r\1l\2d" ```
- Improved the font rendering (higher res fonts)
- Improved support for Max Lens Mod 2.0
- Improved upload reliability with an optional maximum transfer time (timeout). e.g. !U3 <- upload now, for up to 3 minutes.
- minor Labs bug fixes


### 1.30.70 - Nov 17, 2023
- Added STDL - Start Delay (default 2000ms, wait before any other commands.) oMSTDL=100 for less wait. Experimental scripting performance.
- minor bug fixes 


### 1.20.70 - Nov 2, 2023
- Fixed NR01 to full disable noise reduction
- Fixed HSTO Hindsight Timing control
- minor bug fixes 


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


### 2.32.70 - Jan 21, 2025
- Added variable $f to determine how full the SD Card is. Returns -1 if the SD card is ejected, or storage remaining in GBytes. Use $f:U for storage used in GBytes. e.g. `$PMSG="$f GB"!R`
- Added support for printing the contents of permanent fourCCs directly `"bitrate $BITR"` and `"Owner $OWNR"` are now supported.
- general labs scripting bug fixes.


### 2.30.70 - Mar 14, 2024
- Added *wxyz, permanent storage, is the simplified version of !Mwxyz, e.g. *BITR=160
- Added $wxyz, temporary storage, is the simplified version of oMwxyz, e.g. $WIDE=1$NR01=1
- Added support for macros, or crude scripting subroutines. This expands the potential complexity for QR scripting, as the entire script is no longer limited to 255 characters. It would be possible to run scripts nearing ~1.2KB. 
Note: recursion is supported, macros can call other macros, and can call themselves.
  * Subroutines are saved in string FourCCs. e.g. *SUBA="mVr4p60!S!2E!1N"   Note: Use single quotes for text within double quotes.
  * Subroutines are launched ```^SUBA```  e.g. ```>19:30^NIGH~^DAYS``` (if(time>19:30) Night(); else Day(); ).
- Added support testing current camera mode, system variable 'v' will have the mode like follows.
  * video=12
  * TLV=13
  * Looping Video=15
  * Photo=16
  * Night Photo=18
  * Burst Photo=19, etc.<br>
Display the current mode with with this command:  ```"mode $v"!R``` or fast/cleaner ```$PMSG="mode $v"!R```
- Added precise variable testing with '=='. Previously only < for less_than and > for greater_than_equal were supported.
   e.g. command:   ```>10:10<11:00"do thing between 10:10 and 10:59"```
   now you can do: ```==10:10"do thing only at 10:10"```
   useful for mode testing: ```==v12"video mode, do thing only on video mode"```
- Added $GRAB=x screen grab x-frames, !F (grab now) and !F3 (grab next 3 Labs overlays) - frame grab the UI. Useful for education and bug reporting
- Added font color for script messaging. e.g. try this QR Code ```"\1H\2e\3l\4l\5o \6W\7o\8r\1l\2d"```
- Added $STDL=x - Start Delay (default 2000ms, wait before any other commands.) $STDL=100 for less wait. Experimental scripting performance.
- Improved the font rendering (higher res fonts)
- Improved upload reliability with an optional maximum transfer time (timeout). e.g. !U3 <- upload now, for up to 3 minutes.
- Improved processing speed for looping scripts about 10-15x faster.
- Fixed ```x++``` and ```x--``` EV up and down controls (handy for scuba)
- minor Labs bug fixes


### 2.20.70 - Nov 2, 2023

- Added !Cx where x is GBs to make sure is clear.  If more than x is available, no files are removed. x is limited to half SD size.
- Added !X to exit a running script. >l99!X!S!2R <- loop for 99 times, then exit. 
- Added QR Equals logo when scaning the same code twice (the first check is all you needed.)
- Added oMWG84=1 to switch GPS altitude from Mean Sea Level to WGS84 elipsoid. 
- Restored Overlays and Logos to Livestream feeds
- Fixed motion detection so would scan the full image in TimeWarp mode (was only scanning middle 50%.)
- Fixed Overlays use AM/PM now correctly use 12 hour time
- Fixed error with WLBK and WIDE applied at the same time
- Fixed HSTO Hindsight Timing control
- other minor bug fixes 


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

### 2.50.71 - June 1, 2024
- Minor bug fix

### 2.50.70 - May 9, 2024
- Most of the latets Labs features from HERO11 v2.30.70

### 2.40.70 - Dec 14, 2023
- Added FEAT - Display the Labs feature you have active, without have to reboot the camera. e.g. oMFEAT=4 <- display for 4 seconds.
- Improved upload reliability with an optional maximum transfer time (timeout). e.g. !U3 <- upload now, for up to 3 minutes.
- minor Labs bug fixes

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

### 2.02.70 - July 12, 2024
- Improved QR Code scanning on complex code in 360 mode.
- Improved the Labs fonts for LCD and Overlays.
- Latest logic for scripting
- Support for $ and * commands (etc. *BITR=90 and $FEAT=5)  
- Added *WAKE=2 support (boot on power)

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

### 1.62.70 - May 28, 2024
- Added $RLTC=1 - Read LTC timecode via MediaMod line input.
- Added repeat support to subroutines.
- Fixed setting commands after an End command could be missed.
- minor Labs bug fixes

### 1.60.70 - April 4, 2024
- Added the new scripting like that of HERO11 & 12. Supports https://gopro.github.io/labs/build/
- Added Macro Support
- Added $BITR=150 and *BITR=150 versions of oMBITR and !MBITR
- Added FEAT - Display the Labs feature you have active, without have to reboot the camera. e.g. oMFEAT=4 <- display for 4 seconds.
- Added font color for script messaging. e.g. try this QR Code ```"\1H\2e\3l\4l\5o \6W\7o\8r\1l\2d"```
- Added support testing current camera mode, system variable 'v' will have the mode.
   e.g. Video=12, TLV=13, Looping Video=15, Photo=16, Night Photo=18, Burst Photo=19, etc.
   Display the current mode with with this command:  ```"mode $v"!R``` or fast/cleaner ```oMPMSG="mode $v"!R```
- Added precise variable testing with '=='. Previously only < for less_than and > for greater_than_equal were supported.
   e.g. command:   ```>10:10<11:00"do thing between 10:10 and 10:59"```
   now you can do: ```==10:10"do thing only at 10:10"```
   useful for mode testing: ```==v12"video mode, do thing only on video mode"```
- Fixed ```x++``` and ```x--``` EV up and down controls (handy for scuba)
- Enhanced $EXPS=1 to work in all modes (timelapse and photo)
- Enhanced $EXPS=1 to support shutter speeds longer than 1s
- Enhancing processing speed for looping scripts about 10-15x faster.
   example code print to the loop speed: ```=Sl=Tt:Q=S/T=Ll=L%9<L1oMPMSG="loops $S/s"!R```
- Improved the font rendering (higher res fonts)
- many minor Labs bug fixes

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



updated: January 25, 2025

[Learn more](..) on QR Control
