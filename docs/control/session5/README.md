# QR Control Customizer (H5S)

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

Create a custom camera mode, and even start a capture all through QR Codes. This is the fastest way to access many of the new GoPro Labs' firmware features.

<b>Camera Mode:</b>&nbsp;&nbsp;<input type="radio" id="m5" name="mode" value="" checked> <label for="m5">not set</label><br>
  <input type="radio" id="m1" name="mode" value="mV"> <label  for="m1">Video</label>&nbsp;&nbsp;
  <input type="radio" id="m2" name="mode" value="mP"> <label  for="m2">Photo</label>&nbsp;&nbsp;
  <input type="radio" id="m3" name="mode" value="mT"> <label  for="m3">Timelapse Video</label>&nbsp;&nbsp;
  <input type="radio" id="m4" name="mode" value="mTP"> <label for="m4">Timelapse Photo</label><br>

<div id="settingsRES">
<b>Video Resolution:</b>&nbsp;&nbsp;<input type="radio" id="r8" name="res" value="" checked> <label for="r8">not set</label><br>
  <input type="radio" id="r1" name="res" value="r720" > <label for="r1">720p </label>&nbsp;&nbsp;
  <input type="radio" id="r2" name="res" value="r960" > <label for="r2">960p </label>&nbsp;&nbsp;
  <input type="radio" id="r3" name="res" value="r1080"> <label for="r3">1080p </label>&nbsp;&nbsp;
  <input type="radio" id="r4" name="res" value="r1440"> <label for="r4">1440p </label>&nbsp;&nbsp;
  <input type="radio" id="r5" name="res" value="r27"  > <label for="r5">2.7k  </label>&nbsp;&nbsp;
  <input type="radio" id="r6" name="res" value="r27T" > <label for="r6">2.7k 4x3 </label>&nbsp;&nbsp;
  <input type="radio" id="r7" name="res" value="r4"   > <label for="r7">4k </label><br><br>
</div>

<div id="settingsFPS">
<b>FPS Video:</b>&nbsp;&nbsp;<input type="radio" id="p10" name="fps" value="" checked> <label for="p10">not set</label><br>
  <input type="radio" id="p1" name="fps" value="p24">  <label for="p1">24 </label>&nbsp;&nbsp;
  <input type="radio" id="p2" name="fps" value="p25">  <label for="p2">25 </label>&nbsp;&nbsp;
  <input type="radio" id="p3" name="fps" value="p30">  <label for="p3">30 </label>&nbsp;&nbsp;
  <input type="radio" id="p4" name="fps" value="p48">  <label for="p4">48 </label>&nbsp;&nbsp;
  <input type="radio" id="p5" name="fps" value="p50">  <label for="p5">50 </label>&nbsp;&nbsp;
  <input type="radio" id="p6" name="fps" value="p60">  <label for="p6">60 </label>&nbsp;&nbsp;
  <input type="radio" id="p7" name="fps" value="p90">  <label for="p7">90 </label>&nbsp;&nbsp;
  <input type="radio" id="p8" name="fps" value="p100"> <label for="p8">100 </label>&nbsp;&nbsp;
  <input type="radio" id="p9" name="fps" value="p120"> <label for="p9">120 </label><br><br>
</div>

<div id="settingsFOV">
<b>Lens:</b>
  <input type="radio" id="f1" name="fov" value="fW"> <label for="f1">Wide </label>&nbsp;&nbsp;
  <input type="radio" id="f2" name="fov" value="fM"> <label for="f2">Medium </label>&nbsp;&nbsp;
  <input type="radio" id="f3" name="fov" value="fN"> <label for="f3">Narrow </label>&nbsp;&nbsp;
  <input type="radio" id="f4" name="fov" value="fL"> <label for="f4">Linear </label>&nbsp;&nbsp;
  <input type="radio" id="f5" name="fov" value="fS"> <label for="f5">Superview </label>&nbsp;&nbsp;
  <input type="radio" id="f6" name="fov" value="" checked> <label for="f6">not set</label><br><br>
 </div>
 
 
