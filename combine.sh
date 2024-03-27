#!/bin/sh
esptool.py --chip esp32s3 merge_bin \
--output ./build/WebguiappTemplate_0000_hw1_ff.bin \
0x0000 ./build/bootloader/bootloader.bin \
0x8000 ./build/partition_table/partition-table.bin \
0x3C000 ./build/ota_data_initial.bin \
0x40000 ./build/WebguiappTemplate.bin
