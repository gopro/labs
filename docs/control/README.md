# QR Control

### Configuration Commands for All Labs Enabled Cameras
* Set most camera modes with the [**Customizable QR Code Creator**](./custom)
and as a mobile app:<br>
[![google play](google-play-823.png)](https://play.google.com/store/apps/details?id=com.miscdata.qrcontrol)
[![apple app store](apple-store-823.png)](https://apps.apple.com/us/app/gopro-app/id1518134202)
* Precisely setup your cameras with [**Local Date and Time**](./precisiontime) or [**UTC Time**](./precisiontime_utc)
* Personalize your cameras with [**Owner Information**](./owner)
* Subset of commands for the [**HERO 5 Session**](./session5). Limit to camera settings, date & time, scheduled captures and ownership information.

### Capture Triggers 
* Use the image sensor for [**Motion Detection**](./motion), capturing only scenes with motion
* <span style="color:steelblue">**UPDATED**</span> Capture using [**IMU Motion Triggers**](./imutrigger) for detecting camera movement
* Start capture only when traveling fast with [**GPS Speed Triggers**](./speedtrigger) 
* Use the [**USB Power Trigger**](./usb) to start and stop the camera (pseudo dash-cam mode)
* <span style="color:steelblue">**NEW**</span> **HERO9 only** - Start capture using [**Sound Pressure Level Trigger**](./spltrigger)

### Extended Time-lapse Features
* Start a 24-hour long time-lapse or greater with [**Extra Long Time-lapses**](./longtimelapse)
* Use your GoPro to time-lapse [**Construction Projects**](./construction)
* Schedule your camera to automatically [**Time-lapse Sunsets and Sunrises**](./solartimelapse)
* <span style="color:steelblue">**NEW**</span> **HERO9 only** - Daily Time-lapse with [**auto upload**](./dailytl) (GoPro Subscription required)

### Video Alteration Features
* **HERO8/9 and MAX only** - Add text like Date and Time with [**Video 'Burn-in' Overlays**](./overlays)
* Set the [**Maximum Shutter Angle**](./maxshut) for greater control over stabilization in low light
* Set the [**Exposure Lock**](./explock) via QR Code
* <span style="color:steelblue">**NEW**</span> **HERO9 only** - Add a logo or any small image to your video with [**Logo Overlays**](./logo)

### Miscellaneous Features
* Enable [**Archive Mode**](./archive), a video only capture mode for loaned cameras 
* **HERO8/9 only** - Configure your camera for [**Live-streaming**](./rtmp) via QR Code
* **HERO9 only** - Sync multiple cameras' timecode via [**GPS Time Synchronization**](./gpssync)
* **HERO8/9 and MAX only** - Experiment with larger chapter sizes with [**12 GB Chapters**](./chapters)
* **HERO8/9 and MAX only** - Multi-camera users, label you media with [**Altered File Naming**](./basename)
* <span style="color:steelblue">**NEW**</span> **HERO9 only** - Timecode Support via [**LTC**](./ltc) over audio line-in using Media Mod 
* <span style="color:steelblue">**NEW**</span> **HERO9 only** - Enable media [**encryption**](./encrypt) for increased security
* <span style="color:steelblue">**UPDATED**</span> Many more [**extensions**](./extensions) via QR Code

Note: <span style="color:steelblue">**NEW**</span> - Requires Labs Firmware released in June 2021.

## Forum Discussions 

Please join the [**GoPro Labs Community**](https://community.gopro.com/t5/GoPro-Labs/bd-p/GoProLabs)

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


### ver 1.15
