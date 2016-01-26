#include "msgqueue.h"
static int com_creat_queue(int def)
{
	key_t key = ftok(_PATH_,_PROJ_ID_);//key标识唯一的消息队列
	if(key < 0){
		perror("ftok");
		return -1;
	}
 	int msgqueue_id = msgget(key,def);
	if(msgqueue_id < 0){
		perror("msgget");//创建消息队列失败
		return -2;
	}
	return msgqueue_id;
}
int creat_queue()
{
	int def = IPC_CREAT|IPC_EXCL|0666;//IPC_CREAT和IPC_EXCL一起使用保证创建一个全新的消息队列，IPC_EXCL单独使用没有用，必须和IPC_CREAT配合着使用，若消息队列存在，则错误返回；0666是使创建的消息队列的权限是666
	return com_creat_queue(def);
}
int get_queue()
{
	int def = IPC_CREAT;//如果该队列不存在，则创建它，否则打开它
	return com_creat_queue(def);
}
int send_msg(int msgqueue_id,int who,char *msg)
{//生产消息
	struct msgbuf _buf;//_buf存放要发送的消息
	memset(&_buf,'\0',sizeof(_buf));
	_buf.mtype = who;//指定是谁发送的消息，也可以指定是谁接受该条消息
	strncpy(_buf.mtext,msg,sizeof(msg)+1);
	printf("I say : %s\n",_buf.mtext);
	return msgsnd(msgqueue_id,&_buf,sizeof(_buf.mtext),0);
}
int recv_msg(int msgqueue_id,int want,char out[],int out_len)
{//消费消息
	struct msgbuf _buf;
	memset(&_buf,'\0',sizeof(_buf));//将_buf里面的消息删除
	int ret = msgrcv(msgqueue_id,&_buf,sizeof(_buf.mtext),want,0);// 想要把want的_buf里面的消息删除，成功则返回消息的大小
	//int ret = msgrcv(msgqueue_id,&_buf,sizeof(_buf),want,0);// 想要把want的_buf里面的消息删除，成功则返回消息的大小
	if(ret <= -1){
		perror("msgrcv");
		return -1;
	}
	memset(out,'\0',out_len);//用out将删除的消息保存起来
	//strncpy(out,_buf.mtext,ret);
	strcpy(out,_buf.mtext);
	//printf("%s\n",out);
	return 0;
}
int delete_queue(int msgqueue_id)
{//删除消息队列
	int ret = msgctl(msgqueue_id,IPC_RMID,NULL);
	if(ret < 0){
		perror("msgctl");
		return -3;
	}
	return 0;
}


函数的作用分析见博客：http://blog.csdn.net/sulijuan66/article/details/50589684