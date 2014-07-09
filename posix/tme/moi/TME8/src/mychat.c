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

#define TAILMSG 100


struct ip_mreq{
  struct in_addr imr_multiaddr;
  struct in_addr imr_interface;
};

int main (int argc, char **argv){
  pid_t pid;
  char chat_text[TAILMSG*2];
  char message[TAILMSG];
  char msgrecu[TAILMSG]; 
  struct sockaddr_in dest, sin;
  int sock_cli, sock_serv;
  struct ip_mreq imr;
  int optval=1;

  pid = fork();
  if(pid){
    if ((sock_cli = socket(AF_INET,SOCK_DGRAM,0)) == -1) {
      perror("socket"); exit(1);
    }
    memset((char*)&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr=inet_addr(argv[1]);
    dest.sin_family=AF_INET;
    dest.sin_port=htons(atoi(argv[2]));
    while(1){
      printf("Veuillez entrer un message...\n");
      memset((char*)message, 0, TAILMSG);
      memset((char*)chat_text, 0, TAILMSG*2);
      fgets(message, TAILMSG, stdin);
      strcpy(chat_text, argv[3]);
      strcat(chat_text, " > ");
      strcat(chat_text, message);
      sendto(sock_cli, chat_text, strlen(chat_text)+1, 0, (struct sockaddr*) &dest, sizeof(dest));
    }
  }
  else {
    if ((sock_serv = socket(AF_INET,SOCK_DGRAM,0)) == -1) {
      perror("socket"); exit(1);
    }
    imr.imr_multiaddr.s_addr=inet_addr(argv[1]);
    imr.imr_interface.s_addr=INADDR_ANY;
    if(setsockopt(sock_serv, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*) &imr, sizeof(struct ip_mreq)) == -1){
      perror("setsockopt");
      exit(1);
    }
    memset((char*)&sin, 0, sizeof(sin));
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_family=AF_INET;
    sin.sin_port=htons(atoi(argv[2]));
    setsockopt(sock_serv, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
    if(bind(sock_serv, (struct sockaddr *) &sin, sizeof(sin))==-1){
      perror("bind");
      exit(2);
    }
    while(1){
      if(recvfrom(sock_serv, msgrecu,sizeof(msgrecu), 0,NULL, NULL)==-1){
	perror("recvfrom");
      }
      printf("%s", msgrecu);
    }
  }
  return 0;
}
