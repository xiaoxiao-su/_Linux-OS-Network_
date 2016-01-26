#include <stdio.h>
#include "msgqueue.h"

int server()
{
	int msgqueue_id = creat_queue();
	if(msgqueue_id < 0){
		perror("server");
		return -1;
	}
	char buf[_SIZE_];
	while(1)
	{
		sleep(2);
		memset(buf,'\0',sizeof(buf));//buf保存消费掉的消息
		int ret = recv_msg(msgqueue_id,CLIENT_TYPE,buf,sizeof(buf));//server删除从client发送来的消息
		if(ret == 0)
		{
			if(strncasecmp(buf,"Quit",4) == 0){
				printf("client Quit!\n");
				break;
			}
			printf("client say : %s\n",buf);
		}
		printf("Please Enter : ");
		fflush(stdout);
		memset(buf,'\0',sizeof(buf));
		gets(buf);//server从标准输出上获取信息并且存放在buf里面
		send_msg(msgqueue_id,SERVER_TYPE,buf);//经buf里面的消息发送给client
	}
	return delete_queue(msgqueue_id);//最后由server删除消息队列
}
int main()
{
	server();
	return 0;
}
