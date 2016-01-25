#include <stdio.h>

#include <unistd.h>

#include <errno.h>

#include <stdlib.h>

char *msg = "hello bit";

int g_val = 0;//父子进程看起来像是共享同一全局变量，实则并非如此

int main()
{
	
	printf("%s\n",msg)；
	
	int val = 0;
	
	printf("uid:%d,euid:%d,gid:%d,egid:%d\n",getuid(),geteuid(),getgid(),getegid());
	
	pid_t id = fork();
	
	if(id < 0){
		
	printf("fork error\n");
		
	exit(1);
	
	}else if(id == 0){
		
		val++;
		
		g_val++;
		
		printf("child:pid:%d,ppid:%d,val:%d,&val:0x%x,g_val:%d,&g_val:0x%x\n",
		getpid(),getppid(),val,&val,g_val,&g_val);
	
	}else{	
		
		sleep(1);
		
		printf("father:pid:%d,ppid:%d,val:%d,&val:0x%x,g_val:%d,&g_val:0x%x\n",
		getpid(),getppid(),val,&val,g_val,&g_val);
		
		sleep(3);
	
	}
	
	return 0

}


//分析在fork前执行语句printf("%s\n",msg)；重定向到文件中会出现什么结果？

//gcc -o fork fork.c 后执行./fork >file，即输出重定向到文件里面，则输出缓冲由行缓冲变成全缓冲，
即子进程拥有一份缓冲区的拷贝，父进程也有一份缓冲区的拷贝，当子进程执行完return后，刷新自己的缓
冲区，当父进程return后也刷新自己的缓冲区，所以此时虽然只有一条printf语句，但是当输出重定向到文
件里面就会出现两条hello bit语句，若程序运行输出到终端上，就只会出现一条hello bit（行缓冲）
