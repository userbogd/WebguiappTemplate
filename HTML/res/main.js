function PostData(data,page,conf,alrt,reld) {
if(conf){if (!confirm(conf)) return;}
var xhr = new XMLHttpRequest();
xhr.open('POST',page, true);
xhr.timeout = 5000;
xhr.send(data);
xhr.onreadystatechange = function() { 
if (xhr.readyState != 4) return;
if (Number(xhr.status) >= 400) {alert(xhr.status+': '+xhr.statusText);} 
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
/*==================== SHOW NAVBAR ====================*/
const showMenu = (headerToggle, navbarId) =>{
    const toggleBtn = document.getElementById(headerToggle),
    nav = document.getElementById(navbarId)
    // Validate that variables exist
    if(headerToggle && navbarId){
        toggleBtn.addEventListener('click', ()=>{
            // We add the show-menu class to the div tag with the nav__menu class
            nav.classList.toggle('show-menu')
            // change icon
            toggleBtn.classList.toggle('bx-x')
        })
    }
}

