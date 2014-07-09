#define _XOPEN_SOURCE 700
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <string.h>
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "netdb.h"
#include "arpa/inet.h"
#include "sys/ipc.h"
#include "sys/sem.h"
#include "time.h"
#include "sys/shm.h"

#define NB_PROC 4
#ifndef PORTSERV
#define PORTSERV 4567
#endif
#ifndef TAILMSG
#define TAILMSG 80
#endif

int main(int argc, char const *argv[])
{
	struct sockaddr_in serv_addr;
	int sockfd;
	int cpt=0;
	char host[64];
	pid_t pid=1;
	int i;
	unsigned int fromlen = sizeof(serv_addr);

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) <0 ){
		perror("creation socket");
		exit(1);
	}
	/***** def socket ****/
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(PORTSERV);
	serv_addr.sin_family=AF_INET;

	/***** nommage ****/
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 ){
		perror("bind");
		exit(2);
	}

	/**** creation des fils****/
	for (i=0; i<NB_PROC && pid; i++){
		pid=fork();
	}
	/****** Le pere rçoit toutes les valeurs comme dans un tube ****/
	if (pid){
		int res=0, temp;
		for (i=0; i<NB_PROC; i++){
			recvfrom(sockfd, &temp, sizeof(int), 0, 0, &fromlen);
			printf("J'ai reçu %d\n", temp);
			res+=temp;
		}
		printf("Resultat final : %d\n", res);
		close(sockfd);
		/**** Pas besoin d'attendre les fils, ils sont deja logiquement terminés ****/
	}
	/****** Les fils envoient des valeurs aléatoires dans le socket ****/
	else{
		int randval;
		sleep(i);
		srand(time(NULL)*getpid());
		randval=(int)(10*(float)rand()/RAND_MAX);
		printf("Moi j'envoie : %d\n", randval);
		if(sendto(sockfd, &randval, sizeof(int), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
			perror("sendto");
			exit(1);
		}
	}
	return 0;
}