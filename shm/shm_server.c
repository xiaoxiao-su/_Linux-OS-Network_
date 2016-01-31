#include <stdio.h>
#include "shm_comm.h"
int main()
{
	int _size = 4096;
	int shm_id = create_shm(_size);
	sleep(10);
	char* mem = (char*)attach(shm_id);
	memset(mem,'\0',_size);
	//读取共享内存数据	
	int count = 60;
	while(count--){
		printf("%s\n",mem);
		sleep(1);
	}

	detach(mem);
	destory_shm(shm_id);
	return 0;
}
