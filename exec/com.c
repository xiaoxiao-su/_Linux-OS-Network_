#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
int main()
{
	//putenv("PATH=bin/com");
	printf("pid:%d,ppid:%d\n",getpid(),getppid());
	printf("get PATH : %s\n",getenv("PATH"));//获取环境变量
	return 0;
}
