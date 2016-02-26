#include <stdio.h>
#incldue <sys/>
#include <c>
int main()
{
	printf("hello world\n,%d,%d\n",getpid(),getppid());
	//当前进程的创建者始终不会改变，而创建的进程一直在改变
	sleep(1);
	return 0;
}
