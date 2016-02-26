#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
void handler(int sig)
{
	printf("catch a sig,signum:%d\n",sig);
	exit(1);
}
int show_pending(sigset_t *pending)
{
	if(pending == NULL){
		return 0;
	}
	int i = 1;
	int flag = 0;
	for(;i<32;i++)
	{
		if(sigismember(pending,i))
		{
			printf("1");
			flag = 1;
		}else
		{
			printf("0");
		}
	}
	printf("\n");
	return flag;
}
int main()
{
	signal(SIGINT,handler);//对信号进行自定义函数处理
	sigset_t new;
	sigset_t old;
	sigset_t pending;//pending表

	sigemptyset(&new);//初始化为全0；
	sigemptyset(&old);//初始化为全0；

	sigaddset(&new,SIGINT);//往block表里添加信号有效位
	sigprocmask(SIG_SETMASK,&new,&old);//old表保存老的block表的位
	while(1){	
		sigemptyset(&pending);//初始化pending表
		sigpending(&pending);//获取pending表的信号
		int ret = show_pending(&pending);
		if(ret == 1){
			printf("begin unbrock sig\n");
			sleep(3);
			sigprocmask(SIG_SETMASK,&old,NULL);//恢复block表
		}
		sleep(1);
	}
	return 0;
}
