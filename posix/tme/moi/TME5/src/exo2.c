#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#define _SVID_SOURCE 1
#define NB_PROC 4


sem_t *sem1, *sem2;


void wait_barrier (int nb_procs){
	int i;
	if(sem_trywait(sem1)==-1){
		printf("Je suis le dernier\n");
		for(i=0; i<nb_procs; i++){
			sem_post(sem2);
		}
	}
	sem_wait(sem2);
}

void process (int nb_procs) {
    printf ("avant barrière\n");
    wait_barrier (nb_procs);
    printf ("après barrière\n");
    exit (0);
}


int main(int argc, char const *argv[])
{
	int i;
	pid_t pid=1;
	sem1=sem_open("/sem1", O_CREAT, 0777, NB_PROC-1);
	sem2=sem_open("/sem2", O_CREAT, 0777, 0);
	if(sem1==SEM_FAILED || sem2==SEM_FAILED){
		perror("sem_open");
		exit(1);
	}
	for(i=0;i<NB_PROC && pid; i++){
		pid=fork();
	}

	if(pid){
		while(wait(NULL)!=-1);	
		sem_unlink("./sem1");
		sem_unlink("./sem2");
	}
	else{
		process(NB_PROC);
	}



	return 0;
}