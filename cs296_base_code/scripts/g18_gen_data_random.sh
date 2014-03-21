#!/bin/bash

cd ./../data
iterVal=1

while [ "$iterVal" -le 15 ]
do
	rerunVal=1
	while [ "$rerunVal" -le 2 ]
	do
		number=$[$RANDOM%15 + 1]
		sed -n "$[$[$iterVal*15-15] + $number] p" g18_lab05data_02.csv >> g18_lab05data_random.csv
		rerunVal=$[$rerunVal + 1]
	done
	iterVal=$[$iterVal + 1]
done
