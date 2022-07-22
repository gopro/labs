# GoPro Labs Firmware Release Notes 

Only the more recent releases are documented below. This a general list of Labs enhancements on top on the mainline firmware updates. Changes to mainline firmware are not listed.

## HERO10 Black 

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
 

## MAX

### 2.00.71 - January 2021
 - The only Labs release for MAX


## HERO5 Session

### 2.70.71 - January 2021
 - The only Labs release for HERO5 Session



### ver 1.03
updated: July 22, 2022

[Learn more](..) on QR Control
