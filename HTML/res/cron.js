objects_test = ["scene_1","scene_2","scene_3","scene_4","scene_5","scene_6","scene_7","scene_8","scene_9","scene_10","scene_11","scene_12","scene_13","scene_14","scene_15","scene_16"];	
  actions_test = ["start", "stop"];
  timarr_test = [{'num':1, 'obj':2, 'act':0, 'start':1000000000,'cron':'*/2 * * * * *'},
	  {'num':2, 'obj':12,'act':1, 'start':1622222222,'cron':'6 0 12 * * *'},
	  {'num':3, 'obj':8,'act':0, 'start':1675757575,'cron':'* * * * * *'}]; 
  function savetm(n)
  {
	  
  }
  function deltm(n)
  {
	  alert("Delete timer "+n);
	  timarr_test.splice(n-1,1);	
	  drawtimers(timarr_test);
  }
  function closecron(n)
  {
	  var target = document.getElementById("cronext"+n);
	  var content = "";
	  target.innerHTML = content;
  }
  function setcron(n)
  {
	  var target = document.getElementById("cronext"+n);
	  var content = "";
	  content +=("<p>Here extebnded cron editor</p>");
	  content +=("<button class=\"btn\" type=\"button\" onclick=\"closecron("+n+")\">Ready</button>");
	  target.innerHTML = content;
  }
  function drawtimers(tarr)
  {
 	var num = tarr.length;
 	var target = document.getElementById("timer");
 	var content = "";
 	for (i = 1; i<=num; i++)
 		{
		content +=("<div class=\"timer\">");
		content +=("<label class=\"tmlab\">Timer "+i+"</label>");
		content +=("<div class=\"timerrec\">"); 
		
		content +=("<div class=\"nowrap\">");
		//content +=("<label for=\"cron"+i+"\">Cron string:</label>");
		content +=("<input  type=\"text\" id=\"cron"+i+"\" value=\""+tarr[i-1].cron+"\"></input>");
		content +=("<button class=\"tmbtn btn\" type=\"button\" onclick=\"setcron("+i+")\">Set cron</button></div></div>")
		
		content +=("<div id=\"cronext"+i+"\"></div>");
		
		content +=("<input class=\"tmpick\" type=\"​datetime-local\" value=\""+UnixToStr(tarr[i-1].start,10,1)+"\"></input>");
		content +=("<select id=\"action\">");
		for (k = 0; k < actions_test.length; k++){
			var selected = (tarr[i-1].act == k)?"selected":"";
			content +=("<option value=\""+(k+1)+"\" "+selected+">"+actions_test[k]+"</option>");}
		content +=("</select>");
		
		content +=("<select id=\"object\">");
		for (k = 0; k < objects_test.length; k++){
			var selected = (tarr[i-1].obj == k)?"selected":"";
			content +=("<option value=\""+(k+1)+"\" "+selected+">"+objects_test[k]+"</option>");}
		content +=("</select>");
		

	    content +=("<button class=\"btn\" type=\"button\" onclick=\"savetm("+i+")\">Save</button>");
		content +=("<button class=\"btn\" type=\"button\" onclick=\"deltm("+i+")\">Delete</button>");
	    
		content +=("</div>");
		target.innerHTML = content;
 		}
  }
  function applytm()
  {
	  
  }
  function addtm()
  {
	  var num = timarr_test.length + 1; 
	  timarr_test.push({'num':num,'start':1500000000,'cron':'* * * * * *'});
	  drawtimers(timarr_test);
  }