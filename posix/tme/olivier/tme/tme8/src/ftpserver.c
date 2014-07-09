#define _XOPEN_SOURCE 700
#include "ftpserver.h"
#define NBCLIENTS 5

char path[1024] ;
int cpt;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* process_request(void* scomVoid) {
        int* tmpScom = (int*) scomVoid;
        int scom = *tmpScom;
	char* fileName = (char*) malloc(sizeof(char)*1024);
	char* reponse = (char*) malloc(sizeof(char)*1024);
	void* buffer = (void*) malloc(sizeof(void)*1024);
	char* tmp= (char*) malloc(sizeof(char)*1024);
	char* commande = (char*) malloc(sizeof(char)*1024);
	
	strcpy(reponse,"SERVER -->> connection etablie");
	if(write(scom, reponse, strlen(reponse)+1) == -1){
		perror("Ecriture echouée");
		exit(1);
	}

	// on boucle en attendant les commandes
	 
	while(1){
		
		// reception de la commande demandée par le client 
		
		strcpy(commande,"");
		strcpy(reponse,"");
		strcpy(fileName,"");
		strcpy(buffer,"");
		if (read(scom, commande, sizeof(char)*1024) == -1) { 
			perror("recv commande echouée");
			exit(2);
		}
		printf("%s",commande);
		if(strncmp(commande, "UPLOAD", strlen("UPLOAD")) == 0){
			
			//reception du nom de fichier 
			
			if (read(scom, fileName, sizeof(char)*1024) == -1) { 
				perror("recvfrom"); exit(2);
			}				
			printf("voici le nom de fichier à uploader: %s\n", fileName);
			
			//reception et copie du contenu
			
			int desc;
			strcpy(tmp,path);
			strcat(tmp, fileName);
			if((desc = open(tmp, O_CREAT | O_RDWR, 0700)) == -1){
				perror("Ouverture fichier echouée");
				exit(1);
			}
			strcpy(buffer, "");
			while(1){
				if (read(scom, buffer, sizeof(void)*1024) == -1) { 
					perror("readfrom");
					exit(2);	
				}
				if(strcmp(buffer, "") == 0){
					break;
				}
				if(write(desc, buffer, 1024) == -1){
					perror("Ecriture fichier echouée");
					exit(1);
				}
				strcpy(buffer, "");
			}
			close(desc);
			printf("SERVER -->> Fichier uploadé\n");
			strcpy(reponse," fichier entierement recu ");
			if(write(scom, reponse, strlen(reponse)+1) == -1){
					perror("Ecriture fichier echouée");	exit(1);
				}
		}
		else if(strncmp(commande, "DOWNLOAD",strlen("DOWNLOAD")) == 0){
			
			//recuperation du nom de fichier à download 

			if (read(scom, fileName, sizeof(char)*1024) == -1) { 
				perror("recvfrom");
				exit(2);
			}
			
			printf("voici le nom de fichier à download dans %s: %s \n",path, fileName);
			
			//Ouverture et transmission du contenu
			
			strcpy(tmp,path);
			strcat(tmp, fileName);
			FILE* file = fopen(tmp, "r");
			while(fread(buffer, sizeof(void),1024, file) > -1){
				if(write(scom, buffer, 1024) == -1){
					perror("write");
					exit(1);
				}
			}
			// chaine vide fin de fichier
			if(write(scom, "", sizeof("")) == -1){
					perror("Ecriture fichier echouée"); exit(1);
			}
			fclose(file);
			printf("SERVER -->> fichier entierement transmis\n");
			if(read(scom, reponse, sizeof(char)*1024) == -1) { 
				perror("recv commande echouée");
				exit(2);
			}
			printf("CLIENT -->> %s\n",reponse);
		}
		else if(strncmp(commande, "LIST", strlen("LIST")) == 0){
			DIR* dir = opendir(path);
			struct dirent* file;
			char list[1024];
			strcpy(list, "");
			while((file = readdir(dir)) != NULL){
				strcat(list, file->d_name);
				strcat(list, " \n ");
			}
			if(write(scom, list, sizeof(list)) == -1){
				perror("Ecriture liste echouée");
				exit(1);
			}
			if (read(scom, commande, sizeof(char)*1024) == -1) { 
				perror("recvfrom");
				exit(2);
			}
			printf("CLIENT -->>%s",commande);
			closedir(dir);
		}
		else if(strncmp(commande, "QUIT", strlen("QUIT")) == 0){
			shutdown(scom, 2);
			close(scom);
			printf("Deconnexion effectuée\n");
			pthread_mutex_lock(&mutex);
			cpt--;
			pthread_cond_signal(&cond);
			pthread_mutex_unlock(&mutex);
			return 0;
		}

	}
}

int main(int argc, char *argv[]) {
	if(argc != 3){
		perror("Utilisation: ./ftpserver <port> <dir_path>");
		exit(1);
	}
	struct sockaddr_in sin;  /* nom de la socket du serveur */
	struct sockaddr_in exp;	/* nom de l'expediteur */
	int sc;
	pthread_t tid[NBCLIENTS];
	int fromlen = sizeof(exp);
	int sock;
	strcpy(path, argv[2]);
	
	//creation de la socket TCP

	if ((sc = socket(AF_INET,SOCK_STREAM, 0)) < 0) {
		perror("creation socket serveur echouée");
		exit(1);
	}

	// remplir le nom 
	memset((void*)&sin, 0, sizeof(sin));
	sin.sin_port = atoi(argv[1]);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	
	// nommage
	if (bind(sc, (struct sockaddr*)&sin, sizeof(sin)) == -1) {
		perror("Erreur au nommage");
		exit(1);
	}
	
	if(listen(sc, NBCLIENTS) == -1){
		perror("Erreur listen");
		exit(1);
	}
	printf("attente de connexion\n");
	
	//acceptation d'une connexion 
	
	int i=0;
	pthread_mutex_lock(&mutex);
	cpt=0;	
	while(1){
		if(cpt<NBCLIENTS){
			cpt++;
			pthread_mutex_unlock(&mutex);
			if((sock = accept(sc, (struct sockaddr*)&exp, (socklen_t*)&fromlen)) == -1){
				perror("Accept echouée");
				exit(3);
			}
			i++;
			printf("Une connexion a été etablie\n");
			
			// creation d'un pthread qui traite la requete

			pthread_create(&tid[i], 0, process_request, &sock);	
			pthread_detach(tid[i]);
		}else
			pthread_cond_wait(&cond,&mutex);
	}
	pthread_mutex_unlock(&mutex);
	


	// fermeture de la socket
         shutdown(sc, 2); 
	 close(sc);
	 return 0;
}
