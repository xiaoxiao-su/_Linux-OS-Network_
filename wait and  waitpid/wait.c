#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
	pid_t id = fork();
	if(id == 0){
	printf("child:pid:%d,ppid:%d\n",getpid(),getppid());
	sleep(10);
	exit(3);
	}else{
		printf("This is a father\n");
		int status = 0;
		pid_t dead_id = wait(&status);//父进程等待子进程退出，即使父进程先运			      行完，也会等待子进程运行完
		if(dead_id == -1){
		perror("error");
		}else{
			printf("dead_id:%d\n",dead_id);
			printf("child exit code:%d\n",(status>>8)&0xff);
			//printf("child exit code:%d\n",WEXITSTATUS(status));
			printf("child get signal:%d\n",status&0xff);
			//printf("child get signal:%d\n",WIFEXITED(status));
		}
	}
	return 0;
}
