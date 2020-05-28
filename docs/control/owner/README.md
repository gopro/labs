<script src="../../jquery.min.js"></script>
<script src="../../qrcodeborder.js"></script>
<style>
        #qrcode{
            width: 100%;
        }
        div{
            width: 100%;
            display: inline-block;
        }
</style>

# Personalize via QR Code

You can choose to have your camera display your name, phone number or email, upon camera start-up. This could be helpful in the event the camera is lost. Or simply name your cameras. In addition to being displayed, it is written within a new file, “GoPro-owner.txt”, to the root of the SD card. This information is stored in the camera, not just the SD Card, so even if the camera is stolen, and the SD card replaced, the name will be displayed, and GoPro-owner.txt file is regenerated on each new SD card.
 
Your personalization info here: <input type="text" id="addname" value=""><br>
<center>
<div id="qrcode"></div>
<br>
</center>
QR Command: <b id="qrtext">time</b><br>
Note: Use \n for a new line. 
e.g. Joe Bloggs\ncall (555)555-5555 
        
## ver 1.0
[BACK](..)

<script>
var once = true;
var qrcode;
var cmd = "";

function makeQR() 
{	
  if(once === true)
  {
    qrcode = new QRCode(document.getElementById("qrcode"), 
    {
      text : "!MOWNR=\"\"",
      width : 360,
      height : 360,
      correctLevel : QRCode.CorrectLevel.M
    });
    once = false;
  }
}

function timeLoop()
{
  if(document.getElementById("addname") !== null)
  {
    cmd = "!MOWNR=\"" + document.getElementById("addname").value + "\"";
  }
  else
  {
    cmd = "!MOWNR=\"\"";
  }

  qrcode.clear(); 
  qrcode.makeCode(cmd);
  document.getElementById("qrtext").innerHTML = cmd;
  var t = setTimeout(timeLoop, 50);
}

function myReloadFunction() {
  location.reload();
}

makeQR();
timeLoop();

</script>
