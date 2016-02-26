#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	int fd1 = open("./log",O_RDWR);
	printf("fd1 = %d\n",fd1);
	int copyfd = dup(fd1);
	printf("copyfd = %d\n",copyfd);
	if(fd1 == -1){
		printf("open error\n");
		exit(1);
	}
	char *str = "hello bit\n";
	int count = 0;
	while(count<20){
		write(fd1,str,sizeof(str));
		count++;
	}
	return 0;
}
