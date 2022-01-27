# QR Control Quick Command

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
      
<div id="qrcode"></div>
	  
QR Command: <b id="qrtext"></b><br>

Manual Command: <input type="text" style="width: 500px;" id="addcmd" value="">

Share this QR Code as: <b id="urltext"></b> 

More [GoPro Labs QR Controls](..)


## version 1.03

<script>
       
var once = true;
var qrcode;
var cmd = "\"Hello World\"";
var cmdurl;
var lasttimecmd = ""; 
let urlParams = new URLSearchParams(document.location.search);
cmdurl = urlParams.get('cmd');
if(cmdurl !== null)
	cmd = cmdurl;

let position = cmd.search(/oT/);
if(position >= 0)
{
	var src_cmd = cmd;
	var today = new Date();
	
	var ms = today.getTime();
	var	yy = today.getFullYear() - 2000;
	var	mm = today.getMonth() + 1;
	var	dd = today.getDate();
	var	h = today.getHours();
	var	m = today.getMinutes();
	var	s = today.getSeconds();
	var	ms = today.getMilliseconds();
		
	yy = checkTime(yy);
	mm = checkTime(mm);
	dd = checkTime(dd);
	h = checkTime(h);
	m = checkTime(m);
	s = checkTime(s);
	ms = Math.floor(ms / 10); // hundredths
	ms = checkTime(ms);
		
	var newtimetxt = yy + mm + dd + h + m + s;        
	let letter = src_cmd.charAt(position+14);
    if(letter == '.')
    {
		newtimetxt = newtimetxt + "." + ms;
		cmd = src_cmd.slice(0,position) + newtimetxt + src_cmd.slice(position+17);
    }
    else
    {
		cmd = src_cmd.slice(0,position) + newtimetxt + src_cmd.slice(position+14);
    }    	
}

document.getElementById("qrtext").innerHTML = cmd;

function makeQR() 
{	
  if(once === true)
  {
    qrcode = new QRCode(document.getElementById("qrcode"), 
    {
      text : cmd,
      width : 360,
      height : 360,
      correctLevel : QRCode.CorrectLevel.M
    });
    once = false;
  }
}

function timeLoop()
{  
  qrcode.clear(); 
  qrcode.makeCode(cmd);
  
  if(document.getElementById("addcmd") !== null)
  {
	var addcmd = document.getElementById("addcmd").value;
	if(addcmd.length > 0)
		cmd = addcmd;
  }	
  
  if(cmd != lasttimecmd)
  {
	changed = true;
	lasttimecmd = cmd;
  }
	
  if(changed === true)
  {
	document.getElementById("qrtext").innerHTML = cmd;
	document.getElementById("urltext").innerHTML = window.location.href.split('?')[0] + "?cmd=" + cmd;

	changed = false;
  }
	
  var t = setTimeout(timeLoop, 100);
}

function checkTime(i) {
    if (i < 10) {i = "0" + i;}  // add zero in front of numbers < 10
    return i;
}

function myReloadFunction() {
  location.reload();
}

makeQR();
timeLoop();

</script>

