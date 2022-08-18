var Ku=1.0,Ki=0.02,sc=Ku*Ki/3600000;
var tds=['???','Пиковый','Полупиковый','Ночной'];
var tz=['+0','+1','+2','+3','+4','+5','+6','+7','+8','+9','+10','+11','+12','-12','-11','-10','-9','-8','-7','-6','-5','-4','-3','-2','-1'];
let trpend=[0,0,0];
 
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

function TimeToStr(t){
	if(t>=(65535-1440))return '-----';
if(t>=1440) t-=1440; 
return (Math.floor(t/60)).toString().padStart(2,'0')+':'+(Math.floor((t%60))).toString().padStart(2,'0'); }

function StrToTime(s){
return parseInt(s.substring(0,2))*60+parseInt(s.substring(3,5));}

function TimeToStrSec(t){
hh=Math.floor(t/3600).toString().padStart(2,'0');
mm=Math.floor((t-hh*3600)/60).toString().padStart(2,'0');
ss=Math.floor((t-hh*3600-mm*60)).toString().padStart(2,'0');	
return hh+':'+mm+':'+ss;}

function StrToTimeSec(s){
return parseInt(s.substring(0,2))*3600+parseInt(s.substring(3,5))*60+parseInt(s.substring(6,8));}

function UnixToStr(t, z, base, sec) {
if(t.lenth < 10) t = '000000000';
var d;
if (base == 16) d = new Date((parseInt(t,16)+z)*1000);
else d=new Date((parseInt(t,10)+z)*1000);	
var dd=d.getUTCDate();if(dd<10) dd='0'+dd;
var mm=d.getUTCMonth() + 1;if(mm<10) mm='0'+mm;
var yy=d.getUTCFullYear() % 100;if(yy<10) yy='0'+yy;
var h=d.getUTCHours();if(h<10) h='0'+h;
var m=d.getUTCMinutes();if(m<10) m='0'+m;
var s=d.getUTCSeconds();if(s<10) s='0'+s;
d=yy+'/'+mm+'/'+dd+' '+h+':'+m;
if(sec==1) d+=':'+s;
return d;}

function FloatToString(f) {
var buffer=new ArrayBuffer(4);
var bytes=new Uint8Array(buffer);
var doubles=new Float32Array(buffer); 
bytes[3]='0x'+f.substr(6,2); 
bytes[2]='0x'+f.substr(4,2);
bytes[1]='0x'+f.substr(2,2);
bytes[0]='0x'+f.substr(0,2);
return doubles[0];}

function SndTmr(z) {
body = ''; body2 = '';
for(i=1;i<9;++i){
body += GetInterface(i);
if(i<8) body +='&';}
for(i=9;i<17;++i){
body2 += GetInterface(i); 
if(i<16) body2 +='&';}	
function GetInterface(n) {
s='';
rawd=document.getElementById('tdp'+n).value;
date=Date.parse(rawd+':00Z')/1000-z;
s+='tm'+i+'='+date;
s+='%'+((document.getElementsByName('enb'+n)[0].checked)?'1':'0').toString();
s+='%'+document.getElementsByName('act'+n)[0].value;
s+='%'+document.getElementsByName('prd'+n)[0].value;
return s;}

var xhr2 = new XMLHttpRequest(); 
var xhr = new XMLHttpRequest();
xhr.open('POST','index42.html',true);					
xhr.send(body);
xhr.onreadystatechange = function() { 
if (xhr.readyState != 4) return;
if (xhr.status != 200) {
alert(xhr.status + ': ' + xhr.statusText);
} else{
xhr2.open('POST','index42.html',true);
xhr2.send(body2);
}}

xhr2.onreadystatechange = function() { 
if (xhr2.readyState != 4) return;
if (xhr2.status != 200) {
alert(xhr2.status + ': ' + xhr2.statusText);
} else {
alert('Параметры таймера сохранены')
location.reload();					
}}
}

function clstmr(){PostData('tmr=rst','index42.html',false,'Таймеры очищены',true);}
function ClsTar(){PostData('tar=rst','index23_5.html',false,'Тарифы очищены',true);}

