#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>

int main()
{
	int max_fd = 1;
	fd_set r_set;//可读文件描述符集
	fd_set w_set;//可写文件描述符集
	while(1){
		FD_ZERO(&r_set);//初始化
		FD_ZERO(&w_set);//初始化
	
		FD_SET(0, &r_set);//将文件描述符0加入文件描述符集中
		FD_SET(1,&w_set);
		max_fd = 0;

		struct timeval timeout={5, 0};
		switch( select(max_fd+1, &r_set, &w_set, NULL, &timeout)){
			case 0://timeout
				printf("time is out!\n");
				break;
			case -1://error
				perror("select");
				exit(1);
				break;
			default://success
				{
					char buf[1024];
					memset(buf, '\0', sizeof(buf));
					if(FD_ISSET(0, &r_set)){//检查文件描述符0是否已经就绪
						ssize_t sz = read(0, buf, sizeof(buf)-1);
						if( sz > 0 ){
							buf[sz] = '\0';
							printf("read event ready : %s\n",buf);
						}
					}else if(FD_ISSET(1,&w_set)){//检查文件描述符1是否就绪
						char *msg = "this is select test\n";
						write(1, msg, strlen(msg));
					}else{//作为扩展
					}
				}
				break;
		}
	}
}
