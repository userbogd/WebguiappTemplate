function PostData(data,page,conf,alrt,reld) {
if(conf){if (!confirm(conf)) return;}
var xhr = new XMLHttpRequest();
xhr.open('POST',page, true);
xhr.timeout = 5000;
xhr.send(data);
xhr.onreadystatechange = function() { 
if (xhr.readyState != 4) return;
if (xhr.status != 200) {alert(xhr.status+': '+xhr.statusText);} 
else {if(reld)location.reload();
if(alrt) alert(alrt);
}}}

function GetDataFile(file, callback) {
var xhr = new XMLHttpRequest();
xhr.overrideMimeType("application/json");
xhr.open("GET", file, true);
xhr.onreadystatechange = function() {if (xhr.readyState === 4 && xhr.status == "200") {callback(xhr.responseText);}}
xhr.timeout = 5000;
xhr.send(null);
}

function PrintMenu(){
document.write("<div id='conteiner'><nav id='menu1'><ul>");
document.write("<li><a href='index.html'>Главная</a></li>");

document.write("<li><a href='#'>Сервис</a><ul>");
document.write("<li><a href='index40.html'>Управление</a></li>");
document.write("<li><a href='index41.html'>Статистика</a></li></ul></li>");

document.write("<li><a href='#'>Настройки</a><ul>");
document.write("<li><a href='index30.html'>Панель</a></li>");
document.write("<li><a href='sys/set_mqtt.html'>MQTT</a></li>");
document.write("<li><a href='sys/set_sys.html'>System</a></li>");
document.write("<li><a href='sys/set_time.html'>Time</a></li></ul></li>");

document.write("<li><a href='#'>Сеть</a><ul>");
document.write("<li><a href='sys/set_eth.html'>Ethernet</a></li>");
document.write("<li><a href='sys/set_wifi.html'>WiFi</a></li>");
document.write("<li><a href='sys/set_gprs.html'>GPRS</a></li>");
document.write("<li><a href='index23.html'>LoRaWAN</a></li></ul></li>");
document.write("</ul></nav></div>");}

function PrintIPInput(title,name,value){document.write("<tr><td class='rl'>"+title+"</td><td><input type='text' required size='20' name='"+name+"' value='"+value+"' title='IP адрес xxx.xxx.xxx.xxx' pattern='^\\d{1,3}\.\\d{1,3}\.\\d{1,3}\.\\d{1,3}$' /></td></tr>");}
function PrintMACInput(title,name,value){document.write("<tr><td class='rl'>"+title+"</td><td><input type='text' required size='20' name='"+name+"' value='"+value+"' title='MAC адрес xx-xx-xx-xx-xx-xx' pattern='^([0-9a-fA-F]{2}([-]|$)){6}$|([0-9a-fA-F]{4}([.]|$)){3}$' /></td></tr>");}
function PrintTextInput(title,name,value,min,max){document.write("<tr><td class='rl'>"+title+"</td><td><input type='text' required size='20' name='"+name+"' value="+value+" title='"+min+"-"+max+" символов A-Za-z0-9_\-*!<>)(.@,/'  pattern='^[0-9a-zA-Z_\\-*!<>.@\,/)(\s]{"+min+","+max+"}$' /></td></tr>");}
function PrintHexInput(title,name,value,min,max){document.write("<tr><td class='rl'>"+title+"</td><td><input type='text' required size='20' name='"+name+"' value="+value+" title='"+min+"-"+max+" символов A-Fa-f0-9'  pattern='^[0-9a-fA-F]{"+min+","+max+"}$' /></td></tr>");}
function PrintTextInputNoReg(title,name,value,min,max){document.write("<tr><td class='rl'>"+title+"</td><td><input type='text' required size='20' name='"+name+"' value="+value+" title='"+min+"-"+max+" символов'/></td></tr>");}
function PrintLabel(title,value){document.write("<tr><td class='rl'>"+title+"</td><td align='left'>"+value+"</td></tr>");}
function PrintSpanLabel(title,idx){document.write("<tr><td class='rl'>"+title+"</td><td align='left'><span id='"+idx+"'>?</span></td></tr>");}
function PrintCheckBox(title,name,checked,action){document.write("<tr><td class='rl'>"+title+"</td><td><input type='checkbox' name='"+name+"' value='1' onclick="+action+" "+checked+" /></td></tr>");}
function PrintInt(title,name,value,min,max){document.write("<tr><td class='rl'>"+title+"</td><td><input type='number' required min='"+min+"' max='"+max+"' name='"+name+"' value ='"+value+"'/></td></tr>");}
function PrintIntId(title,id,value,min,max){document.write("<tr><td class='rl'>"+title+"</td><td><input type='number' required min='"+min+"' max='"+max+"' id='"+id+"' value ='"+value+"'/></td></tr>");}
function PrintSep(){document.write("<tr><td height='20px'></td></tr>");}
function PrintSaveBtn(){document.write("<div style='text-align:center;margin-top:10px'><button type='submit' class='btn' name='sav' value='prs'>Сохранить</button></div>");}
function PrintSaveFail(isfail){document.write("<div class='resfail' style='text-align:center;display:"+isfail+"' color='#F00'><font color='red'><h2>Неверный формат данных!</h2></font><br/></div>");}

