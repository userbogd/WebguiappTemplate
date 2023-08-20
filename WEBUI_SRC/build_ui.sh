#!/bin/bash
quasar b
cd /home/bogdan/BOGD_PROJECTS/WebguiappTemplate/WEBUI_DIST
ls | grep -xv "espfs.paths" | xargs rm -r
cp -r /home/bogdan/BOGD_PROJECTS/WebguiappTemplate/WEBUI_SRC/dist/spa/. /home/bogdan/BOGD_PROJECTS/WebguiappTemplate/WEBUI_DIST/
