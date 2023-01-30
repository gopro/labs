# GoPro Labs Command Language

## Setting Commands

All QR Codes are simple text strings, alphanumeric characters to describe settings and actions for your GoPro camera. It is fairly easy to learn, 
so you can create you own custom commands. Here is an example command to set video at 4K 60fps with some Protune customization: **mVr4p60x-.5cFw55**. 
Breaking-down how that command works, firstly all GoPro QR settings commands are separated with lowercase characters, so this command is interpreted 
in these groups mV r4 p60 x-.5 cF w55. This is what each command group means:

* **mV** - is shorthand for mode Video - this is the same a swiping the camera to use video mode.
* **r4** - set resolution to 4K (16:9), r4T (for 4K 4:3) and r4X (for HERO11s 8:7) 
* **p60** - set the frame rate to 60 fps 
* **x-.5** - exposure compensation is set to -0.5
* **cF** - color Flat
* **w55** - white balance to 5500K
  
Any of these can be used on their own, or in a different order, however the order can have meaning. If the camera was currently in a photo mode, 
and you set the Protunes settings first, then switched to video, any Protune changes would be to the photo preset, the video will have whatever Protune 
settings you had previously. The individual commands within a QR code are performed in order, just like you would when using the touchscreen.

### Option Commands

Just like settings, these alter camera options, not the settings used in a preset.  Examples like beep volume and screen brightness. It turns out there are a lot of these. 
While each setting command is a single lowercase character, it can be followed by a number of either uppercase or numbers for the parameters. Option commands, starting with **o** 
can stack many parameter in one command. This is a single options command **oV1B4D2** which translates to Volume - 10%, Brightness 40%, and LEDs rear only. The same command can be 
written as **oV1oB4oD2**, three separate option commands, but as storage in a QR code is limited so options can be stacked for more efficiency, this is also why spaces are not 
used between commands.

### The Full List of [**Settings and Option Commands**](../settings)

## Action and Conditional Commands

Now you know how to set up your camera with QR commands, the fun really begins with Actions and Conditionals. Actions are starting **!S** or ending a capture **!E**, manual upload **!U**, 
beginning a live stream **!G**. As these actions are typically just pressing a button or camera menu, these actions can be enhanced based on time. e.g. **!08:00S**, which will sleep 
the camera until 8am, and then start capture (in the camera's default mode.) We can also do an conditional capture based on time. e.g. **>06:00<19:00mV~mNL!S** with this command, if the 
time is greater than 6am and less than 7pm, set mode Video, else set mode NightLaspe, then start.  You can start pre-programming actions with QR codes.

### The Full List of [**Actions and Conditional Commands**](../actions)

updated: January 29, 2023

[Learn more](..) on QR Control