function sndtmr()
{
var body = '';
var body2 = '';
//var ofc = (new Date).getTimezoneOffset()*60;
var ofc = 0;
for(i=1;i<9;++i)
	{
	body += GetInterface(i);
	if(i<8) body +='&';
	}
for(i=9;i<17;++i)
	{
	body2 += GetInterface(i); 
	if(i<16) body2 +='&';
	}	
function GetInterface(n) {
	var s = '';
	
	s+='tm'+i+'='+ ( +Date.parse(document.getElementById('tdp'+n).value)/1000 + ofc);
	s+= '%'+ ((document.getElementsByName('enb'+n)[0].checked) ? '1':'0').toString();
	s+= '%'+ ((document.getElementsByName('act'+n)[0].value == 'on') ? '1':'0').toString();
	s+= '%'+ (document.getElementsByName('prd'+n)[0].value).toString();
	return s;
}

var xhr2 = new XMLHttpRequest(); 
var xhr = new XMLHttpRequest();
xhr.open('POST', 'index42.html', true);					
xhr.send(body);

xhr.onreadystatechange = function() { 
if (xhr.readyState != 4) return;

if (xhr.status != 200) {
alert(xhr.status + ': ' + xhr.statusText);
} else {
xhr2.open('POST', 'index42.html', true);
xhr2.send(body2);
}
}

xhr2.onreadystatechange = function() { 
if (xhr2.readyState != 4) return;
if (xhr2.status != 200) {
alert(xhr2.status + ': ' + xhr2.statusText);
} else {
alert('Timer settings saved')
location.reload();					
}
}
			
}
function ClickCheckbox()
{			
for(i=1;i<17;++i)
{
var st = !document.getElementsByName('enb'+i)[0].checked;			
document.getElementById('tdp'+i).disabled = st;
document.getElementsByName('prd'+i)[0].disabled = st;
document.getElementsByName('act'+i)[0].disabled = st;
}
}

	
function configIPBoxes() {
e = document.forms.conf;
var ap = document.getElementsByName('netm');
st = e.dhcp.checked;
function apmode(m){
e.wfiap.disabled = m;
e.wfpap.disabled = m;
e.ipaap.disabled = m;
}		
function clnmode(m){
e.wfi.disabled = m;
e.wfp.disabled = m;
e.ipa.disabled = m;
e.mas.disabled = m;
e.gte.disabled = m;
}	
if(ap[0].checked){
apmode(true);
clnmode(false);
e.ipa.disabled = st;
e.mas.disabled = st;
e.gte.disabled = st;
}
if(ap[1].checked){
apmode(false);
clnmode(true);
}
}	

function configIPBoxes2() {
e = document.forms.conf;
st2 = e.tsen.checked;
e.tsr.disabled = !st2;
st3 = e.clen.checked;
e.cld.disabled = !st3;
e.idd.disabled = !st3;
e.top.disabled = !st3;
e.prt.disabled = !st3;
e.clnm.disabled = !st3;
e.clps.disabled = !st3;
e.ssen.disabled = !st3;
}

function configIPBoxesOCPP() {
e = document.forms.conf;
}

function UnixToStr(t, base, sec)
{
if(t.lenth < 10) t = '000000000';
var d;
if (base == 16) d = new Date(parseInt(t,16)*1000);
else d = new Date(parseInt(t,10)*1000);	
var dd = d.getDate();	if (dd < 10) dd = '0' + dd;
var mm = d.getMonth() + 1;	if (mm < 10) mm = '0' + mm;
var yy = d.getFullYear() % 100;	if (yy < 10) yy = '0' + yy;
var h = d.getHours();	if (h < 10) h = '0' + h;
var m = d.getMinutes();	if (m < 10) m = '0' + m;
var s = d.getSeconds();	if (s < 10) s = '0' + s;
d=yy+'/'+mm+'/'+dd+' '+h+':'+m;
if(sec==1) d+=':'+s;
return d;
}

function FloatToString(f)
{
var buffer = new ArrayBuffer(4);
var bytes = new Uint8Array(buffer);
var doubles = new Float32Array(buffer); 
bytes[3] = '0x'+f.substr(6,2); 
bytes[2] = '0x'+f.substr(4,2);
bytes[1] = '0x'+f.substr(2,2);
bytes[0] = '0x'+f.substr(0,2);
return doubles[0];
}

function sendtime() {
var ut = Date.parse(new Date( Date.parse(document.getElementById('curdt').value)))/1000;
var xhr = new XMLHttpRequest();
xhr.open('POST', 'index23.html', true);
var body = 'timenow=' + ut;
xhr.send(body);
xhr.onreadystatechange = function() { 
if (xhr.readyState != 4) return;
if (xhr.status != 200) {
alert(xhr.status + ': ' + xhr.statusText);
} else {
alert('Time changed');
}
}
}

function Pst(Rqv,Pag,Conf){
if (confirm(Conf)) {
var xhr = new XMLHttpRequest();
xhr.open('POST',Pag, true);
xhr.send(Rqv);
xhr.onreadystatechange = function() { 
if (xhr.readyState != 4) return;
if (xhr.status != 200) {
alert(xhr.status + ': ' + xhr.statusText);
} else {
location.reload();
}
}  
} 
}

