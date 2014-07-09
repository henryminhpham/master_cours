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


int main(int argc, char** argv){
  struct sockaddr_in sin, dest;
  int sock, sockenvoi;
  socklen_t fromlen;

  char msgrecu[TAILMSG];
  char msgenvoi[TAILMSG];
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_family=AF_INET;
  sin.sin_port=htons(9999);
  if ((sock=socket(AF_INET, SOCK_DGRAM, 0))==-1){
    perror("socket");
    exit(2);
  }
  if(bind(sock, (struct sockaddr *) &sin, sizeof(sin))==-1){
      perror("bind");
      exit(2);
  }
  if ((sockenvoi=socket(AF_INET, SOCK_DGRAM, 0))==-1){
    perror("socket");
    exit(2);
  }
  strcpy(msgenvoi, "PONG");
  while(1){
    if(recvfrom(sock, msgrecu,sizeof(msgrecu), 0,(struct sockaddr*) &dest, &fromlen)==-1){
      perror("recvfrom");
    } 
    sendto(sockenvoi, msgenvoi, strlen(msgenvoi), 0, (struct sockaddr*) &dest, sizeof(dest));
  }
  return 0;
}
