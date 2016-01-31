#include <stdio.h>
#include "shm_comm.h"
int main()
{
	int _size = 1000;
	int shm_id = get_shm(_size);
	printf("sleep(5)\n");
	sleep(5);
	char* mem = (char*)attach(shm_id);
	memset(mem,'\0',_size);
	int index = 0;
	//多进程往共享内存里面写数据，没有互斥访问共享内存，可以结合信号量机制互斥访问
	int count = 60;
	while(count--)
	{//可以再起一个client进行写，增加挂接共享内存的数目，命令：ipcs -m查看挂接数目
		mem[index] = 'X';
		mem[index+1] = '\0';
		index++;
		sleep(1);
	}
	detach(mem);
	printf("detach\n");
	return 0;
}
