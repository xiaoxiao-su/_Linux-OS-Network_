#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
void* thread_run(void* arg)
{
	int ret = pthread_detach(pthread_self());
	printf("%d,%s\n",ret,strerror(ret));
	int value = (int)arg;
	printf("this is another thread,arg:%d,self:%lu\n",arg,pthread_self());;
	//return (void*)1;//方法一,从函数return返回

	int count = 0		
	while(1){
		printf("this is another thread,arg:%d,self:%lu\n",arg,pthread_self());
		sleep(1);
		count++;
		if(count > 5){
			printf("other thread done\n");
			pthread_exit((void*)34);//方法二：自己终止自己
		}
	}
	//exit(0);//方法三：从函数exit退出
}

int main()
{
	pthread_t tid;
	int code = pthread_create(&tid,NULL,thread_run,(void*)1);
	if(code != 0){
		printf("%d : %s\n",code,strerror(code));
		return 	1;
	}
	int count = 0;
	int flag = 0;
	while(1){
		printf("this is main thread,self:%lu\n",pthread_self());//返回自己的线程ID
		sleep(1);
		count++;
		if(count > 10){
			break;
		}else if(count > 5 && flag == 0){
			flag = 1;
	//		pthread_cancel(tid);//终止方法四：主线程（或者任一个线程）终止其它线程，PTHREAD_CANCELED 一个宏，值为-1
		}
	}
	int ret = pthread_detach(tid);
	printf("%s",strerror(ret));
	void* status = NULL;
	code = pthread_join(tid,&status);//status保存返回的错误码,code获取终止线程的错误码
	if(code == 0){
		printf("pthread_join success,code:%d,%s\n",(int)status,strerror(ret));
	}else{
		printf("%d : %s\n",code,strerror(code));
	}
	return 0;
}
