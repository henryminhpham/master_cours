#include "ftp.h"
#define XOPEN_SOURCE 700

int sock;
char *host= "127.0.0.1";
int port = 2012;
char *name;

int main(int argc, char** argv) {  
  if(argc < 2 || argc > 3) {
    perror("Invalid arguments");
    exit(EXIT_FAILURE);
  }
  if(argc == 2) {
    port = atoi(argv[1]);
  } else {
    host = argv[1];
    port = atoi(argv[2]);
  }

  
  sigset_t sig;
  struct sigaction action;
  // On ferme proprement le client lors d'un SIGINT
  sigemptyset(&sig);
  action.sa_handler = close_program;
  action.sa_mask = sig;
  action.sa_flags = 0;
  sigaction(SIGINT, &action, NULL);
  
  struct sockaddr_in dest;
  struct addrinfo* result;
  // On crée la socket
  if ((sock = socket(AF_INET,SOCK_STREAM,0)) == -1) {
    perror("socket");
    exit(1);
  } 
  
  // On initialise tout + on récupère l'adresse
  if (getaddrinfo(host, 0, 0, &result) != 0) {perror("getaddrinfo"); exit(EXIT_FAILURE);}
  memset((char *)&dest,0, sizeof(dest));
  memcpy((void*)&((struct sockaddr_in*)result->ai_addr)->sin_addr, (void*)&dest.sin_addr, sizeof(dest));
  dest.sin_family = AF_INET;
  dest.sin_port = htons(port);
  
  // On se connecte au serveur
  printf("Connexion au serveur %s sur le port %d\n", host, port);
  if (connect(sock, (struct sockaddr *) &dest, sizeof(dest)) == -1){
    perror("connect"); exit(1);
  } 
  char* request = malloc(50);
  while(1) {
    puts("Ecrivez votre requête : ");
    gets(request);
    execute_operation(request, sock);
  }
  printf("Fermeture du client\n");
  shutdown(sock, 2);
  close(sock);
  return 0;
}

int list(int server) {
  write(server, LIST, sizeof(LIST));
  char* request = malloc(BUFF);
    
  int result = -1;
  printf("\n------------------------------------------------\n");
  if((result = read(server, request, BUFF)) > 0) {
    printf("%s", request);
  }
  printf("------------------------------------------------\n");
  if(result <= 0) {
    // Le serveur est down, on ferme le client
    printf("Le serveur %s:%d n'est plus accessible, l'application est en cours de fermeture\n", host, port);
    close_program(SIGINT);
  }
  free(request);
  return 0;
}

int upload(int server, char* name) {
  // On ouvre le fichier
  int fd;
  if((fd = open(name, O_RDONLY, 0666)) == -1) {
    perror("Le fichier n'existe pas");
    return -1;
  }
  if(write(server, UPLOAD, sizeof(UPLOAD)) == -1) {
    return -1;
  }
  // On envoie le nom du fichier
  printf("Envoi du nom de fichier \"%s\".\n", name);
  if (write(sock,name, sizeof(name)) == -1) {
    return -1;
  } 
  // On lit toutes les lignes et pour chaque ligne lue, on l'envoie
  char *buffer = malloc(FILE_SIZE);
  printf("Début de l'envoi du fichier...\n");
  if(read(fd, buffer, FILE_SIZE) != -1) {
    printf("%s\n", buffer);
    write(sock, buffer, FILE_SIZE);
  }
  // On ferme tout
  printf("Fin de l'envoi du fichier\n");
  close(fd);
  return 0;
}

int download(int server) {
  write(server, DOWNLOAD, sizeof(DOWNLOAD));
  return 0;
}

int execute_operation(char* operation, int server) {
  if(0 == strncmp(UPLOAD, operation, 6)) {
    // On récupère le nom du fichier à uploader
    if((name = strtok (operation," ")) == NULL) {
      return -1;
    }
    if((name = strtok (NULL," ")) == NULL) {
      return -1;
    }  
    return upload(server, name);
  } else if(0 == strcmp(LIST, operation)) {
    return list(server);
  } else if(0 == strncmp(DOWNLOAD, operation, 8)) {
    return download(server);
  } else {
    printf("La requête doit être \"UPLOAD\", \"LIST\", \"DOWNLOAD\"\n");
    return -1;
  }
}

void close_program(int sig) {
  if(sock > -1) {
    shutdown(sock, 2);
    close(sock);
  }
  exit(0);
}