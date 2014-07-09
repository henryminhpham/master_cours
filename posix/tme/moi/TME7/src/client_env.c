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

char* couper_mot( char* string ){
	int i;
	char *res = malloc(strlen(string)*sizeof(char));
	for(i=0; i<strlen(string); i++){
		if(string[i]==' ' || string[i]=='\n'){
			res[i]='\0';
			return res;
		}
		res[i]=string[i];
	}
	return NULL;
}


int main(int argc, char const *argv[])
{
	struct sockaddr_in serv_addr;
	config configs;
	char type;
	char* attr = malloc (TAILMSG*sizeof(char));
	char* val = malloc (TAILMSG*sizeof(char));
	char message[TAILMSG];
	char response[TAILMSG];
	unsigned int fromlen = sizeof(serv_addr);
	int repp;
	char commande[TAILMSG];

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) <0 ){
		perror("creation socket");
		exit(1);
	}
	/***** def socket ****/
	serv_addr.sin_addr.s_addr=inet_addr("0.0.0.0");
	serv_addr.sin_port=htons(PORTSERV);
	serv_addr.sin_family=AF_INET;
	



	signal(SIGINT, finish);


	while(1){
		memset((char*)response, 0, TAILMSG);
		memset((char*)message, 0, TAILMSG);
		memset((char*)attr, 0, TAILMSG);
		memset((char*)val, 0, TAILMSG);
		memset((char*)commande, 0, TAILMSG);

		printf("Veuillez entrer une commande... (Ctrl+C pour sortir)\n");
		fgets(commande, TAILMSG, stdin);
		type=commande[0];

		if (type=='S'){
			attr=couper_mot(commande+2);
			val=couper_mot(commande+2+strlen(attr)+1);
			configs.type=1;
			configs.sizeattr=strlen(attr);
			configs.sizeval=strlen(val);
			if(sendto(sockfd, &configs, sizeof(config), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
				perror("sendto");
				exit(1);
			}
			strcat(attr, val);
			strcpy(message, attr);
			if(sendto(sockfd, message, strlen(message)*sizeof(char), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
				perror("sendto");
				exit(1);
			}
			recvfrom(sockfd, &repp, sizeof(int), 0, 0, &fromlen);
			printf("\nResponse for %c %s : %d\n\n", type, attr, repp);

		}
		else if (type=='G'){
			attr=couper_mot(commande+2);
			configs.type=2;
			configs.sizeattr = strlen(attr);
			configs.sizeval = 0;
			if(sendto(sockfd, &configs, sizeof(config), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
				perror("sendto");
				exit(1);
			}
			strcpy(message, attr);
			if(sendto(sockfd, message, strlen(message)*sizeof(char), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
				perror("sendto");
				exit(1);
			}
			recvfrom(sockfd, response, TAILMSG*sizeof(char), 0, 0, &fromlen);
			printf("\nResponse for %c %s : %s\n\n", type, attr, response);

		}
	}
	return 0;
}