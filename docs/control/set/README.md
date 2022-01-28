# GoPro QR Command

<script src="../../jquery.min.js"></script>
<script src="../../qrcodeborder.js"></script>
<script src="../../html2canvas.min.js"></script>
<style>
        #qrcode{
            width: 100%;
        }
        div{
            width: 100%;
            display: inline-block;
        }
		table{
			border-collapse: collapse;
		}
</style>

<div id="qrcode_txt" style="width: 360px">
 <center>
  <div id="qrcode"></div><br>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext"></em>
 </center>
</div>
<br><button id="copyImg">Copy Image to Clipboard</button>

<!-- Manual Command: <input type="text" style="width: 500px;" id="addcmd" value="">
Share this QR Code as: <b id="urltext"></b>  -->

More [GoPro Labs QR Controls](..)


## version 1.07

<script>
var changed = false;
var clipcopy = "";
var once = true;
var qrcode;
var cmd = "\"Hello World\"";
//var cmdnotime = "";
var cmdurl;
var lasttimecmd = ""; 
let urlParams = new URLSearchParams(document.location.search);
cmdurl = urlParams.get('cmd');
if(cmdurl !== null)
	cmd = cmdurl;

function updateTime()
{
	let position = cmd.search(/oT/);
	
	cmdnotime = cmd;
	if(position >= 0)
	{
		var src_cmd = cmd;
		var today = new Date();
		
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
			cmd = src_cmd.slice(0,position+2) + newtimetxt + src_cmd.slice(position+17);
			//cmdnotime = src_cmd.slice(0,position) + src_cmd.slice(position+17);
		}
		else
		{
			cmd = src_cmd.slice(0,position+2) + newtimetxt + src_cmd.slice(position+14);
			//cmdnotime = src_cmd.slice(0,position) + src_cmd.slice(position+14);
		}    	
	}

	document.getElementById("qrtext").innerHTML = cmd;
}


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
  updateTime();
  qrcode.clear(); 
  qrcode.makeCode(cmd);
  
//  if(document.getElementById("addcmd") !== null)
//  {
//	var addcmd = document.getElementById("addcmd").value;
//	if(addcmd.length > 0)
//		cmd = addcmd;
//  }	
  
//  if(cmd != lasttimecmd)
//  {
//	changed = true;
//	lasttimecmd = cmd;
//  }
//	
//  if(changed === true)
//  {
//	document.getElementById("qrtext").innerHTML = cmd;
//	clipcopy = window.location.href.split('?')[0] + "?cmd=" + cmdnotime;
//
//	changed = false;
//  }
	
  var t = setTimeout(timeLoop, 100);
}

function checkTime(i) {
    if (i < 10) {i = "0" + i;}  // add zero in front of numbers < 10
    return i;
}

function myReloadFunction() {
  location.reload();
}


async function copyTextToClipboard(text) {
	try {
		await navigator.clipboard.writeText(text);
	} catch(err) {
		alert('Error in copying text: ', err);
	}
}

async function copyImageToClipboard() {
    html2canvas(document.querySelector("#qrcode_txt")).then(canvas => canvas.toBlob(blob => navigator.clipboard.write([new ClipboardItem({'image/png': blob})])));
}


function setupButtons() {	
    document.getElementById("copyImg").onclick = function() { 
        copyImageToClipboard();
	};	
}
	
makeQR();
setupButtons();
timeLoop();

</script>

