#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include "../include/bufmsg.h"

#define _XOPEN_SOURCE 700
#define NBMAX_CLI 15


char** clients;



int init_clients(void){
	int i;
	clients=malloc(NBMAX_CLI*sizeof(char*));
	for (i=0; i<NBMAX_CLI; i++){
		clients[i]=malloc(32*sizeof(char));
	}
	if (clients==NULL){
		return -1;
	}
	return 0;
}

void ajouter_nouveauclient(char* nouv_client){
	int i;
	for (i=0; i<NBMAX_CLI; i++){
		if (clients[i][0]!='/'){
			strcpy(clients[i], nouv_client);
			printf("clients[i] : %s, i: %d\n",clients[i], i );
			return;
		}
	}
}


void diffuser_message(char* message){

	int i;
	sem_t *sem_send;
	int clishmid;
	request *buf;
	for (i=0; i<NBMAX_CLI; i++){
		if (clients[i][0]=='/'){
			clishmid=shm_open(clients[i], O_RDWR, 0777);
			buf=mmap(NULL, sizeof(request), PROT_READ|PROT_WRITE, MAP_SHARED, clishmid,0);
			strcpy(buf->content, message);
			munmap(buf, sizeof(request));
			sem_send=sem_open(clients[i], O_RDWR);
			sem_post(sem_send);

		}
	}
}

void deconnecter_client(char* clishm){

	int i;
	for (i=0; i<NBMAX_CLI; i++){
		if (strcmp(clients[i] ,clishm)==0){
			printf("clients[i] : %s\n",clients[i] );
			strcpy(clients[i], "");
			return;
		}
	}

}


int main(int argc, char const *argv[])
{
	int sershmid;
	request buf1, *buf2;
	char* sershm;
	sem_t *sem1, *sem2;
	sershm=malloc(32*sizeof(char));
	strcat(sershm, "/");
	strcat(sershm, argv[1]);
	strcat(sershm, "_shm:0");
	printf("%s\n",sershm );
	sershmid=shm_open(sershm, O_RDWR|O_CREAT, 0777);
	if(sershmid == -1){
		perror("sershmopen");
		exit(1);
	}
	if (ftruncate(sershmid, sizeof(request))==-1){
		perror("ftruncate");
		exit(1);
	}


	/*ouvrir les semaphores necessaires*/
	sem1=sem_open("/sem1", O_CREAT, 0777, 0);/*sem de synchro avec le serveur*/
	sem2=sem_open("/sem2", O_CREAT, 0777, 1);/*sem pour la synchro entre clients*/
	if(sem1==SEM_FAILED || sem2==SEM_FAILED){
		perror("sem_open");
		exit(1);
	}

	/****** initialisation du tableau de clients****/
	if(init_clients()==-1){
		perror("init_clients");
		exit(1);
	}


	/**********Traitement du serveur*********/
	while (1){
		sem_wait(sem1);
		buf2=mmap(NULL, sizeof(request), PROT_READ|PROT_WRITE, MAP_SHARED, sershmid,0);
		if ((*buf2).type==0){
			printf("type 0\n");
			printf("content : %s\n",(*buf2).content);
			ajouter_nouveauclient(buf2->content);
		}
		else if ((*buf2).type == 1){
			printf("type 1\n");
			diffuser_message(buf2->content);
		}
		else if ((*buf2).type == 2){
			printf("type 2\n");
			deconnecter_client(buf2->content);
		}
		munmap(buf2, sizeof(request));

	}
	return 0;
}