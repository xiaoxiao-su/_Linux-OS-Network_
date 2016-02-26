#include <stdio.h>
#include <signal.h>

int main()
{
	raise(8);//出现核心转储，自己给自己发送信号
	abort();//自己给自己发送信号
	return 0;
}
