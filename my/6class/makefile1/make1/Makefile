#test:test.c
#	gcc test.c -o test
#.PHONY:clean
#clean:
#	rm -rf test

test:test.o
	gcc test.o -o test
test.o:test.s
	gcc -c test.s -o test.o
test.s:test.i
	gcc -S test.i -o test.s
test.i:test.c
	gcc -E test.c -o test.i
.PHONY:clean
clean:
	rm -rf test.o test.s test.i
