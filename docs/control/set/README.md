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
  <div id="title_div"><font color="#005CAC"><b id="title_txt"></b></font></div>
 </center>
</div>
<br>
<div id="copyshow">
<button id="copyImg">Copy Image to Clipboard</button>
</div>

<!-- Manual Command: <input type="text" style="width: 500px;" id="addcmd" value="">
Share this QR Code as: <b id="urltext"></b>  -->

[More features](..) for Labs enabled cameras


## version 1.13

<script>
var changed = false;
var clipcopy = "";
var title = "";
var once = true;
var qrcode;
var cmd = "\"Hello World\"";
//var cmdnotime = "";
var cmd_url;
var title_url;
var lasttimecmd = ""; 

let urlParams = new URLSearchParams(document.location.search);
cmd_url = urlParams.get('cmd');
	
if(cmd_url !== null)
	cmd = cmd_url;
	
title_url = urlParams.get('title');
if(title_url !== null)
{
	title = title_url;
	document.getElementById("title_txt").innerHTML = title;
	dset("title_div", true);
}
else
{	
	dset("title_div", false);
}

let hastime = cmd.search(/oT/);
if(hastime >= 0)
	dset("copyshow", false);   // don't what user printing or sharing code with wrong date and time
else	
	dset("copyshow", true);
	
	
function HTMLPrint(txt)
{
	var txt2 = txt.replaceAll("<", "&#60;");
	var newtxt = txt2.replaceAll(">", "&#62;");
	return newtxt;
}


function updateTime()
{
	let position = cmd.search(/oT/);
	
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
		
		var newtimetxt = yy.toString() + mm.toString() + dd.toString() + h.toString() + m.toString() + s.toString();
		let letter = src_cmd.charAt(position+14);
		if(letter == '.')
		{
			newtimetxt = newtimetxt + "." + ms.toString();
			cmd = src_cmd.slice(0,position+2) + newtimetxt + src_cmd.slice(position+17);
		}
		else
		{
			cmd = src_cmd.slice(0,position+2) + newtimetxt + src_cmd.slice(position+14);
		}
	}
	
	document.getElementById("qrtext").innerHTML = HTMLPrint(cmd);
}


function dset(label, on) {
	var settings = document.getElementById(label);
	if(on === true)
	{
		if (settings.style.display === 'none') 
			settings.style.display = 'block';
	}
	else
	{
		settings.style.display = 'none';
	}
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

