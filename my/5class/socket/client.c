#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>


static void usage()
{
	printf("./client [remote_ip] [remote_port]\n");
}

int main(int argc,char *argv[])
{
	if(argc != 3){
		return -1;
	}
	short port = atoi(argv[2]);
	int conn_fd = socket(AF_INET,SOCK_STREAM,0);
	if(conn_fd == -1){
		perror("socket");
		return -1;
	}
	struct sockaddr_in remote;
	//memset();
	remote.sin_family = AF_INET;
	remote.sin_port = htons(port);
	inet_aton(argv[1],&remote.sin_addr);
	if(connect(conn_fd,(struct sockaddr*)&remote,sizeof(remote)) == -1){
		perror("conet");
		close(conn_fd);
		return -1;
	}
	printf("connet seccess...\n");
	char buf[1024];
	while(1){
		memset(buf,'\0',sizeof(buf));
		printf("Please Enter :> ");
		gets(buf);
		if(strncasecmp("quit",buf, 4) == 0){
			break;
		}
		fflush(stdout);
		write(conn_fd,buf,sizeof(buf));
		ssize_t sz = read(conn_fd,buf,sizeof(buf));
		if(sz > 0){
			buf[sz] = '\0';
			printf("echo data:%s\n",buf);
		}
	}
	return 0;
}
