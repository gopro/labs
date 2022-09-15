# GoPro Labs Command Language

On QR Control Instructions page, one of the first demo QR Code was surfing example, using 1440p and 60fps with some custom Protune settings. The QR Code used this command string: **mVr1440p60tw55x.5**. While some of that seems like 1440p60, here is a full breakdown of how that command works:

* **mV** - is shorthand for mode Video - this is the same a swiping the camera to use video mode.
* **r1440** - set resolution to 1440 - same as using the LCD to set 1440p
* **p60** - set fps to 60 
* **t** - Protune on
* **w55** - white balance to 5500K
* **x.5** - exposure compensation is set to 0.5
  
Any of these can be used on their own, or in different order, however the order can have meaning.  If I enable protune with a ‘t’ command, while in the Photo mode, then switched to video, the video will be in whatever mode setting you had previously. The individual commands within a QR Code are performed in order, just like you would when using the touch LCD.

All setting commands start with a lowercase character, followed by either uppercase or numbers for the parameters, the next lowercase character is the next setting command. Below are some additional setting commands with their range of parameters.

## The Full List of [**Settings Commands**](../settings)

## The Full List of [**Action Commands**](../actions)


### ver 1.00
updated: July 7, 2022

[Learn more](..) on QR Control
