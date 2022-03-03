# Live-Stream Setup 

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

## Prerequisites for Live-streaming (HERO8/9 and 10 only)

1. **Pair with the GoPro mobile app once.** Live-streaming won't work with an out-of-box or factory-reset camera, without connecting with the App first, including the setup for auto upload.  
2. Storing WiFi credentials on the camera, for the network you intend to stream over (e.g. your home WiFi or mobile access point.) 
3. Storing the RMTP URL address that you intend to stream to (e.g using a service like Twitch.)

When both of these are stored within your camera's non-volatile memory, you can start a Live-stream with a single QR Code at any time.<br>
<br>

## Pre-store Your WiFi Credentials 

Your Network Name (SSID): <input type="text" id="networkname" value=""> (e.g. HomeWiFi)<br>
Your Network Password: <input type="text" id="networkpass" value=""> (e.g. Pass1234)<br>

<center>
<div id="qrcode1"></div>
<br>
</center>

<b>Scan the code above once for the camera to always know your network login information.</b><br>
<br>

## Pre-store Your RTMP Address for Live 

Enter the full RTMP address here: <input type="text" id="rtmptxt" value=""><br>(e.g. rtmp://<your server url>/live_555...)<br>

For Twitch users:
1. Select your base URL from this [**list of servers**](https://stream.twitch.tv/ingests/).
2. Login to you Twitch account, and get your [**stream key**](https://link.twitch.tv/myChannelSettings) from your channel settings.![Twitch Channel Settings](streamkey.png)
3. Combine the server address, replacing {stream_key} with the primary stream key from channel, copy the combined URL into the above RTMP address.

<center>
<div id="qrcode2"></div>
<br>
</center>

<b>Scan the code above once for the camera to always know the target RTMP address.</b><br>
<br>

## Launch Your Live-Stream 

Select your Resolution:
  <input type="radio" id="rs1" name="rs" value="S"><label for="480p">480p </label>&nbsp;
  <input type="radio" id="rs2" name="rs" value="M" checked><label for="720p">720p </label>&nbsp;
  <input type="radio" id="rs3" name="rs" value="L"><label for="1080p">1080p </label>

Store a high quality copy on camera:
 <input type="checkbox" id="cp" value="t" checked><label for="cp">1080p60 Copy</label><br>

<center>
<div id="qrcode3"></div>
<br>
</center>
QR Command: <b id="qrtext">time</b><br>

<b>Print or save this code to live-stream at any time.</b>

**Compatibility:** Labs enabled HERO8, HERO9 and HERO10
        
## ver 1.04
[Learn more](..) on QR Control

<script>
var once = true;
var qrcode1;
var qrcode2;
var qrcode3;
var cmd1 = "";
var cmd2 = "";
var cmd3 = "";

function makeQR() 
{	
  if(once === true)
  {
    qrcode1 = new QRCode(document.getElementById("qrcode1"), 
    {
      text : "\"Add your Network Info\"",
      width : 360,
      height : 360,
      correctLevel : QRCode.CorrectLevel.M
    });
	
	qrcode2 = new QRCode(document.getElementById("qrcode2"), 
    {
      text : "\"Add your RTMP URL\"",
      width : 360,
      height : 360,
      correctLevel : QRCode.CorrectLevel.M
    });
	
    qrcode3 = new QRCode(document.getElementById("qrcode3"), 
    {
      text : "\"Launch your LS\"",
      width : 360,
      height : 360,
      correctLevel : QRCode.CorrectLevel.M
    });
    once = false;
  }
}

function dcmd(cmd, id) {

	if(document.getElementById(id) != null)
	{
		var x = document.getElementById(id).checked;
		if( x == true)
			cmd = cmd + document.getElementById(id).value;
	}
	else
	{
		for (i = 1; i < 15; i++) { 
			var newid = id+i;
			if(document.getElementById(newid) != null)
			{
				var x = document.getElementById(newid).checked;
				if( x == true)
					cmd = cmd + document.getElementById(newid).value;
			}
		}
	}
	return cmd;
}

function timeLoop()
{
  if(document.getElementById("networkname") !== null && document.getElementById("networkname").value.length > 0)
  {
    cmd1 = "!MJOIN=\"" + document.getElementById("networkname").value + ":" + document.getElementById("networkpass").value + "\"";
  }
  else
  {
    cmd1 = "\"Add your Network Info\"";
  }

  qrcode1.clear(); 
  qrcode1.makeCode(cmd1);



  if(document.getElementById("rtmptxt") !== null && document.getElementById("rtmptxt").value.length > 0)
  {
    cmd2 = "!MRTMP=\"" + document.getElementById("rtmptxt").value + "\"";
  }
  else
  {
    cmd2 = "\"Add your RTMP URL\"";
  }

  qrcode2.clear(); 
  qrcode2.makeCode(cmd2);
  
  
  
  cmd3 = "oW1mVr1080p60!W!G";
  cmd3 = dcmd(cmd3, "rs");
  if(document.getElementById("cp") != null)
  {
    if(document.getElementById("cp").checked == true)
    {
      cmd3 = cmd3 + "C";
    }
  }
  
  qrcode3.clear(); 
  qrcode3.makeCode(cmd3);
		
  document.getElementById("qrtext").innerHTML = cmd3;
  var t = setTimeout(timeLoop, 50);
}

function myReloadFunction() {
  location.reload();
}

makeQR();
timeLoop();

</script>
