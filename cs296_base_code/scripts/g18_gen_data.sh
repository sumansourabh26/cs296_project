#!/bin/bash

iterVal=1

executable="./../mybins/cs296_18_exe"
output="./../data"

while [ "$iterVal" -le 15 ]
do
	rerunVal=1
	while [ "$rerunVal" -le 15 ]
	do
		./$executable $iterVal > $output/g18out-$iterVal-$rerunVal.txt
		rerunVal=$[$rerunVal + 1]
	done
	iterVal=$[$iterVal + 1]
done
