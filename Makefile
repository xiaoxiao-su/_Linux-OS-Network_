#方法一：分步生成可执行文件
test:test.o
	gcc -o test test.o
test.o:test.s
	gcc -c test.s -o test.o 
test.s:test.i
	gcc -S test.i -o test.s
test.i:test.c
	gcc -E test.c -o test.i
.PHONY:clean
clean:
	rm -rf test.o test.s test.i

#方法二：一步生成可执行文件
test:test.c
	gcc -o test test.c
.PHONY:clean
clean:
	rm -rf test

#方法三：通过定义变量生成可执行文件
SOU=test
DST=test.c
CC=gcc
FLAGS=#-static #编写线程时候：FLAGS=-lpthread

$(SOU):$(DST)
	gcc -o $@ $^ $(FLAGS)
.PHONY:clean
clean:
	rm -rf $(SOU)
