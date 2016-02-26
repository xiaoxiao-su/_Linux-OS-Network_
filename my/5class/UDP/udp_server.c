#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
static void usage(const char *msg)
{
	if(msg == NULL){
		printf("%s [ip] [port]\n");
	}
}

int start(const char* const ip,short port)
{
	int sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock == -1)
	{
		perror("scoket");
		return -1;
	}
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);
	if( bind(sock,(struct sockaddr*)&local,sizeof(local)) == -1)
	{
		perror("bind");
		return -1;
	}
	return sock;
}
int main(int argc,char* argv[])
{
	if(argc != 3){
		usage(argv[0]);
		return 1;
	}
	const char* ip = argv[1];
	short port = atoi(argv[2]);//sprintf,sscanf
	int sock = start(ip,port);//启动一个udp套接
	char buf[1024];
	if( sock > 0){
		while(1){
			memset(buf,'\0',sizeof(buf));
	    	struct sockaddr_in client;
			socklen_t len = 0;
			recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&client,&len);
			printf("client :%s\n",buf);
			sendto(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&client,len);
		}
	}
	return 0;
}
