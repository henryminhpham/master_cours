#include "recvfile.h"
#define XOPEN_SOURCE 700
#define BUFF 4096

int main(int argc, char** argv) {
  if(argc != 2) {
    perror("Invalid arguments"); exit(1);
  }
  struct sockaddr_in sin;
  int sc;
  int scom;
  struct sockaddr_in exp;
  int fromlen = sizeof exp;
  
  // On crée la socket
  if ((sc = socket(AF_INET,SOCK_STREAM,0)) < 0) {
      perror("socket"); exit(1);
  }
  // On initialise tout
  memset((char *)&sin,0, sizeof(sin));
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  int port = atoi(argv[1]);
  sin.sin_port = htons(port);
  sin.sin_family = AF_INET;
  
  // On bind la socket, création du serveur
  printf("Démarrage du serveur sur le port %d\n", port);
  if (bind(sc,(struct sockaddr *)&sin,sizeof(sin)) < 0) {
    perror("bind");
    exit(1);
  } 
  // On se met en écoute
  listen(sc, 1);
  // On accepte la socket du client
  if ((scom = accept(sc, (struct sockaddr *)&exp, (socklen_t *)&fromlen))== -1) {
    perror("accept"); exit(3);
  } 
  
  char name[BUFF];
  // On lit le nom du fichier
  if (read(scom,name, BUFF) < 0) {
    perror("read"); exit(4);
  }    
  // On crée le fichier dont on vient de recevoir le nom
  FILE* fd;
  printf("Réception du nom de fichier \"%s\"\n", name);
  if((fd = fopen(name, "w+")) == NULL) {
    perror("fopen");
    return EXIT_FAILURE;
  }
  printf("Début de la réception du contenu...\n");
  char buffer[BUFF];
  // On lit dans la socket et on écrit le contenu dans le fichier
  while(read(scom, buffer, BUFF) > 0) {
    printf("Réception de \"%s\"\n", buffer);
    fputs(buffer, fd);
  }
  printf("Fin de la réception du fichier\n");
  // On ferme tout
  fclose(fd);
  shutdown(scom,2);
  close(scom);
  close(sc);
  return EXIT_SUCCESS;
}
