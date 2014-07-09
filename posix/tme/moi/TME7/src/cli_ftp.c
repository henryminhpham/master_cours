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
#include "time.h"
#include "fcntl.h"
#include "sys/shm.h"

#ifndef TAILMSG
#define TAILMSG 80
#endif


/*
type : 1 : client requests to upload a file
		2 : client requests to download a file
		3 : client requests a list of files in current server WD
		4 : server response information
		5 : server response error
*/


typedef struct ${
	int type;
	char data[TAILMSG];
}message;


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
	struct sockaddr_in serv_addr, servdata_addr;
	unsigned int fromlen = sizeof(serv_addr);
	char msg[TAILMSG];
	int sockcomfd, sockdatafd;
	int pid;
	message msgrecu, msgenvoi;
	char filename[TAILMSG];
	char nomcommande[TAILMSG];
	char commande[TAILMSG];
	int filedin, done, fdout;

	if (argc != 3){
		printf("Invalid arguments\n");
		printf("usage : ./%s <dest_addr> <port_number>\n", argv[0]);
		exit(1);
	}


	if((sockcomfd = socket(AF_INET, SOCK_STREAM, 0)) <0 ){
		perror("creation socket");
		exit(1);
	}
	/***** def socket ****/
	serv_addr.sin_family       = AF_INET;
	serv_addr.sin_addr.s_addr  = inet_addr(argv[1]);
	serv_addr.sin_port         = htons(atoi(argv[2]));
 
	/****** connection to server *****/
	if (connect(sockcomfd, (struct sockaddr *) &serv_addr, fromlen) < 0){
		perror("connect");
		exit(1);
	}
	printf("Connected to com ftp server\n");
	while(1){
		memset((char*)&msgrecu, 0, sizeof(message));
		memset((char*)&msgenvoi, 0, sizeof(message));
		memset((char*)msg, 0, TAILMSG);
		memset((char*)commande, 0, TAILMSG);
		memset((char*)nomcommande, 0, TAILMSG);
		memset((char*)filename, 0, TAILMSG);


		printf("Veuillez entrer une commande... (Ctrl+C pour sortir)\n");
		fgets(commande, TAILMSG, stdin);
		strcpy(nomcommande,couper_mot(commande));


		if (strcmp(nomcommande, "UPLOAD")==0){

			/***** sending the server the command the user entered : 
			"UPLOAD filename" ****/
			msgenvoi.type=1;
			strcpy(filename,couper_mot(commande+strlen(nomcommande)+1));
			strcpy(msgenvoi.data, filename);
			write(sockcomfd, &msgenvoi, sizeof(message));

			/*** reponse of the server of the request with the port number to connect
			for pasive mode****/
			read(sockcomfd, &msgrecu, sizeof(message));
			if (msgrecu.type==5){
				printf("Error to store the file, the server returned : %s\n", msgrecu.data);
			}
			else{
				/****** init socket of the data connection**********/
				if((sockdatafd = socket(AF_INET, SOCK_STREAM, 0)) <0 ){
					perror("creation socket");
					exit(1);
				}
				/***** def socket of the data connection****/
				servdata_addr.sin_family       = AF_INET;
				servdata_addr.sin_addr.s_addr  = inet_addr(argv[1]);
				servdata_addr.sin_port         = htons(atoi(msgrecu.data));
			 
				/****** connection for data transport *****/
				if (connect(sockdatafd, (struct sockaddr *) &servdata_addr, fromlen) < 0){
					perror("connect");
					exit(1);
				}
				printf("Connection in passive mode on port : %d\n", atoi(msgrecu.data));

				if((filedin=open(filename, O_RDWR, 0600))==-1){
					perror("open");
					return EXIT_FAILURE;
				}

				/*** sending the file to server on the data socket ***/
				while((done=read(filedin, msg, TAILMSG))>0){
					write(sockdatafd, msg, done);
				}
				printf("Closing connection of passive mode\n");
				printf("***File sent\n");
				close(sockdatafd);
				close(filedin);
			}
		}


		else if (strcmp(nomcommande, "DOWNLOAD")==0){

			/***** sending to server the request ("DONWLOAD filename")***/
			msgenvoi.type=2;
			strcpy(filename,couper_mot(commande+strlen(nomcommande)+1));
			strcpy(msgenvoi.data, filename);
			write(sockcomfd, &msgenvoi, sizeof(message));

			/*** reponse of the server of the request with the port number to connect
			for pasive mode****/
			read(sockcomfd, &msgrecu, sizeof(message));

			if (msgrecu.type==5){
				printf("Error to download the file, the server returned : %s\n", msgrecu.data);
			}
			else{
				/****** init socket of the data connection**********/
				if((sockdatafd = socket(AF_INET, SOCK_STREAM, 0)) <0 ){
					perror("creation socket");
					exit(1);
				}
				/***** def socket of the data connection****/
				servdata_addr.sin_family       = AF_INET;
				servdata_addr.sin_addr.s_addr  = inet_addr(argv[1]);
				servdata_addr.sin_port         = htons(atoi(msgrecu.data));

				/****** connection for data transport *****/
				if (connect(sockdatafd, (struct sockaddr *) &servdata_addr, fromlen) < 0){
					perror("connect");
					exit(1);
				}
				printf("Connection in passive mode on port : %d\n", atoi(msgrecu.data));

				strcat(filename, "_copy");
				if ((fdout=open(filename, O_RDWR|O_CREAT|O_EXCL, 0600))==-1){
					perror("open");
				}

				/***** receiving the file frome the server *******/
				while((done=read(sockdatafd, msg, TAILMSG))>0){
					write(fdout, msg, done);
				}
				printf("***File received\n");
				close(sockdatafd);
				close(fdout);
			}
		}


		else if (strcmp(nomcommande, "LIST")==0){

			/***** sending to server the request ("LIST")***/
			msgenvoi.type=3;
			write(sockcomfd, &msgenvoi, sizeof(message));
			/*** reponse of the server of the request with the port number to connect
			for pasive mode****/
			read(sockcomfd, &msgrecu, sizeof(message));

			/****** init socket of the data connection**********/
			if((sockdatafd = socket(AF_INET, SOCK_STREAM, 0)) <0 ){
				perror("creation socket");
				exit(1);
			}
			/***** def socket of the data connection****/
			servdata_addr.sin_family       = AF_INET;
			servdata_addr.sin_addr.s_addr  = inet_addr(argv[1]);
			servdata_addr.sin_port         = htons(atoi(msgrecu.data));

			/****** connection for data transport *****/
			if (connect(sockdatafd, (struct sockaddr *) &servdata_addr, fromlen) < 0){
				perror("connect");
				exit(1);
			}
			printf("Connection in passive mode on port : %d\n", atoi(msgrecu.data));

			/***** receiving the file frome the server *******/
			while((done=read(sockdatafd, msg, TAILMSG))>0){
				printf("%s\n",msg);
			}
			printf("***End of list\n");
			close(sockdatafd);
		}
	}
	return 0;
}
