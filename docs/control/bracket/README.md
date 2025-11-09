<script src="../../jquery.min.js"></script>
<script src="../../qrcodeborder.js"></script>
<script src="../../html2canvas.min.js"></script>
<style>
        #qrcode{
            width: 100%;
        }
</style>


# Photo Bracketing 

## Configure Your GoPro to Bracket Photos Easily 

<b>First QR Code</b> is a GoPro Labs macro that will taking up to 9 exposures, with your control.<br> 

Select your desired exposures:<br>
&nbsp;&nbsp;&nbsp;<input type="checkbox" id="ev4"  name="ev4" >ev +4<br> 
&nbsp;&nbsp;&nbsp;<input type="checkbox" id="ev3"  name="ev3" >ev +3<br> 
&nbsp;&nbsp;&nbsp;<input type="checkbox" id="ev2"  name="ev2" checked>ev +2<br> 
&nbsp;&nbsp;&nbsp;<input type="checkbox" id="ev1"  name="ev1" >ev +1<br> 
&nbsp;&nbsp;&nbsp;<input type="checkbox" id="ev0"  name="ev0" checked>ev 0<br> 
&nbsp;&nbsp;&nbsp;<input type="checkbox" id="ev-1" name="ev-1">ev -1<br> 
&nbsp;&nbsp;&nbsp;<input type="checkbox" id="ev-2" name="ev-2" checked>ev -2<br> 
&nbsp;&nbsp;&nbsp;<input type="checkbox" id="ev-3" name="ev-3">ev -3<br> 
&nbsp;&nbsp;&nbsp;<input type="checkbox" id="ev-4" name="ev-4">ev -4<br> 
 
The script will optionally name the files <b>B</b>ab<b>_GS01</b>xzwy.<b>JPG</b> 
(<input type="checkbox" id="lname" name="lname" checked>Enable Name Change), 
to help you find the exposure groups on the SD card, 
however the renamed files will not show in camera playback or in Quik.<br>

<div id="qrcode_txt" style="width: 540px">
  <center>
  <div id="qrcode" style="width: 540px"></div><br>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext"></em><br>
  <b><font color="#005CAC">BRKT Macro v1.0<em id="status"></em></font></b>
  </center>
</div>
<br>
<br>
<b>Second QR Code</b> makes a preset called "BRKT" from the above macro.<br>

<div id="qrcode_txt2" style="width: 540px">
  <center>
  <div id="qrcode2" style="width: 540px"></div><br>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext2"></em><br>
  <b><font color="#005CAC">BRKT Preset<em id="status"></em></font></b>
  </center>
</div>
<br>

## On camera Setup (MAX2 users)

Go to the Menu -> Preferences -> General, scroll down to 360 Photo Format, and select .JPG (rather than .36P).  

## Using BRKT Preset

After scanning the above two QR Codes, to run BRKT mode, select the new BRKT preset from the photo menu. 
The camera will say "Labs processing", as it waiting for a shutter press to run the bracketed exposures. 
 Shutter press via any compatible BLE remote, or the physical button (it will not work via Quik.) The camera should be stationary. <br>
WARNING: While the BRKT preset is selected, the camera will remain on, no auto shutdown. 
You can manual power off, or go to any other preset for returned normal camera functionality.

<script>

let cmd = String.raw`*BRKT="!Z1=Ct:ScFi1x0=Bz!N==zB!R17$BASE='B$C_'$GAMA=2.2x2!S!Nx0!S!Nx-2!S!N=C+1!R14"`;
let cmd2 = String.raw`*BRKt="!Z0$GAMA=0$BASE=''"mPN$PRES="16,BRKT"`;
let once = true;

function makeQR() 
{
  if(once === true)
  {
    qrcode = new QRCode(document.getElementById("qrcode"), 
    {
      text : cmd,
      width : 540,
      height : 540,
      correctLevel : QRCode.CorrectLevel.M
    });
	
	document.getElementById("qrtext").textContent  = cmd;
	
    qrcode2 = new QRCode(document.getElementById("qrcode2"), 
    {
      text : cmd2,
      width : 540,
      height : 540,
      correctLevel : QRCode.CorrectLevel.M
    });
	
	document.getElementById("qrtext2").textContent  = cmd2;
	
    once = false;
  }
}


async function updateQRs()
{
	cmd = String.raw`*BRKT="!Z1=Ct:ScFi1x0=Bz!N==zB!R17`;
	
	if(document.getElementById("lname").checked === true)
		cmd = cmd + String.raw`$BASE='B$C_'`;
	if(document.getElementById("ev4").checked === true)
		cmd = cmd + "x4!S!N";
	if(document.getElementById("ev3").checked === true)
		cmd = cmd + "x2!S!N";
	if(document.getElementById("ev2").checked === true)
		cmd = cmd + "x2!S!N";
	if(document.getElementById("ev1").checked === true)
		cmd = cmd + "x1!S!N";
	if(document.getElementById("ev0").checked === true)
		cmd = cmd + "x0!S!N";
	if(document.getElementById("ev-1").checked === true)
		cmd = cmd + "x-1!S!N";
	if(document.getElementById("ev-2").checked === true)
		cmd = cmd + "x-2!S!N";
	if(document.getElementById("ev-3").checked === true)
		cmd = cmd + "x-3!S!N";
	if(document.getElementById("ev-4").checked === true)
		cmd = cmd + "x-4!S!N";
	cmd = cmd + "=C+1!R14";
	cmd = cmd + String.raw`"`;
	
	document.getElementById("qrtext").textContent = cmd;
	
	qrcode.clear(); 
	qrcode.makeCode(cmd);
}


makeQR();

document.addEventListener("DOMContentLoaded", function() {
  // Select all checkbox elements
  const checkboxes = document.querySelectorAll('input[type="checkbox"]');
  
  // Add change event listener to each checkbox
  checkboxes.forEach(function(checkbox) {
	checkbox.addEventListener('change', function() {
	  // Reload the page when any checkbox changes
	  updateQRs();
	});
  });
});


</script>
