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
	struct sockaddr_in serv_addr;
	int sockfd;
	int cpt=0;
	char host[64];
	char message[TAILMSG];
	int i;
	unsigned int fromlen = sizeof(serv_addr);
	int filedin;
	int done;

	if(argc != 4){
		printf("Invalid arguments\n");
		printf("usage : ./%s <dest addr> <port number> <filetosend>\n", argv[0]);
		exit(1);

	}

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) <0 ){
		perror("creation socket");
		exit(1);
	}
	/***** def socket ****/
	serv_addr.sin_family       = AF_INET;
	serv_addr.sin_addr.s_addr  = inet_addr(argv[1]);
	serv_addr.sin_port         = htons(atoi(argv[2]));
 
	/****** Connection server *****/
	if (connect(sockfd, (struct sockaddr *) &serv_addr, fromlen) < 0){
		perror("connect");
		exit(1);
	}
	printf("Connected\n");
	if((filedin=open(argv[3], O_RDWR, 0600))==-1){
		perror("open");
		return EXIT_FAILURE;
	}
	write(sockfd, argv[3], strlen(argv[3]));
	while((done=read(filedin, message, TAILMSG))>0){
		write(sockfd, message, done);
	}

	close(sockfd);

	return 0;
}