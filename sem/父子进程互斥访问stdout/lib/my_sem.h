#ifndef _MYSEM_
#define _MYSEM_
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define _PATH_ "."
#define _PROJ_ID_ 0x0603

typedef union semun {
	int val;   				 /* Value for SETVAL */
struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
}semun_t;

int create_sem(int nsems);
int get_sem(int nsems);
int init_sem(int sem_id,int which,int init_val);
int p_sem(int sem_id,unsigned short which);//-1
int v_sem(int sem_id,unsigned short which);//+1
int destroy_sem(int sem_id);

#endif