function ClickCheckbox(){			
for(i=1;i<17;++i){
var st = !document.getElementsByName('enb'+i)[0].checked;			
document.getElementById('tdp'+i).disabled = st;
document.getElementsByName('prd'+i)[0].disabled = st;
document.getElementsByName('act'+i)[0].disabled = st;
}}

function GenerateInterface(t, z){
timers = t;	
document.write("<table>");
document.write("<tr><td></td><td>&nbsp;начало</td><td>&nbsp;повтор</td><td></td></tr>");
for(i=1;i<17;++i){			
rep = ['once','1m','2m','5m','10m','15m','20m','30m','1h','2h','3h','6h','9h','12h','18h','1d','2d','7d'];
act=['Off','On','Rst','Wrs'];
tm=timers[i-1];	
pos1=tm.indexOf("%",0);
dt=parseInt(tm.substring(0,pos1),16);
en=parseInt(tm.substr(pos1+1,2),16);
ac=parseInt(tm.substr(pos1+4,2),16);
rp=parseInt(tm.substr(pos1+7),16);
document.write("<div style='padding-top:0px;white-space:pre'>");
ch = (en != 0)?'checked':'';
document.write("<tr><td><input type='checkbox' name='enb"+i+"' "+ch+" onclick='ClickCheckbox()' ></td>");	
date=new Date((dt+z*3600)*1000);			
str=date.toISOString();
val=str.substring(0,16);	
document.write("<td><input type='datetime-local' value='"+val+"' id='tdp"+i+"'></td>");	
document.write("<td><select  name='prd"+i+"'>");			
for(ii=0;ii<18;++ii){
s=(ii==+rp)?"selected":"";
document.write("<option value='"+ii+"' "+s+" >"+rep[ii]+"</option>");}	
document.write("</select></td>");
document.write("<td><select  name='act"+i+"'>");
for(ii=0;ii<4;++ii){
s=(ii==+ac)?"selected":"";
document.write("<option value='"+ii+"' "+s+" >"+act[ii]+"</option>");}	
document.write("</select></td></tr>");
document.write("</div>");}				
document.write("</table>");}

function GenTarifTable(r){
document.write('<table>');
document.write("<tr><td></td><td>&nbsp;начало</td><td>&nbsp;конец</td><td>&nbsp;тариф</td></tr>");
for(i=1;i<7;++i){
var rc=(r[i-1]).split("%",4);	
document.write("<div style='padding-top:0px;white-space:pre'>");
ch=(rc[0] != 0)?'checked':'';
document.write("<tr><td><input type='checkbox' id='tcb"+i+"' "+ch+"></td>"); 
document.write("<td class='tarw'><input type='time' id='tbgn"+i+"'"+"value='"+TimeToStr(parseInt(rc[1],10))+"' ></td>");
document.write("<td class='tarw'><input type='time' id='tend"+i+"'"+"value='"+TimeToStr(parseInt(rc[2],10))+"' ></td>");
document.write("<td><select id='sltar"+i+"'>");
for(ii=1; ii<4 ;++ii){
sel=(rc[3] == ii)?"selected":"";
document.write("<option "+sel+" value='"+ii+"'"+">"+tds[ii]+"</option>");}	
document.write("</select></td></tr>");}
document.write("</table>");}

function SaveTar(){
var d="";
for(i=1;i<7;++i){
d+="tpr"+i+"=";	
d+=((document.getElementById("tcb"+i).checked) ? "1":"0").toString()+"%";
d+=StrToTime(document.getElementById("tbgn"+i).value)+"%";
d+=StrToTime(document.getElementById("tend"+i).value)+"%";
d+=(document.getElementById("sltar"+i).value).toString()+"&";}
for(i=1;i<4;++i){
d+="tar"+i+"="+(document.getElementById("tar"+i).value).toString()+"&";}
d+="unt="+(document.getElementById("unt").value).toString()+"&sav=prs";
PostData(d,"index23_5.html",false,"Параметры тарифов сохранены",true);}

