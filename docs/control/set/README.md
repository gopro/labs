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

# QR Control Quick Command
      
<div id="qrcode"></div>
	  
QR Command: <b id="qrtext"></b><br>
	  
## version 1.00

<script>
       
var once = true;
var qrcode;
var cmd = "\Hello \World"; 
let urlParams = new URLSearchParams(document.location.search);
cmd = urlParams.get('cmd')

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

function myReloadFunction() {
  location.reload();
}

makeQR();

</script>

