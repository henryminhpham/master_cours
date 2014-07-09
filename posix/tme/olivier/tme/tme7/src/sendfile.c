#include "sendfile.h"
#define XOPEN_SOURCE 700
#define BUFF 4096

int main(int argc, char** argv) {
  if(argc != 4) {
    perror("Mauvais arguments");
    return -1;
  }
  // On prend le port
  int port = atoi(argv[2]);
  struct sockaddr_in dest;
  int sock;
  struct addrinfo* result;
  // On crée la socket
  if ((sock = socket(AF_INET,SOCK_STREAM,0)) == -1) {
    perror("socket");
    exit(1);
  } 
  
  // On initialise tout + on récupère l'adresse
  if (getaddrinfo(argv[1], 0, 0, &result) != 0) {perror("getaddrinfo"); exit(EXIT_FAILURE);}
  memset((char *)&dest,0, sizeof(dest));
  memcpy((void*)&((struct sockaddr_in*)result->ai_addr)->sin_addr, (void*)&dest.sin_addr, sizeof(dest));
  dest.sin_family = AF_INET;
  dest.sin_port = htons(port);
  
  // On se connecte au serveur
  printf("Connexion au serveur %s sur le port %d\n", argv[1], port);
  if (connect(sock, (struct sockaddr *) &dest, sizeof(dest)) == -1){
    perror("connect"); exit(1);
  } 
  
  // On ouvre le fichier
  FILE* fd;
  if((fd = fopen(argv[3], "r")) == NULL) {
    perror("Le fichier n'existe pas");
    return EXIT_FAILURE;
  }
  // On envoie le nom du fichier
  printf("Envoi du fichier %s en cours.\n", argv[3]);
  if (write(sock,argv[3],sizeof(argv[3])) == -1) {
    perror("write"); exit(1);
  } 
  // On lit toutes les lignes et pour chaque ligne lue, on l'envoie
  char buffer[BUFF];
  while(fgets(buffer, BUFF, fd) != NULL) {
    printf("Envoi de \"%s\"\n", buffer);
    // Envoi de la ligne
    write(sock, buffer, BUFF);
  }
  // On ferme tout
  printf("Fin de l'envoi du fichier\n");
  fclose(fd);
  shutdown(sock,2);
  close(sock);
  return EXIT_SUCCESS;
}