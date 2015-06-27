#! /bin/bash

function run_csma {
	pushd bin > /dev/null
	./csma $1 $2
	popd > /dev/null
}

function run_csma_verbose {
	pushd bin > /dev/null
	./csma $1 $2 --verbose
	popd > /dev/null 
}

make > /dev/null

echo "============================================================="
echo "                           CSMA/CD                           "
echo ""
echo "Illustrates how global wait times increase with contention"
echo "for the wire as transmission probability per station per time"
echo "slot increases from 10% to 100%. Time slot is 51 mu secs."

for i in `seq 0.1 0.1 1`;
do
	run_csma 10 $i
done

echo ""
echo "                          COMPLETE                          "
echo "============================================================"

make clean > /dev/null