#!/bin/bash

#输出重定向>、输入重定向<

g_file=file
while read line
do
	#echo $line
	part1=$(echo $line | cut -c 1-3)
	part2=$(echo $line | cut -c 4-6 | tr '[a-z]' '[A-Z]')
	part3=$(echo $line | cut -c 7-9)
	echo "${part3}""${part2}""${part1}" #>>log追加重定向,要不然会覆盖
	sleep 1
#done<${g_file}
done<file >log
