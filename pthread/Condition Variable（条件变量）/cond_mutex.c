#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <malloc.h>

pthread_mutex_t lock;//互斥锁
pthread_cond_t cond; //条件变量

//链表
typedef int data_t;
typedef struct _node{                //节点结构
	data_t data;
	struct _node *next;
}node_t,*node_p,**node_pp,*list_head;

list_head head = NULL;

static node_p buy_node(data_t _data) //创建节点
{
	node_p new_node = (node_p)malloc(sizeof(node_t));
	if( NULL == new_node ){
		perror("malloc");
		exit(1);
	}
	new_node->data = _data;
	new_node->next = NULL;
	return new_node;
}

static void delete_node(node_p _node)//删除节点
{
	if(_node){
		free(_node);
		_node = NULL;
	}
}

int is_empty(list_head _head)		//判断链表是否为空
{
	if( _head && NULL == _head->next){
		return 1;//yes
	}
	return 0;//no
}

void list_init(node_pp _head)		//初始化链表
{
	*_head = buy_node(-1);
}

void push_head(list_head _head,data_t _data)//头插节点
{
	if(_head){
		node_p tmp = buy_node(_data);
		//push
		tmp->next = _head->next;
		_head->next = tmp;
	}
}

int pop_head(list_head _head, data_t* _data)//头删节点
{
	if(is_empty(_head)){
		return 0;//fail
	}
	node_p tmp = head->next;
	head->next = head->next->next;
	*_data = tmp->data;
	delete_node(tmp);
	return 1;
}

void clear(list_head _head)					//摧毁链表
{
	data_t tmp = 0;
	while(!is_empty(_head)){
		pop_head(_head,&tmp);
	}
	delete_node(_head);
}

void show_list(list_head _head)			   //打印链表
{
	node_p ptr = _head->next;
	while(ptr){
		printf("%d ",ptr->data);
		ptr = ptr->next;
	}
}

void* comsumer_data(void* arg)			  //消费者
{
	int count = 50;
	data_t _data = -1;
	while(count){
		pthread_mutex_lock(&lock);
		while(is_empty(head)){  //当没有数据的时候，阻塞等待，直到被唤醒
			pthread_cond_wait(&cond,&lock);
		}
		int ret = pop_head(head,&_data);
		pthread_mutex_unlock(&lock);
		if(ret == 0){
			printf("consumer data failed\n");
		}else{
			printf("consumer data done : %d\n",_data);
		}
		sleep(1);
		count--;
		_data = -1;
	}
}
void* producter_data(void* arg)			//生产者
{
	int count = 50;
	while(count){
		pthread_mutex_lock(&lock);
		push_head(head,count);
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&cond);//通知在cond条件变量下等待的消费者有数据可以消费
		printf("data is ready,signal consumer!\n");
		printf("producter data done : %d\n",count);
		sleep(5);
		count--;
	}
}

int main()
{
	pthread_mutex_init(&lock,NULL);//初始化互斥锁
	pthread_cond_init(&cond,NULL); //初始化条件变量

	list_init(&head);
	pthread_t consumer,producter;
	pthread_create(&consumer,NULL,comsumer_data,NULL);
	pthread_create(&producter,NULL,producter_data,NULL);

	pthread_join(consumer,NULL);
	pthread_join(producter,NULL);
	clear(head);

	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond);
	return 0;
}


//线程创建、终止、等待、同步、分离具体分析见：http://blog.csdn.net/SuLiJuan66/article/details/50615208





