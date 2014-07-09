#define _XOPEN_SOURCE 700
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "netdb.h"
#include "arpa/inet.h"
#include "time.h"
#include "fcntl.h"
#include "sys/select.h"


#ifndef TAILMSG
#define TAILMSG 80
#endif


int max_decriptors (int* desc_table, int size){
	int i;
	int res;
	res=desc_table[0];
	for (i=1; i<size; i++){
		if(desc_table[i]>res){
			res=desc_table[i];
		}
	}
	return res;
}


int main(int argc, char const *argv[])
{
	struct sockaddr_in serv_addr, cli_addr;
	unsigned int fromlen = sizeof(serv_addr);
	int fdout;

	int sockcons[argc-1];
	int sockcom;
	int i;
	fd_set mselect;
	int max;
	int on=1;

	time_t timestamp;
	struct tm* t;
	char towrite[TAILMSG];

	if ((fdout=open("cxlog", O_RDWR|O_CREAT|O_EXCL, 0777))==-1){
		perror("open");
		return EXIT_FAILURE;
	}
	for (i=0; i<argc-1; i++){
		/***** init socket****/
		if((sockcons[i] = socket(AF_INET, SOCK_STREAM, 0)) <0 ){
		perror("creation socket");
		exit(1);
		}
		/***** def socket ****/
		serv_addr.sin_family=AF_INET;
		serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
		serv_addr.sin_port=htons(atoi(argv[i+1]));
		/***** nommage ****/
		setsockopt(sockcons[i], SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

		if (bind(sockcons[i], (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 ){
			perror("bind");
			exit(2);
		}
		/****** define the max number of connections on the socket ****/
		if (listen(sockcons[i], 3) < 0){
			perror("listen");
			exit(1);
		}
	}
	while(1){
		memset((char*)towrite, 0, TAILMSG);
		FD_ZERO(&mselect);
		for(i=0; i<argc-1; i++){
			FD_SET(sockcons[i], &mselect);
		}
		FD_SET(0, &mselect);
		max=max_decriptors(sockcons, argc-1);
		if(select(max+1, &mselect, NULL, NULL, NULL)==-1){
			perror("select");
			break;
		}
		if(FD_ISSET(0, &mselect)){
/*			fgets(towrite, TAILMSG-1, stdin);
			if(strcmp(towrite, "quit")==0)
*/				break;
		}

		for (i=0; i<argc-1; i++){
			if(FD_ISSET(sockcons[i], &mselect)){
				if((sockcom=accept(sockcons[i], (struct sockaddr*) &cli_addr, &fromlen))==-1){
					perror("accept");
				}
				timestamp = time(NULL);
				t = localtime(&timestamp);
				sprintf(towrite,"%s_%s_%d/%d/%d_%02u:%02u:%02u\n",inet_ntoa(cli_addr.sin_addr), argv[i+1], t->tm_mday, t->tm_mon+1, t->tm_year - 100, t->tm_hour, t->tm_min, t->tm_sec);
				if(write(fdout, towrite, strlen(towrite))==-1){
					perror("write");
					break;
				}
				shutdown(sockcom, 2);
				close(sockcom);
			}
		}
	}
	for(i=0; i<argc-1; i++){
		close(sockcons[i]);
	}
	close(fdout);
	return 0;
}