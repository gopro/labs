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

# Exposure Lock

Lock exposure after <input type="range" style="width: 200px;" id="locktime" name="locktime" min="0" max="9" value="3"><label for="locktime"></label>&nbsp;&nbsp;<b id="locktimetext"></b> seconds.<br> 

or

<input type="checkbox" id="remove" name="remove"> 
<label for="remove">Remove the exposure lock</label><br>

**Note:** This command wouldn't normally used on it own, more likely combined with more complex commands. The delay is mainly so you don't expose for the QR Code being read. An example command might be **mVr4p24x-1eL3!S**  - set res to 4Kp24, EV -1.0, exposure lock in 3 seconds, then start recording.  

<center>
<div id="qrcode"></div>
<br>
</center>

QR Command: <b id="qrtext">time</b><br>
        
## ver 1.00

[BACK](..)

<script>
var once = true;
var qrcode;
var cmd = "oC15dTmNLeA";
var lasttimecmd = "";
var changed = true;

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

function checkTime(i) {
    if (i < 10) {i = "0" + i;}  // add zero in front of numbers < 10
    return i;
}

function timeLoop()
{
  if(document.getElementById("locktime") !== null)
  {
	cmd = "";
				
	var secs = parseInt(document.getElementById("locktime").value);	
	document.getElementById("locktimetext").innerHTML = secs;	
			
	if(secs > 0)
		cmd = "eL" + secs;
	else
		cmd = "eL";
				
    if(document.getElementById("remove") !== null)
    {
      if(document.getElementById("remove").checked === true)
      {
        cmd = "eL0";
      }
    }
  }
  
  qrcode.clear(); 
  qrcode.makeCode(cmd);
  
  if(cmd != lasttimecmd)
  {
	changed = true;
	lasttimecmd = cmd;
  }
	
  if(changed === true)
  {
	document.getElementById("qrtext").innerHTML = cmd;
	changed = false;
  }
	
  var t = setTimeout(timeLoop, 50);
}

function myReloadFunction() {
  location.reload();
}

makeQR();
timeLoop();


</script>
