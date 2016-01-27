//多进程间向终端打印消息，并没有遵守互斥原则，此实现各进程对终端访问的互斥，同时引用静态库

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "my_sem.h"//链接静态库

int main()
{
	int f_sem_id = creat_sem(1);//使用互斥信号量（二元信号量）父进程先获取信号量
	init_sem(f_sem_id,0,1);//信号量从下标0开始，被初始化为1
	pid_t id = fork();
	if( id == 0)
	{//child
		int c_sem_id = get_sem(1);
		int count = 3;
		while(1)
		{
			p_sem(c_sem_id,0);//对第一个信号量进行P操作
			printf("A");
			fflush(stdout);
			sleep(rand()%3);
			printf("A");
			fflush(stdout);
			sleep(rand()%3);
			v_sem(c_sem_id,0);//对第一个信号量进行V操作
			count--;
			if(count == 0){
				break;
			}
		}
	}
	else
	{//father
		int count = 3;
		while(1)
		{
			p_sem(f_sem_id,0);
			printf("B");
			fflush(stdout);
			sleep(rand()%3);
			printf("B");
			fflush(stdout);
			sleep(rand()%3);
			v_sem(f_sem_id,0);
			count--;
			if(count == 0){
				break;
			}
		}
	}
	//sleep(3);
	wait(NULL);
	destory_sem(f_sem_id);
	return 0;
}
