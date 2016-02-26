#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
int main()
{
	int fd = open("fifo_pipe",O_WRONLY,0);//以只写的方式打开
	if(fd < 0){
		perror("error");
		return 2;
	}
	char buf[1024];
	while(1){
		printf("client Enter :");
		fflush(stdout);
		memset(buf,'\0',sizeof(buf));
		fgets(buf,sizeof(buf)-1,stdin);
		buf[strlen(buf)-1] = '\0';
		write(fd,buf,strlen(buf));
		if(strcasecmp(buf,"Quit") == 0){//忽略大小写
			break;
		}
	}
	close(fd);
	printf("client Quit\n");
	return 0;
}
