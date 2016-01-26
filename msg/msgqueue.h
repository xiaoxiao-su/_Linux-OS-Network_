#ifndef _DEBUG_
#define _DEBUG_

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define _PATH_ "."       //当前路径下
#define _PROJ_ID_ 0x6654
#define _SIZE_ 3000

#define SERVER_TYPE 2
#define CLIENT_TYPE 1

struct msgbuf
{
	long mtype;        //标识是谁发的消息，也可以标识是给谁发的消息，此处举例是前者
	char mtext[_SIZE_];//存放发的消息
};
int creat_queue();//由server创建消息队列，保证创建的是一个全新的消息队列
int get_queue();  //client访问消息队列，若不存在，则创建它；若存在，则打开它（不能保证打开的是一个全新的消息队列）

int send_msg(int msgqueue_id,int who,char *msg);			   //生产消息
int recv_msg(int msgqueue_id,int wang,char out[],int out_len); //消费消息

int delete_msgqueue(int msgqueue_id);						//删除消息队列

#endif