<div id="settingsTLVFOV">
<b>Lens:</b>
  <input type="radio" id="tlvf1" name="tlvfov" value="fW"> <label for="tlvf1">Wide </label>&nbsp;&nbsp;
  <input type="radio" id="tlvf2" name="tlvfov" value="fL"> <label for="tlvf2">Linear </label>&nbsp;&nbsp;
  <input type="radio" id="tlvf3" name="tlvfov" value="" checked> <label for="tlvf3">not set</label><br><br>
 </div>
 
<div id="settingsTimelapse">
<b>Timelapse Interval:</b>&nbsp;&nbsp;
  <input type="radio" id="fpslapse1"    name="fpslapse" value="p2"> <label for="fpslapse1">0.5s </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse2"    name="fpslapse" value="p1"> <label for="fpslapse2">1s </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse3"   name="fpslapse" value="p.2"> <label for="fpslapse3">2s </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse4"   name="fpslapse" value="p.5"> <label for="fpslapse4">5s </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse5"  name="fpslapse" value="p.10"> <label for="fpslapse5">10s </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse6"  name="fpslapse" value="p.30"> <label for="fpslapse6">30s </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse7" name="fpslapse" value="p.60"> <label for="fpslapse7">60s </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse8" name="fpslapse" value="" checked> <label for="fpslapse8">not set</label><br><br>
</div>

<div id="settingsRESTLV">
<b>TLV/Warp Resolution:</b>&nbsp;&nbsp;
  <input type="radio" id="rt1" name="restlv" value="r1080"> <label for="rt1">1080p </label>&nbsp;&nbsp;
  <input type="radio" id="rt2" name="restlv" value="r1440"> <label for="rt2">1440p </label>&nbsp;&nbsp;
  <input type="radio" id="rt3" name="restlv" value="r27T" > <label for="rt3">2.7k 4x3 </label>&nbsp;&nbsp;
  <input type="radio" id="rt4" name="restlv" value="r4"   > <label for="rt4">4k </label>&nbsp;&nbsp;
  <input type="radio" id="rt5" name="restlv" value="" checked> <label for="rt5">not set</label><br><br>
 </div>
 
<div id="settingsVideo">
<b>Stabilization:</b>&nbsp;&nbsp;
	<input type="radio" id="eis1" name="eis" value="e0"> <label for="eis1">Off</label>&nbsp;&nbsp;&nbsp;
	<input type="radio" id="eis2" name="eis" value="e1"> <label for="eis2">On</label>&nbsp;&nbsp;&nbsp;
	<input type="radio" id="eis3" name="eis" value="" checked> <label for="eis3">not set</label><br><br>
</div>

<div id="settingsPT">
<input type="checkbox" id="pt" value="t"> <label for="pt">Protune Controls</label><br>
</div>
<div id="ptCOLOR">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Protune Color:</b>&nbsp;&nbsp;
  <input type="radio" id="ptc1" name="ptc" value="cG"> <label for="ptc1">GoPro</label>&nbsp;&nbsp;
  <input type="radio" id="ptc2" name="ptc" value="cF"> <label for="ptc2">Flat</label>&nbsp;&nbsp;
  <input type="radio" id="ptc3" name="ptc" value="" checked> <label for="ptc3">not set</label>
</div>
<div id="ptWBAL">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>White Balance:</b>&nbsp;&nbsp;
  <input type="radio" id="wb1" name="wb" value="wA" checked> <label for="wb1">Auto </label>&nbsp;&nbsp;
  <input type="radio" id="wb2" name="wb" value="w30" > <label for="wb2">3000K </label>&nbsp;&nbsp;
  <input type="radio" id="wb3" name="wb" value="w48" > <label for="wb3">4800K </label>&nbsp;&nbsp;
  <input type="radio" id="wb4" name="wb" value="w55" > <label for="wb4">5500K </label>&nbsp;&nbsp;
  <input type="radio" id="wb5" name="wb" value="w65"> <label for="wb5">6500K </label>&nbsp;&nbsp;
  <input type="radio" id="wb6" name="wb" value="wN" > <label for="wb6">Native </label>&nbsp;&nbsp;
  <input type="radio" id="wb7" name="wb" value="" checked> <label for="wb7">not set</label>
 </div>
