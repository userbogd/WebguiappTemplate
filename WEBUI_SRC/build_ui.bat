@ECHO ON
SETLOCAL
SET "sourcedir=..\WEBUI_DIST"
SET "keepfile=espfs.paths"
SET "keepdir=keep"

FOR /d %%a IN ("%sourcedir%\*") DO IF /i NOT "%%~nxa"=="%keepdir%" RD /S /Q "%%a"
FOR %%a IN ("%sourcedir%\*") DO IF /i NOT "%%~nxa"=="%keepfile%" DEL "%%a
xcopy /s /e .\dist\spa  %sourcedir%
