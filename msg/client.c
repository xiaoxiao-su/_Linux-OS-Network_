#include <stdio.h>
#include "msgqueue.h"

int client()
{
	int msgqueue_id = get_queue();
	char buf[_SIZE_];
	while(1)
	{
		printf("Please Enter : ");
		fflush(stdout);
		memset(buf,'\0',sizeof(buf));//buf保存消费掉的消息
		gets(buf);//client从标准输出上获取信息并且存放在buf里面
		send_msg(msgqueue_id,CLIENT_TYPE,buf);//经buf里面的消息发送给server
		if(strncasecmp(buf,"Quit",4) == 0){
			printf("Quit\n");
			return 0;
		}
		sleep(2);
		memset(buf,'\0',sizeof(buf));//buf保存消费掉的消息
		int ret = recv_msg(msgqueue_id,SERVER_TYPE,buf,sizeof(buf));//client删除从server发送来的消息
		if(ret == 0)
		{
			printf("server say : %s\n",buf);
		}
	}
}
int main()
{
	client();
	return 0;
}
