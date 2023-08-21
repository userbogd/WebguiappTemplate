@ECHO OFF
SETLOCAL
SET "sourcedir=C:\BOGD-PROJECTS\WebguiappTemplate\WEBUI_DIST"
SET "keepfile=espfs.paths"
SET "keepdir=keep"

FOR /d %%a IN ("%sourcedir%\*") DO IF /i NOT "%%~nxa"=="%keepdir%" RD /S /Q "%%a"
FOR %%a IN ("%sourcedir%\*") DO IF /i NOT "%%~nxa"=="%keepfile%" DEL "%%a
xcopy /s "C:\BOGD-PROJECTS\WebguiappTemplate\WEBUI_SRC\dist\spa" "C:\BOGD-PROJECTS\WebguiappTemplate\WEBUI_DIST"





