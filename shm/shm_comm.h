#ifndef _COMM_
#define _COMM_

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>
#define _PATH_ "."
#define _PROJ_ID_ 0x6602

int create_shm(int _size);
int get_shm(int _size);
int destory_shm(int shm_id);
void* attach(int shm_id);
int detach(void*);

#endif
