#include "shm_comm.h"

static int comm_shm(int _size,int flag)
{
	key_t _key = ftok(_PATH_,_PROJ_ID_);
	if(_key == -1){
		perror("ftok");
		return -1;
	}
	int shm_id = shmget(_key,_size,flag);
	if(shm_id == -1)
	{
		perror("shmget");
		return -2;
	}
	return shm_id;
}
int create_shm(int _size)   //创建共享内存
{
	int flag = IPC_CREAT|IPC_EXCL|0666;
	return comm_shm(_size,flag);
}
int get_shm(int _size)     //获取共享内存
{
	int flag = IPC_CREAT;
	return comm_shm(_size,flag);
}
int destory_shm(int shm_id)//释放共享内存
{
	if(shmctl(shm_id,IPC_RMID,0) == -1)
	{
		perror("shmctl");
		return -1;
	}
	return 0;
}
void* attach(int shm_id)
{//挂接，当server创建出共享内存，必须挂接上共享内存后才能访问共享内存，client也是
	void* mem = NULL;
	if(mem = shmat(shm_id,NULL,0)){
		return mem;
	}
	return NULL;
}
int detach(void* addr)
{//分离，断开挂接
	return shmdt(addr);
}
