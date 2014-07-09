#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>

#define NB_PROC 4
#define _SVID_SOURCE 1

int main(int argc, char const *argv[])
{
	pid_t pid=1;
	int i=0, *mine;
	int shmid;

	

	shmid=shm_open("/shm1", O_RDWR | O_CREAT, 0777);
	if (ftruncate(shmid, sizeof(int))==-1){
		perror("ftruncate");
		exit(1);
	}
	mine=mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, shmid, 0);
	*mine=0;
	munmap(mine, sizeof(int));

	for(i=0;i<NB_PROC && pid; i++){
		pid=fork();
	}
	if (pid){
		for(i=0;i<NB_PROC && pid; i++){
			wait(NULL);
		}
		mine=mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, shmid, 0);
		printf("Le resultat final : %d\n", *mine);
		munmap(mine, sizeof(int));
		shm_unlink("/shm1");

	}
	else {
		int randval;
		srand(time(NULL)*getpid());
		sleep(i);
		mine=mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, shmid, 0);
		randval=(int)(10*(float)rand()/ RAND_MAX);
		*mine+=randval;
		printf("Moi j'envoie : %d\n", randval);
		munmap(mine, sizeof(int));
	}

	return 0;
}