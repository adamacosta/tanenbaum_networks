#!/bin/bash

#################################################
#
# Build and test all lab exercises from 
# Tanenbaum's Computer Networks 5th Ed
#
#################################################

export DIR1=crc

# ===== Test run =====

echo "=================================================="
echo "    Test 1: Chapter 3 Lab - CRC Error Checking    "
echo "=================================================="

cd $DIR1
python test.py 32 8
cd ..

echo "=================================================="
echo "                Test 1 Complete                   "
echo "=================================================="