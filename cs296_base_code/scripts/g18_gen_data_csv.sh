#!/bin/bash

iterVal=1

executable="./../mybins/cs296_18_exe"
output="./../data"

while [ "$iterVal" -le 15 ]
do
	rerunVal=1
	while [ "$rerunVal" -le 15 ]
	do
		./$executable $iterVal > $output/temp
		echo -n " "$iterVal, $rerunVal," " >> $output/g18_lab05data_02.csv
		grep -P -o "[0-9]+.[0-9]+" $output/temp | xargs | sed 's/ /, /g' >> $output/g18_lab05data_02.csv
		rerunVal=$[$rerunVal + 1]
		rm $output/temp
	done
	iterVal=$[$iterVal + 1]
done
