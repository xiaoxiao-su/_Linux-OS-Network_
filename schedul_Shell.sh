#!/bin/bash
					     #shell脚本编写

bar=''                   #定义变量不需要类型,不用分号
index=0

flag=("|" "/" "-" "\\")  #定义数组，\ 和下面的 % 都属于特殊字符，所以需要转义

while [ $index -le 100 ] #while语句进行条件判断
do
	pos=index%4          #或者 let pos=index%4
	bar=${bar}#          # ${bar}是取bar的值
	sleep 0.1
	printf "[%-100s][%d%%][%c]\r" "${bar}" "${index}" "${flag[pos]}";
	(( index++ ))        #或者用let index++
done
