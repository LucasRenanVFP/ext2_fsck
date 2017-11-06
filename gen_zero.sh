#!/bin/bash
filename=fs-0x00dcc605-ext2-10240.img
dd if=/dev/zero of=$filename bs=1024 count=10240
