var hedmen = `
        <header class="header">
            <div class="header__container">
                <img src="youlogo.gif" alt="LOGO" class="header__img">
                <a href="index.html" class="header__logo">YouDevice</a>
                <div class="header__toggle">
                    <i class='icon-menu' id="header-toggle"></i>
                </div>
            </div>
        </header>
          <div class="nav" id="navbar">
            <nav class="nav__container">
                <div>
                    <a href="index.html" class="nav__link nav__logo">
                        <i class='icon-home nav__icon' ></i>
                        <span class="nav__logo-name">Home</span>
                    </a>
                    <div class="nav__list">
						<div class="nav__items">
							<h3 class="nav__subtitle">APPLICATION</h3>
                            <div class="nav__dropdown">
                                <a href="#" class="nav__link">
                                    <i class='icon-chart-bar nav__icon'></i>
                                    <span class="nav__name">APPLICATION1</span>
                                    <i class='icon-down-open nav__icon nav__dropdown-icon'></i>
                                </a>

                                <div class="nav__dropdown-collapse">
                                    <div class="nav__dropdown-content">
                                        <a href="#" class="nav__dropdown-item">App1</a>
                                        <a href="#" class="nav__dropdown-item">App2</a>
										<a href="#" class="nav__dropdown-item">App3</a>
                                    </div>
                                </div>
                            </div>
							
						  <div class="nav__dropdown">
                                <a href="#" class="nav__link">
                                    <i class='icon-chart-bar nav__icon' ></i>
                                    <span class="nav__name">APPLICATION2</span>
                                    <i class='icon-down-open nav__icon nav__dropdown-icon'></i>
                                </a>

                                <div class="nav__dropdown-collapse">
                                    <div class="nav__dropdown-content">
                                        <a href="#" class="nav__dropdown-item">App1</a>
                                        <a href="#" class="nav__dropdown-item">App2</a>
                                        <a href="#" class="nav__dropdown-item">App3</a>
                                    </div>
                                </div>

                            </div>
                        </div>
    
                        <div class="nav__items">
                            <h3 class="nav__subtitle">SYSTEM</h3>
    
                            <div class="nav__dropdown">
                                <a href="#" class="nav__link">
                                    <i class='icon-wifi nav__icon' ></i>
                                    <span class="nav__name">NETWORK</span>
                                    <i class='icon-down-open nav__icon nav__dropdown-icon'></i>
                                </a>

                                <div class="nav__dropdown-collapse">
                                    <div class="nav__dropdown-content">
										<a href="set_network.html" class="nav__dropdown-item">Network</a>
                                        <a href="set_eth.html" class="nav__dropdown-item">Ethernet</a>
                                        <a href="set_wifi.html" class="nav__dropdown-item">WiFi</a>
                                        <a href="set_gprs.html" class="nav__dropdown-item">GPRS</a>
										<a href="set_mqtt.html" class="nav__dropdown-item">MQTT</a>
                                    </div>
                                </div>

                            </div>
							<div class="nav__dropdown">
								<a href="#" class="nav__link">
                                    <i class='icon-cog-alt nav__icon' ></i>
                                    <span class="nav__name">STSTEM</span>
                                    <i class='icon-down-open nav__icon nav__dropdown-icon'></i>
                                </a>

                                <div class="nav__dropdown-collapse">
                                    <div class="nav__dropdown-content">
                                        <a href="set_sys.html" class="nav__dropdown-item">System</a>
                                        <a href="set_time.html" class="nav__dropdown-item">Time</a>
										<a href="control.html" class="nav__dropdown-item">Control</a>
                                    </div>
                                </div>
							</div>
							
                        </div>
						
						
                    </div>
                </div>
            </nav>
        </div>
`;

function PageSurround()
{document.write(hedmen);}

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
function PrintSaveFail(isfail){document.write("<div class='resfail' style='text-align:center;display:"+isfail+"' color='#F00'><font color='red'><h4>Неверный формат данных!</h4></font><br/></div>");}
