#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#define _XOPEN_SOURCE 700


#define NB_PROC 7
#define MAX_LUNCH 4

sem_t **baguettes;

void philosophe_pair(int i){

/*** Le philosophe pair, va d'abord prendre sa baguette de gauche, puis celle de droite pour pouvoir manger ***/
	int time_lunch;
	sem_wait(baguettes[i%NB_PROC]);
	sem_wait(baguettes[(i+1)%NB_PROC]);
	srand(time(NULL)*getpid());
	time_lunch=(rand()%MAX_LUNCH)+1;
	printf("Moi %d, je mange %d seconde(s)\n", i, time_lunch);
	sleep(time_lunch);
	sem_post(baguettes[i%NB_PROC]);
	sem_post(baguettes[(i+1)%NB_PROC]);
	printf("FIN %d\n", i);
}

void philosophe_impair(int i){

/*** Le philosophe impair, va d'abord prendre sa baguette de droite, puis celle de gauche pour pouvoir manger ***/
	int time_lunch;
	sem_wait(baguettes[(i+1)%NB_PROC]);
	sem_wait(baguettes[i%NB_PROC]);
	srand(time(NULL)*getpid());
	time_lunch=(rand()%MAX_LUNCH)+1;
	printf("Moi %d, je mange %d seconde(s)\n", i, time_lunch);
	sleep(time_lunch);
	sem_post(baguettes[i%NB_PROC]);
	sem_post(baguettes[(i+1)%NB_PROC]);
	printf("FIN %d\n", i);

}


int main(int argc, char const *argv[])
{
	int i;
	pid_t pid=1;

	baguettes=malloc(NB_PROC*sizeof(sem_t*));
	char name[24];
	char name2[]="01234";

	strcpy(name, "/philo");

	for(i=0; i<NB_PROC; i++){
		strncat(name, name2, 1);
		baguettes[i]=sem_open(name, O_CREAT,0777,1);
	}

	for(i=0; i<NB_PROC; i++){
		if (baguettes[i]==SEM_FAILED){
			perror("sem_open");
			exit(1);
		}
	}

	printf("A Table !\n");
	for (i=0; i<NB_PROC && pid; i++){
		pid=fork();
	}
	if(!pid){
		i--;
		if(i%2==0)
			philosophe_pair(i);
		else
			philosophe_impair(i);
	}
	else{
		for (i=0; i<NB_PROC; i++){
			wait(NULL);
		}

	}
	return 0;
}