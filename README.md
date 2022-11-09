# GoPro Labs

Labs is GoPro's experimental firmware program that uses QR codes to control your camera and extend your camera’s functionality beyond stocks features. It is especially useful in situations where settings can’t be communicated via voice, where WiFi is not available, where app pairing is not established, or in advanced setups, such as multiple cameras time synchronization or delayed camera triggers.

Learn more information about the program on [GoPro.com](http://www.gopro.com/labs).

Download and install your [GoPro Labs firmware](https://community.gopro.com/s/article/GoPro-Labs).

GoPro QR code generator for basic [camera settings](https://gopro.github.io/labs/control/custom) changes

## Advanced Commands Overviews

- [Camera Macros](https://gopro.github.io/labs/control) e.g. motion or sound level triggers
- [Camera Extension](https://gopro.github.io/labs/control/extensions) e.g. bit-rate enhancements or exposure tweaks

## Primer on Labs actions, scripting and command set

- [Action Commands](https://gopro.github.io/labs/control/actions)
- [Setting Commands](https://gopro.github.io/labs/control/settings)

## Overview of Labs functionality and device compatibility: 

| Feature                                               | HERO11/Mini  | HERO10/Bones  | HERO9 | HERO8 | HERO7 | MAX |
|-------------------------------------------------------|---------|---------|-------|-------|-------|-----|
| [24.0Hz capture vs 23.976](https://gopro.github.io/labs/control/extensions)        | Yes     | Yes     |       |       |       |     |
| [Adobe-compatible proxies](https://gopro.github.io/labs/control/proxies)           | Yes     | Yes/No  |       |       |       |     |
| [Altered File Naming](https://gopro.github.io/labs/control/basename)               | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [Archive Mode](https://gopro.github.io/labs/control/archive) (locked settings)     | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [Audio Channels Gain/Solo/Mute](https://gopro.github.io/labs/control/extensions)   | Yes     | Yes     | Yes   |       |       |     |
| [Audio Disable](https://gopro.github.io/labs/control/extensions)                   | Yes     | Yes     | Yes   |       |       |     |
| [Bitrate Controls](https://gopro.github.io/labs/control/extensions)                | Yes     | Yes     |       |       |       |     |
| [Boot Command](https://gopro.github.io/labs/control/extensions)                    | Yes     | Yes     |       | Yes   |       |     |
| [Exposure Damping](https://gopro.github.io/labs/control/extensions) Control        | Yes     | Yes     |       |       |       |     |
| [Extra Long time-lapse](https://gopro.github.io/labs/control/longtimelapse)        | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [GPS time sync](https://gopro.github.io/labs/control/gpssync)                      | Yes/No  | Yes/No  | Yes   |       |       |     |
| [HDMI display settings](https://gopro.github.io/labs/control/extensions)           | Yes/No  | Yes     | Yes   |       |       |     |
| [Hindsight Timeout Extension](https://gopro.github.io/labs/control/extensions)     | Yes     | Yes     |       |       |       |     |
| [Histogram](https://gopro.github.io/labs/control/extensions) (on LCD screen)       | Yes     | Yes     | Yes   | Yes   |       |     |
| [Large Charpter](https://gopro.github.io/labs/control/chapters) Support (12GB)     | Standard| Yes     | Yes   | Yes   |       | Yes |
| [Live Stream Initiation](https://gopro.github.io/labs/control/rtmp)                | Yes     | Yes     | Yes   | Yes   |       |     |
| [LRV Disable](https://gopro.github.io/labs/control/extensions)                     | limited | limited |       |       |       |     |
| [LTC Time support](https://gopro.github.io/labs/control/ltc) (via MediaMod)        | Yes/No  | Yes/No  | Yes   |       |       |     |
| [Max Shutter Angle](https://gopro.github.io/labs/control/maxshut) exposure control | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [Metadata Injections](https://gopro.github.io/labs/control/extensions)             | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [Overlay - Burn-ins](https://gopro.github.io/labs/control/overlays) e.g. Time/Date | limited | limited | Yes   | Yes   |       |     |
| [Overlay - Color Bar](https://gopro.github.io/labs/control/extensions)             | limited | limited | Yes   | Yes   |       |     |
| [Overlays - Logo Burn-In](https://gopro.github.io/labs/control/logo)               | limited | limited | Yes   |       |       |     |
| [Overlays - Luma Sweep](https://gopro.github.io/labs/control/extensions)           | limited | limited | Yes   | Yes   |       |     |
| [Owner Information](https://gopro.github.io/labs/control/owner)                    | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [QR decoding while recording](https://gopro.github.io/labs/control/extensions)     | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [SD card speed test](https://gopro.github.io/labs/control/extensions)              | Yes     | Yes     | Yes   | Yes   |       |     |
| [Sunrize/Sunset starts](https://gopro.github.io/labs/control/solartimelapse)       | Yes     | Yes/No  | Yes   | Yes   | Yes   | Yes |
| [Time delayed Starts](https://gopro.github.io/labs/control/custom)                 | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [Time/date/timecode QR Code](https://gopro.github.io/labs/control/precisiontime)   | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [Tone Mapping Controls](https://gopro.github.io/labs/control/extensions)           | Yes     | Yes     |       |       |       |     |
| [Trigger - Accelerometer](https://gopro.github.io/labs/control/imutrigger)         | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [Trigger - GPS speed](https://gopro.github.io/labs/control/speedtrigger)           | Yes     | Yes/No  | Yes   | Yes   | Yes   | Yes |
| [Trigger - Gyroscope](https://gopro.github.io/labs/control/imutrigger)             | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [Trigger - IMU Motion](https://gopro.github.io/labs/control/imutrigger)            | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [Trigger - Motion detection](https://gopro.github.io/labs/control/motion)          | Yes     | Yes     | Yes   | Yes   | Yes   | Yes |
| [Trigger - Sound Pressure Level](https://gopro.github.io/labs/control/spltrigger)  | Yes     | Yes     | Yes   |       |       |     |
| [Trigger - USB Power](https://gopro.github.io/labs/control/usb)                    | Yes/No  | Yes/No  | Yes   | Yes   |       | Yes |
| [Upload scripting](https://gopro.github.io/labs/control/dailytl)                   | Yes     | Yes     | Yes   |       |       |     |
| [USB power trust override](https://gopro.github.io/labs/control/extensions)        | Yes     | Yes/No  |       |       |       |     |
| [Wake on Power](https://gopro.github.io/labs/control/extensions)                   | Yes     | Yes     |       | Yes   |       |     |

## ver 1.03


