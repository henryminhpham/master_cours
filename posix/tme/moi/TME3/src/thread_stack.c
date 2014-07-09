#include "../include/thread_stack.h"
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int idx;
int stack[100];

sem_t *sem_push, *sem_pop;

pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;



void initStack ( void ){
	sem_unlink("./sempush");/*On detruit les anciennes semaphores du meme nom*/
	sem_unlink("./sempop");
	idx=-1;
	sem_push=sem_open("./sempush",O_CREAT | O_EXCL , 0600, 99);

	if(sem_push==SEM_FAILED){
	 	printf("FAIL\n");
	 	exit(0);
	}
	sem_pop=sem_open("./sempop", O_CREAT | O_EXCL , 0600, 0);
	printf("initStacl : %d\n",idx);

}

void Push ( int c ){
	sem_wait(sem_push);
	pthread_mutex_lock(&mymutex);
	printf("Appel de push : %d\n", c);
	idx++;
	stack[idx]=c;
	pthread_mutex_unlock(&mymutex);
	sem_post(sem_pop);

}

int Pop ( void ){
	int c;
	sem_wait(sem_pop);
	pthread_mutex_lock(&mymutex);
	idx--;
	c=stack[idx+1];
	printf("Appel de POP : %d\n", c);
	pthread_mutex_unlock(&mymutex);
	sem_post(sem_push);

	return c;
}
