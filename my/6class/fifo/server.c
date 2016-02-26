#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
int main()
{
	if(mkfifo("/home/xiaoxiaosu/class/6class/fifo/fifo_pipe",0666|S_IFIFO) < 0){
		perror("error");
		return 1;
	}
	int fd = open("fifo_pipe",O_RDONLY,0);//以只读的方式打开命名管道
	printf("open file success\n");
	if(fd < 0){
		perror("error");
	}
	char buf[1024];
	while(1){
		memset(buf,'\0',sizeof(buf));
		int len = read(fd,buf,sizeof(buf)-1);
		if(len > 0){
			printf("client say : %s\n",buf);
		}
		if(strcasecmp("Quit",buf) == 0){//忽略大小写的quit
			break;
		}
	}
	close(fd);
	printf("server Quit\n");
	return 0;
}
