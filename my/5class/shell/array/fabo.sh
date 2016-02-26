#!/bin/bash

one=1
two=1
arr[0]=0
arr[1]=1
index=2
max=$1

while [ $index -le  $max ]
do
	let arr[$index+2]=${arr[$index + 1]}+${arr[$index]}
#	let sum=$one+$two
#	one=$two
#	two=$sum
	(( index++ ))
done
echo "${arr[$index-1]}"
#echo "$sum"


#function sum(){
#	local tmp=$1
#	local tmp1
#	if [ $1 -eq 1 ];then
#		r=1
#	elif
#		tmp1=`expr ${tmp} - 1`
#		sum $tmp1
#		r=`expr $r + $tmp`
#	fi
#}
#
#sum $1
#echo $r
