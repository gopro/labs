# GoPro Bones QR Code Creator

<script src="../jquery.min.js"></script>
<script src="../qrcodeborder.js"></script>
<script src="../html2canvas.min.js"></script>
<style>
        #qrcode{
            width: 100%;
        }
        div{
            width: 100%;
            display: inline-block;
        }
</style>

Create a custom camera mode, and even start a capture all through QR Codes. This is the fastest way to access many of the new GoPro Labs' firmware features that are pre-installed on Bones. Many features of this page are also available as a mobile app.<br>
Install from: [![google play](../control/google-play-small.png)](https://play.google.com/store/apps/details?id=com.miscdata.qrcontrol)
[![apple app store](../control/apple-store-small.png)](https://apps.apple.com/us/app/gopro-app/id1518134202)

## Scanning Your Code

<table border="0" cellpadding="0" cellspacing="0" padding="0">
  <tbody border="0" padding="0">
	<tr border="0" padding="0">
	  <td width="30%" border="0" padding="0">
	  
	  <img src="https://0dan0.github.io/qr/bones/scanning.jpg" alt="scanning">

	  </td>
	  <td border="0" padding="0">
	  
	  Whether you scan a QR Code from a laptop screen, a mobile phone, or a piece of paper, the code should be a minimum 1.5"/4cm in size with the camera about 6"/15cm away. The larger the QR Code, the easier it is to scan. Point the camera at the center of the code, hold it still for about a second. With each successful scan the LED will flash twice. The camera will now be in the mode you have selected.
	  
	  </td>
	</tr>
  </tbody>
</table>
	

## Camera Settings

<div id="camMODE">
<b>Mode:</b>
  <input type="radio" id="m1" name="mode"  value="mV" checked> <label for="m1">Video</label>&nbsp;&nbsp;
  <input type="radio" id="m2" name="mode"  value="mV0"> <label for="m2">Standard</label>&nbsp; 
  <input type="radio" id="m3" name="mode"  value="mV1"> <label for="m3">Activity</label><br>&nbsp;&nbsp; &nbsp;&nbsp; 
  <input type="radio" id="m4" name="mode"  value="mV2"> <label for="m4">Cinematic</label>&nbsp;
  <input type="radio" id="m5" name="mode"  value="mV4"> <label for="m5">SloMo</label>&nbsp;&nbsp;     
  <input type="radio" id="m6" name="mode"  value="mV5"> <label for="m6">Basic</label><br>&nbsp;&nbsp; &nbsp;&nbsp; 
  <input type="radio" id="m7" name="mode"  value="mTW"> <label for="m7">TimeWarp</label>&nbsp;
  <input type="radio" id="m8" name="mode"  value="mT">  <label for="m8">Timelapse</label>&nbsp;
  <input type="radio" id="m9" name="mode"  value="mNL"> <label for="m9">Nightlapse</label><br>&nbsp;&nbsp; &nbsp;&nbsp;
  <input type="radio" id="m10" name="mode" value="mP">  <label for="m10">Photo</label>&nbsp;   
  <input type="radio" id="m11" name="mode" value="mPB"> <label for="m11">Burst</label>&nbsp; 
  <input type="radio" id="m12" name="mode" value="mPN"> <label for="m12">Night</label>&nbsp;&nbsp;
  <input type="radio" id="m13" name="mode" value=""> <label for="m13">not set</label>
</div>

<div id="settingsRES">
<b>Resolution:</b>&nbsp;&nbsp;
  <input type="radio" id="r1" name="res" value="r1080"> <label for="r1">1080p</label>&nbsp;
  <input type="radio" id="r2" name="res" value="r27"  > <label for="r2">2.7k</label>&nbsp;
  <input type="radio" id="r3" name="res" value="r4"   > <label for="r3">4k</label>&nbsp;
  <input type="radio" id="r4" name="res" value="r5"   > <label for="r4">5.3k</label><br>&nbsp;&nbsp; &nbsp;&nbsp; 
  <input type="radio" id="r5" name="res" value="r27T" > <label for="r5">2.7k</label><small>4:3</small>&nbsp;
  <input type="radio" id="r6" name="res" value="r4T"  > <label for="r6">4k</label><small>4:3</small>&nbsp;
  <input type="radio" id="r7" name="res" value="r5T"  > <label for="r7">5k</label><small>4:3</small>&nbsp;
  <input type="radio" id="r8" name="res" value="" checked> <label for="r8">not set</label><br>
</div>

<div id="settingsRESTLV">
<b>Resolution:</b>&nbsp;&nbsp;
  <input type="radio" id="rt1" name="restlv" value="r1080"> <label for="rt1">1080p </label>&nbsp;
  <input type="radio" id="rt2" name="restlv" value="r27" >  <label for="rt2">2.7k </label>&nbsp;
  <input type="radio" id="rt3" name="restlv" value="r4"   > <label for="rt3">4k </label><br>&nbsp;&nbsp; &nbsp;&nbsp; 
  <input type="radio" id="rt4" name="restlv" value="r27T" > <label for="rt4">2.7k</label><small>4:3</small>&nbsp;
  <input type="radio" id="rt5" name="restlv" value="r4T"  > <label for="rt5">4k</label><small>4:3</small>&nbsp;
  <input type="radio" id="rt6" name="restlv" value="" checked> <label for="rt6">not set</label><br>
 </div>

<div id="settingsFPS">
<b>Frame Rate:</b>&nbsp;&nbsp;
  <input type="radio" id="p1" name="fps" value="p24">  <label for="p1">24 </label>&nbsp;
  <input type="radio" id="p2" name="fps" value="p25">  <label for="p2">25 </label>&nbsp;
  <input type="radio" id="p3" name="fps" value="p30">  <label for="p3">30 </label>&nbsp;
  <input type="radio" id="p4" name="fps" value="p50">  <label for="p4">50 </label>&nbsp;
  <input type="radio" id="p5" name="fps" value="p60">  <label for="p5">60 </label><br>&nbsp;&nbsp; &nbsp;&nbsp; 
  <input type="radio" id="p6" name="fps" value="p100"> <label for="p6">100 </label>&nbsp;
  <input type="radio" id="p7" name="fps" value="p120"> <label for="p7">120 </label>&nbsp;
  <input type="radio" id="p8" name="fps" value="p200"> <label for="p8">200 </label>&nbsp;
  <input type="radio" id="p9" name="fps" value="p240"> <label for="p9">240 </label>&nbsp;
  <input type="radio" id="p10" name="fps" value="" checked> <label for="p10">not set</label><br>
</div>

<div id="settingsFOV">
<b>Lens FOV:</b>&nbsp;&nbsp;
  <input type="radio" id="f1" name="fov" value="fW"> <label for="f1">Wide </label>&nbsp;
  <input type="radio" id="f2" name="fov" value="fN"> <label for="f2">Narrow </label>&nbsp;
  <input type="radio" id="f3" name="fov" value="fL"> <label for="f3">Linear </label><br>&nbsp;&nbsp; &nbsp;&nbsp; 
  <input type="radio" id="f4" name="fov" value="fS"> <label for="f4">Superview </label>&nbsp;
  <input type="radio" id="f5" name="fov" value="fH"> <label for="f5">Linear+HL </label><br>
  or <b>Max Lens Mod:</b>&nbsp;&nbsp;
  <input type="radio" id="f6" name="fov" value="fM"> <label for="f6">Wide </label>&nbsp;
  <input type="radio" id="f7" name="fov" value="fX"> <label for="f7">Superview </label><br>&nbsp;&nbsp; &nbsp;&nbsp;  
  <input type="radio" id="f8" name="fov" value="fR"> <label for="f8">Linear(1080) </label>&nbsp;
  <input type="checkbox" id="mlmhl" value="L"> <label for="mlmhl">Horizon Lock</label>&nbsp;&nbsp;
  <input type="radio" id="f9" name="fov" value="" checked> <label for="f9">not set</label><br>
 </div>
 
<div id="settingsPFOV">
<b>Lens:</b>&nbsp;&nbsp;
  <input type="radio" id="pf1" name="pfov" value="fW"> <label for="pf1">Wide </label>&nbsp;&nbsp;
  <input type="radio" id="pf2" name="pfov" value="fL"> <label for="pf2">Linear </label>&nbsp;&nbsp;
  <input type="radio" id="pf3" name="pfov" value="fN"> <label for="pf3">Narrow </label><br>  
  or <b>Max Lens Mod:</b>&nbsp;&nbsp; 
  <input type="radio" id="pf4" name="pfov" value="fM"> <label for="pf4">Wide </label>&nbsp;&nbsp;
  <input type="radio" id="pf5" name="pfov" value="fX"> <label for="pf5">Superview </label><br>&nbsp;&nbsp;&nbsp;&nbsp;  
  <input type="checkbox" id="pmlmhl" value="L"> <label for="pmlmhl">Horizon Lock</label>&nbsp;&nbsp;
  <input type="radio" id="pf6" name="pfov" value="" checked> <label for="pf6">not set</label><br>
 </div>
  
 
<div id="settingsTLVFOV">
<b>Lens:</b>
  <input type="radio" id="tlvf1" name="tlvfov" value="fW"> <label for="tlvf1">Wide </label>&nbsp;&nbsp;
  <input type="radio" id="tlvf2" name="tlvfov" value="fL"> <label for="tlvf2">Linear </label>&nbsp;&nbsp;
  <input type="radio" id="tlvf3" name="tlvfov" value="fN"> <label for="tlvf3">Narrow </label>&nbsp;&nbsp;  
  <input type="radio" id="tlvf4" name="tlvfov" value="" checked> <label for="tlvf4">not set</label><br>
 </div>
  
<div id="settingsTWFOV">
<b>Lens:</b>
  <input type="radio" id="twf1" name="twfov" value="fW"> <label for="twf1">Wide </label>&nbsp;
  <input type="radio" id="twf2" name="twfov" value="fL"> <label for="twf2">Linear </label>&nbsp;
  <input type="radio" id="twf3" name="twfov" value="fH"> <label for="twf3">Linear+HL </label><br>&nbsp;&nbsp; &nbsp;&nbsp; 
  <input type="radio" id="twf4" name="twfov" value="fN"> <label for="twf4">Narrow </label> <br>
  or <b>Max Lens Mod:</b>&nbsp;&nbsp; 
  <input type="radio" id="twf5" name="twfov" value="fM"> <label for="twf5">Wide </label>&nbsp;
  <input type="radio" id="twf6" name="twfov" value="fX"> <label for="twf6">Superview </label><br>&nbsp;&nbsp; &nbsp;&nbsp; 
  <input type="radio" id="twf7" name="twfov" value="fL"> <label for="twf7">Linear </label>&nbsp;
  <input type="checkbox" id="twmlmhl" value="L"> <label for="twmlmhl">Horizon Lock</label>&nbsp;&nbsp;
  <input type="radio" id="twf8" name="twfov" value="" checked> <label for="twf8">not set</label><br>
 </div>
 
 
<div id="settingsZoom">
 <b>Zoom:</b> <input type="range" id="zoom" name="zoom" min="0" max="10" value="0"><label for="zoom"></label>&nbsp;&nbsp;<b id="zoomtext"></b><br>
</div>

<div id="settingsBurst">
<b>Burst Style:</b>&nbsp;&nbsp;
  <input type="radio" id="b1" name="burst" value="bA"> <label for="b1">Auto </label>&nbsp;
  <input type="radio" id="b2" name="burst" value="b3N1"> <label for="b2">3/1 </label>&nbsp;
  <input type="radio" id="b3" name="burst" value="b5N1"> <label for="b3">5/1 </label>&nbsp;
  <input type="radio" id="b4" name="burst" value="b10N1"> <label for="b4">10/1 </label><br>&nbsp;&nbsp;&nbsp;&nbsp;
  <input type="radio" id="b5" name="burst" value="b25N1"> <label for="b5">25/1 </label>&nbsp;
  <input type="radio" id="b6" name="burst" value="b10N3"> <label for="b6">10/3 </label>&nbsp;
  <input type="radio" id="b7" name="burst" value="b30N3"> <label for="b7">30/3 </label>&nbsp;
  <input type="radio" id="b8" name="burst" value="b30N6"> <label for="b8">30/6 </label><br>&nbsp;&nbsp;&nbsp;&nbsp;
  <input type="radio" id="b9" name="burst" value="b30N10"> <label for="b9">30/10 </label>&nbsp;
  <input type="radio" id="b10" name="burst" value="" checked> <label for="b10">not set</label><br>
</div>

<div id="settingsTimewarp">
<b>TimeWarp Speed:</b>&nbsp;&nbsp;
  <input type="radio" id="fpswarp1"    name="fpswarp" value="p15"> <label for="fpswarp1">2X </label>&nbsp;
  <input type="radio" id="fpswarp2"    name="fpswarp" value="p6"> <label for="fpswarp2">5X </label>&nbsp;
  <input type="radio" id="fpswarp3"    name="fpswarp" value="p3"> <label for="fpswarp3">10X </label>&nbsp;
  <input type="radio" id="fpswarp4"    name="fpswarp" value="p2"> <label for="fpswarp4">15X </label><br>&nbsp;&nbsp; &nbsp;&nbsp;  
  <input type="radio" id="fpswarp5"    name="fpswarp" value="p1"> <label for="fpswarp5">30X </label>&nbsp;
  <input type="radio" id="fpswarp6"    name="fpswarp" value="pA"> <label for="fpswarp6">Auto </label>&nbsp;&nbsp;
  <input type="radio" id="fpswarp7"    name="fpswarp" value="" checked> <label for="fpswarp7">not set</label><br>
</div>
 
 
<div id="settingsTimelapse">
<b>TLV Interval:</b>&nbsp;&nbsp;
  <input type="radio" id="fpslapse1" name="fpslapse" value="p2"> <label for="fpslapse1">0.5s </label>&nbsp;
  <input type="radio" id="fpslapse2" name="fpslapse" value="p1"> <label for="fpslapse2">1s </label>&nbsp;
  <input type="radio" id="fpslapse3" name="fpslapse" value="p.2"> <label for="fpslapse3">2s </label>&nbsp;
  <input type="radio" id="fpslapse4" name="fpslapse" value="p.5"> <label for="fpslapse4">5s </label>&nbsp;  
  <input type="radio" id="fpslapse5" name="fpslapse" value="p.10"> <label for="fpslapse5">10s </label><br>&nbsp;&nbsp; &nbsp;&nbsp;
  <input type="radio" id="fpslapse6" name="fpslapse" value="p.30"> <label for="fpslapse6">30s </label>&nbsp;
  <input type="radio" id="fpslapse7" name="fpslapse" value="p.60"> <label for="fpslapse7">60s </label>&nbsp;
  <input type="radio" id="fpslapse8"  name="fpslapse" value="p.120" > <label for="fpslapse8">2min </label>&nbsp;
  <input type="radio" id="fpslapse9"  name="fpslapse" value="p.300" > <label for="fpslapse9">5min </label><br>&nbsp;&nbsp; &nbsp;&nbsp;  
  <input type="radio" id="fpslapse10" name="fpslapse" value="p.1800"> <label for="fpslapse10">30min </label>&nbsp;
  <input type="radio" id="fpslapse11" name="fpslapse" value="p.3600"> <label for="fpslapse11">60min </label>&nbsp;
  <input type="radio" id="fpslapse12" name="fpslapse" value="" checked> <label for="fpslapse12">not set</label><br>
</div>

<div id="settingsNightlapse">
<b>NLV Interval:</b>&nbsp;&nbsp;
  <input type="radio" id="fpsnight1" name="fpsnight" value="p"     > <label for="fpsnight1">Auto </label>&nbsp;
  <input type="radio" id="fpsnight2" name="fpsnight" value="p.4"  >  <label for="fpsnight2">4s </label>&nbsp;
  <input type="radio" id="fpsnight3" name="fpsnight" value="p.5"  >  <label for="fpsnight3">5s </label>&nbsp;
  <input type="radio" id="fpsnight4" name="fpsnight" value="p.10"  > <label for="fpsnight4">10s </label><br>&nbsp;&nbsp; &nbsp;&nbsp;  
  <input type="radio" id="fpsnight5" name="fpsnight" value="p.15"  > <label for="fpsnight5">15s </label>&nbsp;
  <input type="radio" id="fpsnight6" name="fpsnight" value="p.20"  > <label for="fpsnight6">20s </label>&nbsp;
  <input type="radio" id="fpsnight7" name="fpsnight" value="p.30"  > <label for="fpsnight7">30s </label>&nbsp;
  <input type="radio" id="fpsnight8" name="fpsnight" value="p.60"  > <label for="fpsnight8">60s </label>&nbsp;  
  <input type="radio" id="fpsnight9" name="fpsnight" value="p.120" > <label for="fpsnight9">2min </label><br>&nbsp;&nbsp; &nbsp;&nbsp;
  <input type="radio" id="fpsnight10" name="fpsnight" value="p.300" > <label for="fpsnight10">5min </label>&nbsp;
  <input type="radio" id="fpsnight11" name="fpsnight" value="p.1800"> <label for="fpsnight11">30min </label>&nbsp;
  <input type="radio" id="fpsnight12" name="fpsnight" value="p.3600"> <label for="fpsnight12">60min </label>&nbsp;
  <input type="radio" id="fpsnight13" name="fpsnight" value="" checked> <label for="fpsnight13">not set</label><br>
</div>

<div id="settingsNightexposure">
<b>Shutter:</b>&nbsp;&nbsp;
  <input type="radio" id="nightexp1" name="nightexp" value="eA" > <label for="nightexp1">auto </label>&nbsp;
  <input type="radio" id="nightexp2" name="nightexp" value="e2" > <label for="nightexp2">2s </label>  &nbsp;
  <input type="radio" id="nightexp3" name="nightexp" value="e5" > <label for="nightexp3">5s </label>  &nbsp;
  <input type="radio" id="nightexp4" name="nightexp" value="e10"> <label for="nightexp4">10s </label><br>&nbsp;&nbsp; &nbsp;&nbsp;  
  <input type="radio" id="nightexp5" name="nightexp" value="e15"> <label for="nightexp5">15s </label>&nbsp;
  <input type="radio" id="nightexp6" name="nightexp" value="e20"> <label for="nightexp6">20s </label>&nbsp;
  <input type="radio" id="nightexp7" name="nightexp" value="e30"> <label for="nightexp7">30s </label>&nbsp;
  <input type="radio" id="nightexp8" name="nightexp" value="" checked> <label for="nightexp8"> not set</label><br>
</div>

<div id="settingsVideo">
<b>Hypersmooth:</b>&nbsp;&nbsp;
	<input type="radio" id="eis1" name="eis" value="e0"> <label for="eis1">Off</label>&nbsp;&nbsp;
	<input type="radio" id="eis2" name="eis" value="e1"> <label for="eis2">Standard</label>&nbsp;&nbsp;
	<input type="radio" id="eis3" name="eis" value="e2"> <label for="eis3">High</label><br>&nbsp;&nbsp; &nbsp;&nbsp;  
	<input type="radio" id="eis4" name="eis" value="e3"> <label for="eis4">Boost</label>&nbsp;&nbsp;
	<input type="radio" id="eis5" name="eis" value="" checked> <label for="eis5">not set</label><br>
</div>

<div id="settingsHindsight">
<b>Hindsight:</b>&nbsp;&nbsp;
	<input type="radio" id="hind1" name="hind" value="hS0"> <label for="hind1">Off</label>&nbsp;&nbsp;
	<input type="radio" id="hind2" name="hind" value="hS1"> <label for="hind2">15s</label>&nbsp;&nbsp;
	<input type="radio" id="hind3" name="hind" value="hS2"> <label for="hind3">30s</label>&nbsp;&nbsp;
	<input type="radio" id="hind4" name="hind" value="" checked> <label for="hind4">not set</label><br>
</div>
					
<div id="settingsDuration">
<b>Duration:</b>&nbsp;&nbsp;
	<input type="radio" id="dur1" name="dur" value="dR0"> <label for="dur1">Off</label>&nbsp;
	<input type="radio" id="dur2" name="dur" value="dR15"> <label for="dur2">15s</label>&nbsp;
	<input type="radio" id="dur3" name="dur" value="dR30"> <label for="dur3">30s</label>&nbsp;
	<input type="radio" id="dur4" name="dur" value="dR60"> <label for="dur4">1min</label>&nbsp;
	<input type="radio" id="dur5" name="dur" value="dR300"> <label for="dur5">5min</label><br>&nbsp;&nbsp; &nbsp;&nbsp;  
	<input type="radio" id="dur6" name="dur" value="dR900"> <label for="dur6">15min</label>&nbsp;
	<input type="radio" id="dur7" name="dur" value="dR1800"> <label for="dur7">30min</label>&nbsp;
	<input type="radio" id="dur8" name="dur" value="dR3600"> <label for="dur8">1hr</label>&nbsp;
	<input type="radio" id="dur9" name="dur" value="dR7200"> <label for="dur9">2hr</label>&nbsp;
	<input type="radio" id="dur10" name="dur" value="dR9999"> <label for="dur10">3hr</label><br>&nbsp;&nbsp; &nbsp;&nbsp;  
	<input type="radio" id="dur11" name="dur" value="" checked> <label for="dur11">not set</label><br>
</div>

<div id="settingsPhotoRAW">
<b>Photo Properties:</b><br>
  <input type="radio" id="raw1" name="raw" value="r0"> <label for="raw1">Standard </label>&nbsp;&nbsp;
  <input type="radio" id="raw2" name="raw" value="r"> <label for="raw2">Raw + JPEG </label>&nbsp;&nbsp;
  <input type="radio" id="raw3" name="raw" value="rS"> <label for="raw3">Superphoto </label>&nbsp;&nbsp;
  <input type="radio" id="raw4" name="raw" value="rH"> <label for="raw4">HDR </label><br>&nbsp;&nbsp; &nbsp;&nbsp;
  <input type="radio" id="raw5" name="raw" value="" checked> <label for="raw5"> not set</label><br>
</div>

<div id="settingsAUDT">
<b>Wind Reduction:</b>&nbsp;&nbsp;
  <input type="radio" id="audt1" name="audt" value="aA"> <label for="audt1">Auto </label>&nbsp;&nbsp;
  <input type="radio" id="audt2" name="audt" value="aS"> <label for="audt2">Off </label>&nbsp;&nbsp;
  <input type="radio" id="audt3" name="audt" value="aW"> <label for="audt3">On</label>&nbsp;&nbsp;
  <input type="radio" id="audt4" name="audt" value="" checked> <label for="audt4"> not set</label><br>
</div>

<div id="spotMeterCheck">
<input type="checkbox" id="sm" value="oSM"> <label for="sm">Spot Metering</label><br>
</div>
<div id="spotMeter">
&nbsp;&nbsp;Your Virtual Touch Screen<br>
&nbsp;&nbsp;<input type="radio" id="sp1"  name="placement" value="1,1">   <label for="sp1" >&nbsp;&nbsp;&nbsp;&nbsp;</label>
&nbsp;&nbsp;<input type="radio" id="sp2"  name="placement" value="25,1">  <label for="sp2" >&nbsp;&nbsp;&nbsp;&nbsp;</label>
&nbsp;&nbsp;<input type="radio" id="sp3"  name="placement" value="50,1">  <label for="sp3" >&nbsp;&nbsp;&nbsp;&nbsp;</label>
&nbsp;&nbsp;<input type="radio" id="sp4"  name="placement" value="75,1">  <label for="sp4" >&nbsp;&nbsp;&nbsp;&nbsp;</label>
&nbsp;&nbsp;<input type="radio" id="sp5"  name="placement" value="99,1">  <label for="sp5" >&nbsp;&nbsp;&nbsp;&nbsp;</label><br>
&nbsp;&nbsp;<input type="radio" id="sp6"  name="placement" value="1,25">  <label for="sp6" >&nbsp;&nbsp;&nbsp;&nbsp;</label>
&nbsp;&nbsp;<input type="radio" id="sp7"  name="placement" value="25,25"> <label for="sp7" >&nbsp;&nbsp;&nbsp;&nbsp;</label>
&nbsp;&nbsp;<input type="radio" id="sp8"  name="placement" value="50,25"> <label for="sp8" >&nbsp;&nbsp;&nbsp;&nbsp;</label>
&nbsp;&nbsp;<input type="radio" id="sp9"  name="placement" value="75,25"> <label for="sp9" >&nbsp;&nbsp;&nbsp;&nbsp;</label>
&nbsp;&nbsp;<input type="radio" id="sp10" name="placement" value="99,25"> <label for="sp10">&nbsp;&nbsp;&nbsp;&nbsp;</label><br>
&nbsp;&nbsp;<input type="radio" id="sp11" name="placement" value="1,50">  <label for="sp11">&nbsp;&nbsp;&nbsp;&nbsp;</label>
&nbsp;&nbsp;<input type="radio" id="sp12" name="placement" value="25,50"> <label for="sp12">&nbsp;&nbsp;&nbsp;&nbsp;</label>
&nbsp;&nbsp;<input type="radio" id="sp13" name="placement" value="50,50" checked> <label for="sp13">&nbsp;&nbsp;&nbsp;&nbsp;</label>
&nbsp;&nbsp;<input type="radio" id="sp14" name="placement" value="75,50"> <label for="sp14">&nbsp;&nbsp;&nbsp;&nbsp;</label>
&nbsp;&nbsp;<input type="radio" id="sp15" name="placement" value="99,50"> <label for="sp15">&nbsp;&nbsp;&nbsp;&nbsp;</label><br>
&nbsp;&nbsp;<input type="radio" id="sp16" name="placement" value="1 ,75"> <label for="sp16">&nbsp;&nbsp;&nbsp;&nbsp;</label>
&nbsp;&nbsp;<input type="radio" id="sp17" name="placement" value="25,75"> <label for="sp17">&nbsp;&nbsp;&nbsp;&nbsp;</label>
&nbsp;&nbsp;<input type="radio" id="sp18" name="placement" value="50,75"> <label for="sp18">&nbsp;&nbsp;&nbsp;&nbsp;</label>
&nbsp;&nbsp;<input type="radio" id="sp19" name="placement" value="75,75"> <label for="sp19">&nbsp;&nbsp;&nbsp;&nbsp;</label>
&nbsp;&nbsp;<input type="radio" id="sp20" name="placement" value="99,75"> <label for="sp20">&nbsp;&nbsp;&nbsp;&nbsp;</label><br>
&nbsp;&nbsp;<input type="radio" id="sp21" name="placement" value="1,99">  <label for="sp21">&nbsp;&nbsp;&nbsp;&nbsp;</label>
&nbsp;&nbsp;<input type="radio" id="sp22" name="placement" value="25,99"> <label for="sp22">&nbsp;&nbsp;&nbsp;&nbsp;</label>
&nbsp;&nbsp;<input type="radio" id="sp23" name="placement" value="50,99"> <label for="sp23">&nbsp;&nbsp;&nbsp;&nbsp;</label>
&nbsp;&nbsp;<input type="radio" id="sp24" name="placement" value="75,99"> <label for="sp24">&nbsp;&nbsp;&nbsp;&nbsp;</label>
&nbsp;&nbsp;<input type="radio" id="sp25" name="placement" value="99,99"> <label for="sp25">&nbsp;&nbsp;&nbsp;&nbsp;</label><br>
&nbsp;&nbsp;<input type="radio" id="sp26" name="placement" value="0"> <label for="sp26">Disable </label><br>
&nbsp;&nbsp;<input type="checkbox" id="sl" value="oSM0!2NoSL"> <label for="sl">Exposure Lock 3s after scan (to avoid locking on the QR Code)</label><br>
</div>

<div id="settingsPT">
<input type="checkbox" id="pt" value="t"> <label for="pt">Protune Controls</label><br>
</div>
<div id="ptCOLOR">&nbsp;&nbsp;<b>Color:</b>&nbsp;&nbsp;
  <input type="radio" id="ptc1" name="ptc" value="cG"> <label for="ptc1">Vibrant</label>&nbsp;&nbsp;
  <input type="radio" id="ptc2" name="ptc" value="cN"> <label for="ptc2">Natural</label>&nbsp;&nbsp;
  <input type="radio" id="ptc3" name="ptc" value="cF"> <label for="ptc3">Flat</label>&nbsp;&nbsp;
  <input type="radio" id="ptc4" name="ptc" value="" checked> <label for="ptc4">not set</label>
</div>
<div id="ptBITRATE">&nbsp;&nbsp;<b>Bit rate:</b>&nbsp;&nbsp;
  <input type="radio" id="br1" name="br" value="b0"> <label for="br1">Standard</label>&nbsp;&nbsp;
  <input type="radio" id="br2" name="br" value="b1"> <label for="br2">High</label>&nbsp;&nbsp;
  <input type="radio" id="br3" name="br" value="" checked> <label for="br3">not set</label>
</div>
<div id="ptWBAL">&nbsp;&nbsp;<b>White Balance:</b>&nbsp;&nbsp;
  <input type="radio" id="wb1" name="wb" value="wA" checked> <label for="wb1">Auto </label>&nbsp;&nbsp;
  <input type="radio" id="wb2" name="wb" value="w23" > <label for="wb2">2300K </label>&nbsp;&nbsp;
  <input type="radio" id="wb3" name="wb" value="w28" > <label for="wb3">2800K </label>&nbsp;&nbsp;
  <input type="radio" id="wb4" name="wb" value="w32" > <label for="wb4">3200K </label>&nbsp;&nbsp;
  <input type="radio" id="wb5" name="wb" value="w40" > <label for="wb5">4000K </label>&nbsp;&nbsp;
  <input type="radio" id="wb6" name="wb" value="w45" > <label for="wb6">4500K </label>&nbsp;&nbsp;
  <input type="radio" id="wb7" name="wb" value="w50" > <label for="wb7">5000K </label><br>&nbsp;&nbsp;
  <input type="radio" id="wb8" name="wb" value="w55" > <label for="wb8">5500K </label>&nbsp;&nbsp;
  <input type="radio" id="wb9" name="wb" value="w60"> <label for="wb9">6000K </label>&nbsp;&nbsp;
  <input type="radio" id="wb10" name="wb" value="w65"> <label for="wb10">6500K </label>&nbsp;&nbsp;
  <input type="radio" id="wb11" name="wb" value="wN" > <label for="wb11">Native </label>&nbsp;&nbsp;
  <input type="radio" id="wb12" name="wb" value="" checked> <label for="wb12">not set</label>
 </div>
<div id="ptIMIN">&nbsp;&nbsp;<b>ISO Min:</b>&nbsp;&nbsp;
  <input type="radio" id="isomin1" name="isomin" value="M1" > <label for="isomin1">100 (def) </label>&nbsp;&nbsp;
  <input type="radio" id="isomin2" name="isomin" value="M2" > <label for="isomin2">200 </label>&nbsp;&nbsp;
  <input type="radio" id="isomin3" name="isomin" value="M4" > <label for="isomin3">400 </label>&nbsp;&nbsp;
  <input type="radio" id="isomin4" name="isomin" value="M8" > <label for="isomin4">800 </label>&nbsp;&nbsp;
  <input type="radio" id="isomin5" name="isomin" value="M16"> <label for="isomin5">1600 </label>&nbsp;&nbsp;
  <input type="radio" id="isomin6" name="isomin" value="M32"> <label for="isomin6">3200 </label>&nbsp;&nbsp;
  <input type="radio" id="isomin7" name="isomin" value="M64"> <label for="isomin7">6400 </label>&nbsp;&nbsp;
  <input type="radio" id="isomin8" name="isomin" value="M1" checked> <label for="isomin8">not set</label>
 </div>
<div id="ptISO">&nbsp;&nbsp;<b>ISO Max:</b>&nbsp;&nbsp;
  <input type="radio" id="iso1" name="iso" value="i1" > <label for="iso1">100 </label>&nbsp;&nbsp;
  <input type="radio" id="iso2" name="iso" value="i2" > <label for="iso2">200 </label>&nbsp;&nbsp;
  <input type="radio" id="iso3" name="iso" value="i4" > <label for="iso3">400 </label>&nbsp;&nbsp;
  <input type="radio" id="iso4" name="iso" value="i8" > <label for="iso4">800 </label>&nbsp;&nbsp;
  <input type="radio" id="iso5" name="iso" value="i16"> <label for="iso5">1600 (def) </label>&nbsp;&nbsp;
  <input type="radio" id="iso6" name="iso" value="i32"> <label for="iso6">3200 </label>&nbsp;&nbsp;
  <input type="radio" id="iso7" name="iso" value="i64"> <label for="iso7">6400 </label>&nbsp;&nbsp;
  <input type="radio" id="iso8" name="iso" value="i16" checked> <label for="iso8">not set</label>
 </div>
<div id="ptSHUT">&nbsp;&nbsp;<b>Lock Shutter:</b>&nbsp;&nbsp;
  <input type="radio" id="shut1" name="shut" value="S360"> <label for="shut1">360&deg; </label>&nbsp;&nbsp;
  <input type="radio" id="shut2" name="shut" value="S180"> <label for="shut2">180&deg; </label>&nbsp;&nbsp;
  <input type="radio" id="shut3" name="shut" value="S90" > <label for="shut3">90&deg; </label>&nbsp;&nbsp;
  <input type="radio" id="shut4" name="shut" value="S45" > <label for="shut4">45&deg; </label>&nbsp;&nbsp;
  <input type="radio" id="shut5" name="shut" value="S22" > <label for="shut5">22&deg; </label>&nbsp;&nbsp;
  <input type="radio" id="shut6" name="shut" value="S10" > <label for="shut6">10&deg; </label>&nbsp;&nbsp;
  <input type="radio" id="shut7" name="shut" value="S5"  > <label for="shut7">5&deg; </label>&nbsp;&nbsp;
  <input type="radio" id="shut8" name="shut" value="S2"  > <label for="shut8">2&deg; </label>&nbsp;&nbsp;
  <input type="radio" id="shut9" name="shut" value="S0"  > <label for="shut9">Auto</label>
  <input type="radio" id="shut10" name="shut" value="" checked> <label for="shut10">not set</label>
</div>
<div id="ptEV">&nbsp;&nbsp;<b>EV Compensation:</b>&nbsp;&nbsp;
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
<div id="ptSHARP">&nbsp;&nbsp;<b>Sharpness:</b>&nbsp;&nbsp;
  <input type="radio" id="sharp1" name="sharp" value="sL"> <label for="sharp1">Low </label>&nbsp;&nbsp;
  <input type="radio" id="sharp2" name="sharp" value="sM"> <label for="sharp2">Medium </label>&nbsp;&nbsp;
  <input type="radio" id="sharp3" name="sharp" value="sH"> <label for="sharp3">High</label>&nbsp;&nbsp;
  <input type="radio" id="sharp4" name="sharp" value="" checked> <label for="sharp4">not set</label>
</div>
<!--
<div id="ptAUD">&nbsp;&nbsp;<b>RAW Audio:</b>&nbsp;&nbsp;
  <input type="radio" id="aud1" name="aud" value="a"> <label for="aud1">Off </label>&nbsp;&nbsp;
  <input type="radio" id="aud2" name="aud" value="aL"> <label for="aud2">Low </label>&nbsp;&nbsp;
  <input type="radio" id="aud3" name="aud" value="aM"> <label for="aud3">Medium </label>&nbsp;&nbsp;
  <input type="radio" id="aud4" name="aud" value="aH"> <label for="aud4">High</label>&nbsp;&nbsp;
  <input type="radio" id="aud5" name="aud" value="" checked> <label for="aud5">not set</label>
</div> -->

<div id="settingsPTR">&nbsp;&nbsp;<b>Protune Reset:</b>&nbsp;&nbsp;
<input type="checkbox" id="ptr" value="t0"> <label for="ptr"> </label><br>
</div>


<div id="cameraOptions">
<input type="checkbox" id="options" value=""> <label for="options">Camera Preferences</label><br>
</div>

<div id="opVC">&nbsp;&nbsp;<b>Voice Control:</b>&nbsp;&nbsp; 
  <input type="radio" id="vc1" name="vc" value="v0"> <label for="vc1">off </label>&nbsp;&nbsp;
  <input type="radio" id="vc2" name="vc" value="v1"> <label for="vc2">on </label>&nbsp;&nbsp;
  <input type="radio" id="vc3" name="vc" value="" checked> <label for="vc3">not set</label>
 </div>
<div id="opQC">&nbsp;&nbsp;<b>Quick Capture:</b>&nbsp;&nbsp;  
  <input type="radio" id="qc1" name="qc" value="q0"> <label for="qc1">off </label>&nbsp;&nbsp;
  <input type="radio" id="qc2" name="qc" value="q1"> <label for="qc2">on </label>&nbsp;&nbsp;
  <input type="radio" id="qc3" name="qc" value="" checked> <label for="qc3">not set </label>
  </div>
<div id="opDM">&nbsp;&nbsp;<b>Default Mode:</b>&nbsp;&nbsp;
  <input type="radio" id="dm1" name="dm" value="dL">  <label for="dm1">Last Used</label>&nbsp;&nbsp;
  <input type="radio" id="dm2" name="dm" value="dV">  <label for="dm2">Video</label>&nbsp;&nbsp;
  <input type="radio" id="dm3" name="dm" value="dP">  <label for="dm3">Photo</label>&nbsp;&nbsp;
  <input type="radio" id="dm4" name="dm" value="dT">  <label for="dm4">Timelapse</label>&nbsp;&nbsp;
  <input type="radio" id="dm5" name="dm" value="" checked> <label for="dm5">not set</label>
</div>
<!--<div id="opBV">&nbsp;&nbsp;<b>Beep Volume:</b>&nbsp;&nbsp; 
  <input type="radio" id="bv1" name="bv" value="V0"> <label for="bv1">0% </label>&nbsp;&nbsp;
  <input type="radio" id="bv2" name="bv" value="V1"> <label for="bv2">10% </label>&nbsp;&nbsp;
  <input type="radio" id="bv3" name="bv" value="V4"> <label for="bv3">40% </label>&nbsp;&nbsp;
  <input type="radio" id="bv4" name="bv" value="V7"> <label for="bv4">70% </label>&nbsp;&nbsp;
  <input type="radio" id="bv5" name="bv" value="V8"> <label for="bv5">85% </label>&nbsp;&nbsp;
  <input type="radio" id="bv6" name="bv" value="V9"> <label for="bv6">100% </label>&nbsp;&nbsp;
  <input type="radio" id="bv7" name="bv" value="" checked> <label for="bv7">not set</label>
  </div>-->
<!--<div id="opLO">&nbsp;&nbsp;<b>LEDs On:</b>&nbsp;&nbsp;
  <input type="radio" id="lo1" name="lo" value="D0"> <label for="lo1">All Off </label>&nbsp;&nbsp;
  <input type="radio" id="lo2" name="lo" value="D2"> <label for="lo2">Rear Only </label>&nbsp;&nbsp;
  <input type="radio" id="lo3" name="lo" value="D4"> <label for="lo3">All On </label>&nbsp;&nbsp;
  <input type="radio" id="lo4" name="lo" value="" checked> <label for="lo4">not set</label>
  </div>-->
<div id="opOR">&nbsp;&nbsp;<b>Orientation Lock:</b>&nbsp;&nbsp; 
  Landscape <input type="radio" id="or1" name="or" value="R1"> <label for="or1">↑</label>&nbsp;&nbsp;&nbsp;
  <input type="radio" id="or2" name="or" value="R2"> <label for="or2">↓</label>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  Portrait <input type="radio" id="or3" name="or" value="R3"> <label for="or3">←</label>&nbsp;&nbsp;&nbsp;
  <input type="radio" id="or4" name="or" value="R4"> <label for="or4">→</label>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <input type="radio" id="or5" name="or" value="R0"> <label for="or5">Unlocked </label>&nbsp;&nbsp;
  <input type="radio" id="or6" name="or" value="" checked> <label for="or6">not set</label>
  </div>
<div id="opAO">&nbsp;&nbsp;<b>Camera Auto Off:</b>&nbsp;&nbsp; 
  <input type="radio" id="ao1" name="ao" value="C5"> <label for="ao1">5 mins </label>&nbsp;&nbsp;
  <input type="radio" id="ao2" name="ao" value="C15"> <label for="ao2">15 mins </label>&nbsp;&nbsp;
  <input type="radio" id="ao3" name="ao" value="C30"> <label for="ao3">30 mins </label>&nbsp;&nbsp;
  <input type="radio" id="ao4" name="ao" value="C"> <label for="ao4">Never </label>&nbsp;&nbsp;
  <input type="radio" id="ao5" name="ao" value="" checked> <label for="ao5">not set</label>
  </div>
<div id="opWC">&nbsp;&nbsp;<b>WiFi Connections:</b>&nbsp;&nbsp; 
  <input type="radio" id="wc1" name="wc" value="W0"> <label for="wc1">Off </label>&nbsp;&nbsp;
  <input type="radio" id="wc2" name="wc" value="W1"> <label for="wc2">On </label>&nbsp;&nbsp;
  <input type="radio" id="wc3" name="wc" value="W2"> <label for="wc3">On 2.4GHz</label>&nbsp;&nbsp;
  <input type="radio" id="wc4" name="wc" value="W5"> <label for="wc4">On 5GHz</label>&nbsp;&nbsp;
  <input type="radio" id="wc5" name="wc" value="" checked> <label for="wc5">not set</label>
  </div>
<div id="opLN">&nbsp;&nbsp;<b>Voice Language:</b>&nbsp;&nbsp;
  <input type="radio" id="ln1" name="ln" value="L0"> <label for="ln1">English US </label>&nbsp;&nbsp;
  <input type="radio" id="ln2" name="ln" value="L01"> <label for="ln2">English UK </label>&nbsp;&nbsp;
  <input type="radio" id="ln3" name="ln" value="L02"> <label for="ln3">English AUS </label>&nbsp;&nbsp;
  <input type="radio" id="ln4" name="ln" value="L03"> <label for="ln4">English IND </label>&nbsp;&nbsp;
  <input type="radio" id="ln5" name="ln" value="L4"> <label for="ln5">Spanish EU </label>&nbsp;&nbsp;
  <input type="radio" id="ln6" name="ln" value="L41"> <label for="ln6">Spanish NA </label>&nbsp;&nbsp;
  <input type="radio" id="ln7" name="ln" value="L1"> <label for="ln7">German </label>&nbsp;&nbsp;
  <input type="radio" id="ln8" name="ln" value="L3"> <label for="ln8">Italian </label>&nbsp;&nbsp;
  <input type="radio" id="ln9" name="ln" value="L5"> <label for="ln9">Chinese </label>&nbsp;&nbsp;
  <input type="radio" id="ln10" name="ln" value="L6"> <label for="ln10">Japanese </label>&nbsp;&nbsp;
  <input type="radio" id="ln11" name="ln" value="L7"> <label for="ln11">Korean </label>&nbsp;&nbsp;
  <input type="radio" id="ln12" name="ln" value="L2"> <label for="ln12">French </label>&nbsp;&nbsp;
  <input type="radio" id="ln13" name="ln" value="L8"> <label for="ln13">Portuguese </label>&nbsp;&nbsp;
  <input type="radio" id="ln14" name="ln" value="L9"> <label for="ln14">Russian </label>&nbsp;&nbsp;
  <input type="radio" id="ln15" name="ln" value="L91"> <label for="ln15">Swedish </label>&nbsp;&nbsp;
  <input type="radio" id="ln16" name="ln" value="" checked> <label for="ln16">not set</label><br>
</div>

<div id="opDT">
<input type="checkbox" id="dt" value="oT" checked> <label for="dt">Set date and time</label><br>
</div>

<div id="opDTS">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" id="dttimecode" value=""> <label for="dttimecode">add 1/100th of a second</label><br>
</div>

<div id="cameraActions">
<input type="checkbox" id="actions" value=""> <label for="actions">Camera Actions</label><br>
</div>

<div id="NakedTools">
&nbsp;&nbsp;<b>Pairing:</b>&nbsp;&nbsp;<input type="radio" id="sap1" name="sap" value="!PA"> <label for="sap1">Quik App</label>
&nbsp;&nbsp;<input type="radio" id="sap2" name="sap" value="!PR"> <label for="sap2">Remote</label>
&nbsp;&nbsp;<input type="radio" id="sap3" name="sap" value="!PS"> <label for="sap3">Cancel</label><br>
&nbsp;&nbsp;<b>Reset:</b>&nbsp;&nbsp;<input type="radio" id="sap4" name="sap" value="!MBOOT=0!MBITR=0!FRESET"> <label for="sap4">Factory</label>
&nbsp;&nbsp;<input type="radio" id="sap5" name="sap" value="!PRESET"> <label for="sap5">Presets</label>
&nbsp;&nbsp;<input type="radio" id="sap6" name="sap" value="!WRESET"> <label for="sap6">WiFi</label>
&nbsp;&nbsp;<input type="radio" id="sap7" name="sap" value="!RESET"> <label for="sap7">Labs</label><br>
&nbsp;&nbsp;<b>Auto Wake on Power:</b>&nbsp;&nbsp;<input type="radio" id="sap8" name="sap" value="!MWAKE=1"> <label for="sap8">Enable</label>
&nbsp;&nbsp;<input type="radio" id="sap9" name="sap" value="!MWAKE=0"> <label for="sap9">Disable</label><br>
&nbsp;&nbsp;<b>Overclock Bitrate:</b>&nbsp;&nbsp;<input type="radio" id="sap10" name="sap" value="b1!MBITR="> 
  <label for="sap10">Take On Risk</label>&nbsp;&nbsp;<input type="checkbox" id="helpBitr" name="helpBitr" value=""><label for="helpBitr">Help</label><br>
  <div id="bitrHelp">
	 &nbsp;&nbsp;&nbsp;&nbsp;<small>
	 
	 <b>Warning:</b> SD Card and encoding reliability is only thoroughly tested at the default bitrates, up to 100Mb/s. Some SD cards can support higher bit-rates when fairly new, but then may fail when extensively used. As the bit-rate is increased, the probability of capture failures increase. Lower frame rate maybe more reliable than higher framerates as some extreme overclocks. Experiment extensively before using this feature on critical projects. You can also disable LRVs and audio capture to help push the video bitrate to the maximum. See more on these <a href="../control/extensions">Labs extensions</a>. Changes can be reversed with a Labs reset. 
	 
	 </small>
</div>
<div id="bitrSlider">
     &nbsp;&nbsp;&nbsp;&nbsp;<input type="range" style="width: 140px;" id="bitr" name="bitr" min="100" max="200" value="100"> <em id="bitrtext"></em><br>
</div>

&nbsp;&nbsp;<b>Auto Capture Trigger:</b><br>
&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="sap11" name="sap" value="!SA"> <label for="sap11">Sound Pressure Level (range 30-120dB)</label><br>
&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="sap12" name="sap" value="!SI"> <label for="sap12">Camera Motion - Gyro+Accel (range 1-9)</label><br>
&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="sap13" name="sap" value="!SM"> <label for="sap13">Scene Motion (range 1-6)</label><br>
  <div id="motionParams">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Sensitivity: <input type="text" id="mstart" value="6" style="width:60px"> (value from range ). <input type="checkbox" id="helpRange" value="">&nbsp;&nbsp;<label for="actions">Help</label>
	<div id="splHelp">
	  <small><table style="margin-left:60px;">
		<thead>	<tr><th>SPL (dB) at 1m/3ft</th>  <th align="left">Activity</th>	</tr> </thead>
		  <tbody> 
			<tr> <td>30</td>    <td>calm room</td> </tr>
			<tr> <td>40-60</td> <td>conversation</td> </tr>
			<tr> <td>60-80</td> <td>passenger car</td> </tr>
			<tr> <td>80-90</td> <td>busy roadway</td> </tr>
			<tr> <td>100</td>   <td>jack hammer</td> </tr>
			<tr> <td>110</td>   <td>chain saw</td> </tr>
			<tr> <td>120</td>   <td>air horn</td> </tr>
		  </tbody>
		</table>
	  </small>
	</div>
	<div id="imuHelp">
	  <small><table style="margin-left:60px;">
		  <thead> <tr> <th>Sensitivity</th> <th align="left">Activity</th></tr> </thead>
		  <tbody>
			<tr> <td>1</td> <td>Throwing the camera</td></tr>
			<tr> <td>2</td> <td>Jumps</td></tr>
			<tr> <td>5</td> <td>any hand-held movement</td></tr>
			<tr> <td>8</td> <td>tiny movement</td> </tr>
			<tr> <td>9</td> <td>small tremor</td> </tr>
		  </tbody>
		</table>
	  </small>
	</div>
	<div id="motionHelp">
	  <small> <table style="margin-left:60px;"> 
		<thead> <tr> <th>Sensitivity</th><th align="left">Activity</th></tr></thead>
		  <tbody>
			<tr> <td>1</td> <td>Everything moving</td></tr>
			<tr> <td>2</td> <td>Large nearby movement</td></tr>
			<tr> <td>3</td> <td>Medium object movement</td></tr>
			<tr> <td>4</td> <td>small movement</td></tr>
			<tr> <td>5</td> <td>tiny movement</td></tr>
			<tr> <td>6</td> <td>any change</td></tr>
		  </tbody>
		</table>
	  </small>
	</div>
	<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Delay start: <input type="text" id="dhold" value="1" style="width:60px"> seconds.<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Hold time: <input type="text" id="mhold" value="5" style="width:60px"> capture seconds after motion stops.<br>
  </div>
  <div id="aR">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" id="repeat" value="" checked> <label for="repeat">Repeat Command</label><br>
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" id="boot" value=""> <label for="boot">Make Boot Command on SD Card -- Automatic Action on boot</label><br>
  </div>
  &nbsp;&nbsp;<input type="radio" id="sap14" name="sap" value="" checked> <label for="sap14">not set</label><br>
</div>


Additional Commands: <input type="text" id="addcmd" value="">

<div id="qrcode_txt" style="width: 360px">
  <center>
  <div id="qrcode"></div><br>
  <b><font color="#009FDF">GoProQR:</font></b> <em id="qrtext"></em>
  </center>
</div>
<div id="copyshow">
<br>
<button id="copyImg">Copy Image to Clipboard</button>
</div>
<br>
Share this QR Code as a URL: <small id="urltext"></small><br>
<button id="copyBtn">Copy URL to Clipboard</button>
<br>
<br>
<button onclick="myReloadFunction()">Reset page</button>

[More features](../control) for Labs enabled cameras

## version 1.01
updated: Apr 9, 2022

<script>
var clipcopy = "";
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
	dset("settingsPFOV", false);
	dset("settingsTLVFOV", false);
	dset("settingsTWFOV", false);
	dset("settingsZoom", false);
	dset("settingsRESTLV", false);
	dset("settingsVideo", false);
	dset("settingsHindsight", false);
	dset("settingsDuration", false);
	dset("settingsPhotoRAW", false);
	dset("settingsPT", false);
	dset("settingsPTR", false);
	dset("spotMeterCheck", false);
	dset("spotMeter", false);
	dset("settingsBurst", false);
	dset("settingsTimewarp", false);
	dset("settingsTimelapse", false);
	dset("settingsNightlapse", false);
	dset("settingsNightexposure", false);
	dset("settingsAUDT",false);
	
	dset("ptCOLOR", false);
	dset("ptBITRATE", false);
	dset("ptWBAL", false);
	dset("ptISO",false);
	dset("ptIMIN",false);
	dset("ptSHUT",false);
	dset("ptIMIN",false);
	dset("ptEV",false);
	dset("ptSHARP",false);
	//dset("ptAUD",false);
		
	dset("opVC", false);
	dset("opQC", false);
	dset("opDM", false);
	//dset("opBV", false);
	//dset("opLO", false);
	dset("opOR", false);
	dset("opAO", false);
	dset("opWC", false);
	dset("opLN", false);
	
	dset("NakedTools", false);
	//dset("aS", false);
	//dset("aSM", false);
	//dset("aIT", false);
	dset("aR", false);
	dset("splHelp", false);
	dset("imuHelp", false);
	dset("motionHelp", false);
	dset("bitrHelp", false);
	dset("bitrSlider", false);
	dset("motionParams", false);
	dset("opDTS", false);
	
	var checkedmode = 0;
	var actionmode = 0;
	var x;
	
	for (i = 1; i < 14; i++) { 
		var mode = "m"+i;
		x = document.getElementById(mode).checked;
		if( x === true)
			checkedmode = i;
	}
	
	
	for (i = 1; i < 14; i++) { 
		var amode = "sap"+i;
		if(document.getElementById(amode) !== null)	{
			x = document.getElementById(amode).checked;
			if( x === true)
				actionmode = i;
		}
	}
	
	//m1 mV 
	//m2 mV0
	//m3 mV1
	//m4 mV2
	//m5 mV3
	//m6 mV4
	//m7 mTW
	//m8 mT 
	//m9 mNL
	//m10 mP 
	//m11 mPB
	//m12 mPN
	
	switch(checkedmode)
	{
		default:
		case 1: //Video	
		case 2: //mV0
		case 3: //mV1
		case 4: //mV2
		case 5: //mV3
		case 6: //mV4
		dset("settingsRES", true);
		dset("settingsFPS", true);
		dset("settingsFOV", true);
		dset("settingsVideo", true);
		dset("settingsHindsight", true);
		dset("settingsDuration", true);
		dset("settingsPT", true);
		//dset("settingsAUDT",true);
		break;
		
		case 7: //TimeWarp Video
		dset("settingsTimewarp", true);		
		dset("settingsDuration", true);
		dset("settingsRESTLV", true);
		dset("settingsTWFOV", true);
		dset("settingsPT", true);
		break;		
		
		case 8: //Timelapse Video
		dset("settingsTimelapse", true);	
		dset("settingsDuration", true);	
		dset("settingsRESTLV", true);
		dset("settingsTLVFOV", true);
		dset("settingsPT", true);
		break;		
		
		case 9: //NL Video
		dset("settingsNightlapse", true);	
		dset("settingsNightexposure", true);
		dset("settingsDuration", true);		
		dset("settingsRESTLV", true);
		dset("settingsPT", true);
		dset("settingsTLVFOV", true);
		break;
	
		case 10: //Photo
		dset("settingsPT", true);
		dset("settingsPFOV", true);
		dset("settingsPhotoRAW", true);
		break;
		
		case 11: //Burst
		dset("settingsBurst", true);
		dset("settingsPT", true);
		dset("settingsTLVFOV", true);
		dset("settingsPhotoRAW", true);
		break;
				
		case 12: //Night
		dset("settingsNightexposure", true);
		dset("settingsPT", true);
		dset("settingsTLVFOV", true);
		dset("settingsPhotoRAW", true);
		break;
		
	}
	
	if(document.getElementById("sm") !== null)
	{
	
		if( (document.getElementById("raw3").checked === true) || //Superphoto
			(document.getElementById("raw4").checked === true)) //HDR
		{	
			document.getElementById("sm").checked = false;
		}
		else
		{
			dset("spotMeterCheck", true);
		}
		
		dset("spotMeter", document.getElementById("sm").checked);	
	}
		
	if(document.getElementById("pt") !== null)
	{
		if(document.getElementById("pt").checked === true)
			dset("settingsPTR", true);
		
		if(document.getElementById("pt").checked === true && document.getElementById("ptr").checked === false)
		{
			dset("ptCOLOR", true);
			dset("ptWBAL", true);
			dset("ptISO",true);
			dset("ptIMIN",true);
			dset("ptSHUT",true);

			if(document.getElementById('iso8').checked === true)
			{
				//dset("ptSHUT",false);
				dset("ptEV",true);
			}
			else
			{
				//dset("ptSHUT",true);

				if(document.getElementById('shut7').checked === true || document.getElementById('shut6').checked === true) 
				{  // not shutter lock
					dset("ptEV",true);
				}
			}
			
			//if(checkedmode >= 1 && checkedmode <= 6) //Video + Audio modes
			//{
			//	dset("ptAUD",true);
			//}
			if(checkedmode >= 1 && checkedmode <= 9) //Video modes
			{
				dset("ptBITRATE", true);
			}
				
			dset("ptSHARP",true);
		}
	}
	
	if(document.getElementById("options") !== null)
	{
		if(document.getElementById("options").checked === true)
		{			
			dset("opVC", true);
			dset("opQC", true);
			dset("opDM", true);
			//dset("opBV", true);
			//dset("opLO", true);
			dset("opOR", true);
			dset("opAO", true);
			dset("opWC", true);
			dset("opLN", true);
		}
	}
	
	if(document.getElementById("actions") !== null)
	{
		if(document.getElementById("actions").checked === true)
		{
			dset("NakedTools", true);
			//dset("aS", true);
			//dset("aSM", true);
			//dset("aIT", true);
			
			if(actionmode > 10) 
			{
				dset("motionParams", true);	
				dset("aR", true);
			}
						
			if(document.getElementById("helpRange") !== null)
			{
				if(document.getElementById("helpRange").checked === true)
				{	
					if(actionmode == 11) dset("splHelp", true);
					if(actionmode == 12) dset("imuHelp", true);
					if(actionmode == 13) dset("motionHelp", true);
				}
			}
		}
		else
			actionmode = 0;
	}

	if(document.getElementById("helpBitr") !== null)
	{
		if(document.getElementById("helpBitr").checked === true)
		{	
			dset("bitrHelp", true);
		}
	}
	
	
	if(actionmode == 10)
	{	
		dset("bitrSlider", true);
	}
			
	
	cmd = dcmd(cmd,"m");  // set mode
		
	switch(checkedmode)
	{
		case 7: //TWarp
			cmd = dcmd(cmd,"fpswarp");
			break;
		case 8: //TLV
			cmd = dcmd(cmd,"fpslapse");
			break;
		case 9: //NLV	
			cmd = dcmd(cmd,"fpsnight");
			cmd = dcmd(cmd,"nightexp");
			break;
		case 11: //Burst 
			cmd = dcmd(cmd,"b");
			break;	
		case 12: //Night
			cmd = dcmd(cmd,"nightexp");
			break;
	}
	
	
	if(checkedmode <= 9)
	{
		if(checkedmode == 7 || checkedmode == 8 || checkedmode == 9) // TLV/TWarp Res/NLV
		{
			cmd = dcmd(cmd, "rt");
		}
		else
		{
			cmd = dcmd(cmd,"r"); //RES
		}
	}
		
	if(checkedmode <= 6) // video mode
	{
		cmd = dcmd(cmd,"p"); //fps
	}
	
	var zoom;
	if(checkedmode > 6) // not video	
	{
		if(checkedmode == 7) //TWarp
		{
			cmd = dcmd(cmd,"twf"); //fov		
		
			if(	(document.getElementById("twf1").checked === true) || //Wide
				(document.getElementById("twf2").checked === true) || //Linear
				(document.getElementById("twf3").checked === true) ) //Linear+HL
			{
				dset("settingsZoom", true);			
					
				zoom = parseInt(document.getElementById("zoom").value);
				zoom *= 10;
				document.getElementById("zoomtext").innerHTML = zoom+"%";	
				if(zoom == 100) zoom = 99;	
				
				cmd = cmd + zoom; //fov
			}			
			else if((document.getElementById("twf5").checked === true) || //MLM Wide
				(document.getElementById("twf6").checked === true) || //MLM Superview
				(document.getElementById("twf7").checked === true) ) //MLM Linear
			{
				if(document.getElementById("twmlmhl").checked === true)
				{
					cmd = cmd + "L"; //level MLM modes
				}
			}
		}
		else if(checkedmode == 10) //Photo
		{
			cmd = dcmd(cmd,"pf"); //fov		
		
			if(	(document.getElementById("pf1").checked === true) || //Wide
				(document.getElementById("pf2").checked === true) ) //Linear
			{
				dset("settingsZoom", true);			
					
				zoom = parseInt(document.getElementById("zoom").value);
				zoom *= 10;
				document.getElementById("zoomtext").innerHTML = zoom+"%";	
				if(zoom == 100) zoom = 99;	
				
				cmd = cmd + zoom; //fov
			}
			else if((document.getElementById("pf4").checked === true) || //MLM Wide
				(document.getElementById("pf5").checked === true)) //MLM Superview
			{
				if(document.getElementById("pmlmhl").checked === true)
				{
					cmd = cmd + "L"; //level MLM modes
				}
			}
		}
		else //Everything else
		{
			cmd = dcmd(cmd,"tlvf"); //fov		
		
			if(	(document.getElementById("tlvf1").checked === true) || //Wide
				(document.getElementById("tlvf2").checked === true) ) //Linear
			{
				dset("settingsZoom", true);			
					
				zoom = parseInt(document.getElementById("zoom").value);
				zoom *= 10;
				document.getElementById("zoomtext").innerHTML = zoom+"%";	
				if(zoom == 100) zoom = 99;	
				
				cmd = cmd + zoom; //fov
			}
		}
	}
	else
	{
		cmd = dcmd(cmd,"f"); //fov
		
		if(	(document.getElementById("f1").checked === true) || //Wide
			(document.getElementById("f3").checked === true) || //Linear
			(document.getElementById("f5").checked === true) ) //Linear+HL
		{
			dset("settingsZoom", true);			
			
			zoom = parseInt(document.getElementById("zoom").value);
			zoom *= 10;
			document.getElementById("zoomtext").innerHTML = zoom+"%";	
			if(zoom == 100) zoom = 99;	
			
			cmd = cmd + zoom; //fov
		}
		else if((document.getElementById("f6").checked === true) || //MLM Wide
			(document.getElementById("f7").checked === true) || //MLM Superview
			(document.getElementById("f8").checked === true) ) //MLM Linear
		{
			if(document.getElementById("mlmhl").checked === true)
			{
				cmd = cmd + "L"; //level MLM modes
			}
			dset("settingsZoom", false);
		}
		else
		{
			dset("settingsZoom", false);
		}
	}
	
	if(checkedmode >= 10 && checkedmode <= 13) //RAW Photo modes
		cmd = dcmd(cmd,"raw"); //raw photo control
		
	if(document.getElementById("sm") !== null)
	{
		if(document.getElementById("sm").checked === true)
		{
			var pos = dcmd("","sp");	
			if(document.getElementById("sl").checked === true)
			{
				cmd = dcmd(cmd,"sl") + pos; //spot Lock
			}
			else
			{
				cmd = dcmd(cmd,"sm") + pos; //spotMeter
			}
		}
	}
	
	if(document.getElementById("pt").checked === true)
	{
		if(document.getElementById("ptr").checked === true)
		{
			cmd = cmd + "t0"; //protune reset
		}
		else
		{
			cmd = cmd + "t"; //protune
		}
	}
	cmd = dcmd(cmd,"eis"); //eis
	cmd = dcmd(cmd,"hind"); //hindsight
	cmd = dcmd(cmd,"dur"); //duration
	cmd = dcmd(cmd,"all"); //auto low light	
	cmd = dcmd(cmd,"audt"); //audio control
	
		
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
		if(document.getElementById("pt").checked === true && document.getElementById("ptr").checked === false)
		{
			cmd = dcmd(cmd,"ptc"); //color
			cmd = dcmd(cmd,"br"); //bitrate
			cmd = dcmd(cmd,"wb"); //wb
			
			if(document.getElementById('iso8').checked === false)
			{
				cmd = dcmd(cmd,"iso"); //iso max
				if(document.getElementById('isomin8').checked === false)
				{
					let isomin = dcmd("","isomin"); //min
					let isomax = dcmd("","iso");    //max
				
					var min = parseInt(isomin.substring(1));
					var max = parseInt(isomax.substring(1));
					
					if(max < min)
					{
						if(max == 1) document.getElementById('isomin1').checked = true;
						if(max == 2) document.getElementById('isomin2').checked = true;
						if(max == 4) document.getElementById('isomin3').checked = true;
						if(max == 8) document.getElementById('isomin4').checked = true;
						if(max == 16) document.getElementById('isomin5').checked = true;
						if(max == 32) document.getElementById('isomin6').checked = true;
						cmd = cmd + "M" + max;    //set the min to match the max iso
					}
					else
						cmd = dcmd(cmd,"isomin"); //add iso min
						
					if(document.getElementById('shut7').checked === false)
					{
						//cmd = dcmd(cmd,"iso"); //iso max
						cmd = dcmd(cmd,"shut");  //shutter angle
					}
				}
				else if(document.getElementById('shut7').checked === false)
				{
					cmd = dcmd(cmd,"shut"); //shutter angle
				}
			} 
			else if(document.getElementById('isomin8').checked === false)
			{
				cmd = cmd + "i64"; //ADD fake ISO max
				cmd = dcmd(cmd,"isomin");//iso min
				if(document.getElementById('shut7').checked === false)
				{
					//cmd = cmd + "i64"; //ADD fake max
					cmd = dcmd(cmd,"shut"); //shutter angle
				}
			}
			else if(document.getElementById('shut7').checked === false)
			{
				cmd = cmd + "i64"; //ADD fake ISO max
				cmd = dcmd(cmd,"shut"); //shutter angle				
			}
								
			cmd = dcmd(cmd,"ev"); //ev
			cmd = dcmd(cmd,"sharp"); //sharp
			//cmd = dcmd(cmd,"aud"); //audio control
			cmd = dcmd(cmd,"bit"); //bitrate control
		}
	}
	
	
	if(document.getElementById("options") !== null)
	{
		if(document.getElementById("options").checked === true)
		{
			var opt = ""; 
			var addO = "o";
			cmd = dcmd(cmd,"gps");
			cmd = dcmd(cmd,"vc");
			cmd = dcmd(cmd,"qc");
			cmd = dcmd(cmd,"dm");
			
			opt = dcmd(addO, "bv"); if(opt != "o") { cmd = cmd + opt; addO = ""; }
			opt = dcmd(addO, "db"); if(opt != "o") { cmd = cmd + opt; addO = ""; }
			opt = dcmd(addO, "lo"); if(opt != "o") { cmd = cmd + opt; addO = ""; }
			opt = dcmd(addO, "or"); if(opt != "o") { cmd = cmd + opt; addO = ""; }
			opt = dcmd(addO, "ao"); if(opt != "o") { cmd = cmd + opt; addO = ""; }
			opt = dcmd(addO, "so"); if(opt != "o") { cmd = cmd + opt; addO = ""; }
			opt = dcmd(addO, "wc"); if(opt != "o") { cmd = cmd + opt; addO = ""; }
			opt = dcmd(addO, "ln"); if(opt != "o") { cmd = cmd + opt; addO = ""; }
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
	
	if((dt === true && actionmode<11) || (dt === true && actionmode>=11 && document.getElementById("repeat").checked === false && document.getElementById("boot").checked === false))
	{
		//dset("opDTS", true);
		dset("copyshow", false);   // don't what user printing or sharing code with wrong date and time
	
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
		dset("copyshow", true);
		
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
		//var S_added = 0;
		//var SM_added = 0;
		
		cmd = dcmd(cmd,"sap"); //naked action
		
		if(actionmode >= 11)
		{
			if(document.getElementById("mstart") !== null)
			{		
				var mstart = document.getElementById("mstart").value;
				
				if(mstart <= 0) mstart = 6;
				if(actionmode == 11 ) //audio trigger
				{
					while(mstart <= 30) mstart*=10;
					if(mstart > 120) mstart = 120;
				}
				else
					if(mstart > 9) mstart = 9;
							
				cmd = cmd + mstart;	
			
				/*if(document.getElementById("mend") !== null)
				{
					var mend = document.getElementById("mend").value;
					if(mend > 0 && SM_added)
					{
						cmd = cmd + "-" + mend;
					}
				}*/
				if(document.getElementById("dhold") !== null)
				{
					var dhold = document.getElementById("dhold").value;
					if(dhold > 0)
					{
						cmd = cmd + "D" + dhold;
					}
				}
				if(document.getElementById("mhold") !== null)
				{
					var mhold = document.getElementById("mhold").value;
					if(mhold > 0)
					{
						cmd = cmd + "H" + mhold;
					}
				}
			}	
		}
		
		if(actionmode>=11 && document.getElementById("repeat").checked === true)
		{
			cmd = cmd + "!" + "R";
			document.getElementById("dt").checked = false;
		}
	}
	
	
    if(document.getElementById("bitr") !== null)
    {
	  var bitrate = parseInt(document.getElementById("bitr").value);
      document.getElementById("bitrtext").innerHTML = bitrate + "Mb/s";
	  
	  if(actionmode == 10)
	  {
		  cmd = cmd + bitrate;
	  }
	}
	
	if(document.getElementById("addcmd") !== null)
	{
		cmd = cmd + document.getElementById("addcmd").value;
	}
	
	
	if(document.getElementById("boot").checked === true)
	{
		cmd = "!MQRDR=1!MBOOT=\"!Lboot\"!SAVEboot=" + cmd;
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
			document.getElementById("qrtext").innerHTML = cmd;
			clipcopy = "https://gopro.github.io/labs/control/set/?cmd=" + cmd;
			document.getElementById("urltext").innerHTML = clipcopy;
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
		for (i = 1; i < 30; i++) { 
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
startTime();

</script>
