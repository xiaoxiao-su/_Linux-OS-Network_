#include <stdio.h>
#include <errno.h>

int main()
{
	int i = 0;
	for(;i<128;i++)
	{
		//errno = i;//标准C提供给我们的一个全局变量
		//perror("errno:");
		printf("%d,%s\n",i,strerror(i));
	}
	return 0;
}
