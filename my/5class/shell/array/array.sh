#!/bin/bash
#定义数组，shell不支持多维数组，只支持一维数组，可以有字符下标

arr=('a' 'b' 'c' 'd' 'e') #类似于初始化列表
arr=('aaa' 'bbb' 'ccc' 'd' 'e') #类似于初始化列表
echo ${arr[@]} #打印数组
echo ${arr[*]} #打印数组,两者等价
echo ${#arr[@]} #数组元素个数
echo ${arr[0]} #打印单个字符
echo ${arr[1]}
echo ${arr[2]}
echo ${arr[3]}
echo ${arr[4]}

for val in ${arr[@]} #在每个元素后面加上_bit
do 
	echo ${val}_bit
done

index=0
while [ $index -lt ${#arr[@]} ]
do 
	echo ${arr[$index]}_bit   
	(( index++ ))
	#index=`expr $index + 1`
done

#赋值
arr[0]="000" #打印时候，arr[3]、arr[4]没有赋值，故为NULL，此时数组大小为4，只算赋值的元素个数，但是可以访问arr[3]、arr[4]
arr[1]="111" #无论初始化为字符串还是整数。在shell看来都是字符串
arr[2]="222"
arr[5]="555"

 


