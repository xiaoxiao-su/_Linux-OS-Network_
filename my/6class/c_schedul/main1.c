#include <stdio.h>
#include <string.h>

int main()
{
	int count = 0;
	const char* lable = "|/-\\";
	char buf[51];
	//多开辟一个字节用来存放‘\0’
	memset(buf,'\0',sizeof(buf));
	while(count<=50)
	{
		printf("[%-50s][%d%%][%c]\r",buf,count,lable[count%4]);
		fflush(stdout);
		usleep(100000);
		buf[count] = '#';
		count++;
	}
	printf("\n");
	return 0;
}
