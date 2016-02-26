#!/bin/bash

#while循环
#read count
#index=0
#while [ &{index} -le &{count} ]
#do
#	echo &index
#	#let index++
#	((index++))
#done

#for循环
#read count1
##for count1 in {a..z} 
#for count1 in {1..100}
#do
#	sleep 1
#	echo $count1
#done

for count1 in $#
do
	sleep 1
	echo $count1
done


##另一种形式的for循环
#read top
#for (( i=0;i<$top ;i++ ))  #若是空循环，不执行任何语句，就在do和done中间加一个分号:
#do
#	sleep 1
#	echo $top
#done

#do--while循环
#read top
#count=0
#until [ ${count} -ge ${top} ];do #知道count大于等于top，要不然就输出count
#	echo $count
#	let count++
#done

#for循环怎么写死循环
#for (( ; ; ))
#do
#	sleep 1
#	echo "dead"
#done

#while语句怎么写死循环
#while :   #：表示恒成立
#do 
#	echo "dead"
#done



