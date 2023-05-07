objects_dscr = ["object_1", "object_2", "object_3", "object_4", "object_5", "object_6",
 "object_7", "object_8", "object_9", "object_10", "object_11", "object_12", "object_13", 
 "object_14", "object_15", "object_16"];
actions_dscr = ["action_1", "action_2", "action_3", "action_4"];

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

function savetm(n) {
var payload = "tmrec={\"num\":"+n+",";
payload += "\"enab\":"+((document.getElementById("encb"+n).checked)?1:0)+",";
payload += "\"prev\":"+((document.getElementById("prev"+n).checked)?1:0)+",";
payload += "\"name\":\""+document.getElementById("tname"+n).value+"\",";
payload += "\"obj\":"+document.getElementById("object"+n).value+",";
payload += "\"act\":"+document.getElementById("action"+n).value+",";
payload += "\"cron\":\""+document.getElementById("cron"+n).value+"\"";
payload += "}";
console.log(payload);
PostData(payload, "application.html", false, false, true);
}
function deltm(n) {
	if(confirm("Confirm delete timer "+n+"?") == true){
	PostData("deltimer="+n, "application.html", false, false, true);}}
function addtm() {
	PostData("addtimer=any", "application.html", false, false, true);}
function extractSelectArr(select){
  var result = [];
  var options = select && select.options;
  var opt;
  for (var i=0, iLen=options.length; i<iLen; i++) {
    opt = options[i];
    if (opt.selected) {
	  if(isNaN(opt.value))
	  	{
		return opt.value;
		}
      result.push(opt.value);
    }}
 
  var grouped = "";
  var intbeg;
  var inside = false;
  for ( i=0; i <result.length;i++)
  	{
		if(parseInt(result[i+1]) == (parseInt(result[i]) + 1))
		{
			if(!inside)
				intbeg = result[i];
			inside = true; 
		}
		else
		{
			if(inside)
			{
				inside=false;
				if((parseInt(result[i]) - parseInt(intbeg)) > 1 )
					grouped+=intbeg+"-"+result[i];
				else
					grouped+=intbeg+","+result[i];
			}
			else
			grouped+=result[i];
		}
		if(i < result.length -1 && !inside)
		grouped+=",";
	}
  return grouped;
}
function handleSelect(tnum, type){
	var cinp = document.getElementById("cron" + tnum);
	var c = (cinp.value).split(" ");
	if(c.length != 6)
	{
		alert("Cron string was edited and not valid");
		return;
	}
	switch(type)
	{
		case 1:
		var s = extractSelectArr(document.getElementById("seconds"));
		if (s != null) c[0] = s;
		break;
		case 2:
		var m = extractSelectArr(document.getElementById("minutes"));
		if (m != null) c[1] = m;
		break;		
		case 3:
		var h = extractSelectArr(document.getElementById("hours"));
		if (h != null) c[2] = h;
		break;		
		case 4:
		var d = extractSelectArr(document.getElementById("days"));
		if (d != null) c[3] = d;
		break;		
		case 5:
		var mm = extractSelectArr(document.getElementById("months"));
		if (mm != null) c[4] = mm;
		break;		
		case 6:
		var w = extractSelectArr(document.getElementById("weekdays"));
		if (w != null) c[5] = w;
		break;		
	}
	cinp.value = c[0] + " " + c[1] + " " + c[2] + " " + c[3] + " " + c[4] + " " + c[5];
}

