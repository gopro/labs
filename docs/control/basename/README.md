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

# Altered File Naming via QR Code

You GoPro HERO8 will typically name your files something like GOPR3606.JPG and GH013607.MP4.  If you format your media, and factory reset your camera, you can change the file counter back to zero, but otherwise, you have no control over the file name, until this Labs hack. This intended for high volume multiple camera production, where simply naming the source media different will ease post productions. **WARNING:** The GoPro App and GoPro Plus will not support these renamed files.

Your base filename here: <input type="text" id="addname" value=""> (use only a-z, A-Z, 0-9, '-', "_" and '+' characters)<br> 
Up to eight characters. e.g. "CAMERA06"<br> 
<br>
Your filenames with be in the format: <b id="newnameMP4">nameGH013607.MP4</b> and <b id="newnameJPG">nameGOPR3607.JPEG</b><br>

<center>
<div id="qrcode"></div>

<input type="checkbox" id="permanent" name="permanent"> <label for="permanent">Make this name change permanent</label><br>
Can be restored by setting the basename to nothing.

</center>
QR Command: <b id="qrtext">time</b><br>
        
## ver 1.01
[BACK](..)

<script>
var once = true;
var qrcode;
var cmd = "";
var lasttimecmd = "";
var changed = true;
var number = 1;

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

function pad(num, size) {
    var s = num+"";
    while (s.length < size) s = "0" + s;
    return s;
}

function filter(txt)
{
	var desired = txt.replace(/[^a-zA-Z0-9-_+]/gi, '');
	return desired;
}

function timeLoop()
{
  var type = "o";
	
  if(document.getElementById("permanent") !== null)
  {
	if(document.getElementById("permanent").checked === true)
	{
		type = "!";
	}
  }
		
  if(document.getElementById("addname") !== null)
  {
    cmd = type + "MBASE=\"" + filter(document.getElementById("addname").value) + "\"";
  }
  else
  {
    cmd = type + "MBASE=\"\"";
  }

  if(document.getElementById("newnameMP4") !== null)
  {
	var MP4 = filter(document.getElementById("addname").value) + "GH01" + pad(number,4) + ".MP4";
	var JPG = filter(document.getElementById("addname").value) + "GOPR" + pad(number,4) + ".JPG";
 
	number++;
	if(number > 9999) 
	{
	  number = 1;
	}
	
	document.getElementById("newnameMP4").innerHTML = MP4;
	document.getElementById("newnameJPG").innerHTML = JPG;
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
  
  var t = setTimeout(timeLoop, 250);
}

function myReloadFunction() {
  location.reload();
}

makeQR();
timeLoop();

</script>
