#!/bin/bash

for ((i=1; i<17; i++)) do
	diff -q output_ans_$i.txt ./Ans/output_ans_$i.txt 1>/dev/null
	if [[ $? == "0" ]]; then
		echo "Output Feature Map channel $i is correct ~"
	else
		echo "Output Feature Map channel $i have the following mistake :"
		diff  output_ans_$i.txt ./Ans/output_ans_$i.txt
	fi
done

#diff  output_ans_$i.txt ./Ans/output_ans_$i.txt
