#include "sys/types.h"
#include "sys/ipc.h"
#include "unistd.h"
#include "sys/sem.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "sys/shm.h"
#include <string.h>
#include "sys/sem.h"
#define SVID_SOURCE 1
#define NB_PROC 4


int semid;

struct sembuf p[2];
struct sembuf v[2];



void wait_barrier (int nb_procs){
	int i;
	if(semop(semid, &p[0], 1)==-1){
		printf("Je suis le dernier\n");
		for(i=0; i<nb_procs; i++){
			semop(semid, &v[1], 1);
		}
	}
	semop(semid, &p[1], 1);

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
	key_t mykey;
	pid_t pid=1;
	p[0].sem_num=0;
	p[0].sem_op=-1;
	p[0].sem_flg=IPC_NOWAIT;
	p[1].sem_num=1;
	p[1].sem_op=-1;
	p[1].sem_flg=0;

	v[0].sem_num=0;
	v[0].sem_op=1;
	v[0].sem_flg=0;
	v[1].sem_num=1;
	v[1].sem_op=1;
	v[1].sem_flg=0;
	mykey=ftok(argv[0], 'a' );
	semid=semget(mykey, 2, IPC_CREAT | 0777);
	semctl(semid, 0, SETVAL, NB_PROC-1);
	semctl(semid, 1, SETVAL, 0);
	for(i=0;i<NB_PROC && pid; i++){
		pid=fork();
	}

	if(pid){
		while(wait(NULL)!=-1);	
		semctl(semid, 0, IPC_RMID, 1);
	}
	else{
		process(NB_PROC);
	}



	return 0;
}