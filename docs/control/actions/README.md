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

## Full List the Action Commands

* **!\<time>S** - Start at exactly **time** if in hh:mm form, or after n seconds. 
* **!\<time>SQ** - Start Quickly at approximately **time** if in hh:mm form, or after n seconds.  
* **!\<time>E** - End at **time** if in hh:mm form, or after n seconds.
* **!\<time>R** - Repeat the whole command.
* **!\<time>N** - No Action until exact **time**, useful if you just need a pause.
* **!\<time>NQ** - No Action until at approximately **time**.
* **!\<time>O** - Off - shutdown the camera.
* **!\<time>SMs-t** - Start Motion detection with start sensitivity 's' and stop sensitivity 't' -- 't' field is optional.
* **!\<time>SMsDdMmHh** - Start Motion detection with sensitivity 's', Delay of 'd', Mask of 'm' and Hold for 'h' seconds (D,M and H fields are all optional.)
* **!\<time>SKs-t** - Start Speed capture at threshold 's' km/h and stop at 't' km/h -- 't' field is optional.
* **!\<time>SKsHh** - Start Speed capture at threshold 's' km/h and Hold for 'h' seconds (H fields are all optional.)

## examples:

* **!S** - start now  
* **!60E** - end after 60 seconds (End commands are not used for photos.)
* **!2R** - repeat after 2 seconds
* **!s-01:00S** - start one hour before sunset
* **!nS** - start at true noon.
* **!s1200E** - end 1200 seconds after sunset
* **!r-600S** - start 600 seconds before sunrise

## Storing metadata (Permanent, survives power off)

* **!M\<fourcc\>”string”**
* **!M\<fourcc\>=Number metadata**

Example for display the owner’s name
**!MOWNR=”Joe Bloggs”**

All tags between **OWNA** and **OWNZ** will be displayed and stored in **GoPro-owner.txt**.

All tags between **OWNa** and **OWNz** will be only stored in the **GoPro-owner.txt**

Any four character code can be used for store other information. You can also store numeric data examples: 
* **!MCAMR=53** - metadata CAMR will be 53 
* **!MABCD=45.234** - metadata ABCD will be floating point 45.234
* **!MUNIT=-1723** - metadata UNIT will be -1723 

As these are a semi-permanent addition to your camera, you can erase all your permanent metadata with a **!RESET** QR command. 

## Storing metadata (Temporarily, until power off)

* **oM\<fourcc\>”string”**  
* **oM\<fourcc\>=Number metadata**

## Scripting

The geek factor is highest in this section.  This is not a Turing-complete language, but it can get many interesting capture control jobs done.  There are save and load commands, additive metadata and clock time conditionals

* **!SAVEname=script**  e.g. !SAVEdaily=dPmP!12:00S!Ldaily - a save script called ‘daily’ that repeatedly shots one photo every day at noon. 
* **!Lname**  e.g. !LnightLapse - load add run a script called nightLapse
* **oAxxxx=1** e.g. oAMETA=1  --  to implement a basic counter in metadata
* **\<timeCMD**  e.g. \<09:00!30R!Lother - if current time is less than 9am, wait 30mins and loop, otherwise load script called ‘other’.
* **\>timeCMD** e.g. !SM9\>22:00!R - do motion detection until 10PM, then stop
* **\>timeA\<timeBcmdTrue~cmdFalse** e.g. mP>06:00<20:00!180SQ~!06:00S!R - If time is between 06:00 and 20:00 take a photo in 180 seconds else start a 6am, repeat.
* **"any text"** e.g. mV"Video\nMode"!S!5E!4NmP"Photo\nMode"!S!5R - this will display "Video Mode" and "Photo Mode" when switch to those modes.  

Known Issue: The saved and load scripts can't support conditionals, as the '<' and '>' characters, nor are " characters supported in scripts. This oversight will hopefully be addressed in a future Labs build. So scripts are currently limited to a simple series of actions. The conditionals are functioning correction within QR Code reading. So commands/scripts that use conditionals will be limited to around 200 characters in a single QR Code.

# Experiment Here

## Typing-in Your Custom Action:


<div id="qrcode"></div>
Custom Mode: <input type="text" id="tryit" value=""><br>


## ver 1.02
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
  var t = setTimeout(timeLoop, 50);
}

function myReloadFunction() {
  location.reload();
}

makeQR();
timeLoop();

</script>

