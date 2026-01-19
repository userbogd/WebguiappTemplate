 #!/bin/sh
echo OUTPUT GENERATOR
VER=$(cat version.txt)
PROJ_NAME=$1
HW_REV=$2

echo "VERSION ${VER}"
echo "DEVICE ${IDF_TARGET}"
echo "PROJECT NAME ${PROJ_NAME}"
echo "HW revision ${HW_REV}"

esptool.py --chip esp32s3 merge_bin \
--output ./build/${PROJ_NAME}_${VER}_hw${HW_REV}_ff.bin \
0x0000 ./build/bootloader/bootloader.bin \
0x8000 ./build/partition_table/partition-table.bin \
0x3C000 ./build/ota_data_initial.bin \
0x40000 ./build/${PROJ_NAME}.bin
cp ./build/${PROJ_NAME}.bin ./build/${PROJ_NAME}_${VER}_hw${HW_REV}_ota.bin 
