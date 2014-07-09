#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include "../include/bufmsg.h" 

sem_t *sem1, *sem2;
int clishmid, sershmid;
char* clishm, *sershm;

void fils_recept (char* clishm, int clishmid, const char* id){
	sem_t *semrecept;
	request *buf;
	semrecept=sem_open(clishm, O_CREAT, 0777, 0);
	while(1){
		sem_wait(semrecept);
		buf=mmap(NULL, sizeof(request), PROT_READ|PROT_WRITE, MAP_SHARED, clishmid,0);
		printf("\nReception du serveur : \n");
		printf("$$ > %s\n",buf->content);
		printf("%s > ", id);
		fflush(stdout);
		munmap(buf, sizeof(request));
	}
}

void deconnexion (int sig){
	request *buf;
	sem_wait(sem2);
	buf=mmap(NULL, sizeof(request), PROT_READ|PROT_WRITE, MAP_SHARED, sershmid,0);
	(*buf).type=2;
	strcpy(buf->content, clishm);
	munmap(buf, sizeof(request));
	sem_post(sem1);
	sem_post(sem2);
	exit(0);

}

int main(int argc, char const *argv[])
{
	request buf1, *buf2;


	clishm=malloc(32*sizeof(char));
	strcat(clishm, "/");
	strcat(clishm, argv[1]);
	strcat(clishm, "_shm:0");
	printf("%s\n",clishm );
	clishmid=shm_open(clishm, O_RDWR|O_CREAT, 0777);
	if (ftruncate(clishmid, sizeof(request))==-1){
		perror("ftruncate");
		exit(1);
	}


	sershm=malloc(32*sizeof(char));
	strcat(sershm, "/");
	strcat(sershm, argv[2]);
	strcat(sershm, "_shm:0");
	printf("%s\n",sershm );
	sershmid=shm_open(sershm, O_RDWR, 0777);


	if(clishmid==-1){
		printf("Error shms\n");
		exit(1);
	}
	if (sershmid==-1)
	{
		printf("sershm\n");
		exit(1);
	}

	/***** Recuperation des semid****/
	sem1=sem_open("/sem1", O_RDWR);/*sem de synchro avec le serveur*/
	sem2=sem_open("/sem2", O_RDWR);/*sem pour la synchro entre clients*/
	if(sem1==SEM_FAILED || sem2==SEM_FAILED){
		perror("sem_open");
		exit(1);
	}


	/***** Connexion ****/
	sem_wait(sem2);
	printf("Connexion\n");
	buf2=mmap(NULL, sizeof(request), PROT_READ | PROT_WRITE, MAP_SHARED, sershmid, 0);
	(*buf2).type=0;
	strcpy((*buf2).content, clishm);
	munmap(buf2, sizeof(request));
	sem_post(sem1);
	sem_post(sem2);

	
	/******** Fils de reception ****/
	if(!fork())
		fils_recept(clishm, clishmid, argv[1]);

	
	/******** Gestion de l'arret ****/
	signal(SIGINT, deconnexion);


	/******* Boucle de traitement ******/
	while (1){
		printf("%s >",argv[1]);
		scanf("%s", buf1.content);
		printf("content : %s\n", buf1.content);
		sem_wait(sem2);
		buf2=mmap(NULL, sizeof(request), PROT_READ|PROT_WRITE, MAP_SHARED, sershmid,0);
		buf1.type=1;
		(*buf2).type=buf1.type;
		strcpy((*buf2).content, buf1.content);
		printf("content buf2 : %s\n", buf2->content);
		munmap(buf2, sizeof(request));
		sem_post(sem1);
		sem_post(sem2);
	}
	return 0;
}