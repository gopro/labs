# Full List the Action Commands

<script src="../../jquery.min.js"></script>
<script src="../../qrcodeborder.js"></script>
<style>
        #qrcode{
            height: 380px;
            width: 380px;
            margin: 0px;
        }
        div{
            height: 380px;
            width: 380px;
            margin: 0px;
            display: inline-block;
        }
</style>     

* **!**time**S** - Start at exactly **time** if in hh:mm form, or after n seconds. 
* **!**time**SQ** - Start Quickly at approximately **time** if in hh:mm form, or after n seconds.  
* **!**time**E** - End at **time** if in hh:mm form, or after n seconds.
* **!**time**R** - Repeat the whole command.
* **!**time**Rx** - (H11 v2.1) Repeat the command starting at position x (i.e. a goto command).
* **!**time**N** - No Action until exact **time**, useful if you just need a pause.
* **!**time**NQ** - No Action until at approximately **time**.
* **!**time**O** - Off, shutdown the camera.
* **!**time**OR** - shutdown and restart the camera.
* **!**time**U** - Attempt a network contention and Upload <sup>9/10/11</sup>.
* **!**time**W** - Connect to a network, requires JOIN metadata to have been previous stored <sup>9/10/11</sup>.
* **!**time**G(S or M or L)(C)** - Start Live-streaming, **S** - 480p, **M** - 720p, **L** - 1080p, optional **C** for capture a local file, requires a previously successful **!W** command <sup>8/9/10/11</sup>
* **!**time**Dx** - (H11) !Dx wait for GPS lock with a DOP less than x, then sync time. For time only locks !D is fine. 
* **!**time**Zx** - (H11 v2.1)  **!Z3** - Disable Buttons, **!Z0** - Enable (default), **!Z1** - Disable Shutter, **!Z2** - Disable Mode

## Capture Triggers (Classic, invent your own below.)

* **!**time**SMs-t** - Start Motion detection with start sensitivity 's' and stop sensitivity 't' -- 't' field is optional.
* **!**time**SMsDdMmHh** - Start Motion detection with sensitivity 's', Delay of 'd', Mask of 'm' and Hold for 'h' seconds (D,M and H fields are all optional.)
* **!**time**SKs-t** - Start Speed capture at threshold 's' km/h and stop at 't' km/h -- 't' field is optional.
* **!**time**SKsHh** - Start Speed capture at threshold 's' km/h and Hold for 'h' seconds (H fields are all optional.)
* **!**time**SAs-tDdHh** - Accelerometer Trigger
* **!**time**SGs-tDdHh** - Gyro Trigger
* **!**time**SIs-tDdHh** - IMU Trigger (both Accerometer and Gyro)
* **!**time**SDs-tDdHh** - Speed Pressure Level Trigger, 's' and 't' values are in dB.

## examples:

* **!S** - start now  
* **!07:00S** - start at precisely 7am  
* **!300SQ** - start in approximately 300 seconds.  
* **!60E** - end after 60 seconds (End commands are not used for photos.)
* **!2R** - repeat after 2 seconds
* **!s-01:00S** - start one hour before sunset
* **!nS** - start at true noon.
* **!s1200E** - end 1200 seconds after sunset
* **!r-600S** - start 600 seconds before sunrise
* **!17:00W!GLC** - start Live-streaming 1080p at 5pm, saving a local copy

## Storing metadata (Permanent, survives power off)

* **!M**fourcc**”string”**
* **!M**fourcc**=Number metadata**

Example for display the owner’s name
**!MOWNR=”Joe Bloggs”**

All tags between **OWNA** and **OWNZ** will be displayed and stored in **GoPro-owner.txt**.

All tags between **OWNa** and **OWNz** will be only stored in the **GoPro-owner.txt**

Any four character code can be used for store other information. You can also store numeric data examples: 
* **!MCAMR=53** - metadata CAMR will be 53 
* **!MABCD=45.234** - metadata ABCD will be floating point 45.234
* **!MUNIT=-1723** - metadata UNIT will be -1723 

