#!/bin/bash

function umage(){
	echo ""
}

function exist_dir(){
	dir=$1
	basename $0
}
for dir in $@  #$@是当前参数列表
do 
	if exist_dir "$dir";then
		echo "${dir} is exist,break"
		exit 1
	elif
		echo "${dir} is no exist,creat it"
		mkdir "${dir}"
	fi
done
