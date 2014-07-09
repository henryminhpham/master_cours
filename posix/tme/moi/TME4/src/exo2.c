#include "sys/types.h"
#include "sys/ipc.h"
#include "unistd.h"
#include "sys/sem.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "sys/shm.h"
#include <string.h>

#define SVID_SOURCE 1
#define NB_PROC 4

int main(int argc, char const *argv[])
{
	pid_t pid=1;
	int i=0, *mine;
	key_t mykey;
	int shmid;
	struct shmid_ds buf;

	

	mykey=ftok(argv[0], 'a');
	shmid=shmget(mykey, sizeof(int), IPC_CREAT|0777);
	mine=shmat(shmid,0,0);
	*mine=0;
	shmdt(mine);

	for(i=0;i<NB_PROC && pid; i++){
		pid=fork();
	}
	if (pid){
		for(i=0;i<NB_PROC && pid; i++){
			wait(NULL);
		}
		mine=shmat(shmid, 0, 0);
		printf("Le resultat final : %d\n", *mine);
		shmdt(mine);
		shmctl(shmid, IPC_RMID, &buf);

	}
	else {
		int randval;
		srand(time(NULL)*getpid());
		sleep(i);
		mine=shmat(shmid, 0, 0);
		randval=(int)(10*(float)rand()/ RAND_MAX);
		*mine+=randval;
		printf("Moi j'envoie : %d\n", randval);
		shmdt(mine);
	}

	return 0;
}