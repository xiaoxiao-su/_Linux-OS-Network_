#include <stdio.h>
#include <signal.h>
int flag = 1;//volatile防止编译器进行优化 
void handler(int sig)
{
	printf("hello bit\n");
	flag = 0;
}
int main()
{
	signal(SIGINT,handler);
	while(flag);
}
