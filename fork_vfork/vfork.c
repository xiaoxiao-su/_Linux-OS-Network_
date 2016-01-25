#include <stdio.h>

#include <sys/types.h>

#include <unistd.h>

#include <errno.h>

#include <stdlib.h>

int g_val = 0;//父子进程共享一个全局变量

int main()
{

	int val = 0;

	pid_t id = vfork();

	if(id < 0){

		printf("vfork error\n");

		exit(1);

	}else if(id == 0){

		val++;

		sleep(2);

		g_val++;

		printf("child:pid:%d,ppid:%d,val:%d,&val:0x%x,g_val:%d,&g_val:0x%x\n",
getpid(),getppid(),val,&val,g_val,&g_val);

		exit(0);//当子进程exec或者exit后，父进程才能执行相关操作

	}else{

		sleep(5);

		printf("father:pid:%d,ppid:%d,val:%d,&val:0x%x,g_val:%d,&g_val:0x%x\n",
getpid(),getppid(),val,&val,g_val,&g_val);

	}

	return 0;

}