## Storing metadata (Temporarily, until power off)<br>
<br>
(All cameras and Older Labs)<br>
<br>
* **oM**fourcc**&#61;"string"**  
* **oM**fourcc**=Number metadata**
<br>
(Alternative H11 v2.1)<br>
<br>
* **#M**fourcc**&#61;"string"**  
* **#M**fourcc**=Number metadata**

## Reset Actions ##

* **!RESET** - erase all your permanent metadata (anything that used !Mxxxx command.)  (requires user confirmation.)
* **!FORMAT**<sup>10/11</sup> - for SD formatting via QR Code (requires user confirmation.)
* **!FRESET**<sup>10/11</sup> - Factory reset, erase everything, except QR code metadata (requires user confirmation.)
* **!PRESET**<sup>10/11</sup> - Presets reset, restore the default presets (requires user confirmation.)
* **!WRESET**<sup>10/11</sup> - WiFi Credentials reset, erase all your BLE and WiFi configurations (requires user confirmation.)

## Scripting

The geek factor is highest in this section.  This is not a Turing-complete language, but it can get many interesting capture control jobs done.  There are save and load commands, additive metadata and clock time conditionals

* **!SAVEname=script**  e.g. !SAVEdaily=dPmP!12:00S!Ldaily - a save script called ‘daily’ that repeatedly shots one photo every day at noon. 
* **!Lname**  e.g. !LnightLapse - load add run a script called nightLapse
* **oAxxxx=1** e.g. oAMETA=1  --  to implement a basic counter in metadata
* **"any text"** e.g. mV"Video Mode"!S!5E!4NmP"Photo Mode"!S!5R - this will display "Video Mode" and "Photo Mode" when switch to those modes.  

### Conditionals Based on Time

**\<** and **>** character are used to indicate a conditionals, less than, and greater than equal.

**\<08:45!S** is equalivant to 

> if(current_time < 8:45) <br>
> &nbsp;&nbsp;&nbsp;   Start

**>18:30!R** is equalivant to 

> if(current_time >= 18:30) <br>
> &nbsp;&nbsp;&nbsp;  Repeat

Note: there is not **equals** condition; nothing like if(time==09:00).

The if condition defaults to effecting only the one command after the condition

**\<08:45!S"Hello World"** is equalivant to:

> if(current_time < 8:45) <br>
> &nbsp;&nbsp;&nbsp;   Start<br>
> print "Hello World"
	
The start will happen if the condition is true, but the print message occurs whether true or false.  To make the print also part of the true state you can use **+** between the joined commands.

**\<08:45!S+"Hello World"** is equalivant to

> if(current_time < 8:45) <br>
> {<br>
> &nbsp;&nbsp;&nbsp;    Start <br>
> &nbsp;&nbsp;&nbsp;    print "Hello World" <br>
> }

These can be stacked too, e.g. **\<08:45!S+"Hello World"+!60E** is equalivant to

> if(current_time < 8:45) <br>
> {<br>
> &nbsp;&nbsp;&nbsp;    Start <br>
> &nbsp;&nbsp;&nbsp;    print "Hello World" <br>
> &nbsp;&nbsp;&nbsp;    After 60 seconds End the capture <br>
> }

Conditions support **else** statements using the **~** character after the last 'true' command

**\<08:45!S+"Hello World"+!60E~!08:44N!R** is equalivant to

> if(current_time < 8:45) <br>
> {<br>
> &nbsp;&nbsp;&nbsp;    Start <br>
> &nbsp;&nbsp;&nbsp;    print "Hello World" <br>
> &nbsp;&nbsp;&nbsp;    After 60 seconds End the capture <br>
> }<br>
> else<br>
> {<br>
> &nbsp;&nbsp;&nbsp;    Sleep until 8:44 the next day <br>
> }<br>
> Repeat


Conditionals themselves can be stacked like **\>09:15<10:00!S** is equalivant to 

> if(current_time >= 9:15) <br>
> &nbsp;&nbsp;&nbsp; if(current_time <= 10:00) <br>
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Start<br>
	
However the else can only be applied to the last condition. **\>09:15<10:00!S+"Hello World"+!60E~!09:30N!R** is equalivant to

