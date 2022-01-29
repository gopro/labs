# Personalize via QR Code

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
</style>

You can choose to have your camera display your name, phone number or email, upon camera start-up. This could be helpful in the event the camera is lost. Or simply name your cameras. In addition to being displayed, it is written within each MP4 or JPG created. This information is stored in the camera, not the SD Card, so even if the camera is stolen, and the SD card replaced, the name will be displayed, and within each new media file regenerated. It will to also create a new file, “GoPro-owner.txt”, within the MISC folder of the SD card.
 
Your personalization info here: <br>
  Line 1: <input type="text" id="addnam1" value=""><br>
  Line 2: <input type="text" id="addnam2" value=""> (optional)<br>
  Line 3: <input type="text" id="addnam3" value=""> (optional)<br>

<div id="qrcode_txt" style="width: 360px">
 <center>
  <div id="qrcode"></div><br>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext"></em><br>
  <b><font color="#005CAC">Owner Information</font></b>
 </center>
</div>
<button id="copyImg">Copy Image to Clipboard</button>
<br>
<br>
Share this QR Code as a URL: <small id="urltext"></small><br>
<button id="copyBtn">Copy URL to Clipboard</button>

Note: For additional lines use \n within your text. 
e.g. Joe Bloggs\ncall (555)555-5555 

**Compatibility:** Labs enabled HERO5 Session, HERO7, HERO8, HERO9, HERO10 and MAX 
        
## ver 1.08
[More features](..) for Labs enabled cameras

<script>
var once = true;
var qrcode;
var cmd = "";
var clipcopy = "";
var lasttimecmd = "";
var changed = true;


function UTF16ToASCII()
{
    var out, i;
	
	var text = document.getElementById("addnam1").value;
	
	if(document.getElementById("addnam2").value.length > 0)
	{
		text += "\\n";
		text += document.getElementById("addnam2").value;
	}
	if(document.getElementById("addnam3").value.length > 0)
	{
		text += "\\n";
		text += document.getElementById("addnam3").value;
	}
    out = "";
	
	for (i=0;i<text.length;i++)
	{
		var code = text.charCodeAt(i);
		if(code<128)
		{
			out += text.charAt(i);
		}
		else if(code == 0x2019 || code == 0x2018 || code == 0x22 ) // all quotes to single quote
		{
			out += "'";
		}
	}
	return out;
}	

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
  if(document.getElementById("addnam1") !== null && document.getElementById("addnam2") !== null && document.getElementById("addnam3") !== null)
  {
	var simplename = UTF16ToASCII();
    cmd = "!MOWNR=\"" + simplename + "\"";
  }
  else
  {
    cmd = "!MOWNR=\"\"";
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
	clipcopy = "https://gopro.github.io/labs/control/set/?cmd=" + cmd + "&title=Owner%20Information";
	document.getElementById("urltext").innerHTML = clipcopy;
	changed = false;
  }
  
  var t = setTimeout(timeLoop, 50);
}

function myReloadFunction() {
  location.reload();
}


async function copyImageToClipboard() {
    html2canvas(document.querySelector("#qrcode_txt")).then(canvas => canvas.toBlob(blob => navigator.clipboard.write([new ClipboardItem({'image/png': blob})])));
}
async function copyTextToClipboard(text) {
	try {
		await navigator.clipboard.writeText(text);
	} catch(err) {
		alert('Error in copying text: ', err);
	}
}

function setupButtons() {	
    document.getElementById("copyBtn").onclick = function() { 
        copyTextToClipboard(clipcopy);
	};
    document.getElementById("copyImg").onclick = function() { 
        copyImageToClipboard();
	};
}

makeQR();
setupButtons();
timeLoop();

</script>
