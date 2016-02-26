#!/bin/bash

read passwd
count=0
while [ ! $"X${passwd}" == "Xyes" ]
do
	let count++
	if [ $count -gt 5 ];then
		echo "you have try 5 times,sorry!"
		exit 1
	fi
	echo "Please try again"
	read passwd
done
echo "success!"