<div id="ptISO">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>ISO Limit:</b>&nbsp;&nbsp;
  <input type="radio" id="iso1" name="iso" value="i1" > <label for="iso1">100 </label>&nbsp;&nbsp;
  <input type="radio" id="iso2" name="iso" value="i2" > <label for="iso2">200 </label>&nbsp;&nbsp;
  <input type="radio" id="iso3" name="iso" value="i4" > <label for="iso3">400 </label>&nbsp;&nbsp;
  <input type="radio" id="iso4" name="iso" value="i8" > <label for="iso4">800 </label>&nbsp;&nbsp;
  <input type="radio" id="iso5" name="iso" value="i16"> <label for="iso5">1600 (def) </label>&nbsp;&nbsp;
  <input type="radio" id="iso6" name="iso" value="i32"> <label for="iso6">3200 </label>&nbsp;&nbsp;
  <input type="radio" id="iso7" name="iso" value="i64"> <label for="iso7">6400 </label>&nbsp;&nbsp;
  <input type="radio" id="iso8" name="iso" value="i16" checked> <label for="iso8">not set</label>
 </div>
<div id="ptSHUT">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Lock Shutter:</b>&nbsp;&nbsp;
  <input type="radio" id="shut1" name="shut" value="S360"> <label for="shut1">360&deg; </label>&nbsp;&nbsp;
  <input type="radio" id="shut2" name="shut" value="S180"> <label for="shut2">180&deg; </label>&nbsp;&nbsp;
  <input type="radio" id="shut3" name="shut" value="S90" > <label for="shut3">90&deg; </label>&nbsp;&nbsp;
  <input type="radio" id="shut4" name="shut" value="S45" > <label for="shut4">45&deg; </label>&nbsp;&nbsp;
  <input type="radio" id="shut5" name="shut" value="S22" > <label for="shut5">22&deg; </label>&nbsp;&nbsp;
  <input type="radio" id="shut6" name="shut" value="S0"  > <label for="shut6">Auto</label>
  <input type="radio" id="shut7" name="shut" value="" checked> <label for="shut7">not set</label><br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(extended beyond camera menu)
  <input type="radio" id="shut8" name="shut" value="S10" > <label for="shut8">10&deg; </label>&nbsp;&nbsp;
  <input type="radio" id="shut9" name="shut" value="S5" > <label for="shut9">5&deg; </label>&nbsp;&nbsp;
  <input type="radio" id="shut10" name="shut" value="S2" > <label for="shut10">2&deg; </label>&nbsp;&nbsp;
</div>
<div id="ptEV">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>EV Compensation:</b>&nbsp;&nbsp;
  <input type="radio" id="ev1" name="ev" value="x-2"  > <label for="ev1">-2 </label>&nbsp;&nbsp;
  <input type="radio" id="ev2" name="ev" value="x-1.5"> <label for="ev2">-1.5 </label>&nbsp;&nbsp;
  <input type="radio" id="ev3" name="ev" value="x-1"  > <label for="ev3">-1 </label>&nbsp;&nbsp;
  <input type="radio" id="ev4" name="ev" value="x-.5" > <label for="ev4">-0.5 </label>&nbsp;&nbsp;
  <input type="radio" id="ev5" name="ev" value="x0"   > <label for="ev5">0 </label>&nbsp;&nbsp;
  <input type="radio" id="ev6" name="ev" value="x.5"  > <label for="ev6">+0.5 </label>&nbsp;&nbsp;
  <input type="radio" id="ev7" name="ev" value="x1"   > <label for="ev7">+1 </label>&nbsp;&nbsp;
  <input type="radio" id="ev8" name="ev" value="x1.5" > <label for="ev8">+1.5 </label>&nbsp;&nbsp;
  <input type="radio" id="ev9" name="ev" value="x2"   > <label for="ev9">+2</label>
  <input type="radio" id="ev10" name="ev" value="" checked> <label for="ev10">not set</label>