function ClsTar(){PostData('tarif=rst','index23_5.html',false,'Тарифы очищены',true);}

function SendSimpTim(btn){	
ts=StrToTimeSec(document.getElementById("stbgn"+btn).value);
ac=document.getElementById("slact"+btn).value;
bt=document.getElementById("simt"+btn);st=bt.value;
if(st=="1"){st="0";bt.innerHTML="Пуск";bt.style.backgroundColor="#FF6633";bt.value="0";}
else {st="1";bt.innerHTML="Стоп";bt.style.backgroundColor="#99CC00";bt.value="1";}
d='tim'+btn+"="+ts+"&act"+btn+"="+ac+"&st"+btn+"="+st+"&sav=prs";
PostData(d,"index42_2.html",false,"",false);}

function GenSimpTimers(r){	
document.write("<table style='margin-left:40px'>");
for(i=1;i<4;++i){rc=(r[i-1]).split("%",3);
t=TimeToStrSec(parseInt(rc[0],10));	
document.write("<tr style='margin-top:40px'><td>Таймер "+i+"</td></tr>");
document.write("<tr><td class='stimr'><input type='time' id='stbgn"+i+"'"+" value='"+t+"' step='1'></td>");
document.write("<td><select id='slact"+i+"'>");s1="",s2="";
if(rc[1]==1)s1="selected";else s2="selected";
document.write("<option "+s1+" value='1'>On</option>");
document.write("<option "+s2+" value='0'>Off</option></select></td>");	
if(rc[2]==1) document.write("<td><button type='submit' class='btn sbtn' id='simt"+i+"' value='1' onclick='SendSimpTim("+i+")'>Стоп</button></td></tr>");
else document.write("<td><button type='submit' class='btn sbtn timact' id='simt"+i+"' value='0' onclick='SendSimpTim("+i+")'>Пуск</button></td></tr>");}
document.write("</table>");}

function RefSimpTimers(){
function refresh(){  
if (this.status == 200) {
r=JSON.parse(this.responseText);
for(i=1;i<4;++i){
var rc=(r.tmr2[i-1]).split("%",3);
tt=parseInt(rc[0],10);t=TimeToStrSec(tt);
if(rc[2]=="1" || trpend[i-1]==1){
document.getElementById("stbgn"+i).value=t;
document.getElementById("slact"+i).value=rc[1];
bt=document.getElementById("simt"+i);
if(rc[2]=="1"){bt.innerHTML="Стоп";bt.style.backgroundColor="#99CC00";}
else{bt.innerHTML="Пуск";bt.style.backgroundColor="#FF6633";}
if(tt<5&&tt!=0&&rc[2]=="1") trpend[i-1]=1;
else trpend[i-1]=0;
}}}};	
var xhr=new XMLHttpRequest();
xhr.onload = refresh;	
xhr.open('GET','/tmr2.json',true);
xhr.send();	
}
	
