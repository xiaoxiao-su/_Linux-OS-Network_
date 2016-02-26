#include "httpd.h"
//多进程的http
void usage(const char* proc)
{
	printf("Usage : %s [ip] [port]",proc);
}

void printf_log(const char* fun,int line,int errno,const char* err_str)

int start(short port)
{
	int listen_sock = socket(AF_INET,SOCK_STREAM,0);
	if(listen_sock == -1){
		printf_log(__FUNCTION__,__LINE__,errno,strerror(errno));
		exit(1);
	}
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr = INADDR_ANY;
	socklen_t len = sizeof(local);
	if(bind(listen_sock,(struct sockaddr*)local,len) == -1){
		printf_log(__FUNCTION__,__LINE__,errno,strerror(errno));
		exit(2);
	}
	if(listen(listen_sock,BACKLOG) == -1){
		printf_log(__FUNCTION__,__LINE__,errno,strerror(errno));
		exit(3);
	}
	return listen_sock;
}

int main(int argc,char *argv[])
{
	if(argc != 3){
		usage(argv[0]);
		exit(1);
	}
	short port = atoi(argv[2]);
	printf("port:%d\n",port);
	int sock = start(port);
}
