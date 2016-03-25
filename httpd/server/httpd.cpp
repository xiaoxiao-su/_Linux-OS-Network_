#include"httpd.h"
#include"database.h"
#include"memc.h"
#include"sock.h"


/**************************************************************/
 /* Run as a thread. Receive the data from network and process 
  * the request ,query and send the page data
  * Parameters: the socket connected to the client
  *		the epoll_event processed with current thread */
 /*************************************************************/
void accept_request(int client,struct epoll_event* even)
{
	signal(13,SIG_IGN);//ignore the sigpipe
	char buf[1024];
	int numchars;
	char method[255];
	char url[255];
	char path[512];
	size_t i, j;
	struct stat st;
	char *query_string = NULL;

	numchars = get_line(client, buf, sizeof(buf));
	i = 0; j = 0;
	while (!ISspace(buf[j]) && (i < sizeof(method)-1))
	{
		method[i] = buf[j];
		i++; j++;
	}
	method[i] = '\0';
	if (strcasecmp(method, "GET") && strcasecmp(method, "POST"))
	{
		unimplemented(client);
		return;
	}


	i = 0;
	while (ISspace(buf[j]) && (j < sizeof(buf)))
		j++;
	while (!ISspace(buf[j]) && (i < sizeof(url)-1) && (j < sizeof(buf)))
	{
		url[i] = buf[j];
		i++; j++;
	}
	url[i] = '\0';

	sprintf(path, "htdocs%s", url);
	char *page_info = (char*)malloc(MAX_SIZE_OF_PAGE);//the content of the html page
	page_info[0] = '\0';
	//request the homepage
	if (path[strlen(path) - 1] == '/')
	{
		strcat(path, "index.html");
		if (stat(path, &st) == -1)
		{
			while ((numchars > 0) && strcmp("\n", buf))  /* read & discard headers */
				numchars = get_line(client, buf, sizeof(buf));
			not_found(client);
		}
		else
		{
			if ((st.st_mode & S_IFMT) == S_IFDIR)
				strcat(path, "/index.html");
			serve_file(client, path);
		}
	}
	//request the page stored in database
	else
	{
		//try to get data from cache first. if failed then try to get it in database
		char *page_name = url + 1;//such as "BeiJing.html"
		memcached_st *memc = memcache_init();
		if (query_memcache(memc,page_info,page_name) < 0)
		{
			if(query_database(page_info,page_name) < 0)
			{
				printf("Im here query database faile and close the client");
				free(page_info);
				memcache_destroy(memc);
				close(client);
				return;
			}
			memcached_set(memc, page_name, strlen(page_name), page_info, strlen(page_info), (time_t)180, (uint32_t)0);
		}
		memcache_destroy(memc);
		header_and_cat(client, page_info);
	}
	free(page_info);
	close(client);
	epoll_ctl(epollfd, EPOLL_CTL_DEL, client, even);
}

/**********************************************************************/
/* send the http header  and the content of the page
 * Parameters: client socket 
 *	       the buffer to send */
/**********************************************************************/
void header_and_cat(int client, char* page_info)
{
	int numchars = 1;
	char buf[1024];

	buf[0] = 'A'; buf[1] = '\0';
	while ((numchars > 0) && strcmp("\n", buf))  /* read & discard headers */
		numchars = get_line(client, buf, sizeof(buf));
	headers(client, NULL);
	socket_send(client, page_info);

}

/**********************************************************************/
/* Inform the client that a request it has made has a problem.
 * Parameters: client socket */
/**********************************************************************/
void bad_request(int client)
{
	char buf[1024];

	sprintf(buf, "HTTP/1.0 400 BAD REQUEST\r\n");
	socket_send(client, buf);
	sprintf(buf, "Content-type: text/html\r\n");
	socket_send(client, buf);
	sprintf(buf, "\r\n");
	socket_send(client, buf);
	sprintf(buf, "<P>Your browser sent a bad request, ");
	socket_send(client, buf);
	sprintf(buf, "such as a POST without a Content-Length.\r\n");
	socket_send(client, buf);
}

/**********************************************************************/
/* Put the entire contents of a file out on a socket.  This function
 * is named after the UNIX "cat" command, because it might have been
 * easier just to do something like pipe, fork, and exec("cat").
 * Parameters: the client socket descriptor
 *             FILE pointer for the file to cat */
/**********************************************************************/
void cat(int client, FILE *resource)
{
	/*///////////////////////debug////
	*
	*struct sockaddr_in name;
	* u_short port;
	* int namelen = sizeof(name);
	* getsockname(client, (struct sockaddr *)&name, &namelen);
	* port = ntohs(name.sin_port);
	*	printf("send port in fun headr_and_cat is %d\n",port);
	*/
	char buf[1024];

	fgets(buf, sizeof(buf), resource);
	while (!feof(resource))
	{
		socket_send(client, buf);
		fgets(buf, sizeof(buf), resource);
	}
}
/**********************************************************************/
/* Inform the client that a CGI script could not be executed.
 * Parameter: the client socket descriptor. */
/**********************************************************************/
void cannot_execute(int client)
{
	char buf[1024];

	sprintf(buf, "HTTP/1.0 500 Internal Server Error\r\n");
	socket_send(client, buf);
	sprintf(buf, "Content-type: text/html\r\n");
	socket_send(client, buf);
	sprintf(buf, "\r\n");
	socket_send(client, buf);
	sprintf(buf, "<P>Error prohibited CGI execution.\r\n");
	socket_send(client, buf);
}



