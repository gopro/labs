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

# Construction Time-lapses

An extension of [Extra Long Time-lapses](../longtimelapse) feature, just performed during construction hours alone, to extend your battery life and reduce the number of images you will assemble into a time-lapse.  Remember to set your camera's clock to [local time](../precisiontime) or [UTC time](../precisiontime-utc) before using this QR Code.

## Daytime Time-lapse Calculator

Start Time <input type="range" style="width: 300px;" id="tlstrt" name="tlstrt" min="6" max="138" value="48"><label for="tlstrt"></label> <b id="starttext"></b>

End Time <input type="range" style="width: 300px;" id="tlend" name="tlend" min="6" max="96" value="54"><label for="tlend"></label> <b id="endtext"></b>

Number of photos per day <input type="range" style="width: 300px;" id="tlday" name="tlday" min="10" max="300" value="60"><label for="tlday"></label> <b id="perdaytext"></b>

Estimated runtime per charged battery: <b id="daystext">0</b> days

<center>
<div id="qrcode"></div>
<br>
</center>

QR Command: <b id="qrtext">time</b><br>
        
## Extending Time-lapse Duration

Simply replacing the battery is the easiest solution for long captures. After the battery is replaced, power on the camera so that the time-lapse can continue. You might want to set and forget for a multi-week or multi-month time-lapse, for this A/C powering the camera via USB is the best. With continuous wall power the battery is optional and the camera should run for a very long time (only SD card storage limitations.) You might be tempted to use a Lithon Ion USB powerbank, however they typically do not work well. They are designed to quickly recharge a smartphone, and when they think power is no longer needed, they shut-off. For this reason they get you far shorter captures than you would expect. If you want to try a USB powerbank, remove the GoPro battery for better results.  For long captures away from the power grid, the best solution is a small 12V 18+Ah sealed lead acid battery and attached a non-smart (doesn't shut off) USB regulator.  With the right photo interval, this configuration could last a year on a single charge.      
		
		
## ver 1.0
[BACK](..)

<script>
var once = true;
var qrcode;
var cmd = "mPdP!60SQ!1R";

function makeQR() 
{	
  if(once === true)
  {
    qrcode = new QRCode(document.getElementById("qrcode"), 
    {
      text : "!oMBURN=\"\"",
      width : 360,
      height : 360,
      correctLevel : QRCode.CorrectLevel.M
    });
    once = false;
  }
}


function pad(num, size) {
    var s = num+"";
    while (s.length < size) s = "0" + s;
    return s;
}


function timeLoop()
{
  if(document.getElementById("tlstrt") !== null)
  {
	var start = parseInt(document.getElementById("tlstrt").value);
	var startmins = start*10;
	var end = parseInt(document.getElementById("tlend").value);
	var endmins = startmins + end*10;
	var perday = parseInt(document.getElementById("tlday").value);
	
	var starthourstime = Math.trunc(startmins / 60);
	var startminstime = startmins - starthourstime * 60;
	
	var endhourstime = Math.trunc(endmins / 60);
	var endminstime = endmins - endhourstime * 60;
	
	
	document.getElementById("perdaytext").innerHTML = perday;	
	
	var stxt = pad(starthourstime, 2) + ":" + pad(startminstime, 2);
	var etxt = pad(endhourstime, 2) + ":" + pad(endminstime, 2);
	
	document.getElementById("starttext").innerHTML = stxt;
	document.getElementById("endtext").innerHTML = etxt;
	
	var d = 406 / perday;
	var dd = (406 - d * 6) / perday;
		
	dd *= 10;
	dd = Math.trunc(dd) / 10;
	
	document.getElementById("daystext").innerHTML = dd;
		
	var interval = Math.trunc(((endmins - startmins)*60 / perday) - 15);
	if(interval < 30) interval = 30;
	
	cmd = "mPdP>" + stxt + "<" + etxt + "!" + interval + "SQ~" + "!" + stxt + "S!1R";
  }
  
  qrcode.clear(); 
  qrcode.makeCode(cmd);
  document.getElementById("qrtext").innerHTML = cmd;
  var t = setTimeout(timeLoop, 100);
}

function myReloadFunction() {
  location.reload();
}

makeQR();
timeLoop();

</script>
