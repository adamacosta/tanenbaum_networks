#!/bin/bash

#################################################
#
# Build and test all lab exercises from 
# Tanenbaum's Computer Networks 5th Ed
#
#################################################

export DIR1=crc
export DIR2=csma

# ===== Test run =====

echo "=================================================="
echo "    Test 1: Chapter 3 Lab - CRC Error Checking    "
echo "=================================================="

pushd $DIR1 > /dev/null
make > /dev/null
pushd bin > /dev/null
python -m unittest discover
popd > /dev/null
make clean > /dev/null
popd > /dev/null

echo "=================================================="
echo "                Test 1 Complete                   "
echo "=================================================="

echo "=================================================="
echo "    Test 2: Chapter 4 Lab - CSMA/CD Contention    "
echo "=================================================="

pushd $DIR2 > /dev/null
./run.sh
popd > /dev/null

echo "=================================================="
echo "                Test 2 Complete                   "
echo "=================================================="