function setcron(n) {
	var target = document.getElementById("cronext" + n);
	var content = "";
	content +=("<div><div><label class=\"selhed\" for=\"seconds\">Seconds:</label></div>");
	content += ("<div><select multiple size=\"7\" class=\"crselect\" name=\"selectSeconds" + n + "[]\" id=\"seconds\" onchange=\"handleSelect("+n+", 1)\">");
	content += ("<option value=\"*\">Every Sec</option>");
	content += ("<option value=\"*/2\">Even Sec</option>");
	content += ("<option value=\"1-59/2\">Odd Sec</option>");
	content += ("<option value=\"*/5\">Every 5 Sec</option>");
	content += ("<option value=\"*/15\">Every 15 Sec</option>");
	content += ("<option value=\"*/30\">Every 30 Sec</option>");
	for (s = 0; s < 60; s++) { content += ("<option value=\"" + s + "\">" + s + "</option>"); }
	content += ("</select></div></div>");

	content +=("<div><div><label class=\"selhed\" for=\"seconds\">Minutes:</label></div>");
	content += ("<div><select multiple size=\"7\" class=\"crselect\" name=\"selectMinutes" + n + "[]\" id=\"minutes\" onchange=\"handleSelect("+n+", 2)\">");
	content += ("<option value=\"*\">Every Min</option>");
	content += ("<option value=\"*/2\">Even Min</option>");
	content += ("<option value=\"1-59/2\">Odd Min</option>");
	content += ("<option value=\"*/5\">Every 5 Min</option>");
	content += ("<option value=\"*/15\">Every 15 Min</option>");
	content += ("<option value=\"*/30\">Every 30 Min</option>");	
	for (s = 0; s < 60; s++) { content += ("<option value=\"" + s + "\">" + s + "</option>"); }
	content += ("</select></div></div>");
	
	content +=("<div><div><label class=\"selhed\" for=\"hours\">Hours:</label></div>");
	content += ("<div><select multiple size=\"7\" class=\"crselect\" name=\"selectHours" + n + "[]\" id=\"hours\" onchange=\"handleSelect("+n+", 3)\">");
	content += ("<option value=\"*\">Every Hour</option>");
	content += ("<option value=\"*/2\">Even Hours</option>");
	content += ("<option value=\"1-23/2\">Odd Hours</option>");
	content += ("<option value=\"*/6\">Every 6 Hours</option>");
	content += ("<option value=\"*/12\">Every 12 Hours</option>");
	for (s = 0; s < 24; s++) { content += ("<option value=\"" + s + "\">" + s + "</option>"); }
	content += ("</select></div></div>");
	
	content +=("<div><div><label class=\"selhed\" for=\"days\">Days:</label></div>");
	content += ("<div><select multiple size=\"7\" class=\"crselect\" name=\"selectDays" + n + "[]\" id=\"days\" onchange=\"handleSelect("+n+", 4)\">");
	content += ("<option value=\"*\">Every Day</option>");
	content += ("<option value=\"*/2\">Even Days</option>");
	content += ("<option value=\"1-31/2\">Odd Days</option>");
	content += ("<option value=\"*/5\">Every 5 Days</option>");
	content += ("<option value=\"*/10\">Every 10 Days</option>");
	content += ("<option value=\"*/15\">Every 15 Days</option>");	
	for (s = 0; s < 32; s++) { content += ("<option value=\"" + s + "\">" + s + "</option>"); }
	content += ("</select></div></div>");
	
	content +=("<div><div><label class=\"selhed\" for=\"months\">Months:</label></div>");
	content += ("<div><select multiple size=\"7\" class=\"crselect\" name=\"selectMonths" + n + "[]\" id=\"months\" onchange=\"handleSelect("+n+", 5)\">");
	content += ("<option value=\"*\">Every Month</option>");
	content += ("<option value=\"*/2\">Even Month</option>");
	content += ("<option value=\"1-11/2\">Odd Month</option>");
	content += ("<option value=\"*/4\">Every 4 Month</option>");
	content += ("<option value=\"*/6\">Every half Year</option>");
	content += ("<option value=\"1\">Jan</option>");
	content += ("<option value=\"2\">Feb</option>");	
	content += ("<option value=\"3\">Mar</option>");
	content += ("<option value=\"4\">Apr</option>");
	content += ("<option value=\"5\">May</option>");
	content += ("<option value=\"6\">Jun</option>");
	content += ("<option value=\"7\">Jul</option>");
	content += ("<option value=\"8\">Aug</option>");
	content += ("<option value=\"9\">Sep</option>");
	content += ("<option value=\"10\">Oct</option>");
	content += ("<option value=\"11\">Nov</option>");
	content += ("<option value=\"12\">Dec</option>");
	content += ("</select></div></div>");
	
	content +=("<div><div><label class=\"selhed\" for=\"weekdays\">Weekdays:</label></div>");
	content += ("<div><select multiple size=\"7\" class=\"crselect\" name=\"selectWeekday" + n + "[]\" id=\"weekdays\" onchange=\"handleSelect("+n+", 6)\">");
	content += ("<option value=\"*\">Every Weekday</option>");
	content += ("<option value=\"1-5\">Monday-Friday</option>");
	content += ("<option value=\"0,6\">Weekend Days</option>");
	content += ("<option value=\"0\">Sun</option>");
	content += ("<option value=\"1\">Mon</option>");	
	content += ("<option value=\"2\">Tue</option>");
	content += ("<option value=\"3\">Wed</option>");
	content += ("<option value=\"4\">Thu</option>");
	content += ("<option value=\"5\">Fri</option>");
	content += ("<option value=\"6\">Sat</option>");
	content += ("</select></div></div>");
	var mainbut = document.getElementById("setcronbut"+n);
	mainbut.innerHTML = "Close editor";
	mainbut.onclick = function (){ 	var target = document.getElementById("cronext"+n);
	target.innerHTML = ""; mainbut.innerHTML = "Open editor"; mainbut.onclick = function(){setcron(n)};}
	target.innerHTML = content;
}
function drawtimers(tarr) {
	var num = tarr.length;
	var target = document.getElementById("timer");
	var content = "";
	for (i = 1; i <= num; i++) {
		if(tarr[i-1].del == 1) continue;
		content += ("<div class=\"timer\">");
		content += ("<label class=\"tmlab\">Timer " + i + "</label>");
		content += ("<div class=\"timerrec\">");

		content += ("<div class=\"nowrap\">");
		content +=("<label for=\"encb"+i+"\">Enabled:  </label>");
		var enb = (tarr[i - 1].enab == 1) ? "checked" : "";
		content += ("<label  class=\"switch\"><input type=\"checkbox\" id=\"encb"+i+"\" value=\"1\" "+enb+"><span class=\"slider round\"></span></label></div>");

		content += ("<div class=\"nowrap\">");
		content +=("<label for=\"encb"+i+"\">Last scheduled:  </label>");
		enb = (tarr[i - 1].prev == 1) ? "checked" : "";
		content += ("<label  class=\"switch\"><input type=\"checkbox\" id=\"prev"+i+"\" value=\"1\" "+enb+"><span class=\"slider round\"></span></label></div>");


		content += ("<div class=\"nowrap\">");
		content +=("<label for=\"tname"+i+"\">Timer name:</label>");
		content += ("<input  type=\"text\" id=\"tname" + i + "\" value=\"" + tarr[i - 1].name + "\"></input></div>");

		content += ("<div class=\"nowrap\">");
		content +=("<div><label for=\"object"+i+"\">Object:</label>");
		content += ("<select class=\"\" id=\"object"+i+"\">");
		for (k = 0; k < objects_dscr.length; k++) {
			var selected = (tarr[i - 1].obj == k) ? "selected" : "";
			content += ("<option value=\"" + (k) + "\" " + selected + ">" + objects_dscr[k] + "</option>");}
		content += ("</select></div></div>");

		content += ("<div class=\"nowrap\">");
		content +=("<div><label for=\"action"+i+"\">Action:</label>");
		content += ("<select class=\"\" id=\"action"+i+"\">");
		for (k = 0; k < actions_dscr.length; k++) {
			var selected = (tarr[i - 1].act == k) ? "selected" : "";
			content += ("<option value=\"" + (k) + "\" " + selected + ">" + actions_dscr[k] + "</option>");}
		content += ("</select></div></div>");

		content += ("<div class=\"nowrap\">");
		content +=("<label for=\"cron"+i+"\">Cron:</label>");
		content += ("<input  type=\"text\" id=\"cron" + i + "\" value=\"" + tarr[i - 1].cron + "\"></input></div>");
		content += ("<div><button class=\"tmbtn btn\" type=\"button\" id=\"setcronbut"+i+"\" onclick=\"setcron(" + i + ")\">Open editor</button></div>")
		content += ("</div>");

		/*Extended editor content*/
		content += ("<div class=\"container\" id=\"cronext" + i + "\"></div>");

		content += ("<button class=\"btn\" type=\"button\" onclick=\"savetm(" + i + ")\">Save</button>");
		content += ("<button class=\"btn\" type=\"button\" onclick=\"deltm(" + i + ")\">Delete</button>");
		content += ("</div>");
	}
	target.innerHTML = content;
}


