#!/bin/bash

proc=${basenanme $0}

function usage(){
	echo "Usage:${proc}data1....."
	exit 1
}

[ $# -lt 1 ] && usage

min=$1   #第一个参数
max=$1
sum=0

for val in $@
do
	if [ $min -gt $val ];then
		min=$val
	fi
	if [ $max -lt $val ];then
		max=$val
	fi
	let sum+=$val
done

echo "max = ${max}"
echo "min = ${min}"
echo "sum = ${sum}"
#echo "ibase=10,scale=2"#10进制和精度
#echo $?
