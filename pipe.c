#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main()
{
	int fd[2] = {0,0};//进行初始化，0号下标表示读端（像嘴），1号下标是写端（像笔）

	int ret = pipe(fd);//创建了一个管道文件
	if(ret == -1){
		perror("error");
		return 1;
	}
	#ifndef _DEBUG_
	#define _DEBUG_
		printf("fd[0]-> %d,fd[1]-> %d\n",fd[0],fd[1]);
	#endif
	pid_t id = fork();
	if(id < 0){
		perror("error");
		return 2;
	}else if(id == 0){//子进程往管道里面写数据
		close(fd[0]);
		char* str = "haha,I am child";
		char* str1 = "my count id > 5 now...";
		int count = 10;
		while(count > 0){
			if(count < 5){
				sleep(1);
				write(fd[1],str,strlen(str));
			}else{
				sleep(1);
				write(fd[1],str1,strlen(str1));
			}
			count--;
		}
		sleep(4);
		write(fd[1],"quit",4);
	}else{//父进程往管道里面读数据
		close(fd[1]);
		char* buf[1024];
		while(1){
			memset(buf,'\0',sizeof(buf));
			size_t len = read(fd[0],buf,sizeof(buf)-1);//读成功返回值是读的字节数，否则返回0
			if( len > 0 ){
				buf[len] = '\0';
				if(strcmp("quit",buf) == 0){
					printf("child proc Quit\n");
					return;
				}
				printf("child msg is :%s\n",buf);
			}
		}
		wait(NULL);
	}
	return 0;
}
