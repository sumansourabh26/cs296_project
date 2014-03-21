#!/bin/bash

cd ./../data

iterVal=1

while [ "$iterVal" -le 15 ]
do
	rerunVal=1
	while [ "$rerunVal" -le 15 ]
	do
		currentFile=g18out-$iterVal-$rerunVal.txt
		echo -n " "$iterVal, $rerunVal," " >> g18_lab05data_01.csv
		grep -P -o "[0-9]+.[0-9]+" $currentFile | xargs | sed 's/ /, /g' >> g18_lab05data_01.csv
		rerunVal=$[$rerunVal + 1]
	done
	iterVal=$[$iterVal + 1]
done 
