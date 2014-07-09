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


#define TAILMSG 100

int sock_diff;


void* thread_envoi( void* args ){
  struct sockaddr_in dest;
  int on=1;
  char message[TAILMSG];

  memset((char*)&dest, 0, sizeof(dest));

  dest.sin_addr.s_addr=htonl(INADDR_BROADCAST);
  dest.sin_port=htons(9999);
  dest.sin_family=AF_INET;
  strcpy(message, "PING");
  while(1){
    printf("PING\n");
    sendto(sock_diff, message, strlen(message), 0, (struct sockaddr*) &dest, sizeof(dest));
    sleep(3);
  }
  return NULL;
}

void* thread_reception ( void* args ){
  struct sockaddr_in  cli_addr;
  char msgrecu[TAILMSG];
  socklen_t fromlen = sizeof(cli_addr);
  while(1){
    if(recvfrom(sock_diff, msgrecu, TAILMSG, 0, (struct sockaddr*) &cli_addr, &fromlen)==-1){
      perror("recvfrom");
    }
    if(msgrecu[1]=='O')
      printf("%s reçu par : %s\n", msgrecu, inet_ntoa(cli_addr.sin_addr));
  }
  return NULL;
}


int main (int argc, char** argv){
  pthread_t tid[2];
  int on=1;

  struct sockaddr_in  sin;

  if ((sock_diff=socket(AF_INET, SOCK_DGRAM, 0))==-1){
    perror("socket");
    exit(2);
  }

  sin.sin_addr.s_addr=htonl(INADDR_ANY);
  sin.sin_family=AF_INET;
  sin.sin_port=htons(9999);
  setsockopt(sock_diff, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  if(setsockopt(sock_diff, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on))==-1){
    perror("setsockopt");
    exit(2);
  }
  if(bind(sock_diff, (struct sockaddr *) &sin, sizeof(sin))==-1){
      perror("bind");
      exit(2);
  }

  pthread_create(&tid[0], NULL, thread_envoi, NULL);
  pthread_create(&tid[1], NULL, thread_reception, NULL);
  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);
  return 0; 
}
