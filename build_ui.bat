@ECHO OFF
SETLOCAL
SET "sourcedir=C:\BOGD-PROJECTS\WebguiappTemplate\WEBUI"
SET "keepfile=espfs.paths"
SET "keepdir=keep"

FOR /d %%a IN ("%sourcedir%\*") DO IF /i NOT "%%~nxa"=="%keepdir%" RD /S /Q "%%a"
FOR %%a IN ("%sourcedir%\*") DO IF /i NOT "%%~nxa"=="%keepfile%" DEL "%%a
cd C:\BOGD-PROJECTS\webui\
quasar %build
xcopy /s C:\BOGD-PROJECTS\webui\dist\spa C:\BOGD-PROJECTS\WebguiappTemplate\WEBUI