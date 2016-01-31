server=shm_server  #shell脚本中定义变量
client=shm_client
CC=gcc
FLAGS=#-static
.PHONY:all
all:$(server) $(client)

#方法一：
$(server):shm_server.c shm_comm.c
	gcc -o $@ $^
$(client):shm_client.c shm_comm.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -rf $(server) $(client)


#方法二

#$(server):shm_server.o shm_comm.o
#	$(CC) -o $@ $^ $(FLAGS) -g
#$(client):shm_client.o shm_comm.o
#	$(CC) -o $@ $^ $(FLAGS) -g #定义为静态链接
#%.o:%.c
#	$(CC) -c $<  #从冒号后面的列表中一个一个取参数
#
#.PHONY:clean
#clean:
#	rm -rf $(server) $(client) *.o

#方法三：静态库的创建

#libmy_shm.a:shm_comm.o
#	ar rcv libmy_shm.a shm_comm.o
#shm_comm.o:shm_comm.c
#	gcc -c shm_comm.c -o shm_comm.o
#.PHONY:clean
#clean:
#	rm -rf libmy_shm.a output shm_comm.o
#.PHONY:output
#output:
#	mkdir output
#	cp shm_comm.h output
#	cp libmy_shm.a output