function GenCntInter(N,curN,pp,tt,unt,tw,tz,ttr){
var T=parseFloat(ttr),P=0;
document.write("<table><tr><td align='right'>Счетчик:</td><td align='left'>№"+N+"</td></tr>");
document.write("<tr><td align='right'>Начало учета:</td><td align='left'><span id='tt"+N+"'>?</span></td></tr>");
document.write("<tr><td align='right'>Конец  учета:</td><td align='left'><span name='tnow'>?</span></td></tr>");
document.write("<tr><td align='right'>Действующий тариф:</td><td align='left'><span id='curt'>?</span></td></tr>");
document.write("<tr><td height='20px'></td></tr>");
document.write("<tr class='acc'><td align='right'>Тариф:</td><td align='left'>Пиковый</td></tr>");
document.write("<tr class='acc'><td align='right'>Потребление:</td><td align='left'><span id='pp"+N+"1'>?</span> кВт*ч</td></tr>");
document.write("<tr class='acc'><td align='right'>Стоимость:</td><td align='left'><span id='prs"+N+"1'>?</span></td></tr><tr><td height='20px'></td></tr>");
document.write("<tr class='yl'><td align='right'>Тариф:</td><td align='left'>Полупиковый</td></tr>");
document.write("<tr class='yl'><td align='right'>Потребление:</td><td align='left'><span id='pp"+N+"2'>?</span> кВт*ч</td></tr>");
document.write("<tr class='yl'><td align='right'>Стоимость:</td><td align='left'><span id='prs"+N+"2'>?</span></td></tr><tr><td height='20px'></td></tr>");
document.write("<tr class='pri'><td align='right'>Тариф:</td><td align='left'>Ночной</td></tr>");
document.write("<tr class='pri'><td align='right'>Потребление:</td><td align='left'><span id='pp"+N+"3'>?</span> кВт*ч</td></tr>");
document.write("<tr class='pri'><td align='right'>Стоимость:</td><td align='left'><span id='prs"+N+"3'>?</span></td></tr><tr><td height='20px'></td></tr>");
document.write("<div class='ctrb'>");
document.write("<tr><td align='right'>Общее потребление:</td><td align='left'><span id='pp"+N+"'>?</span> кВт*ч</td></tr>");
document.write("<tr><td align='right'>Общая стоимость:</td><td align='left'><span id='prs"+N+"'>?</span></tr>");
document.write("</div><tr><td height='20px'></td></tr></table>");
document.getElementById('curt').innerHTML=tds[curN]; 
for(i=1;i<4;++i){
var px = FloatToString(pp[i])*sc;
document.getElementById("pp"+N+i).innerHTML=parseFloat(px).toFixed(4);
document.getElementById("prs"+N+i).innerHTML=(px*T).toFixed(2)+' '+unt;
P+=px;}
document.getElementById("pp"+N).innerHTML=parseFloat(P).toFixed(4);
document.getElementById("tt"+N).innerHTML=UnixToStr(tt,tz,10);
document.getElementById("prs"+N).innerHTML=(P*T).toFixed(2)+' '+unt;
document.getElementsByName('tnow')[0].innerHTML=UnixToStr(tw,tz,10);}
	
function configIPBoxes(){e=document.forms.conf;
var ap=document.getElementsByName('netm');
st=e.dhcp.checked;
function apmode(m){e.wfiap.disabled=m;e.wfpap.disabled=m;e.ipaap.disabled=m;}		
function clnmode(m){e.wfi.disabled=m;e.wfp.disabled=m;e.ipa.disabled=m;e.mas.disabled=m;e.gte.disabled=m;}	
if(ap[0].checked){apmode(true);clnmode(false);
e.ipa.disabled=st;e.mas.disabled=st;e.gte.disabled=st;}
if(ap[1].checked){apmode(false);clnmode(true);}
}	

function sendtime() {var ut=Date.parse(new Date( Date.parse(document.getElementById('curdt').value)))/1000;
var d='timenow='+ut;
PostData(d,'index23_3.html',false,'Время установлено',false);}

function WriteChart(log,z){
var val=[],tst=[],vf=[],scl;
for(i=0;i<32;++i){
var r=log[i];
var t=r.substr(0,8); 
if (t!='00000000') tst[i]=UnixToStr(t,z,16,0);
else tst[i]=0; 
val[i]=FloatToString(r.substr(8,8)); 	
vf[i]=parseFloat((val[i]*sc).toFixed(4));}
scl=Math.max.apply(null, vf);	
document.write("<div class='wnd'><table><div class='wd'>");
document.write("<tr><td>дата&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;время&nbsp;кВт*ч</td><td></td></tr></div>");
for(i=0;i<32;++i){
document.write("<tr><td><div class='wd'>");
if(tst[i]!=0) document.write(tst[i]+"  "+(val[i]*sc).toFixed(4));
else document.write("--/--/-- --:-- -----");
document.write("</div></td><td><div class='chart'>");
if(tst[i]!=0)document.write("<div style='width:"+Math.floor(160*0.95/(scl+sc)*((val[i]*sc).toFixed(4)))+"px;'></div>");
document.write("</div></td></tr>");}
document.write("</table></div>");}

