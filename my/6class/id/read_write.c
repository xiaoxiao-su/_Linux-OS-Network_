#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
//int g_val = 0;
//int main()
//{
//	FILE* fp = fopen("./log","w+");//W+是可以读也可以写，如果当前路径下没有log文件，就创建它
//	if(fp == NULL){
//		perror("open file error\n");
//		return 1;
//	}
//	char str[] = "you are a good girl";
//	int count = 0;
//	while(count < 20){
//		fwrite(str,1,strlen(str),fp);
//		fputc('\n',fp);
//		count++;
//	}
//	return 0;
//}

//open,write,read,close是系统调用函数，可以通过man查看各函数,是用文件描述符，查看文件指针和文件描述符的区别
int main()
{
	int fd = open("./log",O_CREAT | O_RDWR,0644);
	printf("1、open fd is :%d\n",fd);
	if( fd < 0 ){
		perror("open");
		return 1;
	}
	char* msg = "hello world\n";
	int count = 0;
	fd = open("./log",O_CREAT | O_RDWR,0644);
	printf("1、open fd is :%d\n",fd);
	char buf[1024];
	memset(buf,'\0',sizeof(buf));
	fd = open("./log",O_CREAT | O_RDWR,0644);
	printf("1、open fd is :%d\n",fd);
	while(count < 20){
		//write(fd,msg,strlen(msg));
		ssize_t size = read(fd,buf,sizeof(buf)-1);
		if( size > 0 )
		{
			buf[size] = '\0';
			printf("%s\n",buf);
		}else{ //end of file
			perror("read:");
			break;
		}
		count++;
	}
	close(fd);
	return 0;
}

int main()
{
	//close(0);//stdin,默认通过键盘输入，一切皆文件，dup，dup2（实现文件描述符的重定向）
	close(1);//stdout，默认输出终端，若此时1变成了文件，那么printf打印的信息默认打印到了该文件里面，实现了输出重定向，也可以设置输出到远程网络上，运用到套接字
	//close(2);//stderr，默认输出终端
	int fd = open("./log",O_CREAT | O_RDWR,0644);//此时fd为1,先把最小序号分配出去，从0开始，类似数组下标，
	printf("1、open fd is :%d\n",fd);
	if( fd < 0 ){//打开
		perror("open");
		return 1;
	}
	
	printf("open fd is:%d\n",fd);
}
