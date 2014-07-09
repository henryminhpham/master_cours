#include "../include/thread_stack_shm.h"
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>
#include "stdlib.h"
int idx;

sem_t *sem_push, *sem_pop;

pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;



void initStack ( void ){
	key_t mykey;
	int shmid;
	sem_unlink("./sempush");/*On detruit les anciennes semaphores du meme nom*/
	sem_unlink("./sempop");
	idx=-1;
	sem_push=sem_open("./sempush",O_CREAT | O_EXCL , 0600, 99);

	if(sem_push==SEM_FAILED){
	 	printf("FAIL\n");
	 	exit(0);
	}
	sem_pop=sem_open("./sempop", O_CREAT | O_EXCL , 0600, 0);

	mykey=ftok("./exo5", 'a');
	shmid=shmget(mykey, 100*sizeof(char), IPC_CREAT | 0777);

	printf("initStacl : %d\n",idx);
}

void Push ( int c ){
	key_t mykey;
	int shmid;
	char *stack=NULL;
	sem_wait(sem_push);
	pthread_mutex_lock(&mymutex);
	printf("Appel de push : %d\n", c);
	idx++;
	mykey=ftok("./exo5", 'a');
	shmid=shmget(mykey, 100*sizeof(char), IPC_EXCL);
	stack=shmat(shmid, 0, 0);
	*(stack+idx)=c;
	shmdt(stack);
	pthread_mutex_unlock(&mymutex);
	sem_post(sem_pop);

}

int Pop ( void ){
	int c;
	key_t mykey;
	int shmid;
	char *stack=NULL;
	sem_wait(sem_pop);
	pthread_mutex_lock(&mymutex);
	idx--;
	mykey=ftok("./exo5", 'a');
	shmid=shmget(mykey, 100*sizeof(char), IPC_EXCL);
	stack=shmat(shmid, 0, 0);
	c=(*(stack+idx+1));
	shmdt(stack);
	printf("Appel de POP : %d\n", c);
	pthread_mutex_unlock(&mymutex);
	sem_post(sem_push);

	return c;
}
