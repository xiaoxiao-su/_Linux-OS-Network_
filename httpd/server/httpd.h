#ifndef _HTTPD_
#define _HTTPD_

#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h>
#include<errno.h>
#include<threadpool.hpp>
#include <sys/epoll.h> 

void accept_request(int);
void bad_request(int);
void cat(int, FILE *);
void cannot_execute(int);
void error_die(const char *);
int get_line(int, char *, int);
void headers(int, const char *);
void not_found(int);
void serve_file(int, const char *);
void unimplemented(int);
void header_and_cat(int, char*);
#define ISspace(x) isspace((int)(x))
#define SERVER_STRING "Server: jdbhttpd/0.1.0\r\n"
#define MAX_SIZE_OF_PAGE 200
#define MAX_EVENTS 100
#define THREAD_SIZE 50

#endif
