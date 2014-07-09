#define _XOPEN_SOURCE 700
#include "ftpclient.h"

int main(int argc, char *argv[]){
	if(argc != 3){
		perror("Utilisation: ftpclient <addr> <port>");
		exit(1);
	}
	
	struct sockaddr_in dest;  /* Nom de la socket du serveur */
	int sc;
	struct hostent* hp;
	char* fileName = (char*) malloc(sizeof(char)*1024);
	char* commande = (char*) malloc(sizeof(char)*1024);
	char* reponse = (char*) malloc(sizeof(char)*1024);
	void* buffer = (void*) malloc(sizeof(void)*1024);
	
	/* creation de la socket */
	if ((sc = socket(AF_INET,SOCK_STREAM, 0)) < 0) {
		perror("creation socket");
		exit(1);
	}

	if ((hp = gethostbyname(argv[1])) == NULL) {
		perror("gethostbyaddr");
		exit(3);
	}

	/* remplir le nom */
	memset((void*)&dest, 0, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_port = atoi(argv[2]);
	memcpy(&dest.sin_addr.s_addr, hp->h_addr_list[0], hp->h_length);
	
	/* demande d'une connexion */
	if(connect(sc, (struct sockaddr*)&dest, sizeof(dest)) == -1){
		perror("Connexion echouée");
		exit(3);
	}
	if (read(sc, reponse, sizeof(char)*1024) == -1) { 
					perror("readfrom");	exit(2);
	}
	printf("%s\n",reponse);
	printf("les commandes : \n \t LIST \n \t DOWNLOAD  \n \t UPLOAD\n \t QUIT \n ");
	/**
	 * boucle principale
	 * */
	while(1){
		printf("En attente de vos commandes\n");
		
		fgets(commande, sizeof(char)*1024, stdin);
		if(strcmp(commande, "UPLOAD\n") == 0){
			printf("COMMANDE ENTREE %s\n",commande);
			if(write(sc, commande, strlen(commande)+1) == -1){
				perror("Envoi message echoué"); exit(1);
			}
			/**
			 * demande et envoi du nom de fichier à uploader ( à transmettre)
			 * */
			printf("\tNom de fichier?\n");
			fgets(fileName, sizeof(char)*1024, stdin);
			/* suppression du \n de fin d'entrée */
			char* fin = strchr(fileName, '\n');
			*fin = '\0';
			if(write(sc, fileName, 1024) == -1){
				perror("Envoi message echoué"); exit(1);
			}
			FILE* file = fopen(fileName, "r");

			while(fread(buffer, sizeof(void), 1024, file) > -1){
				if(write(sc, buffer, 1024) == -1){
					perror("Ecriture fichier echouée"); exit(1);
				}
			}
			/* envoi d'une chaine vide pour signifier la fin de fichier */
			if(write(sc, "", sizeof("")) == -1){
					perror("Ecriture fichier echouée"); exit(1);
			}
			fclose(file);
			printf("CLIENT -->> Fichier uploadé fichier entierment transmis\n");
			if(read(sc, reponse, sizeof(char)*1024) == -1) { 
					perror("recv commande echouée"); exit(2);
			}
			printf("SERVER -->> %s\n",reponse);
			continue;
		}
		else if(strcmp(commande, "DOWNLOAD\n") == 0){
			printf("COMMANDE ENTREE %s\n",commande);
			if(write(sc, commande, strlen(commande)+1) == -1){
				perror("Envoi message echoué");	exit(1);
			}
			/**
			 * demande et reception du nom de fichier à telecharger 
			 * */
			printf("\tNom de fichier?\n");
			fgets(fileName, sizeof(char)*1024, stdin);
			/* on retire le \n à la fin du nom de fichier */
			char* fin = strchr(fileName, '\n');
			*fin = '\0';
			if(write(sc, fileName, strlen(fileName)+1) == -1){
				perror("Envoi message echoué");	exit(1);
			}
			/**
			 * reception et copie du contenu 
			 * */
			int desc;
			if((desc = open(fileName, O_CREAT | O_RDWR | O_TRUNC, 0700)) == -1){
				perror("Ouverture fichier echouée"); exit(1);
			}
			
			strcpy(buffer, "");
			while(1){
				if (read(sc, buffer, sizeof(void)*1024) == -1) { 
					perror("readfrom");	exit(2);
				}
				if(strcmp(buffer, "") == 0){
					break;
				}
				if(write(desc, buffer, 1024) == -1){
					perror("Ecriture fichier echouée");	exit(1);
				}
				strcpy(buffer, "");
			}
			close(desc);
			strcpy(reponse," fichier entierement recu ");
			if(write(sc, reponse, sizeof(char)*1024) == -1) { 
					perror("recv commande echouée"); exit(2);
			}
			printf("CLIENT -->> Fichier entierement telechargé\n");
		}
		else if(strcmp(commande, "LIST\n") == 0){
			printf("COMMANDE ENTREE %s\n",commande);
			if(write(sc, commande, strlen(commande)+1) == -1){
				perror("Envoi message echoué");	exit(1);
			}
			strcpy(reponse, "");
			if(read(sc, reponse, sizeof(char)*1024) == -1){
				perror("Reception message echouée"); exit(2);
			}
			printf("voici la liste des fichiers contenus sur le serveur:\n %s\n", reponse);
			strcpy(reponse, "");
			strcpy(reponse, "liste du contenu du serveur recu\n");
			if(write(sc, reponse, strlen(reponse)+1) == -1){
				perror("Envoi message echoué");	exit(1);
			}
		}
		else if(strcmp(commande, "QUIT\n") == 0){
			printf("COMMANDE ENTREE %s\n",commande);
			if(write(sc, commande, strlen(commande)+1) == -1){
				perror("Envoi message echoué");	exit(1);
			}
			shutdown(sc, 2);
			close(sc);
			printf("Vous avez été deconnecté\n");
			return (0);
		}
		else{
			printf("Commande non reconnue\n");
		}
	}
	shutdown(sc, 2);
	close(sc);
	return (0);
}
