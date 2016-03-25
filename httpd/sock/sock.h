#ifndef _SOCK_
#define _SOCK_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include<string.h>
#include <fcntl.h> 
#include <sys/epoll.h> 
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#define SER_PORT 59470
extern int epollfd;
int  AcceptConn(int);
void socket_send(int,char*);
int startup();
void setSockNonBlock(int);
//void socket_recv(int,char*);
#endif