</div>
<div id="ptSHARP">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Sharpness:</b>&nbsp;&nbsp;
  <input type="radio" id="sharp1" name="sharp" value="sL"> <label for="sharp1">Low </label>&nbsp;&nbsp;
  <input type="radio" id="sharp2" name="sharp" value="sM"> <label for="sharp2">Medium </label>&nbsp;&nbsp;
  <input type="radio" id="sharp3" name="sharp" value="sH"> <label for="sharp3">High</label>&nbsp;&nbsp;
  <input type="radio" id="sharp4" name="sharp" value="" checked> <label for="sharp4">not set</label>
</div>

<div id="cameraOptions">
<input type="checkbox" id="options" value=""> <label for="options">Camera Preferences</label><br>
</div>

<div id="opVC">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Voice Control:</b>&nbsp;&nbsp; 
  <input type="radio" id="vc1" name="vc" value="v0"> <label for="vc1">off </label>&nbsp;&nbsp;
  <input type="radio" id="vc2" name="vc" value="v1"> <label for="vc2">on </label>&nbsp;&nbsp;
  <input type="radio" id="vc3" name="vc" value="" checked> <label for="vc3">not set</label>
 </div>
<div id="opBV">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Beep Volume:</b>&nbsp;&nbsp; 
  <input type="radio" id="bv1" name="bv" value="V0"> <label for="bv1">0% </label>&nbsp;&nbsp;
  <input type="radio" id="bv2" name="bv" value="V1"> <label for="bv2">10% </label>&nbsp;&nbsp;
  <input type="radio" id="bv3" name="bv" value="V4"> <label for="bv3">40% </label>&nbsp;&nbsp;
  <input type="radio" id="bv4" name="bv" value="V7"> <label for="bv4">70% </label>&nbsp;&nbsp;
  <input type="radio" id="bv5" name="bv" value="V9"> <label for="bv5">100% </label>&nbsp;&nbsp;
  <input type="radio" id="bv6" name="bv" value="" checked> <label for="bv6">not set</label>
  </div>
  
<div id="opLO">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>LEDs On:</b>&nbsp;&nbsp;
  <input type="radio" id="lo1" name="lo" value="D0"> <label for="lo1">All Off </label>&nbsp;&nbsp;
  <input type="radio" id="lo2" name="lo" value="D2"> <label for="lo2">Rear Only </label>&nbsp;&nbsp;
  <input type="radio" id="lo3" name="lo" value="D4"> <label for="lo3">All On </label>&nbsp;&nbsp;
  <input type="radio" id="lo4" name="lo" value="" checked> <label for="lo4">not set</label>
  </div>
<div id="opWC">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>WiFi Connections:</b>&nbsp;&nbsp; 
  <input type="radio" id="wc1" name="wc" value="W0"> <label for="wc1">Off </label>&nbsp;&nbsp;
  <input type="radio" id="wc2" name="wc" value="W1"> <label for="wc2">On </label>&nbsp;&nbsp;
  <input type="radio" id="wc3" name="wc" value="" checked> <label for="wc3">not set</label>
  </div>
