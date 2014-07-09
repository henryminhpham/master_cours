#include "connectserver.h"
#define XOPEN_SOURCE 700

int size;
int* sc;
int fd_file;

int main(int argc, char** argv) {
  if(argc == 1) {
    perror("Arguments <port1> <port2> ...");
    return EXIT_FAILURE;
  }
  int i;
  int scom;
  struct sockaddr_in exp;
  memset(&exp, 0, sizeof(exp));
  socklen_t fromlen = sizeof exp;
  size = argc - 1;
  sc = malloc(sizeof(int) * size);  
  sigset_t sig;
  struct sigaction action;
  // On kill proprement le serveur
  sigemptyset(&sig);
  action.sa_handler = close_socket;
  action.sa_mask = sig;
  sigaction(SIGINT, &action, 0);
  
  // On prépare le fichier
  if((fd_file = open(FILENAME, O_WRONLY | O_TRUNC | O_CREAT, 0600)) == -1) {
    perror("open file");
    return EXIT_FAILURE;
  }
  
  init_socket(sc, size, argv);
  for(;;) {
    fd_set mselect;
    FD_ZERO(&mselect);
    for(i = 0 ; i < size ; i++) {
      // On met toutes les sockets
      FD_SET(sc[i], &mselect);
    }
    printf("En attente d'un évènement...\n");
    if(-1 == select(sizeof(mselect) * sizeof(int), &mselect, NULL, NULL, NULL)) {
      perror("select");
      close_socket(SIGINT);
      return EXIT_FAILURE;
    } 
    for(i = 0 ; i < size ; i++) {
      // On récupère la connexion
      if(FD_ISSET(sc[i], &mselect)) {
        if ((scom = accept(sc[i], (struct sockaddr *)&exp, &fromlen)) == -1) {
          perror("accept"); 
          close_socket(SIGINT);
          exit(3);
        }
        // On écrit dans le fichier
        char* addr = inet_ntoa(exp.sin_addr);
        write_file(addr);
        // On ferme le client
        shutdown(scom, 2);
        close(scom);
      }
    }   
  }
  return EXIT_SUCCESS;
}

void init_socket(int* array, int size, char** argv) {
  int i;
  int yes = 1;
  printf("Initialisation des %d sockets en cours...\n", size);
  for(i = 0 ; i < size ; i++) {
    struct sockaddr_in sin;
    // On crée la socket
    if ((sc[i] = socket(AF_INET,SOCK_STREAM,0)) < 0) {
        perror("socket"); exit(1);
    }
    // Eviter le Address already in use
    if(setsockopt(sc[i], SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
      perror("Server-setsockopt");
      exit(1);
    }
    // On initialise tout
    memset((char *)&sin,0, sizeof(sin));
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    int port = atoi(argv[i + 1]);
    sin.sin_port = htons(port);
    sin.sin_family = AF_INET;
    // Bind
    if (bind(sc[i],(struct sockaddr *)&sin,sizeof(sin)) < 0) {
      perror("bind");
      exit(1);
    } 
    // On fait client par client
    if(listen(sc[i], 1) == -1) {
      perror("listen");
      exit(1);
    }
    printf("Socket %d prête sur le port %d.\n", i, port);
  }
}

void write_file(char* addr) {
  // On écrit l'adresse dans le fichier
  printf("Ecriture de %s\n", addr);
  write(fd_file, addr, sizeof(addr) + 1);
  write(fd_file, "\n", sizeof("\n"));
}

void close_socket(int sig) {
  // On ferme proprement lors d'une erreur ou d'un SIGINT
  int i;
  printf("Fermeture des sockets et du fichier %s en cours.\n", FILENAME);
  for(i = 0 ; i < size ; i++) {
    shutdown(sc[i], 2);
    close(sc[i]);
  }
  close(fd_file);
  exit(0);
}