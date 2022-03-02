#  GoPro QR Code Creator

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

Create a custom camera mode, and even start a capture all through QR Codes. This is the fastest way to access many of the new GoPro Labs' firmware features. 
**†** indicates the control requires HERO10 Labs 1.20 or better. Many features of this page are also available as a mobile app.<br>
Install from: [![google play](../google-play-small.png)](https://play.google.com/store/apps/details?id=com.miscdata.qrcontrol)
[![apple app store](../apple-store-small.png)](https://apps.apple.com/us/app/gopro-app/id1518134202)

<b>Camera Mode:</b>&nbsp;&nbsp;<input type="radio" id="m19" name="mode" value="" checked> <label for="m19">not set</label><br>
  <input type="radio" id="m1" name="mode" value="mV"> <label  for="m1">Video </label>&nbsp;&nbsp;
  <input type="radio" id="m2" name="mode" value="mVP"> <label for="m2">Performance†</label>&nbsp;&nbsp;
  <input type="radio" id="m3" name="mode" value="mVE"> <label for="m3">Endurance†</label>&nbsp;&nbsp;
  <input type="radio" id="m4" name="mode" value="mVS"> <label for="m4">Stationary†</label><br>
  **Presets †:** 
  <input type="radio" id="m5" name="mode" value="mV0"> <label for="m5">Standard</label>&nbsp;&nbsp;
  <input type="radio" id="m6" name="mode" value="mV1"> <label for="m6">Activity</label>&nbsp;&nbsp;
  <input type="radio" id="m7" name="mode" value="mV2"> <label for="m7">Cinematic</label>&nbsp;&nbsp;
  <input type="radio" id="m8" name="mode" value="mV4"> <label for="m8">SloMo</label>&nbsp;&nbsp;
  <input type="radio" id="m9" name="mode" value="mV5"> <label for="m9">Basic</label><br>
  **VideoTL-Modes:** 
  <input type="radio" id="m10" name="mode" value="mTW"> <label for="m10">TimeWarp</label>&nbsp;&nbsp;
  <input type="radio" id="m11" name="mode" value="mT"> <label  for="m11">Timelapse</label>&nbsp;&nbsp;
  <input type="radio" id="m12" name="mode" value="mNL"> <label for="m12">Nightlapse</label><br>
  **Photo-Modes:** 
  <input type="radio" id="m13" name="mode" value="mP">  <label for="m13">Photo</label>&nbsp;&nbsp;
  <input type="radio" id="m14" name="mode" value="mPB"> <label for="m14">Burst</label>&nbsp;&nbsp;
  <input type="radio" id="m15" name="mode" value="mL">  <label for="m15">Live Burst</label>&nbsp;&nbsp;
  <input type="radio" id="m16" name="mode" value="mPN"> <label for="m16">Night</label>&nbsp;&nbsp;
  <input type="radio" id="m17" name="mode" value="mTP"> <label for="m17">Timelapse</label>&nbsp;&nbsp;
  <input type="radio" id="m18" name="mode" value="mNP"> <label for="m18">Nightlapse</label><br>

<div id="noteMODE" style="font-size:13px;">
<b>Time/Night-Lapse modes:</b> The camera defaults to having presets for only one time-lapse mode and one night-lapse mode, yet both modes have two configurations (video or photo.) For all QR Code mode commands to work, a preset is needed for every mode you wish to use. e.g. If you only have a preset for night-lapse video (NLV), the QR command for NLV will work, but will not for night-lapse photo (NLP). To solve this, create a new preset for NLP, and both video and photo night-lapse commands will work.<br><br>
</div>

<div id="settingsRES">
<b>Video Resolution:</b>&nbsp;&nbsp;<input type="radio" id="r10" name="res" value="" checked> <label for="r10">not set</label><br>
  <input type="radio" id="r1" name="res" value="r1080"> <label for="r1">1080p </label>&nbsp;&nbsp;
  <input type="radio" id="r2" name="res" value="r1440"> <label for="r2">1440p </label>&nbsp;&nbsp;
  <input type="radio" id="r3" name="res" value="r27"  > <label for="r3">2.7k  </label>&nbsp;&nbsp;
  <input type="radio" id="r4" name="res" value="r27T" > <label for="r4">2.7k 4x3 </label>&nbsp;&nbsp;
  <input type="radio" id="r5" name="res" value="r3"   > <label for="r5">3k 360°</label>&nbsp;&nbsp;
  <input type="radio" id="r6" name="res" value="r4"   > <label for="r6">4k </label>&nbsp;&nbsp;
  <input type="radio" id="r7" name="res" value="r4T"  > <label for="r7">4k 4x3 </label>&nbsp;&nbsp;
  <input type="radio" id="r8" name="res" value="r5"   > <label for="r8">5.3k </label>&nbsp;&nbsp;
  <input type="radio" id="r9" name="res" value="r5T"  > <label for="r9">5k 4x3† </label><br><br>
</div>

<div id="settingsRESTLV">
<b>Video Resolution:</b>&nbsp;&nbsp;
  <input type="radio" id="rt1" name="restlv" value="r1080"> <label for="rt1">1080p </label>&nbsp;&nbsp;
  <input type="radio" id="rt2" name="restlv" value="r27" >  <label for="rt2">2.7k </label>&nbsp;&nbsp;
  <input type="radio" id="rt3" name="restlv" value="r27T" > <label for="rt3">2.7k 4x3 </label>&nbsp;&nbsp;
  <input type="radio" id="rt4" name="restlv" value="r4"   > <label for="rt4">4k </label>&nbsp;&nbsp;
  <input type="radio" id="rt5" name="restlv" value="r4T"  > <label for="rt5">4k 4x3† </label>&nbsp;&nbsp;
  <input type="radio" id="rt6" name="restlv" value="" checked> <label for="rt6">not set</label><br><br>
 </div>
 
<div id="settingsFPS">
<b>FPS Video:</b>&nbsp;&nbsp;<input type="radio" id="p10" name="fps" value="" checked> <label for="p10">not set</label><br>
  <input type="radio" id="p1" name="fps" value="p24">  <label for="p1">24 </label>&nbsp;&nbsp;
  <input type="radio" id="p2" name="fps" value="p25">  <label for="p2">25 </label>&nbsp;&nbsp;
  <input type="radio" id="p3" name="fps" value="p30">  <label for="p3">30 </label>&nbsp;&nbsp;
  <input type="radio" id="p4" name="fps" value="p50">  <label for="p4">50 </label>&nbsp;&nbsp;
  <input type="radio" id="p5" name="fps" value="p60">  <label for="p5">60 </label>&nbsp;&nbsp;
  <input type="radio" id="p6" name="fps" value="p100"> <label for="p6">100 </label>&nbsp;&nbsp;
  <input type="radio" id="p7" name="fps" value="p120"> <label for="p7">120 </label>&nbsp;&nbsp;
  <input type="radio" id="p8" name="fps" value="p200"> <label for="p8">200 </label>&nbsp;&nbsp;
  <input type="radio" id="p9" name="fps" value="p240"> <label for="p9">240 </label><br><br>
</div>

<div id="settingsFOV">
<b>Lens:</b>
  <input type="radio" id="f1" name="fov" value="fW"> <label for="f1">Wide </label>&nbsp;&nbsp;
 <!-- <input type="radio" id="f2" name="fov" value="fM"> <label for="f2">Medium </label>&nbsp;&nbsp; -->
  <input type="radio" id="f2" name="fov" value="fN"> <label for="f2">Narrow </label>&nbsp;&nbsp;
  <input type="radio" id="f3" name="fov" value="fL"> <label for="f3">Linear </label>&nbsp;&nbsp;
  <input type="radio" id="f4" name="fov" value="fS"> <label for="f4">Superview </label>&nbsp;&nbsp;
  <input type="radio" id="f5" name="fov" value="fH"> <label for="f5">Linear+HL </label><br>
  Max Lens Mod:  <input type="radio" id="f6" name="fov" value="oX1fW"> <label for="f6">Enable Wide </label>&nbsp;&nbsp;
  <input type="radio" id="f7" name="fov" value="oX1fX"> <label for="f7">Enable Superview </label>&nbsp;&nbsp;
  <input type="radio" id="f8" name="fov" value="oX0"> <label for="f8">Disable MLM</label>&nbsp;&nbsp;
  <input type="radio" id="f9" name="fov" value="" checked> <label for="f9">not set</label><br><br>
 </div>
 
<div id="settingsPFOV">
<b>Lens:</b>
  <input type="radio" id="pf1" name="pfov" value="fW"> <label for="pf1">Wide </label>&nbsp;&nbsp;
  <input type="radio" id="pf2" name="pfov" value="fL"> <label for="pf2">Linear </label>&nbsp;&nbsp;
  <input type="radio" id="pf3" name="pfov" value="fN"> <label for="pf3">Narrow </label><br>
  Max Lens Mod:  <input type="radio" id="pf4" name="pfov" value="oX1fW"> <label for="pf4">Enable Wide </label>&nbsp;&nbsp;
  <input type="radio" id="pf5" name="pfov" value="oX1fX"> <label for="pf5">Enable Superview </label>&nbsp;&nbsp;
  <input type="radio" id="pf6" name="pfov" value="oX0"> <label for="pf6">Disable MLM</label>&nbsp;&nbsp;
  <input type="radio" id="pf7" name="pfov" value="" checked> <label for="pf7">not set</label><br><br>
 </div>
  
 
<div id="settingsTLVFOV">
<b>Lens:</b>
  <input type="radio" id="tlvf1" name="tlvfov" value="fW"> <label for="tlvf1">Wide </label>&nbsp;&nbsp;
  <input type="radio" id="tlvf2" name="tlvfov" value="fL"> <label for="tlvf2">Linear </label>&nbsp;&nbsp;
  <input type="radio" id="tlvf3" name="tlvfov" value="fN"> <label for="tlvf3">Narrow </label>&nbsp;&nbsp;  
  <input type="radio" id="tlvf4" name="tlvfov" value="" checked> <label for="tlvf4">not set</label><br><br>
 </div>
  
<div id="settingsTWFOV">
<b>Lens:</b>
  <input type="radio" id="twf1" name="twfov" value="fW"> <label for="twf1">Wide </label>&nbsp;&nbsp;
  <input type="radio" id="twf2" name="twfov" value="fL"> <label for="twf2">Linear </label>&nbsp;&nbsp;
  <input type="radio" id="twf3" name="twfov" value="fH"> <label for="twf3">Linear+HL </label>&nbsp;&nbsp;
  <input type="radio" id="twf4" name="twfov" value="fN"> <label for="twf4">Narrow </label>&nbsp;&nbsp;  <br>
  Max Lens Mod:  <input type="radio" id="twf5" name="twfov" value="oX1fW"> <label for="twf5">Enable Wide </label>&nbsp;&nbsp;
  <input type="radio" id="twf6" name="twfov" value="oX1fX"> <label for="twf6">Enable Superview </label>&nbsp;&nbsp;
  <input type="radio" id="twf7" name="twfov" value="oX0"> <label for="twf7">Disable MLM</label>&nbsp;&nbsp;
  <input type="radio" id="twf8" name="twfov" value="" checked> <label for="twf8">not set</label><br><br>
 </div>
 
 
<div id="settingsZoom">
 <b>Zoom:</b> <input type="range" id="zoom" name="zoom" min="0" max="10" value="0"><label for="zoom"></label>&nbsp;&nbsp;<b id="zoomtext"></b><br><br>
</div>

<div id="settingsBurst">
<b>Burst Style:</b>&nbsp;&nbsp;
  <input type="radio" id="b1" name="burst" value="bA"> <label for="b1">Auto </label>&nbsp;&nbsp;
  <input type="radio" id="b2" name="burst" value="b3N1"> <label for="b2">3/1 </label>&nbsp;&nbsp;
  <input type="radio" id="b3" name="burst" value="b5N1"> <label for="b3">5/1 </label>&nbsp;&nbsp;
  <input type="radio" id="b4" name="burst" value="b10N1"> <label for="b4">10/1 </label>&nbsp;&nbsp;
  <input type="radio" id="b5" name="burst" value="b25N1"> <label for="b5">25/1 </label><br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <input type="radio" id="b6" name="burst" value="b10N2"> <label for="b6">10/2 </label>&nbsp;&nbsp;
  <input type="radio" id="b7" name="burst" value="b10N3"> <label for="b7">10/3 </label>&nbsp;&nbsp;
  <input type="radio" id="b8" name="burst" value="b30N3"> <label for="b8">30/3 </label>&nbsp;&nbsp;
  <input type="radio" id="b9" name="burst" value="b30N6"> <label for="b9">30/6 </label>&nbsp;&nbsp;
  <input type="radio" id="b10" name="burst" value="b30N10"> <label for="b10">30/10 </label>&nbsp;&nbsp;
  <input type="radio" id="b11" name="burst" value="" checked> <label for="b11">not set</label><br><br>
</div>

<div id="settingsTimewarp">
<b>TimeWarp Speed:</b>&nbsp;&nbsp;
  <input type="radio" id="fpswarp1"    name="fpswarp" value="p15"> <label for="fpswarp1">2X </label>&nbsp;&nbsp;
  <input type="radio" id="fpswarp2"    name="fpswarp" value="p6"> <label for="fpswarp2">5X </label>&nbsp;&nbsp;
  <input type="radio" id="fpswarp3"    name="fpswarp" value="p3"> <label for="fpswarp3">10X </label>&nbsp;&nbsp;
  <input type="radio" id="fpswarp4"    name="fpswarp" value="p2"> <label for="fpswarp4">15X </label>&nbsp;&nbsp;
  <input type="radio" id="fpswarp5"    name="fpswarp" value="p1"> <label for="fpswarp5">30X </label>&nbsp;&nbsp;
  <input type="radio" id="fpswarp6"    name="fpswarp" value="pA"> <label for="fpswarp6">Auto </label>&nbsp;&nbsp;
  <input type="radio" id="fpswarp7"    name="fpswarp" value="" checked> <label for="fpswarp7">not set</label><br><br>
</div>
 
 
<div id="settingsTimelapse">
<b>Timelapse Interval:</b>&nbsp;&nbsp;
  <input type="radio" id="fpslapse1"    name="fpslapse" value="p2"> <label for="fpslapse1">0.5s </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse2"    name="fpslapse" value="p1"> <label for="fpslapse2">1s </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse3"   name="fpslapse" value="p.2"> <label for="fpslapse3">2s </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse4"   name="fpslapse" value="p.5"> <label for="fpslapse4">5s </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse5"  name="fpslapse" value="p.10"> <label for="fpslapse5">10s </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse6"  name="fpslapse" value="p.30"> <label for="fpslapse6">30s </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse7" name="fpslapse" value="p.60"> <label for="fpslapse7">60s </label>&nbsp;&nbsp;<br>
  
  &nbsp;&nbsp;&nbsp;&nbsp;HERO 8/9&nbsp;&nbsp; <input type="radio" id="fpslapse8"  name="fpslapse" value="p.120" > <label for="fpslapse8">2min </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse9"  name="fpslapse" value="p.300" > <label for="fpslapse9">5min </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse10" name="fpslapse" value="p.1800"> <label for="fpslapse10">30min </label>&nbsp;&nbsp;
  <input type="radio" id="fpslapse11" name="fpslapse" value="p.3600"> <label for="fpslapse11">60min </label>&nbsp;&nbsp;
  
  <input type="radio" id="fpslapse12" name="fpslapse" value="" checked> <label for="fpslapse12">not set</label><br><br>
</div>
 
<div id="settingsNightlapse">
<b>Nightlapse Interval:</b>&nbsp;&nbsp;
  <input type="radio" id="fpsnight1" name="fpsnight" value="p"     > <label for="fpsnight1">Auto </label>&nbsp;&nbsp;
  <input type="radio" id="fpsnight2" name="fpsnight" value="p.4"  >  <label for="fpsnight2">4s </label>&nbsp;&nbsp;
  <input type="radio" id="fpsnight3" name="fpsnight" value="p.5"  >  <label for="fpsnight3">5s </label>&nbsp;&nbsp;
  <input type="radio" id="fpsnight4" name="fpsnight" value="p.10"  > <label for="fpsnight4">10s </label>&nbsp;&nbsp;
  <input type="radio" id="fpsnight5" name="fpsnight" value="p.15"  > <label for="fpsnight5">15s </label>&nbsp;&nbsp;
  <input type="radio" id="fpsnight6" name="fpsnight" value="p.20"  > <label for="fpsnight6">20s </label>&nbsp;&nbsp;
  <input type="radio" id="fpsnight7" name="fpsnight" value="p.30"  > <label for="fpsnight7">30s </label>&nbsp;&nbsp;
  <input type="radio" id="fpsnight8" name="fpsnight" value="p.60"  > <label for="fpsnight8">60s </label><br>&nbsp;&nbsp;
  <input type="radio" id="fpsnight9" name="fpsnight" value="p.120" > <label for="fpsnight9">2min </label>&nbsp;&nbsp;
  <input type="radio" id="fpsnight10" name="fpsnight" value="p.300" > <label for="fpsnight10">5min </label>&nbsp;&nbsp;
  <input type="radio" id="fpsnight11" name="fpsnight" value="p.1800"> <label for="fpsnight11">30min </label>&nbsp;&nbsp;
  <input type="radio" id="fpsnight12" name="fpsnight" value="p.3600"> <label for="fpsnight12">60min </label>&nbsp;&nbsp;
  <input type="radio" id="fpsnight13" name="fpsnight" value="" checked> <label for="fpsnight13">not set</label><br><br>
</div>

<div id="settingsNightexposure">
<b>Shutter:</b>&nbsp;&nbsp;
  <input type="radio" id="nightexp1" name="nightexp" value="eA" > <label for="nightexp1">auto </label>&nbsp;&nbsp;
  <input type="radio" id="nightexp2" name="nightexp" value="e2" > <label for="nightexp2">2s </label>&nbsp;&nbsp;
  <input type="radio" id="nightexp3" name="nightexp" value="e5" > <label for="nightexp3">5s </label>&nbsp;&nbsp;
  <input type="radio" id="nightexp4" name="nightexp" value="e10"> <label for="nightexp4">10s </label>&nbsp;&nbsp;
  <input type="radio" id="nightexp5" name="nightexp" value="e15"> <label for="nightexp5">15s </label>&nbsp;&nbsp;
  <input type="radio" id="nightexp6" name="nightexp" value="e20"> <label for="nightexp6">20s </label>&nbsp;&nbsp;
  <input type="radio" id="nightexp7" name="nightexp" value="e30"> <label for="nightexp7">30s </label>&nbsp;&nbsp;
  <input type="radio" id="nightexp8" name="nightexp" value="" checked> <label for="nightexp8"> not set</label><br><br>
</div>

<div id="settingsVideo">
<b>Hypersmooth:</b>&nbsp;&nbsp;
	<input type="radio" id="eis1" name="eis" value="e0"> <label for="eis1">Off</label>&nbsp;&nbsp;&nbsp;
	<input type="radio" id="eis2" name="eis" value="e1"> <label for="eis2">On</label>&nbsp;&nbsp;&nbsp;
	<input type="radio" id="eis3" name="eis" value="e2"> <label for="eis3">High</label>&nbsp;&nbsp;&nbsp;
	<input type="radio" id="eis4" name="eis" value="e3"> <label for="eis4">Boost</label>&nbsp;&nbsp;&nbsp;
	<input type="radio" id="eis5" name="eis" value="" checked> <label for="eis5">not set</label><br><br>
</div>

<div id="settingsHindsight">
<b>Hindsight (HERO9/10):</b>&nbsp;&nbsp;
	<input type="radio" id="hind1" name="hind" value="hS0"> <label for="hind1">Off</label>&nbsp;&nbsp;&nbsp;
	<input type="radio" id="hind2" name="hind" value="hS1"> <label for="hind2">15s</label>&nbsp;&nbsp;&nbsp;
	<input type="radio" id="hind3" name="hind" value="hS2"> <label for="hind3">30s</label>&nbsp;&nbsp;&nbsp;
	<input type="radio" id="hind4" name="hind" value="" checked> <label for="hind4">not set</label><br><br>
</div>
					
<div id="settingsDuration">
<b>Duration (HERO9/10):</b>&nbsp;&nbsp;
	<input type="radio" id="dur1" name="dur" value="dR0"> <label for="dur1">Off</label>&nbsp;&nbsp;
	<input type="radio" id="dur2" name="dur" value="dR15"> <label for="dur2">15s</label>&nbsp;&nbsp;
	<input type="radio" id="dur3" name="dur" value="dR30"> <label for="dur3">30s</label>&nbsp;&nbsp;
	<input type="radio" id="dur4" name="dur" value="dR60"> <label for="dur4">1min</label>&nbsp;&nbsp;
	<input type="radio" id="dur5" name="dur" value="dR300"> <label for="dur5">5min</label>&nbsp;&nbsp;
	<input type="radio" id="dur6" name="dur" value="dR900"> <label for="dur6">15min</label>&nbsp;&nbsp;
	<input type="radio" id="dur7" name="dur" value="dR1800"> <label for="dur7">30min</label><br>
	<input type="radio" id="dur8" name="dur" value="dR3600"> <label for="dur8">1hour</label>&nbsp;&nbsp;
	<input type="radio" id="dur9" name="dur" value="dR7200"> <label for="dur9">2hour</label>&nbsp;&nbsp;
	<input type="radio" id="dur10" name="dur" value="dR9999"> <label for="dur10">3hour</label>&nbsp;&nbsp;
	<input type="radio" id="dur11" name="dur" value="" checked> <label for="dur11">not set</label><br><br>
</div>

<div id="settingsPhotoRAW">
<b>Photo Properties:</b><br>
  <input type="radio" id="raw1" name="raw" value="r0"> <label for="raw1">JPEG only</label>&nbsp;&nbsp;
  <input type="radio" id="raw2" name="raw" value="r"> <label for="raw2">Raw + JPEG</label>&nbsp;&nbsp;
  <input type="radio" id="raw3" name="raw" value="" checked> <label for="raw3"> not set</label><br><br>
</div>

<div id="settingsAUDT">
<b>Audio Type:</b>&nbsp;&nbsp;
  <input type="radio" id="audt1" name="audt" value="aA"> <label for="audt1">Auto </label>&nbsp;&nbsp;
  <input type="radio" id="audt2" name="audt" value="aS"> <label for="audt2">Stereo </label>&nbsp;&nbsp;
  <input type="radio" id="audt3" name="audt" value="aW"> <label for="audt3">Wind</label>&nbsp;&nbsp;
  <input type="radio" id="audt4" name="audt" value="" checked> <label for="audt4"> not set</label><br><br>
</div>
<input type="checkbox" id="sm" value="oSM"> <label for="sm">Spot Metering (H10) † </label><br>
<div id="spotMeter">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="sp1" name="placement" value="25,25"> <label for="sp1">Top Left    </label>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<input type="radio" id="sp2" name="placement" value="50,25"> <label for="sp2">Top Center  </label>&nbsp;&nbsp;&nbsp;&nbsp;
<input type="radio" id="sp3" name="placement" value="75,25"> <label for="sp3">Top Right   </label><br>&nbsp;&nbsp;&nbsp;&nbsp;
<input type="radio" id="sp4" name="placement" value="25,50"> <label for="sp4">Mid Left    </label>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<input type="radio" id="sp5" name="placement" value="50,50" checked> <label for="sp5">Center    </label>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<input type="radio" id="sp6" name="placement" value="75,50"> <label for="sp6">Mid Right   </label><br>&nbsp;&nbsp;&nbsp;&nbsp;
<input type="radio" id="sp7" name="placement" value="25,75"> <label for="sp7">Lower Left  </label>&nbsp;&nbsp;
<input type="radio" id="sp8" name="placement" value="50,75"> <label for="sp8">Lower Center</label>&nbsp;
<input type="radio" id="sp9" name="placement" value="75,75"> <label for="sp9">Lower Right </label>&nbsp;<br>&nbsp;&nbsp;&nbsp;&nbsp;
<input type="radio" id="sp10" name="placement" value="0"> <label for="sp10">Disable </label><br>&nbsp;&nbsp;&nbsp;&nbsp;
<input type="checkbox" id="sl" value="oSM0!2NoSL"> <label for="sl">Exposure Lock 3s after scan (to avoid locking on the QR Code)</label><br>
</div>
<div id="settingsPT">
<input type="checkbox" id="pt" value="t"> <label for="pt">Protune Controls</label><br>
</div>
<div id="settingsPTR">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Protune Reset:</b>&nbsp;&nbsp;
<input type="checkbox" id="ptr" value="t0"> <label for="ptr"> </label><br>
</div>
<div id="ptCOLOR">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Protune Color:</b>&nbsp;&nbsp;
  <input type="radio" id="ptc1" name="ptc" value="cG"> <label for="ptc1">GoPro</label>&nbsp;&nbsp;
  <input type="radio" id="ptc2" name="ptc" value="cN"> <label for="ptc2">Natural†</label>&nbsp;&nbsp;
  <input type="radio" id="ptc3" name="ptc" value="cF"> <label for="ptc3">Flat</label>&nbsp;&nbsp;
  <input type="radio" id="ptc4" name="ptc" value="" checked> <label for="ptc4">not set</label>
</div>
<div id="ptBITRATE">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Bit rate:</b>&nbsp;&nbsp;
  <input type="radio" id="br1" name="br" value="b0"> <label for="br1">Standard</label>&nbsp;&nbsp;
  <input type="radio" id="br2" name="br" value="b1"> <label for="br2">High</label>&nbsp;&nbsp;
  <input type="radio" id="br3" name="br" value="" checked> <label for="br3">not set</label>
</div>
<div id="ptWBAL">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>White Balance:</b>&nbsp;&nbsp;
  <input type="radio" id="wb1" name="wb" value="wA" checked> <label for="wb1">Auto </label>&nbsp;&nbsp;
  <input type="radio" id="wb2" name="wb" value="w23" > <label for="wb2">2300K </label>&nbsp;&nbsp;
  <input type="radio" id="wb3" name="wb" value="w28" > <label for="wb3">2800K </label>&nbsp;&nbsp;
  <input type="radio" id="wb4" name="wb" value="w32" > <label for="wb4">3200K </label>&nbsp;&nbsp;
  <input type="radio" id="wb5" name="wb" value="w40" > <label for="wb5">4000K </label>&nbsp;&nbsp;
  <input type="radio" id="wb6" name="wb" value="w45" > <label for="wb6">4500K </label>&nbsp;<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <input type="radio" id="wb7" name="wb" value="w50" > <label for="wb7">5000K </label>&nbsp;&nbsp;
  <input type="radio" id="wb8" name="wb" value="w55" > <label for="wb8">5500K </label>&nbsp;&nbsp;
  <input type="radio" id="wb9" name="wb" value="w60"> <label for="wb9">6000K </label>&nbsp;&nbsp;
  <input type="radio" id="wb10" name="wb" value="w65"> <label for="wb10">6500K </label>&nbsp;&nbsp;
  <input type="radio" id="wb11" name="wb" value="wN" > <label for="wb11">Native </label>&nbsp;&nbsp;
  <input type="radio" id="wb12" name="wb" value="" checked> <label for="wb12">not set</label>
 </div>
<div id="ptIMIN">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>ISO Min:</b>&nbsp;&nbsp;
  <input type="radio" id="isomin1" name="isomin" value="M1" > <label for="isomin1">100 (def) </label>&nbsp;&nbsp;
  <input type="radio" id="isomin2" name="isomin" value="M2" > <label for="isomin2">200 </label>&nbsp;&nbsp;
  <input type="radio" id="isomin3" name="isomin" value="M4" > <label for="isomin3">400 </label>&nbsp;&nbsp;
  <input type="radio" id="isomin4" name="isomin" value="M8" > <label for="isomin4">800 </label>&nbsp;&nbsp;
  <input type="radio" id="isomin5" name="isomin" value="M16"> <label for="isomin5">1600 </label>&nbsp;&nbsp;
  <input type="radio" id="isomin6" name="isomin" value="M32"> <label for="isomin6">3200 </label>&nbsp;&nbsp;
  <input type="radio" id="isomin7" name="isomin" value="M64"> <label for="isomin7">6400 </label>&nbsp;&nbsp;
  <input type="radio" id="isomin8" name="isomin" value="M1" checked> <label for="isomin8">not set</label>
 </div>
<div id="ptISO">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>ISO Max:</b>&nbsp;&nbsp;
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
<div id="ptAUD">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>RAW Audio:</b>&nbsp;&nbsp;
  <input type="radio" id="aud1" name="aud" value="a"> <label for="aud1">Off </label>&nbsp;&nbsp;
  <input type="radio" id="aud2" name="aud" value="aL"> <label for="aud2">Low </label>&nbsp;&nbsp;
  <input type="radio" id="aud3" name="aud" value="aM"> <label for="aud3">Medium </label>&nbsp;&nbsp;
  <input type="radio" id="aud4" name="aud" value="aH"> <label for="aud4">High</label>&nbsp;&nbsp;
  <input type="radio" id="aud5" name="aud" value="" checked> <label for="aud5">not set</label><br>
</div>

<div id="cameraOptions">
<input type="checkbox" id="options" value=""> <label for="options">Camera Preferences</label><br>
</div>

<div id="opGPS">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>GPS:</b>&nbsp;&nbsp;
  <input type="radio" id="gps1" name="gps" value="g0"> <label for="gps1">off </label>&nbsp;&nbsp;
  <input type="radio" id="gps2" name="gps" value="g1"> <label for="gps2">on </label>&nbsp;&nbsp;
  <input type="radio" id="gps3" name="gps" value="" checked> <label for="gps3">not set </label>
</div>
<div id="opVC">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Voice Control:</b>&nbsp;&nbsp; 
  <input type="radio" id="vc1" name="vc" value="v0"> <label for="vc1">off </label>&nbsp;&nbsp;
  <input type="radio" id="vc2" name="vc" value="v1"> <label for="vc2">on </label>&nbsp;&nbsp;
  <input type="radio" id="vc3" name="vc" value="" checked> <label for="vc3">not set</label>
 </div>
<div id="opQC">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Quick Capture:</b>&nbsp;&nbsp;  
  <input type="radio" id="qc1" name="qc" value="q0"> <label for="qc1">off </label>&nbsp;&nbsp;
  <input type="radio" id="qc2" name="qc" value="q1"> <label for="qc2">on </label>&nbsp;&nbsp;
  <input type="radio" id="qc3" name="qc" value="" checked> <label for="qc3">not set </label>
  </div>
<div id="opDM">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Default Mode:</b>&nbsp;&nbsp;
  <input type="radio" id="dm1" name="dm" value="dV">  <label for="dm1">Last Used Video</label>&nbsp;&nbsp;
  <input type="radio" id="dm2" name="dm" value="dP">  <label for="dm2">Last Used Photo</label>&nbsp;&nbsp;
  <input type="radio" id="dm3" name="dm" value="dT">  <label for="dm3">Last Used Timelapse</label>&nbsp;&nbsp;
  <input type="radio" id="dm4" name="dm" value="" checked> <label for="dm4">not set</label>
</div>
<div id="opBV">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Beep Volume:</b>&nbsp;&nbsp; 
  <input type="radio" id="bv1" name="bv" value="V0"> <label for="bv1">0% </label>&nbsp;&nbsp;
  <input type="radio" id="bv2" name="bv" value="V1"> <label for="bv2">10% </label>&nbsp;&nbsp;
  <input type="radio" id="bv3" name="bv" value="V4"> <label for="bv3">40% </label>&nbsp;&nbsp;
  <input type="radio" id="bv4" name="bv" value="V7"> <label for="bv4">70% </label>&nbsp;&nbsp;
  <input type="radio" id="bv5" name="bv" value="V8"> <label for="bv5">85% </label>&nbsp;&nbsp;
  <input type="radio" id="bv6" name="bv" value="V9"> <label for="bv6">100% </label>&nbsp;&nbsp;
  <input type="radio" id="bv7" name="bv" value="" checked> <label for="bv7">not set</label>
  </div>
  
<div id="opDB">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Display Brightness:</b>&nbsp;&nbsp;
  <input type="radio" id="db1" name="db" value="B1"> <label for="db1">10% </label>&nbsp;&nbsp;
  <input type="radio" id="db2" name="db" value="B4"> <label for="db2">40% </label>&nbsp;&nbsp;
  <input type="radio" id="db3" name="db" value="B7"> <label for="db3">70% </label>&nbsp;&nbsp;
  <input type="radio" id="db4" name="db" value="B9"> <label for="db4">100% </label>&nbsp;&nbsp;
  <input type="radio" id="db5" name="db" value="" checked> <label for="db5">not set</label>
  </div>
<div id="opLO">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>LEDs On:</b>&nbsp;&nbsp;
  <input type="radio" id="lo1" name="lo" value="D0"> <label for="lo1">All Off </label>&nbsp;&nbsp;
  <input type="radio" id="lo2" name="lo" value="D2"> <label for="lo2">Rear Only </label>&nbsp;&nbsp;
  <input type="radio" id="lo3" name="lo" value="D4"> <label for="lo3">All On </label>&nbsp;&nbsp;
  <input type="radio" id="lo4" name="lo" value="" checked> <label for="lo4">not set</label>
  </div>
<div id="opOR">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Orientation Lock:</b>&nbsp;&nbsp; 
  Landscape <input type="radio" id="or1" name="or" value="R1"> <label for="or1">↑</label>&nbsp;&nbsp;&nbsp;
  <input type="radio" id="or2" name="or" value="R2"> <label for="or2">↓</label>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  Portrait <input type="radio" id="or3" name="or" value="R3"> <label for="or3">←</label>&nbsp;&nbsp;&nbsp;
  <input type="radio" id="or4" name="or" value="R4"> <label for="or4">→</label>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <input type="radio" id="or5" name="or" value="R0"> <label for="or5">Unlocked </label>&nbsp;&nbsp;
  <input type="radio" id="or6" name="or" value="" checked> <label for="or6">not set</label>
  </div>
<div id="opAO">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Camera Auto Off:</b>&nbsp;&nbsp; 
  <input type="radio" id="ao1" name="ao" value="C5"> <label for="ao1">5 mins </label>&nbsp;&nbsp;
  <input type="radio" id="ao2" name="ao" value="C15"> <label for="ao2">15 mins </label>&nbsp;&nbsp;
  <input type="radio" id="ao3" name="ao" value="C30"> <label for="ao3">30 mins </label>&nbsp;&nbsp;
  <input type="radio" id="ao4" name="ao" value="C"> <label for="ao4">Never </label>&nbsp;&nbsp;
  <input type="radio" id="ao5" name="ao" value="" checked> <label for="ao5">not set</label>
  </div>
<div id="opSO">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Screen Auto Off:</b>&nbsp;&nbsp;
  <input type="radio" id="so1" name="so" value="S1"> <label for="so1">1 mins </label>&nbsp;&nbsp;
  <input type="radio" id="so2" name="so" value="S2"> <label for="so2">2 mins </label>&nbsp;&nbsp;
  <input type="radio" id="so3" name="so" value="S3"> <label for="so3">3 mins </label>&nbsp;&nbsp;
  <input type="radio" id="so4" name="so" value="S"> <label for="so4">Never </label>&nbsp;&nbsp;
  <input type="radio" id="so5" name="so" value="" checked> <label for="so5">not set</label>
  </div>
<div id="opWC">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>WiFi Connections:</b>&nbsp;&nbsp; 
  <input type="radio" id="wc1" name="wc" value="W0"> <label for="wc1">Off </label>&nbsp;&nbsp;
  <input type="radio" id="wc2" name="wc" value="W1"> <label for="wc2">On </label>&nbsp;&nbsp;
  <input type="radio" id="wc3" name="wc" value="W2"> <label for="wc3">On 2.4GHz</label>&nbsp;&nbsp;
  <input type="radio" id="wc4" name="wc" value="W5"> <label for="wc4">On 5GHz</label>&nbsp;&nbsp;
  <input type="radio" id="wc5" name="wc" value="" checked> <label for="wc5">not set</label>
  </div>
<div id="opLN">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Voice Language:</b>&nbsp;&nbsp;
  <input type="radio" id="ln1" name="ln" value="L0"> <label for="ln1">English US </label>&nbsp;&nbsp;
  <input type="radio" id="ln2" name="ln" value="L01"> <label for="ln2">English UK </label>&nbsp;&nbsp;
  <input type="radio" id="ln3" name="ln" value="L02"> <label for="ln3">English AUS </label>&nbsp;&nbsp;
  <input type="radio" id="ln4" name="ln" value="L03"> <label for="ln4">English IND </label>&nbsp;&nbsp;<br>
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="ln5" name="ln" value="L4"> <label for="ln5">Spanish EU </label>&nbsp;&nbsp;
  <input type="radio" id="ln6" name="ln" value="L41"> <label for="ln6">Spanish NA </label>&nbsp;&nbsp;
  <input type="radio" id="ln7" name="ln" value="L1"> <label for="ln7">German </label>&nbsp;&nbsp;
  <input type="radio" id="ln8" name="ln" value="L3"> <label for="ln8">Italian </label>&nbsp;&nbsp;
  <input type="radio" id="ln9" name="ln" value="L5"> <label for="ln9">Chinese </label>&nbsp;&nbsp;
  <input type="radio" id="ln10" name="ln" value="L6"> <label for="ln10">Japanese </label>&nbsp;&nbsp;<br>
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" id="ln11" name="ln" value="L7"> <label for="ln11">Korean </label>&nbsp;&nbsp;
  <input type="radio" id="ln12" name="ln" value="L2"> <label for="ln12">French </label>&nbsp;&nbsp;
  <input type="radio" id="ln13" name="ln" value="L8"> <label for="ln13">Portuguese </label>&nbsp;&nbsp;
  <input type="radio" id="ln14" name="ln" value="L9"> <label for="ln14">Russian </label>&nbsp;&nbsp;
  <input type="radio" id="ln15" name="ln" value="L91"> <label for="ln15">Swedish </label>&nbsp;&nbsp;
  <input type="radio" id="ln16" name="ln" value="" checked> <label for="ln16">not set</label><br>
</div>


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
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>or</b> minutes after <b>sunrise</b>: <input type="text" id="risemins" value="" style="width:60px"> e.g. -30 for mins before (requires GPS)<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>or</b> minutes after <b>sunset</b>: <input type="text" id="setmins" value="" style="width:60px"> e.g. -45 for mins before (requires GPS)<br>
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
<div id="aSM">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Start via Motion Detection:</b> 
<input type="text" id="mstart" value="" style="width:60px">start <input type="text" id="mend" value="" style="width:60px">end sensitivity (1-9)<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Delay start: <input type="text" id="dhold" value="" style="width:60px"> seconds to get out of the shot.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Mask motion: <input type="text" id="mmhold" value="" style="width:60px"> seconds to learn background motion.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Hold time: <input type="text" id="mhold" value="" style="width:60px"> seconds to capture after motion stops.<br>
<br>
</div>
<div id="aSV">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Start at GPS Velocity (km/h):</b> 
<input type="text" id="vstart" value="" style="width:60px">start speed <input type="text" id="vend" value="" style="width:60px">end speed <b><br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</b> Hold time: <input type="text" id="vhold" value="" style="width:60px"> seconds)<br><br>
</div>

<div id="aR">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" id="repeat" value=""> <b><label for="repeat">Repeat Command</label></b><br></div>
<!--
<div id="aR">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Repeat command after: </b> 
<input type="text" id="repeathrs" value="" style="width:45px">hours <input type="text" id="repeatmins" value="" style="width:45px">mins <input type="text" id="repeatsecs" value="" style="width:45px">secs <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>or</b> delay for HH:MM <input type="text" id="repeattime" value="" style="width:60px"> <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>or</b> minutes after <b>sunrise</b>: <input type="text" id="repeatrisemins" value="" style="width:60px"> e.g. -30 for mins before<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>or</b> minutes after <b>sunset</b>: <input type="text" id="repeatsetmins" value="" style="width:60px"> e.g. -45 for mins before<br> 
</div>-->


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

**Compatibility:** Labs enabled [HERO5 Session](../session5), HERO7, HERO8, HERO9, HERO10 and MAX 

**HERO10 Note:** LCD must be on for the QR Code scanning to be active.<br>
        
[More features](..) for Labs enabled cameras

## version 1.52
updated: Mar 2, 2022

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
	dset("noteMODE", false);
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
	dset("ptAUD",false);
		
	dset("opGPS", false);
	dset("opVC", false);
	dset("opQC", false);
	dset("opDM", false);
	dset("opBV", false);
	dset("opDB", false);
	dset("opLO", false);
	dset("opOR", false);
	dset("opAO", false);
	dset("opSO", false);
	dset("opWC", false);
	dset("opLN", false);
	
	dset("aS", false);
	dset("aE", false);
	dset("aSD", false);
	dset("aEND", false);
	dset("aSM", false);
	dset("aSV", false);
	dset("aR", false);
	
	var checkedmode = 0;
	var x;
	
	for (i = 1; i < 19; i++) { 
		var mode = "m"+i;
		x = document.getElementById(mode).checked;
		if( x === true)
			checkedmode = i;
	}
	
	//m1 mV 
	//m2 mVP
	//m3 mVE
	//m4 mVS
	//m5 mV0
	//m6 mV1
	//m7 mV2
	//m8 mV3
	//m9 mV4
	//m10 mTW
	//m11 mT 
	//m12 mNL
	//m13 mP 
	//m14 mPB
	//m15 mL
	//m16 mPN
	//m17 mTP
	//m18 mNP
	
	switch(checkedmode)
	{
		default:
		case 1: //Video		
		case 2: //mVP
		case 3: //mVE
		case 4: //mVS
		case 5: //mV0
		case 6: //mV1
		case 7: //mV2
		case 8: //mV3
		case 9: //mV4
		dset("settingsRES", true);
		dset("settingsFPS", true);
		dset("settingsFOV", true);
		dset("settingsVideo", true);
		dset("settingsHindsight", true);
		dset("settingsDuration", true);
		dset("settingsPT", true);
		dset("settingsAUDT",true);
		break;
		
		case 10: //TimeWarp Video
		dset("settingsTimewarp", true);		
		dset("settingsDuration", true);
		dset("settingsRESTLV", true);
		dset("settingsTWFOV", true);
		dset("settingsPT", true);
		break;		
		
		case 11: //Timelapse Video
		dset("settingsTimelapse", true);	
		dset("settingsDuration", true);	
		dset("settingsRESTLV", true);
		dset("settingsTLVFOV", true);
		dset("settingsPT", true);
		dset("noteMODE", true);
		break;		
		
		case 12: //NL Video
		dset("settingsNightlapse", true);	
		dset("settingsNightexposure", true);
		dset("settingsDuration", true);		
		dset("settingsRESTLV", true);
		dset("settingsPT", true);
		dset("settingsTLVFOV", true);
		dset("noteMODE", true);
		break;
	
		case 13: //Photo
		dset("settingsPT", true);
		dset("settingsPFOV", true);
		dset("settingsPhotoRAW", true);
		break;
		
		case 14: //Burst
		dset("settingsBurst", true);
		dset("settingsPT", true);
		dset("settingsTLVFOV", true);
		dset("settingsPhotoRAW", true);
		break;
		
		case 15: //Burst Live
		dset("settingsPT", true);
		dset("settingsAUDT",true);
		break;
		
		case 16: //Night
		dset("settingsNightexposure", true);
		dset("settingsPT", true);
		dset("settingsTLVFOV", true);
		dset("settingsPhotoRAW", true);
		break;
		
		case 17: //TLP
		dset("settingsTimelapse", true);	
		dset("settingsPT", true);
		dset("settingsTLVFOV", true);
		dset("settingsPhotoRAW", true);
		dset("settingsDuration", true);
		dset("noteMODE", true);
		break;
		
		case 18: //NLP
		dset("settingsNightlapse", true);	
		dset("settingsNightexposure", true);	
		dset("settingsPT", true);
		dset("settingsTLVFOV", true);
		dset("settingsPhotoRAW", true);
		dset("settingsDuration", true);
		dset("noteMODE", true);
		break;
		
	}
	
	if(document.getElementById("sm") !== null)
	{
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
			
			if(checkedmode >= 1 && checkedmode <= 9) //Video + audio modes
			{
				dset("ptAUD",true);
			}
			
			if(checkedmode >= 1 && checkedmode <= 12) //Video modes
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
			dset("opGPS", true);
			dset("opVC", true);
			dset("opQC", true);
			dset("opDM", true);
			dset("opBV", true);
			dset("opDB", true);
			dset("opLO", true);
			dset("opOR", true);
			dset("opAO", true);
			dset("opSO", true);
			dset("opWC", true);
			dset("opLN", true);
		}
	}
	
	if(document.getElementById("actions") !== null)
	{
		if(document.getElementById("actions").checked === true)
		{
			dset("aSD", true);
			dset("aEND", true);
			dset("aSM", true);
			dset("aSV", true);
			dset("aR", true);
		}
	}
	
	cmd = dcmd(cmd,"m");  // set mode
		
	switch(checkedmode)
	{
		case 10: //TWarp
			cmd = dcmd(cmd,"fpswarp");
			break;
		case 11: //TLV
			cmd = dcmd(cmd,"fpslapse");
			break;
		case 12: //NLV	
			cmd = dcmd(cmd,"fpsnight");
			cmd = dcmd(cmd,"nightexp");
			break;
		case 14: //Burst 
			cmd = dcmd(cmd,"b");
			break;	
		case 15: //Live Burst 
			break;	
		case 16: //Night
			cmd = dcmd(cmd,"nightexp");
			break;
		case 17: //TLP
			cmd = dcmd(cmd,"fpslapse");
			break;
		case 18: //NLP	
			cmd = dcmd(cmd,"fpsnight");
			cmd = dcmd(cmd,"nightexp");
			break;
	}
	
	if(checkedmode == 10 || checkedmode == 11 || checkedmode == 12) // TLV/TWarp Res/NLV
		cmd = dcmd(cmd, "rt");
	else
		cmd = dcmd(cmd,"r"); //RES
		
	cmd = dcmd(cmd,"p"); //fps
	
	if(checkedmode > 9) // not video	
	{
		if(checkedmode == 10) //TWarp
		{
			cmd = dcmd(cmd,"twf"); //fov		
		
			if(	(document.getElementById("twf1").checked === true) || //Wide
				(document.getElementById("twf2").checked === true) || //Linear
				(document.getElementById("twf3").checked === true) ) //Linear+HL
			{
				dset("settingsZoom", true);			
					
				var zoom = parseInt(document.getElementById("zoom").value);
				zoom *= 10;
				document.getElementById("zoomtext").innerHTML = zoom+"%";	
				if(zoom == 100) zoom = 99;	
				
				cmd = cmd + zoom; //fov
			}
		}
		else if(checkedmode == 13) //Photo
		{
			cmd = dcmd(cmd,"pf"); //fov		
		
			if(	(document.getElementById("pf1").checked === true) || //Wide
				(document.getElementById("pf2").checked === true) ) //Linear
			{
				dset("settingsZoom", true);			
					
				var zoom = parseInt(document.getElementById("zoom").value);
				zoom *= 10;
				document.getElementById("zoomtext").innerHTML = zoom+"%";	
				if(zoom == 100) zoom = 99;	
				
				cmd = cmd + zoom; //fov
			}
		}
		else if(checkedmode == 15) //Live Burst
		{
			// do nothing custom
		}
		else //Everything else
		{
			cmd = dcmd(cmd,"tlvf"); //fov		
		
			if(	(document.getElementById("tlvf1").checked === true) || //Wide
				(document.getElementById("tlvf2").checked === true) ) //Linear
			{
				dset("settingsZoom", true);			
					
				var zoom = parseInt(document.getElementById("zoom").value);
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
			
			var zoom = parseInt(document.getElementById("zoom").value);
			zoom *= 10;
			document.getElementById("zoomtext").innerHTML = zoom+"%";	
			if(zoom == 100) zoom = 99;	
			
			cmd = cmd + zoom; //fov
		}
		else
		{
			dset("settingsZoom", false);
		}
	}
	
	if(checkedmode >= 13 && checkedmode <= 18) //RAW Photo modes
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
	
	cmd = dcmd(cmd,"pt"); //protune
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
						cmd = dcmd(cmd,"shut"); //shutter angle
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
					cmd = cmd + "i64"; //ADD fake max
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
			cmd = dcmd(cmd,"aud"); //audio control
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
	
	if(dt === true)
	{
		dset("opDTS", true);		
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
		var S_added = 0;
		var SM_added = 0;
		var SK_added = 0;
		if(document.getElementById("starthrs") !== null && document.getElementById("startmins") !== null && document.getElementById("time") !== null)
		{
			var newcmd = "";
			var secs = 0;
			var starttime = document.getElementById("time").value;
			secs = Number(3600 * document.getElementById("starthrs").value) + Number(60 * document.getElementById("startmins").value) + Number(document.getElementById("startsecs").value);
			var risemins = 60 * document.getElementById("risemins").value;
			var setmins = 60 * document.getElementById("setmins").value;
			if(setmins !== 0)
			{
				newcmd = "!s" + setmins + "N" + cmd + "!S";
				cmd = newcmd;
				S_added = 1;
			}
			else if(risemins !== 0)
			{
				newcmd = "!r" + risemins + "N" + cmd + "!S";
				cmd = newcmd;
				S_added = 1;
			}
			else if(secs > 0)
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
		
		if(document.getElementById("mstart") !== null)
		{
			var mstart = document.getElementById("mstart").value;
			if(mstart > 0)
			{
				if(S_added)	
				{
					cmd = cmd + "M" + mstart;
					SM_added = 1;
				}
				else
				{
					cmd = cmd + "!SM" + mstart;
					SM_added = 1;
				}			
			}
			
			if(document.getElementById("mend") !== null)
			{
				var mend = document.getElementById("mend").value;
				if(mend > 0 && SM_added)
				{
					cmd = cmd + "-" + mend;
				}
			}
			
			if(document.getElementById("dhold") !== null)
			{
				var dhold = document.getElementById("dhold").value;
				if(dhold > 0 && SM_added)
				{
					cmd = cmd + "D" + dhold;
				}
			}
			if(document.getElementById("mmhold") !== null)
			{
				var mmhold = document.getElementById("mmhold").value;
				if(mmhold > 0 && SM_added)
				{
					cmd = cmd + "M" + mmhold;
				}
			}
			if(document.getElementById("mhold") !== null)
			{
				var mhold = document.getElementById("mhold").value;
				if(mhold > 0 && SM_added)
				{
					cmd = cmd + "H" + mhold;
				}
			}
		}
		
		
		if(document.getElementById("vstart") !== null)
		{
			var vstart = document.getElementById("vstart").value;
			if(vstart > 0)
			{
				if(S_added)	
				{
					cmd = cmd + "K" + vstart;
					SK_added = 1;
				}
				else
				{
					cmd = cmd + "!SK" + vstart;
					SK_added = 1;
				}			
			}
			
			if(document.getElementById("vend") !== null)
			{
				var vend = document.getElementById("vend").value;
				if(vend > 0 && SK_added)
				{
					cmd = cmd + "-" + vend;
				}
			}
			if(document.getElementById("vhold") !== null)
			{
				var vhold = document.getElementById("vhold").value;
				if(vhold > 0 && SK_added)
				{
					cmd = cmd + "H" + vhold;
				}
			}
		}
		
		
		
		if(document.getElementById("endhrs") !== null && document.getElementById("endmins") !== null && document.getElementById("endsecs") !== null && document.getElementById("time") !== null)
		{
			var secs = 0;
			var endtime = document.getElementById("endtime").value;
			//var endrisemins = 60 * document.getElementById("endrisemins").value;
			//var endsetmins = 60 * document.getElementById("endsetmins").value;
			secs = Number(60 * 60 * document.getElementById("endhrs").value) + Number(60 * document.getElementById("endmins").value) + Number(document.getElementById("endsecs").value);
			/*if(endsetmins != 0)
			{
				cmd = cmd + "!s" + endsetmins + "E";
			}
			else if(endrisemins != 0)
			{
				cmd = cmd + "!r" + endrisemins + "E";
			}
			else*/ 
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
		
		/*
		if(document.getElementById("repeathrs") !== null && document.getElementById("repeatmins") !== null && document.getElementById("repeatsecs") !== null && document.getElementById("time") !== null)
		{
			var secs = 0;
			var repeattime = document.getElementById("repeattime").value;
			var repeatrisemins = 60 * document.getElementById("repeatrisemins").value;
			var repeatsetmins = 60 * document.getElementById("repeatsetmins").value;
			secs = Number(60 * 60 * document.getElementById("repeathrs").value) + Number(60 * document.getElementById("repeatmins").value) + Number(document.getElementById("repeatsecs").value);
			if(repeatsetmins !== 0)
			{
				cmd = cmd + "!s" + repeatsetmins + "R";
			}
			else if(repeatrisemins !== 0)
			{
				cmd = cmd + "!r" + repeatrisemins + "R";
			}
			else if(secs > 0)
			{
				cmd = cmd + "!" + secs + "R";
			}
			else if(repeattime.length == 5)
			{
				cmd = cmd + "!" + repeattime + "R";
			}
		}*/
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
		for (i = 1; i < 19; i++) { 
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
