# Metadata Extraction - Global Settings
Ever wanted to know what settings were used on an existing GoPro video or photo? This simple utility will display the GPMF header metadata for any GoPro file you open.  In the section labeled "User Metadata" is a list of the Labs hacks/features you may have enabled, and your ownership information if stored. 

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


<div>

Open GoPro MP4/LRV/360 or JPG file: <input id="file" type="file" /><br>
file name: <b><span id="name"></span></b><br>
file size: <b><span id="size"></span></b><br>
</div>

<div id="copyMetadata">
<br>
<button id="copyBtn">Copy Metadata to Clipboard</button><br>
<br>
</div>


<div id="myMetadata">
  <small> 
    <table id="scrollTable" class="scrollTable" border="1">
	  <thead> <tr> <th>FourCC</th><th align="left">Data</th></tr></thead>
	  <tbody> <tr><td></td><td></td></tr></tbody>
    </table>
  </small>
</div>

**Compatibility:** All GoPro cameras since HERO5 Black

updated: Sept 19, 2023

[More features](..) for Labs enabled cameras


<script>

var clipcopy = "";
var hdr_bytes;
var file;

(function() {

	var inputFile = document.getElementById("file");
	var reader = new FileReader();
	var reader2 = new FileReader();

	inputFile.addEventListener("change", fileChange, false);
	reader.addEventListener('load', fileHeaderLoad, false);
	reader2.addEventListener('load', fileLoad, false);

	function tableAllDelete(){
		var table = document.getElementById("scrollTable");
	    var len = table.rows.length;
		for (var i = (len - 1); i > 1; i--){
			table.deleteRow(i);
		}

		table.scrollTop = 0;
	}
	
	var mdat_offset = 0;
	var gpmf_offset = 0;
	var gpmf_size = 0;
	var jpeg_gpmf_offset = 0;
	var jpeg_gpmf_size = 0;
	
	function fileChange(event){
		var target = event.target;
		file = target.files[0];

		document.querySelector('#name').innerHTML = file.name;
		//document.querySelector('#type').innerHTML = file.type;
		document.querySelector('#size').innerHTML = file.size + " Bytes";

		mdat_offset = 0;
		gpmf_offset = 0;
		gpmf_size = 0;
		jpeg_gpmf_offset = 0;
		jpeg_gpmf_size = 0;
	
		var blob = file.slice(0, 1024*1024*24);
		reader.readAsArrayBuffer(blob);   // read head to find the moov offset (from mdat)
	}
	
	function fileHeaderLoad(){	
		hdr_bytes = new Uint8Array(reader.result);
		for(i=0; i<60; i++)
		{
			if(hdr_bytes[i] == 109 /*'m'*/ && hdr_bytes[i+1] == 100 /*'d'*/ && hdr_bytes[i+2] == 97 /*'a'*/ && hdr_bytes[i+3] == 116 /*'t'*/)
			{
				if(hdr_bytes[i-4] == 0 && hdr_bytes[i-3] == 0 && hdr_bytes[i-2] == 0 && hdr_bytes[i-1] == 1) // 64-bit offset 
				{
					mdat_offset = (hdr_bytes[i+7]*4294967296);
					mdat_offset += (hdr_bytes[i+8]*16777216);
					mdat_offset += (hdr_bytes[i+9]<<16) + (hdr_bytes[i+10]<<8) + (hdr_bytes[i+11]<<0) + i - 4;
				}
				else
				{
					mdat_offset = (hdr_bytes[i-4]*16777216);
					mdat_offset += (hdr_bytes[i-3]<<16) + (hdr_bytes[i-2]<<8) + (hdr_bytes[i-1]<<0) + i - 4;
				}
			}
		}
		//console.log("moov offset:" + mdat_offset.toString());		
		
		if(mdat_offset == 0) // not an MP4, check for JPEG
		{
			i = 0;
			do
			{			
				while(hdr_bytes[i] == 0xff && (hdr_bytes[i+1] < 0xe0 || hdr_bytes[i+1] > 0xef)) i+=2;
								
				if(hdr_bytes[i] == 0xff && hdr_bytes[i+1] >= 0xe1 && hdr_bytes[i+1] <= 0xef)
				{					
					if(hdr_bytes[i+1] == 0xe6) //APP6
					{
						//console.log("APP6");
						if(hdr_bytes[i+4] == 0x47/*G*/ && hdr_bytes[i+5] == 0x6F/*o*/ && hdr_bytes[i+6] == 0x50/*P*/ && hdr_bytes[i+7] == 0x72/*r*/ && hdr_bytes[i+8] == 0x6F/*o*/)
						{							
							//console.log("GoPro file");
				
							jpeg_gpmf_offset = i+10;
							jpeg_gpmf_size = (hdr_bytes[i+2]<<8) + (hdr_bytes[i+1]<<0);	
						}
						break;
					}
					else
					{
						i += (hdr_bytes[i+2]<<8) + (hdr_bytes[i+3]) + 2;
					}
				}
				else
				{
					break; // bad formatted JPEG
				}
			} while(1);
			
				
			var blob = file.slice(jpeg_gpmf_offset, jpeg_gpmf_offset+(jpeg_gpmf_size+1024));
			reader2.readAsArrayBuffer(blob);   
			//console.log("gpmf offset:" + jpeg_gpmf_offset.toString());
			//console.log("gpmf size:" + jpeg_gpmf_size.toString());
		}
		else
		{
			var blob = file.slice(mdat_offset, mdat_offset+(1024*1024*24));
			reader2.readAsArrayBuffer(blob);  
		}
	}
	
	function Bytes2Float32(bytes) {
		var sign = (bytes & 0x80000000) ? -1 : 1;
		var exponent = ((bytes >> 23) & 0xFF) - 127;
		var significand = (bytes & ~(-1 << 23));

		if (exponent == 128) 
			return sign * ((significand) ? Number.NaN : Number.POSITIVE_INFINITY);

		if (exponent == -127) {
			if (significand == 0) return sign * 0.0;
			exponent = -126;
			significand /= (1 << 22);
		} else significand = (significand | (1 << 23)) / (1 << 23);

		return sign * significand * Math.pow(2, exponent);
	}

	function fileLoad(){
		// console.log(reader.result);

		tableAllDelete();
		
		if(mdat_offset == 0 && jpeg_gpmf_offset == 0) 
		{
			dumpHeader(0);
			return;
		}

		var bytes = new Uint8Array(reader2.result);
		var new_float_bytes = new Uint8Array(4);

		mdat_offset = 0;
		var udta_offset = 0;
		
		if(jpeg_gpmf_offset == 0)
		{
			for(i=0; i<1024*1024*24; i++)
			{
				if(bytes[i] == 117 /*'u'*/ && bytes[i+1] == 100 /*'d'*/ && bytes[i+2] == 116 /*'t'*/ && bytes[i+3] == 97 /*'a'*/)
				{
					udta_offset = i;
					break;
				}
			}
			//console.log("udta offset:" + udta_offset.toString());
			
			if(udta_offset)
			{
				for(i=udta_offset; i<udta_offset+4096; i++)
				{
					if(bytes[i] == 0x47 /*'G'*/ && bytes[i+1] == 0x50 /*'P'*/ && bytes[i+2] == 0x4D /*'M'*/ && bytes[i+3] == 0x46 /*'F'*/)
					{
						gpmf_offset = i+4;
						gpmf_size = (bytes[i-3]<<16) + (bytes[i-2]<<8) + (bytes[i-1]<<0) - 8;
						break;
					}
				}
				//console.log("GPMF offset:" + gpmf_offset.toString());
				//console.log("GPMF size:" + gpmf_size.toString());
			}
			
			if(gpmf_offset == 0 || gpmf_size == 0) 
			{							
				dumpHeader(1);			
				return;
			}
		}
		else
		{
			gpmf_size = jpeg_gpmf_size;
		}
		
		if(gpmf_size > 0)
			clipcopy = ""; //reset for each new file.
		
		var txt = "";
		var hex;
		var dat;
		var j = 0;
		var k = 0;
		
		var cleantxt = "";
		var indent = 0;
		var devcsize = 0;
		var strmsize = 0;
		for (var i = gpmf_offset; i < gpmf_offset+gpmf_size;) {
			cleantxt = "";
			txt = "";
			dat = "";
			
			var fourcc = (bytes[i]*16777216);
			fourcc += (bytes[i+1]<<16) + (bytes[i+2]<<8) + (bytes[i+3]<<0);
			
			if(fourcc == 0) break;
			
			//console.log("GPMF 4CC:" + String.fromCharCode(bytes[i]) + String.fromCharCode(bytes[i+1]) + String.fromCharCode(bytes[i+2]) + String.fromCharCode(bytes[i+3]));
			
			var type = bytes[i+4];
			var typsize = bytes[i+5];
			var repeat = (bytes[i+6]<<8) + bytes[i+7];
			var size = typsize * repeat;
			var align_size = Math.trunc((size + 3)/4)*4;
			
			if(fourcc == 0x44455643) //DEVC
			{
				indent = 0;
				devcsize = size;
			}
			if(fourcc == 0x5354524D) //STRM
			{
				strmsize = size;
			}

			for(j=0; j<indent; j++)
				txt += "&nbsp;&nbsp;&nbsp;";
			txt += String.fromCharCode(bytes[i]);
			txt += String.fromCharCode(bytes[i+1]);
			txt += String.fromCharCode(bytes[i+2]);
			txt += String.fromCharCode(bytes[i+3]);
			
			for(j=0; j<indent; j++)
				cleantxt += "  ";
			cleantxt += String.fromCharCode(bytes[i]);
			cleantxt += String.fromCharCode(bytes[i+1]);
			cleantxt += String.fromCharCode(bytes[i+2]);
			cleantxt += String.fromCharCode(bytes[i+3]);
			
			if(type == 0)
			{
				indent++;
				i += 8;
				
				if(fourcc != 0x44455643) //DEVC
					devcsize -= 8;
			} 
			else
			{
				if(type == 0x63 /* c */)
				{
					if(bytes[i+8] == 0)
					{
						dat += ".empty.";
					}
					else
					{
						for(j=0; j<size; j++)
						{
							if(bytes[i+8+j] != 0 && bytes[i+8+j] != 10 && bytes[i+8+j] != 13)
								dat += String.fromCharCode(bytes[i+8+j]);
							if(bytes[i+8+j] == 10 || bytes[i+8+j] == 13)
								dat += '\\' + 'n';
						}
					}
				}
				
				if(type == 0x4c || type == 0x6c /* L or l */)
				{
					if(typsize > 4) repeat *= typsize / 4;
					for(k=0; k<repeat; k++)
					{
						var num = (bytes[i+8+k*4]*16777216);
						num += (bytes[i+8+k*4+1]<<16) + (bytes[i+8+k*4+2]<<8) + (bytes[i+8+k*4+3]<<0);						
						if(num > 2147483647) num -= 4294967296; // signed numbers
						if(k > 0) dat += ", ";
						dat += num.toString();
					}
				}
				if(type == 0x53 || type == 0x73 /* S or s */)
				{
					if(typsize > 2) repeat *= typsize / 2;
					for(k=0; k<repeat; k++)
					{
						var num = (bytes[i+8+k*2+0]<<8) + (bytes[i+8+k*2+1]<<0);
						if(num > 32767) num -= 65536; // signed numbers
						if(k > 0) dat += ", ";
						dat += num.toString();
					}
				}
				if(type == 0x42 || type == 0x62 /* B or b */)
				{
					if(typsize > 1) repeat *= typsize;
					for(k=0; k<repeat; k++)
					{
						var num = (bytes[i+8+k]);
						if(num > 127) num -= 256; // signed numbers
						if(k > 0) dat += ", ";
						dat += num.toString();
					}
				}
				if(type == 0x66 /* f */) //float
				{
					if(typsize > 4) repeat *= typsize / 4;
					for(k=0; k<repeat; k++)
					{
						var num = (bytes[i+8+k*4]*16777216);
							num += (bytes[i+8+k*4+1]<<16) + (bytes[i+8+k*4+2]<<8) + (bytes[i+8+k*4+3]<<0);
						if(k > 0) dat += ", ";
				
						var val = Bytes2Float32(num);
						var fnum = val.toFixed(4);
						dat += fnum.toString();
					}
				}
				if(type == 0x64 /* d */) //double
				{
					if(typsize > 8) repeat *= typsize / 8;
					for(k=0; k<repeat; k++)
					{
						var signbit = (bytes[i+8+k*8] & 0x80) >> 7;
						
						// Convert 64-bit double to 32-bit float, directly.
						
						// convert an 11-bit exponent to 8-bit 
						var expo = ((bytes[i+8+k*8] & 0x7f) << 4) + ((bytes[i+8+k*8+1] & 0xf0) >> 4) - 1023; 
						var new_expo = expo + 127; 
						
						// extract the 23-bit mantissa from the MSBs of the double's mantissa 
						var new_mant23 = (((bytes[i+8+k*8+1] & 0x0f) << 19) + (bytes[i+8+k*8+2] << 11) + (bytes[i+8+k*8+3] << 3) + ((bytes[i+8+k*8+4]) >> 5));

						// reconstruct a 32-bit float
						new_float_bytes[0] = (signbit << 7) + (new_expo>>1);
						new_float_bytes[1] = ((new_expo << 7) & 0x80) + ((new_mant23 >> 16) & 0x7f);
						new_float_bytes[2] = ((new_mant23 >> 8) & 0xff);
						new_float_bytes[3] = (new_mant23 & 0xff);
					
						var num = (new_float_bytes[0]*16777216);
							num += (new_float_bytes[1]<<16) + (new_float_bytes[2]<<8) + (new_float_bytes[3]<<0);
						if(k > 0) dat += ", ";
				
						var val = Bytes2Float32(num);
						var fnum = val.toFixed(4);
						dat += fnum.toString();
					}
				}
				if(type == 0x46 /* F */) //FOURCC
				{
					if(typsize > 4) repeat *= typsize / 4;
					for(k=0; k<repeat; k++)
					{
						if(k > 0) dat += ", ";
						dat += String.fromCharCode(bytes[i+8+k*4]) + String.fromCharCode(bytes[i+8+k*4+1]) + String.fromCharCode(bytes[i+8+k*4+2]) + String.fromCharCode(bytes[i+8+k*4+3])
					}
				}
				
				if(type == 0x4A /* J */) // Jumbo 64-bit integer
				{
					dat += "0x";
					if(typsize > 8) repeat *= typsize / 8;
					for(k=0; k<repeat*8; k++)
					{
						//var num = (bytes[i+8+k]);
						//if(k > 0) dat += ", ";
						//dat += num.toString();
						
						hex = ("0" + bytes[i+8+k].toString(16)).toUpperCase().substr(-2);
						
						dat += hex;
					}
				}
				
				if(type == 0x3F /* ? */) //complex
				{
					dat += ".complex.";
				}
								
				i += 8+align_size;
				devcsize -= 8+align_size;
				
				if(strmsize)
				{
					strmsize -= 8+align_size;
					if(strmsize == 0) indent--;
				}					
			}
	

			var table = document.getElementById("scrollTable");
			var row = table.insertRow(-1);
			var cell1 = row.insertCell(-1);
			var cell2 = row.insertCell(-1);

			cell1.innerHTML = txt;
			cell2.innerHTML = dat;
			
			clipcopy = clipcopy + cleantxt + " " + dat + "\n";
		}

		txt += "\n";
	}
	
	//if(clipcopy.length > 0)
	//	dset("copyMetadata",true);
	//else
	//	dset("copyMetadata",false);

}());


