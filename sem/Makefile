#my_sem:my_sem.h my_sem.c
#	gcc -o my_sem my_sem.h my_sem.c
#.PHONY:clean
#clean:
#	rm -rf my_sem

#链接静态库

libmy_sem.a:my_sem.o
	ar rcv libmy_sem.a my_sem.o
my_sem.o:my_sem.c
	gcc -c my_sem.c -o my_sem.o
.PHONY:clean
clean:
	rm -rf libmy_sem.a lib my_sem.o
.PHONY:lib
lib:
	mkdir lib
	cp my_sem.h lib
	cp libmy_sem.a lib