<!--
<div id="opLN">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Language:</b>&nbsp;&nbsp;
  <input type="radio" id="ln1" name="ln" value="L0"> <label for="ln1">English US </label>&nbsp;&nbsp;
  <input type="radio" id="ln2" name="ln" value="L01"> <label for="ln2">English UK </label>&nbsp;&nbsp;
  <input type="radio" id="ln3" name="ln" value="L02"> <label for="ln3">English AUS </label>&nbsp;&nbsp;
  <input type="radio" id="ln4" name="ln" value="L4"> <label for="ln4">Spanish EU </label>&nbsp;&nbsp;
  <input type="radio" id="ln5" name="ln" value="L41"> <label for="ln5">Spanish NA </label>&nbsp;&nbsp;
  <input type="radio" id="ln6" name="ln" value="L2"> <label for="ln6">German </label>&nbsp;&nbsp;<br>
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="ln7" name="ln" value="L3"> <label for="ln7">Italian </label>&nbsp;&nbsp;
  <input type="radio" id="ln8" name="ln" value="L1"> <label for="ln8">Chinese </label>&nbsp;&nbsp;
  <input type="radio" id="ln9" name="ln" value="L5"> <label for="ln9">Japanese </label>&nbsp;&nbsp;
  <input type="radio" id="ln10" name="ln" value="L7"> <label for="ln10">Korean </label>&nbsp;&nbsp;
  <input type="radio" id="ln11" name="ln" value="L6"> <label for="ln11">French </label>&nbsp;&nbsp;
  <input type="radio" id="ln12" name="ln" value="L8"> <label for="ln12">Portuguese </label>&nbsp;&nbsp;
  <input type="radio" id="ln13" name="ln" value="L9"> <label for="ln13">Russian </label>&nbsp;&nbsp;
  <input type="radio" id="ln14" name="ln" value="" checked> <label for="ln14">not set</label><br>
</div>
-->


<div id="opDT">
<input type="checkbox" id="dt" value="oT"> <label for="dt">Set date + time automatically</label><br>
</div>

<div id="opDTS">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" id="dttimecode" value=""> <label for="dttimecode">add 1/100th of a second</label><br>
</div>

<div id="cameraActions">
<input type="checkbox" id="actions" value=""> <label for="actions">Delayed Actions</label><br>
</div>

<div id="aSD">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Shutdown and capture in:</b>
<input type="text" id="starthrs" value="" style="width:45px">hours <input type="text" id="startmins" value="" style="width:45px">mins <input type="text" id="startsecs" value="" style="width:45px">secs <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>or</b> at camera time: <input type="text" id="time" value="" style="width:60px"> (format 24hr HH:MM)<br>
</div>
<div id="aS">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Start Capture:</b>
  <input type="radio" id="as1" name="as" value="!S"> <label for="as1">Now </label>&nbsp;&nbsp;
  <input type="radio" id="as2" name="as" value="!1S"> <label for="as2">in 1 sec </label>&nbsp;&nbsp;
  <input type="radio" id="as3" name="as" value="!3S"> <label for="as3">in 3 secs </label>&nbsp;&nbsp;
  <input type="radio" id="as4" name="as" value="!30S"> <label for="as4">in 30 secs </label>&nbsp;&nbsp;
  <input type="radio" id="as5" name="as" value="" checked> <label for="as5">not set</label>
  </div>
<div id="aE">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>End Capture:</b>
  <input type="radio" id="ae1" name="ae" value="!5E"> <label for="ae1">End after 5 secs </label>&nbsp;&nbsp;
  <input type="radio" id="ae2" name="ae" value="!10E"> <label for="ae2">End after 10 secs </label>&nbsp;&nbsp;
  <input type="radio" id="ae3" name="ae" value="!60E"> <label for="ae3">End after 1 min </label>&nbsp;&nbsp;
  <input type="radio" id="ae4" name="ae" value="!600E"> <label for="ae4">End after 10 min  </label>&nbsp;&nbsp;
  <input type="radio" id="ae5" name="ae" value="" checked> <label for="ae5">not set</label>
</div>
<div id="aEND">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>End capture after:</b> 
<input type="text" id="endhrs" value="" style="width:45px">hours <input type="text" id="endmins" value="" style="width:45px">mins <input type="text" id="endsecs" value="" style="width:45px">secs <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>or</b> at camera time: <input type="text" id="endtime" value="" style="width:60px"> (format 24hr HH:MM)<br><br>
</div>
<div id="aR">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" id="repeat" value=""> <b><label for="actions">Repeat Command</label></b><br></div>