function dumpHeader(type)
{
	var table = document.getElementById("scrollTable");
	var row = table.insertRow(-1);
	var cell1 = row.insertCell(-1);
	var cell2 = row.insertCell(-1);

	if(type == 1)
	{
		clipcopy = "MP4 Source Type : No GPMF metadata found\n\n";
		cell1.innerHTML = "MP4 Source Type";
		cell2.innerHTML = "No GPMF metadata found";
	}
	else
	{	
		clipcopy = "Invalid Source Media : Not GoPro Media or Corrupted\n\n";
		cell1.innerHTML = "Invalid Source Media";
		cell2.innerHTML = "Not GoPro Media or Corrupted";
	}
	
	row = table.insertRow(-1);
	cell1 = row.insertCell(-1);
	cell2 = row.insertCell(-1);
	
	clipcopy = clipcopy + file.name + " : " + file.size + " Bytes" + "\n\n";				
		
	var line,rows;
	var pos = 0;
	var hex;
	for(line=0; line < 16; line++)
	{
		row = table.insertRow(-1);
		cell1 = row.insertCell(-1);
		cell2 = row.insertCell(-1);
		
		hex = hexpad(line);
		cell1.innerHTML = "0x"+hex; 
		
		clipcopy = clipcopy + "0x" + hex + "   "; 
		
		var hexline = "";
		var charline = "";
		for(rows = 0; rows < 16; rows++)
		{
			
			var chr = hdr_bytes[pos];
			hex = hexpad(chr); 
			
			if(chr >= 0x21 && chr <= 0x7f)
				charline = charline + String.fromCharCode(chr);
			else 
				charline = charline + ".";
			
			pos++;
			
			hexline = hexline + hex + " ";
		}		
		
		cell2.innerHTML = hexline + "  |  " + charline;
		
		clipcopy = clipcopy + hexline + "  " + charline + "\n";				
	}
	
	return;
}

function hexpad(line)
{
	var hex="";
	if(line >= 16)
	   hex = line.toString(16).toUpperCase(); 
	else if(line >= 1)
	   hex = '0' + line.toString(16).toUpperCase(); 
	else
	   hex = "00"; 
	
	return hex;
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
}


setupButtons();

</script>