> if(current_time >= 9:15) <br>
> {<br>
> &nbsp;&nbsp;&nbsp;	if(current_time <= 10:00) <br>
> &nbsp;&nbsp;&nbsp;	{<br>
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;		Start<br>
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;		print "Hello World"<br>
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;		After 60 seconds End the capture<br>
> &nbsp;&nbsp;&nbsp;	}<br>
> &nbsp;&nbsp;&nbsp;	else<br>
> &nbsp;&nbsp;&nbsp;	{<br>
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;		Sleep until 9:30 the next day<br>
> &nbsp;&nbsp;&nbsp;	}<br>
> }<br>
> Repeat

The command language is kept simple, so it doesn't maintain a stack on the conditional nesting. 

### Conditionals Based on Camera Status

Coming soon (HERO11), new conditional commands. Now \>xValue and/or \<xValue can be used to test camera states, where 'x' is the camera state to test, and Value the amount to test against:<br>
* **a** accelerationValue - **\>aValue**CMD if(acceleration \> Value) then CMD, units in Gs
* **b** batteryLevel - **\>bValue**CMD if(battery \> Value) then CMD, units in percentage
* **c** coordDistance - **\>cDist**CMD  then CMD, units in meters, compare distance from initial GPS location
* **c:X** coord[A-Z]Distance - **\>c:XDist**CMD There are up to 26 pre-stored GPS locations oMFRMA=latt,long thru oMFRMZ. If nothing is store in FRMx, it will initialize with the current location.
* **d** GPS DOP - **\<dValue**CMD - if(DOP \< Value) then CMD, units in 100x DOP. GPS location precision.
* **e** random - **\<eValue**CMD \<e50 - 50% true \<e90 - 90% true.
* **g** gyroValue - **\>gValue**CMD if(gryo \> Value) CMD, numbers are in degrees per second.
* **h** heightValue - **\>hValue**CMD if(height \> Value) CMD, numbers are in meters above sealevel.
* **i** isoValue - **\>iValue**CMD - testing ISO where ISO ranges from 100 to 6400
* **k** speedValue - **\>kValue**CMD if(gps Speed \> Value) CMD e.g. >k45!S, numbers are in km/h.
* **l** loop_countValue - **\<lValue**CMD if(loop_count \< Value) CMD e.g. \<l45!R, this is the loop count for !R repeat, since last QR scan or boot.
* **m** motionValue - **\<mValue**CMD if(motion \< Value) CMD Motion value is a percentage of pixels moving  e.g. >m5!S+60E!R, this look of motion greater than 5%, and record for 60seconds when detected.
* **m:X** motion[A-Z]Value - <m:A through <m:Z adjusts the sensitivity of the detector, the above is the equivalent <m:J.  'A' is very low sensitivity, only large pixel changes detected, 'Z' tiniest change detected. 
* **p** soundpressureValue - **\>pValue**CMD if(spl \> Value) CMD, numbers are in dB
* **r** recording - **\>r0**CMD1~CMD2 if(Recording > 0) then CMD1 else CMD2 
* **r:C** remote Connected - **\>r:C0**CMD1~CMD2 if(RC_Connected) then CMD1 else CMD2 
* **r:A** remote App Connected - **\>r0:A**CMD1~CMD2 if(App_Connected) then CMD1 else CMD2 
* **s** shutterValue - **\>sValue**CMD - testing shutter, where 1/Value is used for shutter speed
* **t:X** timedate - **\>t:XValue**CMD - where X Y-Year M-Month D-Day H-Hour N-miNute S-second W-day_of_the_Week B-seconds_since_Boot Q-seconds_since_Qrcode
* **u** USB power - **\>u0**CMD1~CMD2 if(power is on USB) then CMD1 else CMD2
* **y** mode_pressesValue - **\>y0**CMD1~CMD2 if(mode_presses > 0) then CMD1 else CMD2
* **z** shutter_pressesValue - **\>z0**CMD1~CMD2 if(shutter_presses > 0) then CMD1 else CMD2

### Assignments, Variables and Math

