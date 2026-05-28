# GoPro Labs

## Firmware

Labs offers experimental firmware program that uses QR codes to control your camera and extend your camera's functionality beyond stocks features. 
It is especially useful in situations where settings can't be communicated via voice, where WiFi is not available, where app pairing is not established, 
or in advanced setups, such as multiple cameras time synchronization or delayed camera triggers. You will not lose any pre-existing modes or features on 
your GoPro, this update simply adds more features.  Safe to install, safe to use, only the extended feature are experimental and they are all off by default. 

Download the GoPro Labs firmware for current shipping cameras:
- [MISSION 1 PRO](https://bit.ly/LABS_M1PRO_01_10_71) - v1.10.71, May 28, 2026
- [MISSION 1](https://bit.ly/LABS_M1_01_10_71) - v1.10.71, May 28, 2026
- [HERO13 Black](https://bit.ly/LABS_H13_2_10_70) - v2.10.70, October 17, 2025
- [MAX2](https://bit.ly/LABS_MAX2_01_30_70) - v1.30.70, March 17, 2025

Download and install for older cameras:
- [HERO12 Black](https://bit.ly/LABS_H12_2_40_70) - v2.40.70, November 4, 2025
- [HERO11 Black](https://bit.ly/LABS_H11_2_32_70) - v2.32.70, January 2025
- [HERO11 Black Mini](https://bit.ly/LABS_M11_2_50_71b) - v2.50.71, June 2024
- [HERO10 Black](https://bit.ly/LABS_H10_1_62_70) - v1.62.70, May 2024
- [GoPro MAX](https://bit.ly/LABS_MAX_2_02_70) - v2.02.70, July 2024
- [HERO9 Black](https://bit.ly/LABS_H9_1_72_70) - v1.72.70, June 2022
- [HERO8 Black](https://bit.ly/LABS_H8_2_51_75) - v2.51.75, July 2022
- [HERO7 Black](https://bit.ly/LABS_H7_1_90_71) - v1.90.71, January 2021
- [HERO5 Session](https://bit.ly/LABS_H5S_2_51_72) - v2.51.72, May 2021

**By downloading any of the public updates provided to you on, from, or through this page or the GoPro website you signify your agreement to [these terms of participation (the "Terms")](https://gopro.com/content/dam/help/gopro-labs/Beta_Participation_Terms_and_Conditions.pdf).**

Follow the [manual firmware update instructions](install).

[Discussion forum](https://github.com/gopro/labs/discussions) if you need help, have Labs questions, or feature suggestions. 

See updates and changes in the [Release Notes](https://gopro.github.io/labs/control/notes/)

Learn more information about the program on [GoPro.com](https://gopro.com/info/gopro-labs).

### Labs Camera Control
 
There is a lot in Labs, this is the best page to start [Labs Camera Control](https://gopro.github.io/labs/control)

### Primer on Labs actions, scripting and command sets

- New [AI Chat Bot](https://bit.ly/chat_gp_labs) to help you create Labs scripts
- Technical information on the [Labs command language](https://gopro.github.io/labs/control/tech)
- [Visual Script Tool](https://gopro.github.io/labs/build/) M1P/M1/MAX2/H13/H12/H11/H11Mini/H10/Max

### Overview of Labs functionality and device compatibility: 

| Feature                                                                                     | M1P | Mx2 | H13 | H12 | H11 | H10 | H9 | H8 | H7 | Max |
|                                                                                             | M1  | 360 |     |     | M11 | Bns |    |    |    | 360 |
|---------------------------------------------------------------------------------------------|--------|--------|--------|----------|-----------|----|----|----|-----|
| [24.0Hz capture vs 23.976](https://gopro.github.io/labs/control/extensions)                 | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ❌ | ❌ | ❌ | ❌ |
| [All Integer frame rates 30.0 vs 29.97](https://gopro.github.io/labs/control/extensions)    | ✔️ | ✔️ | ✔️ | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| [NLE proxies](https://gopro.github.io/labs/control/proxies)                                 | ✔️ | 2D️ | ✔️ | ✔️ | ✔️ | ⅓/❌ | ❌ | ❌ | ❌ | ❌ |
| [Altered File Naming](https://gopro.github.io/labs/control/basename)                        | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ |
| [Archive Mode](https://gopro.github.io/labs/control/archive) (locked settings)              | ❌️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ |
| [Audio Channels Gain/Solo/Mute](https://gopro.github.io/labs/control/extensions)            | ❌️ | ❌️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ❌ | ❌ | ❌ |
| [Audio Disable](https://gopro.github.io/labs/control/extensions)                            | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ❌ | ❌ | ❌ |
| [Bitrate Controls](https://gopro.github.io/labs/control/extensions)                         | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ❌ | ❌ | ❌ | ✔️ |
| [Boot Command](https://gopro.github.io/labs/control/extensions)                             | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ❌ | ❌ |
| [Command Shell via USB Comms](https://gopro.github.io/labs/control/extensions)              | ❌️ | ✔️ | ✔️ | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| [Commands over Open GoPro WiFi links](https://gopro.github.io/labs/control/extensions)      | ✔️ | ✔️ | ✔️ | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| [Distance-Lapse](https://gopro.github.io/labs/control/extensions)                           | ❌️ | ✔️ | ✔️ | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| [Dive Mode](https://gopro.github.io/labs/control/extensions)                                | ✅ | ❌️ | ✔️ | ✔️ | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| [Exposure Display](https://gopro.github.io/labs/control/extensions) current ISO and shutter | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ❌ | ❌ | ❌ | ❌ | ❌ |
| [Exposure Damping](https://gopro.github.io/labs/control/extensions) control                 | ❌️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ❌ | ❌ | ❌ | ❌ |
| [Exposure Curve](https://gopro.github.io/labs/control/extensions) custom log encoding       | ❌️ | ✔️ | ✔️ | ✔️ | ✔️ | ❌ | ❌ | ❌ | ❌ | ❌ |
| [Exposure Min/Max Times](https://gopro.github.io/labs/control/extensions)                   | ❌️ | ✔️ | ✔️ | ✔️ | ✔️ | ❌ | ❌ | ❌ | ❌ | ❌ |
| [Extra Long time-lapse](https://gopro.github.io/labs/control/longtimelapse)                 | ✔️ | ✔️ | ✔️ | ✔️ | ✔️/❌ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ |
| [GPS Log without capture](https://gopro.github.io/labs/control/extensions)                  | ✔️ | ✔️ | ✔️ | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| [GPS time sync](https://gopro.github.io/labs/control/gpssync)                               | ⅓ | ✔️ | ✔️ | ❌ | ✔️/❌ | ✔️/❌ | ✔️ | ❌ | ❌ | ❌ |
| [Guidelines Display](https://gopro.github.io/labs/control/extensions) on rear LCD           | ✔️ | ✔️ | ✔️ | ✔️ | ✔️/❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| [HDMI display settings](https://gopro.github.io/labs/control/extensions)                    | ❌️ | ❌️ | ✔️ | ✔️ | ✔️/❌ | ✔️ | ✔️ | ❌ | ❌ | ❌ |
| [Hindsight Timeout Extension](https://gopro.github.io/labs/control/extensions)              | ✔️ | ❌️ | ✔️ | ✔️ | ✔️ | ✔️ | ❌ | ❌ | ❌ | ❌ |
| [Histogram](https://gopro.github.io/labs/control/extensions) (on display)                   | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ❌ | ❌ |
| [Histogram Position/Size](https://gopro.github.io/labs/control/extensions) (either screen)  | ✔️ | ✔️ | ✔️ | ✔️ | ✔️/❌  | ❌ | ❌ | ❌ | ❌ | ❌ |
| [I-Frame only HEVC Encoding](https://gopro.github.io/labs/control/extensions)               | ✔️ | ✔️ | ✔️ | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| [Large Chapter](https://gopro.github.io/labs/control/chapters) Support (12GB)               | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ❌ | ✔️ |
| [Live Stream Initiation](https://gopro.github.io/labs/control/rtmp)                         | ❓ | ❌️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ❌ | ❌ |
| [Low Light mode](https://gopro.github.io/labs/control/extensions)                           | ✅ | ✔️ | ✔️ | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| [LRV Disable](https://gopro.github.io/labs/control/extensions)                              | ❌️ | ❌️ | ❌ | ❌ | ✔️ | ⅓ | ❌ | ❌ | ❌ | ❌ |
| [LTC Time support](https://gopro.github.io/labs/control/ltc) (via MediaMod/Pro Mic Adapter) | ❌️ | ❌️ | ✔️ | ✔️ | ✔️ | ✔️/❌  | ✔️ | ❌ | ❌ | ❌ |
| [Max Shutter Angle](https://gopro.github.io/labs/control/maxshut) exposure control          | 📍 | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ |
| [Metadata Injections](https://gopro.github.io/labs/control/extensions)                      | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ |
| [Noise Reduction](https://gopro.github.io/labs/control/extensions) control                  | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ❌ | ❌ | ❌ | ❌ | ❌ |
| [Overlay - Burn-ins](https://gopro.github.io/labs/control/overlays) e.g. Time/Date          | ❌️ | ❌️ | ⅓ | ⅓ | ⅓ | ⅓ | ✔️ | ✔️ | ❌ | ❌ |
| [Overlay - Color Bar](https://gopro.github.io/labs/control/extensions)                      | ❌️ | ❌️ | ⅓ | ⅓ | ⅓ | ⅓ | ✔️ | ✔️ | ❌ | ✔️ |
| [Overlays - Logo Burn-In](https://gopro.github.io/labs/control/logo)                        | ❌️ | ❌️ | ⅓ | ⅓ | ⅓ | ⅓ | ✔️ | ❌ | ❌ | ✔️ |
| [Overlays - Luma Sweep](https://gopro.github.io/labs/control/extensions)                    | ❌️ | ❌️ | ⅓ | ⅓ | ⅓ | ⅓ | ✔️ | ✔️ | ❌ | ❌ |
| [Owner Information](https://gopro.github.io/labs/control/owner)                             | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ |
| [Preset names with Labs commands](https://gopro.github.io/labs/control/extensions)          | ✔️ | ✔️ | ✔️ | ❌ | ❌️ | ❌ | ❌ | ❌ | ❌ | ❌ |
| [QR decoding while recording](https://gopro.github.io/labs/control/extensions)              | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ |
| [SD card speed test](https://gopro.github.io/labs/control/extensions)                       | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ❌ | ❌ |
| [Spirit Level Display](https://gopro.github.io/labs/control/extensions) on rear LCD         | ✔️ | ✔️ | ✔️ | ✔️ | ✔️/❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| [Stop Motion](https://gopro.github.io/labs/control/extensions)                              | ❌️ | ❌️ | ✔️ | ✔ | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| [Sunrise/Sunset starts](https://gopro.github.io/labs/control/solartimelapse)                | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️/❌ | ✔️ | ✔️ | ✔️ | ✔️ |
| [Time delayed Starts](https://gopro.github.io/labs/control/custom)                          | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ |
| [Time/date/timecode QR Code](https://gopro.github.io/labs/control/precisiontime)            | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ |
| [Tone Mapping Controls](https://gopro.github.io/labs/control/extensions)                    | ❌️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ❌ | ❌ | ❌ | ❌ |
| [Trigger - Accelerometer](https://gopro.github.io/labs/control/imutrigger)                  | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ |
| [Trigger - GPS speed](https://gopro.github.io/labs/control/speedtrigger)                    | ✔️ | ✔️ | ✔️ | ❌ | ✔️ | ✔️/❌  | ✔️ | ✔️ | ✔️ | ✔️ |
| [Trigger - Gyroscope](https://gopro.github.io/labs/control/imutrigger)                      | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ |
| [Trigger - IMU Motion](https://gopro.github.io/labs/control/imutrigger)                     | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ |
| [Trigger - Motion detection](https://gopro.github.io/labs/control/motion)                   | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ |
| [Trigger - Sound Pressure Level](https://gopro.github.io/labs/control/spltrigger)           | ❌️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ❌ | ❌ | ❌ |
| [Trigger - USB Power](https://gopro.github.io/labs/control/usb)                             | ✔️ | ✔️ | ✔️ | ✔️ | ✔️/❌ | ✔️/❌ | ✔️ | ✔️ | ❌ | ✔️ |
| [Upload scripting](https://gopro.github.io/labs/control/dailytl)                            | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ❌ | ❌ | ❌ |
| [USB power trust override](https://gopro.github.io/labs/control/extensions)                 | ⅓ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️/❌ | ❌ | ❌ | ❌ | ❌ |
| [Visual Scripting Blockly](https://gopro.github.io/labs/build)                              | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️/❌ | ❌ | ❌ | ❌ | ✔️ |
| [Wake on Power](https://gopro.github.io/labs/control/extensions)                            | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ✔️ | ❌ | ✔️ | ❌ | ✔️ |
| [Wider Color Gamut](https://gopro.github.io/labs/control/extensions)                        | ✅️ | ✔️ | ✔️ | ✔️ | ✔️ | ❌ | ❌ | ❌ | ❌ | ❌ |
| [White Balance Lock](https://gopro.github.io/labs/control/extensions)                       | ✔️ | ✔️ | ✔️ | ✔️ | ❌ | ❌ | ❌ | ❌ | ❌ |
| [White Balance Warmer/Cooler](https://gopro.github.io/labs/control/extensions)              | ✔️ | ✔️ | ✔️ | ✔ | ❌️ | ❌ | ❌ | ❌ | ❌ | ❌ |
| [Zero to sixty timing](https://gopro.github.io/labs/control/extensions)                     | ❌️ | ✔️ | ✔️ | ❌ | ❌️ | ❌ | ❌ | ❌ | ❌ | ❌ |

Key:
- ✅ now standard
- ✔️ supported 
- ❌️ unsupported
- ❓ untested
- ⅓ partly implemented 

## Software 

Labs is expanding, experiment software for GoPro users [GoPro Labs software](software).

updated: May 28, 2026<br>