function setprm(p) {     
document.getElementById("vmin").value=Math.round(p[0]*Ku);
document.getElementById("vmax").value=Math.round(p[1]*Ku);
document.getElementById("imin").value=(p[2]*Ki).toFixed(1);
document.getElementById("imax").value=(p[3]*Ki).toFixed(1);}

function sld(){document.getElementById("vn").innerHTML=document.getElementById("vmin").value+' В';
document.getElementById("vx").innerHTML=document.getElementById("vmax").value+' В';
document.getElementById("in").innerHTML=document.getElementById("imin").value+' A';
document.getElementById("ix").innerHTML=document.getElementById("imax").value+' A';}   

function sendprm(){var d='umin='+Math.round( parseFloat(document.getElementById("vmin").value,10)/Ku);
d+='&umax='+Math.round( parseFloat(document.getElementById("vmax").value,10)/Ku);
d+='&imin='+Math.round( parseFloat(document.getElementById("imin").value,10)/Ki);
d+='&imax='+Math.round( parseFloat(document.getElementById("imax").value,10)/Ki);
d+='&pten='+((document.getElementsByName('pten')[0].checked) ? '1':'0').toString();
d+='&rstt='+document.getElementById('rstt').value;
d+='&rstn='+document.getElementById('rstn').value;
d+='&sav=prs';
PostData(d,'index41.html',false,'Параметры установлены',true);}

function GenTzSel(zn) {
document.write('<tr><td class=\'rl\'>Time zone:</td><td><select size="1" name = "tz" id="tz">');
for(i=0;i<=24;++i) document.write('<option value='+i+'>GMT'+tz[i]+'</option>');
document.write('</select></td></tr>');
document.getElementById('tz').value = zn;}


function PrintIPInput(title,name,value){document.write("<tr><td class='rl'>"+title+"</td><td><input type='text' required size='20' name='"+name+"' value='"+value+"' title='IP адрес xxx.xxx.xxx.xxx' pattern='^\\d{1,3}\.\\d{1,3}\.\\d{1,3}\.\\d{1,3}$' /></td></tr>");}
function PrintMACInput(title,name,value){document.write("<tr><td class='rl'>MAC:</td><td><input type='text' required size='20' name='"+name+"' value='"+value+"' title='MAC адрес xx-xx-xx-xx-xx-xx' pattern='^([0-9a-fA-F]{2}([-]|$)){6}$|([0-9a-fA-F]{4}([.]|$)){3}$' /></td></tr>");}
function PrintTextInput(title,name,value,min,max){document.write("<tr><td class='rl'>"+title+"</td><td><input type='text' required size='20' name='"+name+"' value="+value+" title='"+min+"-"+max+" символов A-Za-z0-9_\-*!<>)(.@,/'  pattern='^[0-9a-zA-Z_\\-*!<>.@\,/)(\s]{"+min+","+max+"}$' /></td></tr>");}
function PrintTextInputNoReg(title,name,value,min,max){document.write("<tr><td class='rl'>"+title+"</td><td><input type='text' required size='20' name='"+name+"' value="+value+" title='"+min+"-"+max+" символов'/></td></tr>");}
function PrintLabel(title,value){document.write("<tr><td class='rl'>"+title+"</td><td align='left'>"+value+"</td></tr>");}
function PrintCheckBox(title,name,checked,action){document.write("<tr><td class='rl'>"+title+"</td><td><input type='checkbox' name='"+name+"' value='1' onclick="+action+" "+checked+" /></td></tr>");}
function PrintInt(title,name,value,min,max){document.write("<tr><td class='rl'>"+title+"</td><td><input type='number' required min='"+min+"' max='"+max+"' name='"+name+"' value ='"+value+"'/></td></tr>");}
function PrintIntId(title,id,value,min,max){document.write("<tr><td class='rl'>"+title+"</td><td><input type='number' required min='"+min+"' max='"+max+"' id='"+id+"' value ='"+value+"'/></td></tr>");}
function PrintSep(){document.write("<tr><td height='20px'></td></tr>");}
function PrintTar(title,name,value){document.write("<tr><td class='rl'>"+title+"</td><td><input type='text' required value='"+value+"' size='6' id='"+name+"' title='число 3-6 символов с десятичной точкой' pattern='[0-9\.]{3,6}'/></td></tr>");}
function PrintSaveBtn(){document.write("<div style='text-align:center;margin-top:10px'><button type='submit' class='btn' name='sav' value='prs'>Сохранить</button></div>");}
function PrintSaveFail(isfail){document.write("<div class='resfail' style='text-align:center;display:"+isfail+"' color='#F00'><font color='red'><h2>Ошибка формата данных!</h2></font><br/></div>");}

