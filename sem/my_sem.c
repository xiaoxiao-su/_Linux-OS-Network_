#include "my_sem.h"

static int com_sem(int nsems,int flag)
{
	key_t key = ftok(_PATH_,_PROJ_ID_);
	if( key < 0 ){
		perror("ftok");
		return -1;
	}
	int sem_id = semget(key,nsems,flag);//创建信号量
	if(sem_id < 0){
		perror("semget");
		return -2;
	}
	return sem_id;
}
int creat_sem(int nsems)
{
	int flag = IPC_CREAT | IPC_EXCL | 0666;
	return com_sem(nsems,flag);
}
int get_sem(int nsems)
{
	int flag = IPC_CREAT;
	return com_sem(nsems,flag);
}
static int com_semop(int sem_id,unsigned short which,short op)
{//对哪个信号量集中的哪一个信号进行op指定的操作
	struct sembuf semb[1];//只考虑二元信号量，所以只有一个元素
	semb[0].sem_num = which;
	semb[0].sem_op = op;//进行什么操作是由op说了算
	semb[0].sem_flg = 0;//UNDO,若一个进程在临界区崩溃了，那么flag就维护信号量，把信号量恢复
	if(semop(sem_id,semb,1) < 0)
	{
		perror("semop");
		return -1;
	}
	return 0;
}
int p_sem(int sem_id,unsigned short which)
{//进行p操作
	int op = -1;
	return com_semop(sem_id,which,op);
}
int v_sem(int sem_id,unsigned short which)
{//进行v操作
	int op = 1;
	return com_semop(sem_id,which,op);
}
int init_sem(int sem_id,int which,int init_val)
{
	semun_t sem_val;
	sem_val.val = init_val;
	int ret = semctl(sem_id,which,SETVAL,sem_val);//初始化信号量
	if(ret < 0)
	{
		perror("semct");
		return -1;
	}
	return 0;
}
int destory_sem(int sem_id)
{
	int ret = semctl(sem_id,0,IPC_RMID);//0是指定的信号量，此处讨论的是二元信号量
	if(ret < 0){
		perror("semctl");
		return -1;
	}
	printf("\ndestroy success\n");
	return 0;
}
//链接静态库的时候，不能有main函数，因为用户会自己写一个main函数
//int main()
//{
//	int nsems = 8;
//	int sem_id = creat_sem(nsems);
//	printf("sem_id = %d\n",sem_id);
//	sleep(3);
//	destory_sem(sem_id);
//	return 0;
//}
