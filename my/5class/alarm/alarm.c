#include <stdio.h>
#include <signal.h>
int main()
{
	alarm(1);//此函数的返回值是0或者是上一次闹钟的剩余秒数
	int count = 0;
	while(1){
		printf("I am alive;%d\n",count++);
	}
	return 0;
}
