#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
void alarm_handler(int sig)
{}

int mysleep(int second)
{
	struct sigaction act,oact;
	memset(&act,0,sizeof(act));
	memset(&oact,0,sizeof(oact));
	act.sa_handler = alarm_handler;//自定义函数
	sigemptyset(&act.sa_mask);//进行清空
	sigaction(SIGALRM,&act,&oact);
	alarm(second);
	pause();//调用自定义函数就会发生出错返回-1
	int ret = alarm(0);//取消闹钟,将闹钟清零了
	printf("%d\n",ret);
	sigaction(SIGALRM,&oact,NULL);//恢复信号处理动作，以免影响原来函数的信号，对函数的顺序执行有一定的影响
	return ret;//返回闹钟以前剩余的秒数
}
int main()
{
	while(1){
		mysleep(3);
		printf("hello bit\n");
	}
	return 0;
}

