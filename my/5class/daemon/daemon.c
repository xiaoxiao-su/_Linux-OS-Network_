#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
int mydaemon()
{
	umask(0);
	pid_t id = fork();
	if(id > 0){
		exit(0);
	}
	signal(SIGCHLD,SIG_IGN);
	setsid();//建立一个会话
	//if(fork() > 0){//保证后续的操作不嫩过程为会话首进程
	//	exit(0);
	//}
	close(0);
	close(1);
	close(2);
	chdir("/");//修改当前工作目录为根目录
	return 0;
}
int main()
{
	//mydaemon();
	daemon(0,0);//系统调用，该进程调用前是一个普通进程，调用之后就变成一个精灵进程
	while(1){//只有一个一个进程在执行while语句
		sleep(1);
	}
	return 0;
}
