#include <stdio.h>
#include <poll.h>
#include <string.h>

int main()
{
	int timeout = 3000;			   //大概三秒钟
	char buf[1024];
	struct pollfd fd_poll[1];	   //设置只有一个事件
	while(1){
		fd_poll[0].fd = 0;         //关心的是读事件
		fd_poll[0].events = POLLIN;//保存用户感兴趣的事件
		fd_poll[0].revents = 0;	   //保存内核返回的就绪事件
		memset(buf, '\0', sizeof(buf));
		switch( poll(fd_poll, 1, timeout) ){
			case 0:
				perror("timeout!");
				break;
			case -1:
				perror("poll");
				break;
			default:
				{
					if( fd_poll[0].revents & POLLIN ){//read event ready,检查相同位
						gets(buf);
						printf("buf : %s\n",buf);
					}
				}
				break;
		}
	}
	return 0;
}
