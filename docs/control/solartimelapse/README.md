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

# Simplified Sunset and Sunrise Time-lapses

The Labs's firmware can use the GPS to get a world position, then calculate the time for pretty solar events.  To ensure the accuracy of your location, it may make take a couple of minutes to get a high-precision GPS lock (you will need to be outdoors.)

## Sunrise/Sunset Time-lapse Calculator

Start <input type="range" id="tlmin" name="tlmin" min="1" max="60" value="15"><label for="tlmin"></label>&nbsp;&nbsp;<b id="minstext"></b> minutes before <input type="radio" id="sr1" name="solar" value="r"><label for="sr1">sunrise</label> or <input type="radio" id="sr2" name="solar" value="s" checked><label for="sr2">sunset</label><br> and end after <input type="range" id="tlendmin" name="tlendmin" min="10" max="120" value="60"><label for="tlendmin"></label>&nbsp;&nbsp;<b id="minsendtext"></b> minutes of capture.
 
<input type="checkbox" id="repeat" name="repeat" checked> 
<label for="repeat">Repeat for tomorrow's sunrise/sunset</label><br>

Note: you will have to manually set the interval and resolution for the night lapse mode, unfortunately not everything got hooked up with a QR Code. 
 
<center>
<div id="qrcode"></div>
<br>
</center>

QR Command: <b id="qrtext">time</b><br>
        
## ver 1.0
[BACK](..)

<script>
var once = true;
var qrcode;
var cmd = "oC30mNLeA";

function dcmd(cmd, id) {
    var x;
	if(document.getElementById(id) !== null)
	{
		x = document.getElementById(id).checked;
		if( x === true)
			cmd = cmd + document.getElementById(id).value;
	}
	else
	{
	    var i;
		for (i = 1; i < 15; i++) { 
			var newid = id+i;
			if(document.getElementById(newid) !== null)
			{
				x = document.getElementById(newid).checked;
				if( x === true)
					cmd = cmd + document.getElementById(newid).value;
			}
		}
	}
	return cmd;
}

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

function timeLoop()
{
  if(document.getElementById("tlmin") !== null)
  {
	cmd = "oC30mNLeA";
			
	var mins = parseInt(document.getElementById("tlmin").value);	
	document.getElementById("minstext").innerHTML = mins;	
	
	mins *= 60;
	
	var endmins = parseInt(document.getElementById("tlendmin").value);	
	document.getElementById("minsendtext").innerHTML = endmins;	
	
	endmins *= 60;
	
	cmd = cmd + "!" + dcmd("", "sr") + "-" + mins + "S!" + endmins + "E";
	
	
    if(document.getElementById("repeat") != null)
    {
      if(document.getElementById("repeat").checked == true)
      {
        cmd = cmd + "!R";
      }
    }
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
