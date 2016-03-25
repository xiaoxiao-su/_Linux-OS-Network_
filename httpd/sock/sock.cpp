#include"sock.h"

/*************************************************/
 /* send data to NoBlock socket descriptor
  * Parameters: the client socket descriptor
  *		the buffer to send
 /***********************************************/
void socket_send(int fd,char* buf)
{
	int nsend;
	int data_size = strlen(buf);
	int n = data_size;
	while(n > 0)
	{
		nsend = send(fd,buf + data_size -n,n,0);
		if(nsend < n)
		{
			if(nsend == -1 && errno != EAGAIN)
			{
			//	perror("send error");
			}
			break;
		}
		n -= nsend;
	}
}

/*****************************************************/
 /* The function accept the connect from the sevfd
  * and add the new socketfd to epoll
  * Parameters: the server socket descriptor
  * Return va:  1 success   -1 failed  */
  /***************************************************/

int  AcceptConn(int srvfd)
{
	int confd;
	struct epoll_event event;
	
	struct sockaddr_in sin;
	socklen_t len = sizeof(struct sockaddr_in);
	bzero(&sin, len);

	confd = accept(srvfd, (struct sockaddr*)&sin, &len);

	if (confd == -1)
	{
		return -1;
	}
	setSockNonBlock(confd);

	event.data.fd = confd;
	event.events = EPOLLIN | EPOLLET;
	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, confd, &event) == -1) {
		perror("epoll_ctl(EPOLL_CTL_ADD) failed\n");
		exit(EXIT_FAILURE);
	}
	return 1;
}

/**********************************************************************/
/* This function starts the process of listening for web connections
 * on a specified port. 
 * Returns: the socket */
/**********************************************************************/
int startup()
{
	int httpd = 0;
	struct sockaddr_in name;

	httpd = socket(PF_INET, SOCK_STREAM, 0);
	if (httpd == -1)
	{
		perror("socket");
		exit(1);
	}
	memset(&name, 0, sizeof(name));
	name.sin_family = AF_INET;
	name.sin_port = htons(SER_PORT);
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(httpd, (struct sockaddr *)&name, sizeof(name)) < 0)
	{
		perror("bind");
		exit(1);
	}
	if (listen(httpd, 5) < 0)
	{
		perror("listen");
		exit(1);
	}
		
	setSockNonBlock(httpd);
	printf("server is running at port %d\n",SER_PORT);
	return(httpd);
}
/***************************************************/
/*set  socket descriptor on NoBlock mode
 *Parameter: socket descriptor. */
 /***************************************************/
void setSockNonBlock(int sock)
{
	int flags;
	flags = fcntl(sock, F_GETFL, 0);
	if (flags < 0)
	{
		perror("fcntl(F_GETFL) failed");
		exit(1);
	}
	if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) < 0)
	{
		perror("fcntl(F_SETFL) failed");
		exit(1);
	}
}
