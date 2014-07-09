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
#include "dirent.h"
#include "pthread.h"


#ifndef TAILMSG
#define TAILMSG 80
#endif

#ifndef TAILPATH
#define TAILPATH 100
#endif

#ifndef MAXCONN
#define MAXCONN 5
#endif

/*
type : 1 : client requests to upload a file
		2 : client requests to download a file
		3 : client requests a list of files in current server WD
		4 : server response information
		5 : server response error
*/
int nb_conn;

typedef struct ${
	int type;
	char data[TAILMSG];
}message;

char** copy_argv;


void* connexion_thread(void* args){
	int *pt = malloc(sizeof(int));
	pt=(int*) args;
	int newsockcomfd = *pt;
	int fdout, done, filedin, optval=1, myport;
	int sockdatafd, newsockdatafd;
	char msg[TAILMSG];
	char destfiles[TAILMSG];
	char buff_path[TAILPATH];
	message msgrecu, msgenvoi;
	struct sockaddr_in servdata_addr, clidata_addr;
	DIR *pt_Dir;
	struct dirent* dirEnt;
	unsigned int fromlen = sizeof(servdata_addr);
	myport = atoi(copy_argv[1])+nb_conn;

	memset((char*)&msgrecu, 0, sizeof(message));
	memset((char*)&msgenvoi, 0, sizeof(message));
	memset((char*)destfiles, 0, TAILMSG);
	memset((char*)msg, 0, TAILMSG);
	memset((char*)buff_path, 0, TAILPATH);

	if((sockdatafd = socket(AF_INET, SOCK_STREAM, 0)) <0 ){
		perror("creation socket");
		exit(1);
	}
	servdata_addr.sin_family=AF_INET;
	servdata_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	servdata_addr.sin_port=htons(myport);
		
	setsockopt(sockdatafd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
	if (bind(sockdatafd, (struct sockaddr *) &servdata_addr, sizeof(servdata_addr)) < 0 ){
		perror("bind");
		exit(2);
	}
	if (listen(sockdatafd, 1) < 0){
		perror("listen");
		exit(1);
	}
	while(read(newsockcomfd, &msgrecu, sizeof(message))!=-1){
		if (msgrecu.type == 1){

			/****UPLOAD SUR SERVEUR*****/
			strcpy(destfiles, "recvfiles/");
			strcat(destfiles, msgrecu.data);
			printf("UPLOAD REQUEST: Nom du fichier : %s\n", destfiles);

			if ((fdout=open(destfiles, O_RDWR|O_CREAT|O_EXCL, 0600))==-1){
				perror("open");
				msgenvoi.type=5;
				strcpy(msgenvoi.data,"File already exists"); 
				write(newsockcomfd, &msgenvoi, sizeof(message));
			}
			if(fdout != -1){
				/**** sending the client the port on which we accept data 
				connection (control port +1 generally)***/
				msgenvoi.type=4;
				sprintf(msgenvoi.data, "%i", myport);
				write(newsockcomfd, &msgenvoi, sizeof(message));

				/****** waiting for the client to connect on the data socket ***/
				newsockdatafd=accept(sockdatafd, (struct sockaddr*) &clidata_addr, &fromlen);
				printf("Connection from client in pasv\n");
				
				/***** receiving the file from the client ***/
				while((done=read(newsockdatafd, msg, TAILMSG))>0){
					write(fdout, msg, done);
				}
				printf("Fin de fichier\n");
				close(fdout);
				close(newsockdatafd);
			}
		}

			
		else if (msgrecu.type == 2){

			/****** DOWNLOAD D'UN FICHIER DU SERVEUR*********/
			printf("DOWNLOAD REQUEST: Nom du fichier : %s\n", msgrecu.data);
			strcpy(destfiles, msgrecu.data);

			/**** sending the client the port on which we accept data 
			connection (control port +1 generally)***/
			msgenvoi.type=4;
			sprintf(msgenvoi.data, "%i", myport);
			write(newsockcomfd, &msgenvoi, sizeof(message));

			/****** waiting for the client to connect on the data socket ***/
			newsockdatafd=accept(sockdatafd, (struct sockaddr*) &clidata_addr, &fromlen);
			printf("Connection from client in pasv\n");

			if((filedin=open(destfiles, O_RDWR, 0600))==-1){
				perror("open");
				msgenvoi.type=5;
				strcpy(msgenvoi.data,"File doesn't exists"); 
				write(newsockcomfd, &msgenvoi, sizeof(message));
			}

			/*** sending the requested file on the data socket ***/
			while((done=read(filedin, msg, TAILMSG))>0){
				write(newsockdatafd, msg, done);
			}
			printf("File sent\n");
			printf("Closing connection of passive mode\n");
			close(newsockdatafd);
			close(filedin);
		}


		else if (msgrecu.type == 3){

			printf("LIST REQUEST\n");
			/***** obtaining the current working directory***/
			if (getcwd (buff_path, TAILPATH) == NULL ) {
				perror ("erreur getwcd \n");
				exit (1);
			}
			if ( ( pt_Dir = opendir (buff_path) ) == NULL) {
				perror ("erreur opendir \n");
				exit (1);
			}

			/**** sending the client the port on which we accept data 
			connection (control port +1 generally)***/
			msgenvoi.type=4;
			sprintf(msgenvoi.data, "%i", myport);
			write(newsockcomfd, &msgenvoi, sizeof(message));

			/****** waiting for the client to connect on the data socket ***/
			newsockdatafd=accept(sockdatafd, (struct sockaddr*) &clidata_addr, &fromlen);
			printf("Connection from client in pasv\n");

			/*** sending the list of files of cwd on the data socket ***/
			while ((dirEnt= readdir (pt_Dir)) !=NULL){
				strcpy(msg, dirEnt->d_name);
				write(newsockdatafd, msg, TAILMSG);
			}
			printf("List sent\n");
			close(newsockdatafd);
			closedir(pt_Dir);
		}
		else if(msgrecu.type == 6){
			printf("Deconnexion du client\n");
			break;
		}
		memset((char*)&msgrecu, 0, sizeof(message));
		memset((char*)&msgenvoi, 0, sizeof(message));
		memset((char*)destfiles, 0, TAILMSG);
		memset((char*)msg, 0, TAILMSG);
		memset((char*)buff_path, 0, TAILPATH);
	}
	close(newsockcomfd);
	nb_conn--;
	return NULL;
}



int main(int argc, char const *argv[])
{
	struct sockaddr_in serv_addr, cli_addr;
	unsigned int fromlen = sizeof(serv_addr);
	int sockcomfd, newsockcomfd;
	pthread_t thread_id[MAXCONN];
	nb_conn=0;
	int optval = 1;

	copy_argv=argv;

	if (argc != 2){
		printf("Invalid arguments\n");
		printf("usage : ./%s <port_number>\n", argv[0]);
		exit(1);
	}

	/***** init socket****/
	if((sockcomfd = socket(AF_INET, SOCK_STREAM, 0)) <0 ){
		perror("creation socket");
		exit(1);
	}

	/***** def socket ****/
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
	/***** nommage ****/
	setsockopt(sockcomfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
	if (bind(sockcomfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 ){
		perror("bind");
		exit(2);
	}

	/****** define the max number of connections on the socket ****/
	if (listen(sockcomfd, 5) < 0){
		perror("listen");
		exit(1);
	}
	while(1){
			newsockcomfd = accept(sockcomfd, (struct sockaddr *) &cli_addr, &fromlen);
			int *ref = malloc(sizeof(int));
			*ref=newsockcomfd;
			printf("New Connection !\n");
			printf("Client adress : %s\n",inet_ntoa(cli_addr.sin_addr));
			nb_conn++;
		if(nb_conn < 5){
			pthread_create(&thread_id[nb_conn], NULL, connexion_thread, (void*) ref);	
		}
	}
	return 0;
}