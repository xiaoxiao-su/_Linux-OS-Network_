#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
int main()
{
	int sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock == -1){
		perror("socket");
		return -1;
	}
	struct sockaddr_in remote;
	remote.sin_family = AF_INET;
	remote.sin_port = htons(8080);
	remote.sin_addr.s_addr = inet_addr("192.168.18.129");
	
	char buf[1024];
	while(1){
		memset(buf,'\0',sizeof(buf));
		printf("Please Enhter");
		fflush(stdout);
		socklen_t len = sizeof(remote);
		gets(buf);
	    sendto(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&remote,sizeof(remote));
	    recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&remote,&len);
		printf("echo :%s\n",buf);

	}
	return 0;
}
