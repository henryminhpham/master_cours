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
#include <fcntl.h>
#include <errno.h>


#ifndef PORTSERV
#define PORTSERV 4567
#endif
#ifndef TAILMSG
#define TAILMSG 80
#endif



int main(int argc, char const *argv[])
{
	struct sockaddr_in serv_addr, cli_addr;
	int sockfd, newsockfd;
	int cpt=0;
	char host[64];
	char message[TAILMSG];
	int i;
	unsigned int fromlen = sizeof(serv_addr);
	int fdout;
	int done;
	char destfiles[128];
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) <0 ){
		perror("creation socket");
		exit(1);
	}
	if (argc != 2){
		printf("Invalid arguments\n");
		printf("usage : ./%s <port number>\n", argv[0]);
		exit(1);
	}
	/***** def socket ****/
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));

	/***** nommage ****/
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 ){
		perror("bind");
		exit(2);
	}

	if (listen(sockfd, 3) < 0){
		perror("listen");
		exit(1);
	}

	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &fromlen);
	printf("New Connection !\n");

	printf("Client adress : %s\n",inet_ntoa(cli_addr.sin_addr));

	strcpy(destfiles, "recvfiles/");
	read(newsockfd, message, TAILMSG);
	strcat(destfiles, message);
	printf("Nom du fichier : %s\n", destfiles);
	

	if ((fdout=open(destfiles, O_RDWR|O_CREAT|O_EXCL, 0600))==-1){
		perror("open");
	}
	if(fdout != -1){
		while((done=read(newsockfd, mesage, TAILMSG))>0){
			write(fdout, message, done);
		}
		printf("Fin de fichier\n");
		close(fdout);
	}


	close(newsockfd);
	close(sockfd);
	return 0;
}

