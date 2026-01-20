 #!/bin/sh
echo ****************Generate release artefacts************************
VER=$(cat version.txt)
PROJ_NAME=$1
HW_REV=$2
TARGET=$3
echo "Artefacts version: ${VER}"
echo "Device type: ${TARGET}"
echo "Project name: ${PROJ_NAME}"
echo "Hardware revision: ${HW_REV}"

if [ "$TARGET" = "esp32" ]; then
	BOOTLOADER_OFFSET=0x1000  
else
  	BOOTLOADER_OFFSET=0x0000
fi

esptool.py --chip ${TARGET} merge_bin \
--output ./build/${PROJ_NAME}_${VER}_hw${HW_REV}_ff.bin \
${BOOTLOADER_OFFSET} ./build/bootloader/bootloader.bin \
0x8000 ./build/partition_table/partition-table.bin \
0x3C000 ./build/ota_data_initial.bin \
0x40000 ./build/${PROJ_NAME}.bin

cp ./build/${PROJ_NAME}.bin ./build/${PROJ_NAME}_${VER}_hw${HW_REV}_ota.bin