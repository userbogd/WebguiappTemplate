var hedmen = `
        <header class="header">
            <div class="header__container">
                <img src="res/logo.png" alt="LOGO" class="header__img"/>
                <a href="index.html" class="header__logo">~name~ ~serial~</a>
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
                                    <span class="nav__name">UTILITIES</span>
                                    <i class='icon-down-open nav__icon nav__dropdown-icon'></i>
                                </a>

                                <div class="nav__dropdown-collapse">
                                    <div class="nav__dropdown-content">
                                        <a href="application.html" class="nav__dropdown-item">Utilities</a>
                                       
                                    </div>
                                </div>
                            </div>
                            
                            <div class="nav__dropdown">
                                <a href="#" class="nav__link">
                                    <i class='icon-wrench nav__icon'></i>
                                    <span class="nav__name">SETTINGS</span>
                                    <i class='icon-down-open nav__icon nav__dropdown-icon'></i>
                                </a>

                                <div class="nav__dropdown-collapse">
                                    <div class="nav__dropdown-content">
                                        <a href="vendsettings.html" class="nav__dropdown-item">Controller settings</a>
                                    </div>
                                </div>
                            </div>
                        </div>
    
                        <div class="nav__items">
                            <h3 class="nav__subtitle">SYSTEM</h3>
    
                            <div class="nav__dropdown">
                                <a href="#" class="nav__link">
                                    <i class='icon-cog-alt nav__icon' ></i>
                                    <span class="nav__name">SETTINGS</span>
                                    <i class='icon-down-open nav__icon nav__dropdown-icon'></i>
                                </a>

                                <div class="nav__dropdown-collapse">
                                    <div class="nav__dropdown-content">
										<a href="adapters.html" class="nav__dropdown-item">Network</a>
										<a href="services.html" class="nav__dropdown-item">Services</a>
										<a href="system.html" class="nav__dropdown-item">System</a>
                                    </div>
                                </div>

                            </div>
							
                        </div>
						
						<a href="info.html" class="nav__link nav__logo">
                        <i class='icon-info-circled nav__icon' ></i>
                        <span class="nav__logo-name">About</span>
                    </a>
                    </div>
                </div>
            </nav>
        </div>
`;

function PageSurround()
{document.write(hedmen);}

function PrintIPInput(title,name,value){document.write("<tr><td class='rl'>"+title+"</td><td><input type='text' required size='20' name='"+name+"' value='"+value+"' title='IP адрес xxx.xxx.xxx.xxx' pattern='^\\d{1,3}\.\\d{1,3}\.\\d{1,3}\.\\d{1,3}$' /></td></tr>");}
function PrintMACInput(title,name,value){document.write("<tr><td class='rl'>"+title+"</td><td><input type='text' required size='20' name='"+name+"' value='"+value+"' title='MAC адрес xx-xx-xx-xx-xx-xx' pattern='^([0-9a-fA-F]{2}([-]|$)){6}$|([0-9a-fA-F]{4}([.]|$)){3}$' /></td></tr>");}
function PrintTextInput(title,name,value,min,max){document.write("<tr><td class='rl'>"+title+"</td><td><input type='text' required size='20' name='"+name+"' value="+value+" title='"+min+"-"+max+" chars'  pattern='^*{"+min+","+max+"}$' /></td></tr>");}
function PrintTextInputID(title,id,value,min,max){document.write("<tr><td class='rl'>"+title+"</td><td><input type='text' required size='20' id='"+id+"' value="+value+" title='"+min+"-"+max+" chars'  pattern='^*{"+min+","+max+"}$' /></td></tr>");}
function PrintHexInput(title,name,value,min,max){document.write("<tr><td class='rl'>"+title+"</td><td><input type='text' required size='20' name='"+name+"' value="+value+" title='"+min+"-"+max+" chars A-Fa-f0-9'  pattern='^[0-9a-fA-F]{"+min+","+max+"}$' /></td></tr>");}
function PrintTextInputNoReg(title,name,value,min,max){document.write("<tr><td class='rl'>"+title+"</td><td><input type='text' required size='20' name='"+name+"' value="+value+" title='"+min+"-"+max+" chars'/></td></tr>");}
function PrintLabel(title,value){document.write("<tr><td class='rl lab'>"+title+"</td><td align='left' class='lab'>"+value+"</td></tr>");}
function PrintSpanLabel(title,idx){document.write("<tr><td class='rl'>"+title+"</td><td align='left'><span id='"+idx+"'>?</span></td></tr>");}
function PrintCheckBox(title,name,checked,action){document.write("<tr><td class='rl'>"+title+"</td><td><input type='checkbox' name='"+name+"' value='1' onclick="+action+" "+checked+" /></td></tr>");}
function PrintSwitch(title,name,checked,action){document.write("<tr><td class='rl'>"+title+"</td><td><label  class='switch'><input type='checkbox' name='"+name+"' value='1' onclick="+action+" "+checked+" ><span class='slider round'></span></label></td></tr>");}
function PrintInt(title,name,value,min,max){document.write("<tr><td class='rl'>"+title+"</td><td><input type='number' required min='"+min+"' max='"+max+"' name='"+name+"' value ='"+value+"'/></td></tr>");}
function PrintIntId(title,id,value,min,max){document.write("<tr><td class='rl'>"+title+"</td><td><input type='number' required min='"+min+"' max='"+max+"' id='"+id+"' value ='"+value+"'/></td></tr>");}
function PrintSep(){document.write("<tr><td height='20px'></td></tr>");}
function PrintSaveBtn(form){document.write("<button type='submit' class='btn' name='save' value='"+form+"'>Save reboot</button>");}
function PrintApplyBtn(form){document.write("<button type='submit' class='btn' name='apply' value='"+form+"'>Apply</button>");}
function PrintSaveFail(isfail){document.write("<div class='resfail' style='text-align:center;display:"+isfail+"' color='#F00'><font color='red'><h4>Wrong data format!</h4></font><br/></div>");}
