#!/bin/bash
quasar b
cd ../WEBUI_DIST
ls | grep -xv "espfs.paths" | xargs rm -r
cd ../WEBUI_SRC
cp -r ./dist/spa/. ../WEBUI_DIST/