Coming soon (HERO11), QR Command scripts can include variables and operation on them. Why? Fun maybe? A complete program in a QR Code.

As 'a' to 'z' and system system fields, 'A' to 'Z' are the variable can contain any floating point number. This new variables are all initialized to zero, 
and can be tested with the '<' and '>' conditionals. To make them non-zero, they can be assign with and '=' command. Just like with conditions and action, 
the '=' character is the command delimiter and comes first.  

**=A5**  is the command variable A = 5.

**=P3.14159265** assigns Pi to variable P.  

Now math can be used to modify your variables.

* **=A+1.4** adds in form A = A + 1.4
* **=D-2** substraction D = D - 2  (note: assignments of negative numbers aren't support, but subtracting is. So **=D0=D-2** would initialize D to be -2, although =D0 is unnessary as all variable are initialize to zero at boot.)
* **=A*P** multiply A = A * P
* **=E&#47;7** divide E = E &#47; 7
* **=H^A** raised to a power H = H ^ A
* **=F^0.5** raised to a power F = sqrt(F)
* **=B%10** modulus  B = B % 10 
* **=G#2** Log base N  G = log(G)/log(2) 
* **=J&6** and  J = (float)((int)J & 6) 
* **=K&#124;3** or  K = (float)((int)K &#124; 3) 

There should be a prize if some can come up with a practical use for all of these ;)

So if thought the above is crazy, it gets weirder.

* **=B$BITR**  load the contents of the BITR (bitrate) hack into variable B, otherwise store zero.  So you can test if a feature is enabled.
* **=Tt:W** load the day of the week into varible T
* **=Di** load the current ISO value into varible D
* **oMEVBS=E**  store the current into EV Bias hack, so you can make a variable mess with your exposure (potential mid capture.)
* **!MVarC=C**  permanently store the current variable C into metadata field VarC, so this can be read back on next boot.  

### Why Add Math to QR codes

You the user can have very particular shooting needs, this improves the robustness of Labs to cover a wider range of automatic captures. And is it cool. ;)

Say you want use a GoPro as a crude light meter, and report the output as an [exposure value](https://en.wikipedia.org/wiki/Exposure_value), then make capture decision based on that EV value.

EV = logbase2 (f-number^2/(time x gain_above_base_iso))  is the formula for EV<br>

As a QR command: **=E6.25=Gi=G&#42;0.01=E/G=E&#42;s=E#2"Exposure value $E"!R**<br>

Command steps explained:
> E=6.25<br>
> G=ISO value<br>
> G=G&#42;0.01<br>
> E=E/G<br>
> E=E&#42;shutter value (1/s)<br>
> E=log(E)/log(2)<br>
> print E<br>
> repeat<br>
 
# Experiment Here

## Typing-in Your Custom Action:


<div id="qrcode_txt" style="width: 360px">
 <center>
  <div id="qrcode"></div><br>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext"></em>
 </center>
</div>

Custom Mode: <input type="text" id="tryit" value=""><br>


updated: Feb 24, 2023

[BACK](..)


<script>
var once = true;
var qrcode;
var cmd = "";

function makeQR() {	
  if(once === true)
  {
    qrcode = new QRCode(document.getElementById("qrcode"), 
    {
      text : "\"Try It\"",
      width : 400,
      height : 400,
      correctLevel : QRCode.CorrectLevel.M
    });
    once = false;
  }
}

function HTMLPrint(txt)
{
	var txt2 = txt.replaceAll("<", "&#60;");
	var newtxt = txt2.replaceAll(">", "&#62;");
	return newtxt;
}

function timeLoop()
{
  if(document.getElementById("tryit") !== null)
  {
    cmd = document.getElementById("tryit").value;
	if(cmd.length === 0)
	{
		cmd = "\"Try It\"";
	}
  }
  else
  {
    cmd = "\"Try It\"";
  }

  qrcode.clear(); 
  qrcode.makeCode(cmd);
  
  document.getElementById("qrtext").innerHTML = HTMLPrint(cmd);
  
  var t = setTimeout(timeLoop, 50);
}

function myReloadFunction() {
  location.reload();
}

makeQR();
timeLoop();

</script>

