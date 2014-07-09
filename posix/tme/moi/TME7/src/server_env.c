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

typedef struct ${
	int type;
	int sizeattr;
	int sizeval;
}config;

int sockfd;


void finish (int sig){
	printf("\nSortie\n");
	close(sockfd);
	exit(0);

}


int main(int argc, char const *argv[])
{
	struct sockaddr_in serv_addr, cli_addr;
	unsigned int fromlen = sizeof(serv_addr);
	config configs;
	char message[TAILMSG];
	char *attr;
	char *val;
	char *rep;
	int repp;

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) <0 ){
		perror("creation socket");
		exit(1);
	}
	/***** def socket ****/
	memset((char*)&serv_addr, 0, sizeof(serv_addr));
	memset((char*)&cli_addr, 0, sizeof(cli_addr));
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(PORTSERV);
	serv_addr.sin_family=AF_INET;

	/***** nommage ****/
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 ){
		perror("bind");
		exit(2);
	}
	signal(SIGINT, finish);
	attr = malloc(TAILMSG*sizeof(char));
	val = malloc(TAILMSG*sizeof(char));

	while(recvfrom(sockfd, &configs, sizeof(config), 0, (struct sockaddr *)&cli_addr, &fromlen)){
		memset((char*)message, 0, TAILMSG);
		memset((char*)attr, 0, TAILMSG);
		memset((char*)val, 0, TAILMSG);
		printf("Nouvelle requete ");
		if (configs.type==1){
			printf("SET\n");
			recvfrom(sockfd, message, TAILMSG*sizeof(char), 0, 0, &fromlen);
			strncpy(attr, message, configs.sizeattr);
			strcpy(val, message+configs.sizeattr);
			repp=setenv(attr, val, 0);
			if(sendto(sockfd, &repp, sizeof(int), 0, (struct sockaddr *) &cli_addr, sizeof(serv_addr)) < 0){
				perror("sendto");
				exit(1);
			}

		}
		else if (configs.type==2){
			printf("GET\n");
			recvfrom(sockfd, message, TAILMSG*sizeof(char), 0, 0, &fromlen);
			strncpy(attr, message, strlen(message));
			rep=getenv(attr);
			if(rep==NULL){
				rep=malloc(TAILMSG*sizeof(char));
				strcpy(rep,"Error environnement doesn't exists");
			}
			if(sendto(sockfd, rep, strlen(rep)*sizeof(char), 0, (struct sockaddr *) &cli_addr, sizeof(serv_addr)) < 0){
				perror("sendto");
				exit(1);
			}
		}
	}

	return 0;
}