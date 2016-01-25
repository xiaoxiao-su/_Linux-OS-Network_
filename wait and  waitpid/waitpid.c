#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
//创建多个进程，并且waitpid多个进程
#define _NUM_ 10
#define _INIT_VAL_ -1
pid_t id_num[_NUM_];
int m = 0;
static void run_proc()
{
	int timeCount = rand()%10;
	//sleep(timeCount);
	sleep(1);
	printf("child wait success\n");
	printf("child:pid:%d,timeCount:%d\n",getpid(),timeCount);
}
void init_num_proc()//初始化进程
{
	int i = 0;
	int num = sizeof(id_num)/sizeof(id_num[0]);
	for(;i<num;i++)
	{
		id_num[i] = _INIT_VAL_;
	}
}
void creat_num_proc()
{
	int i = 0;
	int num = sizeof(id_num)/sizeof(id_num[0]);
	for(;i<num;i++)
	{
		pid_t id = fork();
		if(id == 0){
			run_proc();
			//sleep(1);
			exit(i);
		}else{
			id_num[i] = id;
		}
	}
}
void wait_num_proc()
{
	int i = 0;
	int status = 0;
	int num = sizeof(id_num)/sizeof(id_num[0]);
	pid_t dead_id;
	for(;i<num;i++)
	{
		if(id_num[i] == _INIT_VAL_){
			continue;
		}
		dead_id = waitpid(id_num[i],&status,0);
		if(dead_id == id_num[i] && WIFEXITED(status)){
			sleep(2);
			printf("child%d exit code:%d\n",i,WEXITSTATUS(status));
			//exit(7);
		}else{
			printf("Now runing...wait...");
			sleep(4);
		}
	}
}
int main()
{
	init_num_proc();//初始化
	creat_num_proc();
	wait_num_proc();
	return 0;
}
