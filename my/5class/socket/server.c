#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
//基于流式tcp

void recycle(int sig){//捕获信号
	pid_t id;
	while((id = waitpid(-1,NULL,WNOHANG)) > 0){
		printf("wait child %d\n",id);
	}
}
static void usage()
{
	printf("%s [ip] [port]\n");
}
int start(char* ip,short port)//成功的话返回sock，否则返回-1
{
	//step 1
	int sock_fd = socket(AF_INET,SOCK_STREAM,0);//IPV4协议，流式套接，创建套接，成功返回新的套接，否则返回-1
	if(sock_fd == -1){
		perror("socket");
		return -1;
	}
	//step 2
	struct sockaddr_in local;//绑定本地信息
	local.sin_family = AF_INET;
	local.sin_port = htons(port);//将主机序列转换成网络序列,host -> net
	inet_aton(ip,&local.sin_addr);//ip -> int
	if(bind(sock_fd,(struct sockaddr*)&local,sizeof(local)) == -1){
		perror("bind");//绑定
		return -1;
	}
	//step 3
	if(listen(sock_fd,5) == -1){//监听，当我去accept新的链接时候，最多稚嫩观看到5个链接，维护系统的开销
		perror("listen");
		return -1;
	}
	return sock_fd;
}
void echo_data(int new_sock)
{
 	while(1){
		char buf[1024];
		memset(buf,'\0',sizeof(buf));
		ssize_t sz = read(new_sock,buf,sizeof(buf)-1);
		if(sz > 0){
			buf[sz] = '\0';
			write(new_sock,buf,strlen(buf));
			printf("%s\n",buf);
		}else if(sz == 0){
			printf("client is close\n");
			close(new_sock);
			break;
		}else{
			break;
		}
	}
}
static void *service(void *arg)
{//方法三：线程
	printf("thread is create && detach success\n");
	pthread_detach(pthread_self());
	int new_sock = (int)arg;
	echo_data(new_sock);
}
int main(int argc,char *argv[])
{
	if(argc != 3){
		usage();
		return 1;
	}
	int port = atoi(argv[2]);//string -> int
	int listen_sock = start(argv[1],port);
	if(listen_sock == -1){
		return -1;
	}
	//signal(SIGCHLD,recycle);//多进程的捕捉信号
	signal(SIGCHLD,SIG_IGN);//若信号SIGCHLD，则忽略它
	while(1)
	{
		//step 4
		struct sockaddr_in remote;//定义用户缓冲区
		memset(&remote,'\0',sizeof(remote));
		socklen_t len = sizeof(remote);//用户缓冲区的大小
		int new_sock = accept(listen_sock,(struct sockaddr*)&remote,&len);//得到新的套接，底层已经把对端链接好了，所以取到新的套接就直接可以保证数据有序可靠的传输
		if(new_sock < 0)
		{
			perror("accept");
		}else{
			//线程使用套接
			printf("get a new client\n");
			pthread_t tid;
			int ret = pthread_create(&tid,NULL,service,(void*)new_sock);
			if(ret == 0){
				perror("pthread_create");
				return -1;
			}
	//方法二：创建进程，多进程间使用套接字
	//		printf("get a new client\n");
	//		pid_t id = fork();
	//		if(id == 0){//子进程
	//			close(listen_sock);
	//			while(1){
	//				char buf[1024];
	//				memset(buf,'\0',sizeof(buf));
	//				ssize_t sz = read(new_sock,buf,sizeof(buf));
	//				if(sz > 0){
	//					buf[sz] = '\0';
	//					write(new_sock,buf,strlen(buf));
	//					printf("%s\n",buf);
	//				}else if(sz == 0){
	//					printf("client is close\n");
	//					close(new_sock);
	//					break;
	//				}else{
	//					
	//				}
	//			}
	//			exit(0);
	//		}else{//父进程
	//			
	//		}
		}
	//方法一：单进程间使用套接字
	//		while(1){
	//			char buf[1024];
	//			memset(buf,'\0',sizeof(buf));
	//			ssize_t sz = read(new_sock,buf,sizeof(buf));
	//			if(sz > 0){
	//				buf[sz] = '\0';
	//				write(new_sock,buf,strlen(buf));
	//				printf("%s\n",buf);
	//			}else if(sz == 0){
	//				printf("client is close\n");
	//				close(new_sock);
	//				break;
	//			}else{
	//				
	//			}
	//		}
	//	}
	}
	return 0;
}