function PrintMenu(){
document.write("<div id='conteiner'><nav id='menu1'><ul>");
document.write("<li><a href='index.html'>Главная</a></li>");

document.write("<li><a href='#'>Измерения</a><ul>");
document.write("<li><a href='index31.html'>Счетчик1</a></li>");
document.write("<li><a href='index31_5.html'>Счетчик2</a></li>");
document.write("<li><a href='index32.html'>5 минут</a></li>");
document.write("<li><a href='index33.html'>1 час</a></li>");
document.write("<li><a href='index34.html'>1 день</a></li></ul></li>");

document.write("<li><a href='#'>Контроль</a><ul>");
document.write("<li><a href='index41.html'>Защита</a></li>");
document.write("<li><a href='index42.html'>Менеджер</a></li>");
document.write("<li><a href='index42_2.html'>Таймер</a></li>");
document.write("<li><a href='index43.html'>Астрореле</a></li>");
document.write("<li><a href='index44.html'>ПингТаймер</a></li></ul></li>");

document.write("<li><a href ='#'>Настройки</a><ul>");
document.write("<li><a href='index21.html'>Сеть</a></li>");
document.write("<li><a href='index22.html'>MQTT</a></li>");
document.write("<li><a href='index23.html'>Система</a></li>");
document.write("<li><a href='index23_3.html'>Время</a></li>");
document.write("<li><a href='index23_5.html'>Тарифы</a></li>");
document.write("<li><a href='index24.html'>Журнал</a></li></ul></li>");
document.write("</ul></nav></div>");}

function saveFile(fileName,urlFile){
let a = document.createElement("a");
a.style = "display: none";
document.body.appendChild(a);
a.href = urlFile;
var D = new Date();
a.download ='WS10_'+fileName+'_'+((D).toISOString()).substr(0,19)+'.dat';
a.click();
window.URL.revokeObjectURL(urlFile);
a.remove();
}

function ReadEEPR(v5m,v1h,v1d,z){
document.getElementById('tmr').innerHTML=0;
var str=document.location.toString();
var ref=str.substring(0,str.lastIndexOf('/savehist.html'));
let data = {bufm:[],bufh:[],bufd:[],adr:0x1006,isReady:true};

function PrcdData(){	
function Iter(item){
if(item.substr(0,8)!='00000000')
prnt+=UnixToStr(item.substr(0,8),z,16,0)+' '+(FloatToString(item.substr(8,8))*sc).toFixed(4)+' кВт*ч\r\n'}
data.bufm.sort();data.bufh.sort();data.bufd.sort();
var prnt='5 минут\r\n';data.bufm.forEach(Iter);
prnt+='1 час\r\n';data.bufh.forEach(Iter);
prnt+='1 день\r\n';data.bufd.forEach(Iter);
let blobData = new Blob([prnt], {type: "text/plain"});
let url = window.URL.createObjectURL(blobData);
saveFile('measures',url);	
window.location=ref+'/index23.html';
}
function ReadChunk(){
if (this.readyState==4 && this.status==200) {
for(i=0;i<8;++i){
r=(this.response.mem[i]).substr(5,32);
r1=r.substr(6,2)+r.substr(4,2)+r.substr(2,2)+r.substr(0,2)+r.substr(8,8);
r2=r.substr(22,2)+r.substr(20,2)+r.substr(18,2)+r.substr(16,2)+r.substr(24,8);
if(data.adr<0x1906){data.bufm.push(r1);data.bufm.push(r2);}
else if (data.adr<0x1f06){data.bufh.push(r1);data.bufh.push(r2);}
else{data.bufd.push(r1);data.bufd.push(r2);}}
data.adr+=0x80;data.isReady=true;
document.getElementById('tmr').innerHTML=Math.round((data.adr-0x1006)/(0x2B06-0x1006)*100);
if(data.adr==0x2B06) {clearInterval(timerId);
PrcdData();
}}else{alert(xhr.status+': '+xhr.statusText);window.location=ref+'/index23.html'}}
let timerId = setInterval(function(){
if(data.isReady){
data.isReady=false;	
var xhr=new XMLHttpRequest();	
xhr.open('POST',ref+'/mem.json', true);
xhr.responseType='json';
xhr.onreadystatechange=ReadChunk;
xhr.send('base='+data.adr.toString(16));}},5);
}