/**********************************************************************/
/* Get a line from a socket, whether the line ends in a newline,
  carriage return, or a CRLF combination.  Terminates the string read
 * with a null character.  If no newline indicator is found before the
 * end of the buffer, the string is terminated with a null.  If any of
 * the above three line terminators is read, the last character of the
 * string will be a linefeed and the string will be terminated with a
 * null character.
 * Parameters: the socket descriptor
 *             the buffer to save the data in
 *             the size of the buffer
 * Returns: the number of bytes stored (excluding null) */
/**********************************************************************/
int get_line(int sock, char *buf, int size)
{
	int i = 0;
	char c = '\0';
	int n;

	while ((i < size - 1) && (c != '\n'))
	{
		n = recv(sock, &c, 1, 0);
		/* DEBUG printf("%02X\n", c); */
		if (n > 0)
		{
			if (c == '\r')
			{
				n = recv(sock, &c, 1, MSG_PEEK);
				/* DEBUG printf("%02X\n", c); */
				if ((n > 0) && (c == '\n'))
					recv(sock, &c, 1, 0);
				else
					c = '\n';
			}
			buf[i] = c;
			i++;
		}
		else
			c = '\n';
	}
	buf[i] = '\0';

	return(i);
}

/**********************************************************************/
/* Return the informational HTTP headers about a file. */
/* Parameters: the socket to print the headers on
 *             the name of the file */
/**********************************************************************/
void headers(int client, const char *filename)
{
	char buf[1024];
	(void)filename;  /* could use filename to determine file type */

	strcpy(buf, "HTTP/1.0 200 OK\r\n");
	socket_send(client, buf);
	strcpy(buf, SERVER_STRING);
	socket_send(client, buf);

	sprintf(buf, "Content-/Type: text/html\r\n");
	socket_send(client, buf);
	strcpy(buf, "\r\n");
	socket_send(client, buf);


}

/**********************************************************************/
/* Give a client a 404 not found status message. */
/**********************************************************************/
void not_found(int client)
{
	char buf[1024];

	sprintf(buf, "HTTP/1.0 404 NOT FOUND\r\n");
	socket_send(client, buf);
	sprintf(buf, SERVER_STRING);
	socket_send(client, buf);
	sprintf(buf, "Content-Type: text/html\r\n");
	socket_send(client, buf);
	sprintf(buf, "\r\n");
	socket_send(client, buf);
	sprintf(buf, "<HTML><TITLE>Not Found</TITLE>\r\n");
	socket_send(client, buf);
	sprintf(buf, "<BODY><P>The server could not fulfill\r\n");
	socket_send(client, buf);
	sprintf(buf, "your request because the resource specified\r\n");
	socket_send(client, buf);
	sprintf(buf, "is unavailable or nonexistent.\r\n");
	socket_send(client, buf);
	sprintf(buf, "</BODY></HTML>\r\n");
	socket_send(client, buf);
}

/**********************************************************************/
/* Send a regular file to the client.  Use headers, and report
 * errors to client if they occur.
 * Parameters: a pointer to a file structure produced from the socket
 *              file descriptor
 *             the name of the file to serve */
/**********************************************************************/
void serve_file(int client, const char *filename)
{
	FILE *resource = NULL;
	int numchars = 1;
	char buf[1024];

	buf[0] = 'A'; buf[1] = '\0';
	while ((numchars > 0) && strcmp("\n", buf))  /* read & discard headers */
		numchars = get_line(client, buf, sizeof(buf));

	resource = fopen(filename, "r");
	if (resource == NULL)
		not_found(client);
	else
	{
		headers(client, filename);
		cat(client, resource);
	}
	fclose(resource);
}

/**********************************************************************/
/* Inform the client that the requested web method has not been
 * implemented.
 * Parameter: the client socket */
/**********************************************************************/
void unimplemented(int client)
{
	char buf[1024];

	sprintf(buf, "HTTP/1.0 501 Method Not Implemented\r\n");
	socket_send(client, buf);
	sprintf(buf, SERVER_STRING);
	socket_send(client, buf);
	sprintf(buf, "Content-Type: text/html\r\n");
	socket_send(client, buf);
	sprintf(buf, "\r\n");
	socket_send(client, buf);
	sprintf(buf, "<HTML><HEAD><TITLE>Method Not Implemented\r\n");
	socket_send(client, buf);
	sprintf(buf, "</TITLE></HEAD>\r\n");
	socket_send(client, buf);
	sprintf(buf, "<BODY><P>HTTP request method not supported.\r\n");
	socket_send(client, buf);
	sprintf(buf, "</BODY></HTML>\r\n");
	socket_send(client, buf);
}

/**********************************************************************/



int epollfd;
struct epoll_event eventList[MAX_EVENTS];

int main(void)
{
	int server_sock = -1;
	server_sock = startup();
	//init epoll
	struct epoll_event event;
	epollfd = epoll_create(MAX_EVENTS);
	if (epollfd == -1){
		perror("epoll create failed.");
		exit(1);
	}
	event.events = EPOLLIN | EPOLLET;
	event.data.fd = server_sock;

	//epoll_ctrl  
	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, server_sock, &event) < 0){
		printf("epoll add fail : fd = %d\n", server_sock);
		return -1;
	}
	boost::threadpool::pool tp(THREAD_SIZE);
	while (1)
	{
		int ret = epoll_wait(epollfd, eventList, MAX_EVENTS, -1);
		if (ret < 0)
		{
			printf("epoll wait failed\n");
			break;
		}
		for (int n = 0; n < ret; n++)
		{
			if (eventList[n].data.fd == server_sock)
			{
				while(AcceptConn(server_sock) > 0);
			}
			else
			{
				 tp.schedule(boost::bind(accept_request, eventList[n].data.fd,&eventList[n]));
			}
		}
		
	}
	close(server_sock);
	close(epollfd);
	tp.wait();

	return(0);
}
