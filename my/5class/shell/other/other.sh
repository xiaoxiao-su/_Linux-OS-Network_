#!/bin/bash

echo $0       #可执行脚本的名称
echo $1 $2 $3 #命令行第一、二、三个参数
echo $#  #参数个数，不输入任何数时shell里是0(不包括可执行文件名)，argc为1（此时的1是可执行文件名的计数）
echo $$  #当前shell进程的PID
echo $!  #但前shell脚本里面离$!最近的后台进程的PID
echo $@  #参数列表
echo $?  #退出码
############
echo $0       #可执行文件
echo $1 $2 $3 #命令行第一、二、三个参数
echo $#  #参数个数，不输入任何数时shell里是0(不包括可执行文件名)，argc为1（此时的1是可执行文件名的计数）
./back_proc
sleep1
./back_proc  #此时$!打印的是这个进程的PID
sleep1
echo $$  #当前shell进程的PID
echo $!  #但前shell脚本里面离$!最近的后台进程的PID
echo $@  #参数列表
echo $?  #退出码
############
shift 1  #shift 2:改变当前参数列表的值（移位）
echo "$1"
echo "$2"
echo "$3"
echo "$4"
sum=0
for val in $@
do
	let sum+=val
	echo "$sum"
done
