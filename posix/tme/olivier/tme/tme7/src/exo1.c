#include "exo1.h"
#define XOPEN_SOURCE 700

int main(int argc, char** argv) {
  struct sockaddr_in sin;
  struct sockaddr_in exp;
  int fromlen = sizeof(exp);
  int sc;
  int message;
  
  if((sc = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("Erreur de création de la socket");
    exit(1);
  }
  memset((void*) &sin, 0, sizeof(sin));
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_port = htons(PORT);
  sin.sin_family = AF_INET;
  if (bind(sc,(struct sockaddr *)&sin,sizeof(sin)) < 0) {
    perror("bind"); 
    exit(2);
  }
  printf("Serveur lancé sur le port %d.\n", PORT);
  int i;
  for(i = 0 ; i < PROC ; i++) {
    if(child() <= 0) {
      return EXIT_SUCCESS;
    }
  }
  int random_final = 0;
  for(i = 0 ; i < PROC ; i++) {
    if (recvfrom(sc,&message,sizeof(message),0, (struct sockaddr *)&exp, (socklen_t *)&fromlen) == -1) {
      perror("recvfrom"); 
      exit(2);
    }
    printf("Réception de %d.\n", message);
    random_final += message;
  }
  printf("Le random final est %d.\n", random_final);
  for(i = 0 ; i < PROC ; i++) {
   wait(NULL);
  }
  return EXIT_SUCCESS;
}

pid_t child() {
  pid_t pid;
  if((pid = fork()) == -1) {
    perror("Create child");
    exit(1);
  }
  if(pid > 0) {
    return pid;
  }
  struct sockaddr_in dest;
  int sock;
  int random = (int) (10*(float)rand()/ RAND_MAX);
  struct addrinfo *result;
  
  if ((sock = socket(AF_INET,SOCK_DGRAM,0)) == -1) {
    perror("socket"); 
    exit(1);
  } 
  
  if (getaddrinfo("127.0.0.1", 0, 0, &result) != 0) { 
    perror("getaddrinfo"); 
    exit(EXIT_FAILURE);
  }
  memset((char *)&dest,0, sizeof(dest));
  memcpy((void*)&((struct sockaddr_in*)result->ai_addr)->sin_addr, (void*)&dest.sin_addr, sizeof(dest));
  
  dest.sin_family = AF_INET;
  dest.sin_port = htons(PORT);
  printf("Je suis %d et j'envoie %d\n", getpid(), random);
  if (sendto(sock,&random,sizeof(int) ,0, (struct sockaddr *)&dest, sizeof(dest)) == -1) {
    perror("sendto"); 
    exit(1);
  } 
  close(sock);
  return pid;
}