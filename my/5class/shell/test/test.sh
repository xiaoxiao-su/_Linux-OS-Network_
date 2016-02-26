#!/bin/bash
#read val
#test $val -eq 0
#echo  $?
#[ $val -eq 0 ]
#echo $?
#if test $val -eq 0;then 
#    echo "girl"
#else
#    echo "boy"
#fi
read sex

if [ "X$sex" == "Xman" ];then #加入X是为了防止sex是空串，两个命令写在一起要用分号隔开，shell下的判断语句没有{}符号，
    echo "hello boy"
elif [ "X$sex" == "Xwomen" ];then #注意这里的elif
    echo "hello girl"
else
    echo "unknow"
fi #语句是以fi结束的


val=""
[ "X$val" == "Xboy" ] #使用=也可以进行比较，但是建议使用==
echo $?
[ -d "./log" ] # 判断当前目录底下是否有log这个目录，-f判断是否有该文件
echo $?

if [ -d "./log" ];then
    echo "log Is dir"
fi

if [ -f "file" ];then
    echo "file Is file"
fi

if [ -f "file1" ];then
    :   #这是一条空语句，什么操作也不做，但是冒号不可以去掉，不像c语言
fi


if :;then
    echo ": is always true"
fi

[ ! -d "./log" ] || {  #相当于if else
    echo "dir Is dir"
}

[ -f "file" ] && {   #相当于 if then 
    echo "file Is file"
}
#&&和||用于连接两个命令，而-a和-o仅用于在测试表达式中连接两个测试条件

read val1 #读入一个变量
read val2
[ $val1 -eq 0 -a  $val2 -eq 1] #-a  在两个条件之间表示逻辑与&&
echo $?

[ $val1 -eq 0 -o  $val2 -eq 1] #-o  在两个条件之间表示逻辑或||
echo $?


#整数比较：是否相等（-eq），大于（-gt），大于等于（-ge），小于（-lt），小于等于（-le）
#在shell脚本下：0表示真，非0为假
#$? 取到test的返回值


#case语句，与c语言中的switch，case语句的不同在于：c语言中的switch语句只能判断字符或者数字，而shell中的case语句什么都可以判断,比如指针、结构体、正则表达式、
read val3  
case $val3 in
    'a' )
    echo "a"
    ;;
    'b' )
    echo "b"
    ;;
    '*' )
    echo "*"
    ;;
	"start" )
	echo "This is start"
	"stop"|"start" ) #其一满足就执行该语句
	echo "this is stop and start"
	;;
esac 


echo $0 $1 $2 $3 #$0是可执行文件名称、$1是第一个命令参数...类似于main函数里的char* argv[]
$0
