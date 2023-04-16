#!/bin/sh
esptool.py --chip esp32 merge_bin \
--output ./build/webguiapp_combined.bin \
0x1000 ./build/bootloader/bootloader.bin \
0x8000 ./build/partition_table/partition-table.bin \
0x11000 ./build/ota_data_initial.bin \
0x20000 ./build/webguiapp_ref_implement.bin
