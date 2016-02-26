#!/bin/bash


#function是指明fun十一个函数，起到的作用只是直观就知道fun是一个函数而已，不加也可以的
#function fun(){
#	echo "This Is a Function"
#}
#fun  #函数的调用

function fun(){
	echo $1
	echo $2
	echo $3
	echo $@
	echo $$
	echo $!
	echo "this is a function"
}
fun a b c d  #函数的传参数

#fun "hello""good"  #传字符串


#function fun(){
#	echo 1 #函数中的echo语句不多时候，可以使用echo返回值
#	echo "this is a function"
#	#return 100 #当函数中echo语句比较多就无法确定哪一个是返回值，此时就用return，建议都使用return返回值
#}
#ret=$(fun) #或者ret=`fun`
#echo $ret
