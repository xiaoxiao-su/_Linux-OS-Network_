#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/epoll.h>
#define EVENT_SIZE 64

//基于TCP协议
static void usage(const char *const proc)
{
	printf("%s [ip] [port]\n",proc);
}
//设置文件描述符非阻塞，保证对端没有关闭写端时，read函数不会一直阻塞
static void set_nonblock(int new_sock)
{
	int fl = fcntl(new_sock, F_GETFL);
	if( fl < 0 ){
		perror("fcntl");
		exit(1);
	}
	fcntl(new_sock, F_SETFL, fl | O_NONBLOCK);
}

//if 0-> read success, and write success, and remote close
static int read_write_data(int fd)
{
	char buf[10240];
	int len = sizeof(buf)-1;
	ssize_t sz = 0;
	int total = 0;
	memset(buf, '\0', sizeof(buf));
	while( (sz = recv(fd, buf+total, len, 0)) > 0 ){
		total += sz;
		if( sz < len ){
			break;
		}
	}
	if( total > 0 ){
		buf[total] = '\0';
		printf("buf : %s\n",buf);
		memset(buf, '\0', sizeof(buf));
		sprintf(buf, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\nhello world:)",13);//回显消息
		send(fd, buf, sizeof(buf), 0);
	}
	return 0;
}

int start(const char* ip,short port)
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0){
		perror("socket");
		return -1;
	}
	//防止因为timewait情况而使得某个端口无法绑定的情况
	int flag = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
	//绑定前进行本地信息的填充
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);
	//进行绑定
	if( bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0){
		perror("bind");
		exit(1);
	}
	//监听链接，一次最多可以监听5个链接
	if( listen(sock, 5) < 0){
		perror("listen");
		exit(1);
	}
	return sock;
}

int main(int argc,char* argv[])
{
	if(argc != 3){
		usage(argv[1]);
		return 0;
	}
	const char* ip = argv[1];
	short port = atoi(argv[2]);
	int listen_sock = start(ip,port);
	//创建一个epoll句柄，占用一个文件描述符
	int epfd = epoll_create(256);
	if(epfd < 0){
		perror("epoll_create");
		exit(1);
	}

	struct epoll_event _event;
	_event.events = EPOLLIN;//对读事件感兴趣
	if(epoll_ctl(epfd,EPOLL_CTL_ADD,listen_sock,&_event) < 0)//将listen_sock添加进epfd中
	{
		perror("epoll_ctl");
		exit(1);
	}
	//out -> ready fd & event
	struct epoll_event ready_event[EVENT_SIZE];//存放
	int ready_event_size = EVENT_SIZE;
	int timeout = 3000;

	int ready_num = 0;
	while(1){//accept
		switch(ready_num = epoll_wait(epfd, ready_event, ready_event_size, timeout))
		{
			case 0://timeout
				perror("timeout");
				break;
			case -1://error
				perror("epoll_wait");
				break;
			default://success -> we have fd & events ready at least 1
				{
					int i = 0;
					for(; i < ready_num; i++){
						int fd = ready_event[i].data.fd;
						if( fd == listen_sock && (ready_event[i].events & EPOLLIN) ){//listen socket
							struct sockaddr_in client;
							socklen_t len  = sizeof(client);
							int new_sock = accept(fd, (struct sockaddr*)&client, &len);	
							if( new_sock < 0 ){
								perror("accept");
								continue;
							}
							//accpt success
							set_nonblock(new_sock);
							_event.events = EPOLLIN | EPOLLOUT | EPOLLET;
							if(epoll_ctl(epfd, EPOLL_CTL_ADD, new_sock, &_event) < 0){
								perror("epoll_wait");
								close(new_sock);
								continue;
							}
						}else if( (ready_event[i].events & EPOLLIN) && (ready_event[i].events & EPOLLOUT) ){//other socket
							if( read_write_data(fd) == 0 ){
								close(fd);
								epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
							}
						}
					}
				}
				break;
		}
	}
	return 0;
}