function ReadConf(){
document.getElementById('tmr').innerHTML=0;
var str=document.location.toString();
var ref=str.substring(0,str.lastIndexOf('/saveconf.html'));
let data = {buf:[],adr:0x0000,isReady:true};
function PrcdData(){	
function Iter(item){prnt+=item+'\r\n';}
var prnt='';data.buf.forEach(Iter);
let blobData = new Blob([prnt], {type: "text/plain"});
let url = window.URL.createObjectURL(blobData);
saveFile('config',url);	
window.location=ref+'/index23.html';
}
function ReadChunk(){
if (this.readyState==4 && this.status==200) {
for(i=0;i<8;++i){
r=(this.response.mem[i]).substr(5,32);
data.buf.push(r);}
data.adr+=0x80;data.isReady=true;
document.getElementById('tmr').innerHTML=Math.round((data.adr-0x0000)/(0x0800-0x0000)*100);
if(data.adr==0x0800) {clearInterval(timerId);
PrcdData();
}}else{alert(xhr.status+': '+xhr.statusText);window.location=ref+'/index23.html'}}
let timerId = setInterval(function(){
if(data.isReady){
data.isReady=false;	
var xhr=new XMLHttpRequest();	
xhr.open('POST',ref+'/mem.json', true);
xhr.responseType='json';
xhr.onreadystatechange=ReadChunk;
xhr.send('base='+data.adr.toString(16));}},5);
}

function WriteConf(input){
document.getElementById('tmr').innerHTML=0;
var str=document.location.toString();
var ref=str.substring(0,str.lastIndexOf('/restconf.html'));
let data = {buf:[],adr:0x0000,isReady:true};
let file = input.files[0];
let reader = new FileReader();
reader.readAsText(file);
reader.onload = function() {
data.buf = reader.result.split('\r\n');

function ReadChunk(){
if (this.readyState==4 && this.status==200) {
data.adr+=0x40;data.isReady=true;
document.getElementById('tmr').innerHTML=Math.round((data.adr-0x0000)/(0x0800-0x0000)*100);
if(data.adr==0x0800) {
clearInterval(timerId);
window.location=ref+'/reboot.html';
}}else{alert(xhr.status+': '+xhr.statusText);window.location=ref+'/index23.html'}}

let timerId = setInterval(function(){
if(data.isReady){	
data.isReady=false;
var ind=data.adr/0x10;
var dt='write='+data.adr.toString(16);
dt+='&dt1='+data.buf[ind];
dt+='&dt2='+data.buf[ind+1];
dt+='&dt3='+data.buf[ind+2];
dt+='&dt4='+data.buf[ind+3];
var xhr=new XMLHttpRequest();	
xhr.open('POST',ref+'/mem.json', true);
xhr.responseType='json';
xhr.onreadystatechange=ReadChunk;
xhr.send(dt);}},5);

};
reader.onerror = function() {};
}
