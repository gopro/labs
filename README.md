# GoPro Labs

## Firmware

See this as a styled page https://gopro.github.io/labs/

Labs offers experimental firmware program that uses QR codes to control your camera and extend your camera’s functionality beyond stocks features. 
It is especially useful in situations where settings can’t be communicated via voice, where WiFi is not available, where app pairing is not established, 
or in advanced setups, such as multiple cameras time synchronization or delayed camera triggers. You will not lose any pre-existing modes or features on 
your GoPro—this update simply adds more features.  Safe to install, safe to use, only the extended feature are experimental and they are all off by default. 

Download the GoPro Labs firmware for current shipping cameras:
- [HERO11 Black](https://github.com/gopro/labs/raw/master/docs/firmware/lfs/LABS_HERO11_02_10_70.zip) - v2.10.70, Mar 2023
- [HERO11 Black Mini](https://github.com/gopro/labs/raw/master/docs/firmware/lfs/LABS_MINI11_02_20_70.zip) - v2.20.70, Mar 2023
- [HERO10 Black](https://github.com/gopro/labs/raw/master/docs/firmware/lfs/LABS_HERO10_01_50_70.zip) - v1.50.70, Jan 2023
- [GoPro MAX](https://github.com/gopro/labs/raw/master/docs/firmware/lfs/LABS_MAX_02_00_71.zip) - v2.00.71, January 2021

Download and install for older cameras:
- [HERO9 Black](https://github.com/gopro/labs/raw/master/docs/firmware/lfs/LABS_HERO9_01_72_70.zip) - v1.72.70, June 2022
- [HERO8 Black](https://github.com/gopro/labs/raw/master/docs/firmware/lfs/LABS_HERO8_02_51_75.zip) - v2.51.75, July 2022
- [HERO7 Black](https://github.com/gopro/labs/raw/master/docs/firmware/lfs/LABS_HERO7_01_90_71.zip) - v1.90.71, January 2021
- [HERO5 Session](https://github.com/gopro/labs/raw/master/docs/firmware/lfs/LABS_HERO5Session_2.51.72.zip) - v2.51.72, May 2021

**By downloading any of the public updates provided to you on, from, or through this page or the GoPro website you signify your agreement to [these terms of participation (the "Terms”)](https://gopro.com/content/dam/help/gopro-labs/Beta_Participation_Terms_and_Conditions.pdf).**

Follow the manual firmware update instructions for [Windows](https://gopro.com/en/us/support/hero11-black-product-update/windows) or [MacOS](https://gopro.com/en/us/support/hero11-black-product-update/macos).

Learn more information about the program on [GoPro.com](https://gopro.com/info/gopro-labs).

### Labs Camera Control
 
GoPro QR code generator for basic [camera settings](https://gopro.github.io/labs/control/custom) changes

### Advanced Commands Overviews

- [Camera Macros](https://gopro.github.io/labs/control) e.g. motion or sound level triggers, long form time-lapses, etc.
- [Camera Extensions](https://gopro.github.io/labs/control/extensions) e.g. bit-rate enhancements or exposure tweaks

### Primer on Labs actions, scripting and command sets

- [Action Commands](https://gopro.github.io/labs/control/actions)
- [Setting Commands](https://gopro.github.io/labs/control/settings)

### Overview of Labs functionality and device compatibility: 

| Feature                                                                            | HERO11/Mini | HERO10/Bones | HERO9 | HERO8 | HERO7 | MAX |
|------------------------------------------------------------------------------------|-------------|--------------|-------|-------|-------|-----|
| [24.0Hz capture vs 23.976](https://gopro.github.io/labs/control/extensions)                 | Yes     | Yes     |       |       |       |     |
| [Adobe-compatible proxies](https://gopro.github.io/labs/control/proxies)                    | Yes     | Yes/No  |       |       |       |     |
| [Altered File Naming](https://gopro.github.io/labs/control/basename)                        | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [Archive Mode](https://gopro.github.io/labs/control/archive) (locked settings)              | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [Audio Channels Gain/Solo/Mute](https://gopro.github.io/labs/control/extensions)            | Yes     | Yes     | Yes   |       |       |     |
| [Audio Disable](https://gopro.github.io/labs/control/extensions)                            | Yes     | Yes     | Yes   |       |       |     |
| [Bitrate Controls](https://gopro.github.io/labs/control/extensions)                         | Yes     | Yes     |       |       |       |     |
| [Boot Command](https://gopro.github.io/labs/control/extensions)                             | Yes     | Yes     |       | Yes   |       |     |
| [DaVinci-compatible proxies](https://gopro.github.io/labs/control/proxies)                  | Yes     |         |       |       |       |     |
| [Exposure Display](https://gopro.github.io/labs/control/extensions) current ISO and shutter | Yes     |         |       |       |       |     |
| [Exposure Damping](https://gopro.github.io/labs/control/extensions) control                 | Yes     | Yes     |       |       |       |     |
| [Exposure Curve](https://gopro.github.io/labs/control/extensions) custom log encoding       | Yes     |         |       |       |       |     |
| [Exposure Min/Max Times](https://gopro.github.io/labs/control/extensions)                   | Yes     |         |       |       |       |     |
| [Extra Long time-lapse](https://gopro.github.io/labs/control/longtimelapse)                 | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [GPS time sync](https://gopro.github.io/labs/control/gpssync)                               | Yes/No  | Yes/No  | Yes   |       |       |     |
| [Guidelines Display](https://gopro.github.io/labs/control/extensions) on rear LCD           | Yes/No  |         |       |       |       |     |
| [HDMI display settings](https://gopro.github.io/labs/control/extensions)                    | Yes/No  | Yes     | Yes   |       |       |     |
| [Hindsight Timeout Extension](https://gopro.github.io/labs/control/extensions)              | Yes     | Yes     |       |       |       |     |
| [Histogram](https://gopro.github.io/labs/control/extensions) (on display)                   | Yes     | Yes     | Yes   | Yes   |       |     |
| [Histogram Position/Size](https://gopro.github.io/labs/control/extensions) (either screen)  | Yes/No  |         |       |       |       |     |
| [Large Chapter](https://gopro.github.io/labs/control/chapters) Support (12GB)               | Standard| Yes     | Yes   | Yes   |       | Yes |
| [Live Stream Initiation](https://gopro.github.io/labs/control/rtmp)                         | Yes     | Yes     | Yes   | Yes   |       |     |
| [LRV Disable](https://gopro.github.io/labs/control/extensions)                              | Yes     | limited |       |       |       |     |
| [LTC Time support](https://gopro.github.io/labs/control/ltc) (via MediaMod)                 | Yes/No  | Yes/No  | Yes   |       |       |     |
| [Max Shutter Angle](https://gopro.github.io/labs/control/maxshut) exposure control          | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [Metadata Injections](https://gopro.github.io/labs/control/extensions)                      | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [Noise Reduction](https://gopro.github.io/labs/control/extensions) control                  | Yes     |         |       |       |       |     |
| [Overlay - Burn-ins](https://gopro.github.io/labs/control/overlays) e.g. Time/Date          | limited | limited | Yes   | Yes   |       |     |
| [Overlay - Color Bar](https://gopro.github.io/labs/control/extensions)                      | limited | limited | Yes   | Yes   |       |     |
| [Overlays - Logo Burn-In](https://gopro.github.io/labs/control/logo)                        | limited | limited | Yes   |       |       |     |
| [Overlays - Luma Sweep](https://gopro.github.io/labs/control/extensions)                    | limited | limited | Yes   | Yes   |       |     |
| [Owner Information](https://gopro.github.io/labs/control/owner)                             | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [QR decoding while recording](https://gopro.github.io/labs/control/extensions)              | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [SD card speed test](https://gopro.github.io/labs/control/extensions)                       | Yes     | Yes     | Yes   | Yes   |       |     |
| [Spirit Level Display](https://gopro.github.io/labs/control/extensions) on rear LCD         | Yes/No  |         |       |       |       |     |
| [Sunrise/Sunset starts](https://gopro.github.io/labs/control/solartimelapse)                | Yes     | Yes/No  | Yes   | Yes   | Yes   | Yes |
| [Time delayed Starts](https://gopro.github.io/labs/control/custom)                          | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [Time/date/timecode QR Code](https://gopro.github.io/labs/control/precisiontime)            | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [Tone Mapping Controls](https://gopro.github.io/labs/control/extensions)                    | Yes     | Yes     |       |       |       |     |
| [Trigger - Accelerometer](https://gopro.github.io/labs/control/imutrigger)                  | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [Trigger - GPS speed](https://gopro.github.io/labs/control/speedtrigger)                    | Yes     | Yes/No  | Yes   | Yes   | Yes   | Yes |
| [Trigger - Gyroscope](https://gopro.github.io/labs/control/imutrigger)                      | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [Trigger - IMU Motion](https://gopro.github.io/labs/control/imutrigger)                     | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [Trigger - Motion detection](https://gopro.github.io/labs/control/motion)                   | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [Trigger - Sound Pressure Level](https://gopro.github.io/labs/control/spltrigger)           | Yes     | Yes     | Yes   |       |       |     |
| [Trigger - USB Power](https://gopro.github.io/labs/control/usb)                             | Yes/No  | Yes/No  | Yes   | Yes   |       | Yes |
| [Upload scripting](https://gopro.github.io/labs/control/dailytl)                            | Yes     | Yes     | Yes   |       |       |     |
| [USB power trust override](https://gopro.github.io/labs/control/extensions)                 | Yes     | Yes/No  |       |       |       |     |
| [Wake on Power](https://gopro.github.io/labs/control/extensions)                            | Yes     | Yes     |       | Yes   |       |     |
| [Wider Color Gamut](https://gopro.github.io/labs/control/extensions)                        | Yes     |         |       |       |       |     |
| [White Balance Lock](https://gopro.github.io/labs/control/extensions)                       | No/Yes  |         |       |       |       |     |

### Labs Firmware Release Notes

- [Release Notes](https://gopro.github.io/labs/control/notes/)

## Software 

Labs is expanding, experiment software for GoPro users [GoPro Labs software](software).

updated: March 31, 2023<br>
