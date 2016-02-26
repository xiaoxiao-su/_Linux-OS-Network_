#include <stdio.h>
#include <signal.h>
#include <string.h>
void handler(int sig)
{
	switch(sig){
		case SIGINT:
			printf("catch a signal sigint:%d\n",sig);
			break;
		case SIGUSR1:
			printf("catch a signal sigusr1:%d\n",sig);
			break;
		default:
			break;
	}
}
//int main()
//{
//	signal(SIGINT,handler);//捕捉信号
//	while(1){
//		printf("hello bit\n");
//	}
//	return 0;
//}

int main()
{
	struct sigaction new_act;
	memset(&new_act,0,sizeof(new_act));
	new_act.sa_handler = handler;
	//new_act.sa_handler = SIG_IGN;//忽略信号处理
	sigemptyset(&new_act.sa_mask);

	
	sigaction(SIGINT,&new_act,NULL);//也可以捕捉信号
	signal(SIGUSR1,handler);
	while(1){
		printf("hello bit\n");
		sleep(1);
	}
}