Additional Commands: <input type="text" id="addcmd" value="">

<div id="qrcode"></div>

GoPro QR Command: <b id="txt"></b>

Share this QR Code as a URL: <b id="urltext"></b> 

<button onclick="myReloadFunction()">Reset page</button>

[Learn more](..) on QR Control

## This Page as a Mobile App

[![google play](../google-play-823.png)](https://play.google.com/store/apps/details?id=com.miscdata.qrcontrol)
[![apple app store](../apple-store-823.png)](https://apps.apple.com/us/app/gopro-app/id1518134202)

Compatibility: Labs enabled HERO5 Session
        
## ver 1.30
[Learn more](..) on QR Control

<script>
var lastcmd = "";
var lasttimecmd = "xxxxxxxxx";
var changed = false;
var ms = 0;
var lastms = 0;
var timechecked = false;
var once = true;
var even = 0;
var qrcode;
var i;

function makeQR() {	
	if(once === true)
	{
		qrcode = new QRCode(document.getElementById("qrcode"), 
		{
			text : "QR Control\nReady",
			width : 400,
			height : 400,
			correctLevel : QRCode.CorrectLevel.M
		});
	}
	once = false;
}

function startTime() {	
    var today;
    var yy;
    var mm;
    var dd;
    var h;
    var m;
    var s;
	var timecodefps = 30;
	var cmd = "";
	var timenotchecked;
		
	dset("settingsRES", false);
	dset("settingsFPS", false);
	dset("settingsFOV", false);
	dset("settingsTLVFOV", false);
	dset("settingsRESTLV", false);
	dset("settingsVideo", false);
	dset("settingsPT", false);
	dset("settingsTimelapse", false);
	
	dset("ptCOLOR", false);
	dset("ptWBAL", false);
	dset("ptISO",false);
	dset("ptSHUT",false);
	dset("ptEV",false);
	dset("ptSHARP",false);
		
	dset("opVC", false);
	dset("opBV", false);
	dset("opLO", false);
	dset("opWC", false);
	//dset("opLN", false);
	
	dset("aS", false);
	dset("aE", false);
	dset("aSD", false);
	dset("aEND", false);
	dset("aR", false);
	
	var checkedmode = 0;
	var x;
	
	for (i = 1; i < 5; i++) { 
		var mode = "m"+i;
		x = document.getElementById(mode).checked;
		if( x === true)
			checkedmode = i;
	}
	
	switch(checkedmode)
	{
		default:
		case 1: //Video		
		dset("settingsRES", true);
		dset("settingsFPS", true);
		dset("settingsFOV", true);
		dset("settingsVideo", true);
		dset("settingsPT", true);
		break;
			
		case 2: //Photo
		dset("settingsPT", true);
		dset("settingsTLVFOV", true);
		break;
		
		case 3: //Timelapse Video
		dset("settingsTimelapse", true);	
		dset("settingsRESTLV", true);
		dset("settingsTLVFOV", true);
		dset("settingsPT", true);
		break;
				
		case 4: //TLP
		dset("settingsTimelapse", true);	
		dset("settingsPT", true);
		dset("settingsTLVFOV", true);
		break;
	}
		
	if(document.getElementById("pt") !== null)
	{
		if(document.getElementById("pt").checked === true)
		{
			dset("ptCOLOR", true);
			dset("ptWBAL", true);
			dset("ptISO",true);

			if(document.getElementById('iso8').checked === true)
			{
				dset("ptSHUT",false);
				dset("ptEV",true);
			}
			else
			{
				dset("ptSHUT",true);

				if(document.getElementById('shut7').checked === true || document.getElementById('shut6').checked === true) 
				{  // not shutter lock
					dset("ptEV",true);
				}
			}
				
			dset("ptSHARP",true);
		}
	}
	
	if(document.getElementById("options") !== null)
	{
		if(document.getElementById("options").checked === true)
		{			
			dset("opVC", true);
			dset("opBV", true);
			dset("opLO", true);
			dset("opWC", true);
			//dset("opLN", true);
		}
	}
	
	if(document.getElementById("actions") !== null)
	{
		if(document.getElementById("actions").checked === true)
		{
			dset("aSD", true);
			dset("aEND", true);
			dset("aR", true);
		}
	}
	
	
	cmd = dcmd(cmd,"m");  // set mode
	
	switch(checkedmode)
	{
		case 3: //TLV
		case 4: //TLP
			cmd = dcmd(cmd,"fpslapse");
			break;
	}
	
	if(checkedmode == 3) // TLV
		cmd = dcmd(cmd, "rt");
	else
		cmd = dcmd(cmd,"r"); //RES
		
	cmd = dcmd(cmd,"p"); //fps
	
	if(checkedmode > 1) // not video		
		cmd = dcmd(cmd,"tlvf"); //fov
	else
		cmd = dcmd(cmd,"f"); //fov
	
	cmd = dcmd(cmd,"pt"); //protune
	cmd = dcmd(cmd,"eis"); //eis
	
	if(document.getElementById("p1") !== null)
	{
		x = document.getElementById("p1").checked;
		if( x === true)
			timecodefps = 24;
	}
	if(document.getElementById("p2") !== null)
	{
		x = document.getElementById("p2").checked;
		if( x === true)
			timecodefps = 30;
	}
	if(document.getElementById("p3") !== null)
	{
		x = document.getElementById("p3").checked;
		if( x === true)
			timecodefps = 60;
	}
	if(document.getElementById("p6") !== null)
	{
		x = document.getElementById("p6").checked;
		if( x === true)
			timecodefps = 25;
	}
	if(document.getElementById("p7") !== null)
	{
		x = document.getElementById("p7").checked;
		if( x === true)
			timecodefps = 50;
	}
		
	if(document.getElementById("pt") !== null)
	{
		if(document.getElementById("pt").checked === true)
		{
			cmd = dcmd(cmd,"ptc"); //color
			cmd = dcmd(cmd,"wb"); //wb

			if(document.getElementById('iso8').checked === false)
			{
				cmd = dcmd(cmd,"iso"); //iso
				
				if(document.getElementById('shut7').checked === false)
					cmd = dcmd(cmd,"shut"); //shutter angle
				else
					cmd = cmd + "M1";//
			}
				
			cmd = dcmd(cmd,"ev"); //ev
			cmd = dcmd(cmd,"sharp"); //sharp
		}
	}
	
	
	if(document.getElementById("options") !== null)
	{
		if(document.getElementById("options").checked === true)
		{
			var opt = ""; 
			var addO = "o";
			cmd = dcmd(cmd,"vc");
			
			opt = dcmd(addO, "bv"); if(opt != "o") { cmd = cmd + opt; addO = ""; }
			opt = dcmd(addO, "lo"); if(opt != "o") { cmd = cmd + opt; addO = ""; }
			opt = dcmd(addO, "wc"); if(opt != "o") { cmd = cmd + opt; addO = ""; }
			//opt = dcmd(addO, "ln"); if(opt != "o") { cmd = cmd + opt; addO = ""; }
		}
	}
	
	
	if(document.getElementById("actions") !== null)
	{
		if(document.getElementById("actions").checked === true)
		{			
			
		}
		else
		{
			dset("opDT", true);
		}
	}
	
	var dt = document.getElementById("dt").checked;
	
	today = new Date();
	
	if(cmd != lastcmd)
	{
		ms = today.getTime();
		changed = true;
		lastcmd = cmd;
	}
	
	if(dt === true)
	{
		dset("opDTS", true);
	
		var frms;
		var secs = true;//document.getElementById("dtsec").checked;
		var timecode = document.getElementById("dttimecode").checked;
		
		yy = today.getFullYear() - 2000;
		mm = today.getMonth() + 1;
		dd = today.getDate();
		h = today.getHours();
		m = today.getMinutes();
		s = today.getSeconds();
		ms = today.getMilliseconds();
		
		
		frms = (h * 3600 + m * 60 + s) * timecodefps + Math.floor((timecodefps * ms) / 1000);
		
		yy = checkTime(yy);
		mm = checkTime(mm);
		dd = checkTime(dd);
		h = checkTime(h);
		m = checkTime(m);
		s = checkTime(s);
		ms = Math.floor(ms / 10); // hundredths
		ms = checkTime(ms);
	
		//var curr = today.getTime();
		
		cmd = cmd + "oT" + yy + mm + dd + h + m;
		if(secs || timecode)
		{
			cmd = cmd + s;
			if(timecode)
			{			
				cmd = cmd + "." + ms;
			}
		}
	
		timechecked = true; 
	}
	else
	{
		dset("opDTS", false);
		if(timechecked === true)
		{
			ms = today.getTime();
			changed = true;
		}
		timenotchecked = false; 
	}
	
	
	var actions = document.getElementById("actions").checked;
 	if(actions === true)
	{
		var S_added = 0;
		var SM_added = 0;
		var SK_added = 0;
		if(document.getElementById("starthrs") !== null && document.getElementById("startmins") !== null && document.getElementById("time") !== null)
		{
			var newcmd = "";
			var secs = 0;
			var starttime = document.getElementById("time").value;
			secs = Number(3600 * document.getElementById("starthrs").value) + Number(60 * document.getElementById("startmins").value) + Number(document.getElementById("startsecs").value);
			if(secs > 0)
			{
				if(secs < 20)
				{
					newcmd = cmd + "!" + secs + "S";
					cmd = newcmd;
					S_added = 1;
				}
				else
				{
					newcmd = "!" + secs + "N" + cmd + "!S";
					cmd = newcmd;
					S_added = 1;
				}
			}
			else if(starttime.length == 5)
			{
				newcmd = "!" + starttime + "N" + cmd + "!S";
				cmd = newcmd;
				S_added = 1;
			}
		}
		
		
		if(document.getElementById("endhrs") !== null && document.getElementById("endmins") !== null && document.getElementById("endsecs") !== null && document.getElementById("time") !== null)
		{
			var secs = 0;
			var endtime = document.getElementById("endtime").value;
			secs = Number(60 * 60 * document.getElementById("endhrs").value) + Number(60 * document.getElementById("endmins").value) + Number(document.getElementById("endsecs").value);
			if(secs > 0)
			{
				cmd = cmd + "!" + secs + "E";
			}
			else if(endtime.length == 5)
			{
				cmd = cmd + "!" + endtime + "E";
			}
		}
		
		if(document.getElementById("repeat").checked === true)
		{
			cmd = cmd + "!" + "R";
		}
	}
	
	if(document.getElementById("addcmd") !== null)
	{
		cmd = cmd + document.getElementById("addcmd").value;
	}
	
	
	if(cmd != lasttimecmd)
	{
		changed = true;
	}	
	
	var delay = 200;
	
	if(changed === true)
	{	
		
		if(cmd === "") cmd = "\"QR Control\nReady\"";

		makeQR();
		
		even ++;
		{
			qrcode.clear(); 
			qrcode.makeCode(cmd);
		}
		
		if(cmd != lasttimecmd)
		{
			document.getElementById('txt').innerHTML = cmd;	
			document.getElementById("urltext").innerHTML = "https://gopro.github.io/labs/control/set/?cmd=" + cmd;			
			lasttimecmd = cmd;
		}		
		
		lastms = today.getTime();
		changed = false;
		
		delay = 10;
		//console.log(cmd);
	}
	
	var t = setTimeout(startTime, delay);
}
function checkTime(i) {
    if (i < 10) {i = "0" + i;}  // add zero in front of numbers < 10
    return i;
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


function myReloadFunction() {
    location.reload();
}


makeQR();
startTime();

</script>
