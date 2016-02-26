#include <stdio.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define _PORT_ 80
#define _BACKLOG_ 5
#define _SIZE_ 10240
#define _TIMEOUT_ 3000

static void set_nonblock(int fd)
{
	int fl = fcntl(fd, F_GETFL);
	if( fl < 0 ){
		perror("fcntl error!\n");
		return;
	}
	if( fcntl(fd, F_SETFL, fl|O_NONBLOCK)){
		perror("fcntl set nonblock error\n");
		return;
	}
}

static int read_data(int fd, char buf[])
{
	int nread = 0;
	int n = 0;
	//read normal data
	while( (nread = read(fd, buf+n, 128)) > 0){
		n = nread;
	}
	return nread; 
}

static int write_data(int fd, char buf[])
{
	int len = strlen(buf);
	int nwrite = 0;
	int send_n = 0;
	do{
		nwrite = write(fd, buf+send_n, len-send_n);
		send_n += nwrite;
	}while(nwrite > 0);
	return nwrite;
}

int epoll_server()
{
	struct sockaddr_in ser;
	struct sockaddr_in cli;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if( sock == 0 ){
		perror("socket");
		return 1;
	}
	set_nonblock( sock );

	ser.sin_family = AF_INET;
	ser.sin_port = htons(_PORT_);
	ser.sin_addr.s_addr = INADDR_ANY;//由系统指定任一个IP地址

	int yes = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

	//bind
	if(bind(sock, (struct sockaddr*)&ser, sizeof(ser)) < 0){
		perror("bind error!");
		return 2;
	}

	if(listen(sock, _BACKLOG_) < 0){
		perror("listen error!");
		return 3;
	}

	int epoll_fd = epoll_create(256);
	if(epoll_fd < 0){
		perror("epoll_create error!");
		close(sock);
		return 4;
	}
	struct epoll_event ev,revent[20];
	
	ev.data.fd = sock;
	ev.events = EPOLLIN;
	if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sock, &ev) != 0){
		perror("epoll_ctl error!");
		return 5;
	}
	//int timeout = _TIMEOUT_;
	int timeout = -1;
	for(;;){
		int revent_size = sizeof(revent)/sizeof(revent[0]);
		int epoll_n = epoll_wait(epoll_fd, revent, revent_size, timeout);
		switch(epoll_n){
			case -1:
				perror("epoll_wait error!");
				exit(6);
				break;
			case 0:
				printf("epoll_wait timeout!\n");
				break;
			default:
				{
					int i = 0;
					int new_fd = 0;
					socklen_t len = sizeof(cli);
					for(; i < epoll_n; i++){
						char buf[_SIZE_];
						memset(buf, '\0', sizeof(buf));
						int fd = revent[i].data.fd;
						if( fd == sock ){//sock ready, accept
							while( new_fd = accept(fd,(struct sockaddr*)&cli, &len) ){
								set_nonblock(new_fd);
								ev.data.fd = new_fd;
								ev.events = EPOLLIN|EPOLLET;
								if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_fd, &ev) < 0){
									perror("add new fd error!\n");
									exit(7);
								}
								printf("get a new client, fd is : %d\n",new_fd);
							}
							continue;
						}
						if( revent[i].events & EPOLLIN){
							int ret = read_data(fd, buf);
							if( ret < 0 ){
								printf("##########################");
								printf("buf : %s\n",buf);
								printf("##########################");
							}else if( ret == 0 ){
								perror("remote cli is close!");
							}else{
								//do nothing
							}
						}
						//echo data back
						ev.data.fd = fd;
						ev.events = revent[i].events | EPOLLOUT;
						if(epoll_ctl(epoll_fd, EPOLL_CTL_MOD, fd, &ev) < 0){
							perror("mod event error");
							//exit(0);
						}
						if(revent[i].events & EPOLLOUT){
							memset(buf, '\0', sizeof(buf));
							sprintf(buf, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\nhello world",13);
							write_data(fd,buf);
							close(fd);
							epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
						}
					}
				}
				break;
		}
	}
}

int main()
{
	epoll_server();
	return 0;
}
