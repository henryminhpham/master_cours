#include "ponger.h"
#define XOPEN_SOURCE 700

char send_message[] = "PONG\0";
char recv_message[] = "PING\0";

int main(int argc, char** argv) {
  char message[4];
  while(1) {
    await_message(message);
  }	
}

void await_message(char* message) {
    // On prépare la socket d'écoute
    int sock;                                               
    struct sockaddr_in sin;                                              
    struct ip_mreq imr; /* Structure pour setsockopt */    
    if((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){  
      perror("socket");                              
      exit(1);                                         
    }                                              
    imr.imr_multiaddr.s_addr = INADDR_BROADCAST;
    imr.imr_interface.s_addr = INADDR_ANY;         
    // Broadcast
    if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&imr, sizeof(struct ip_mreq)) == -1){
      perror("setsockopt");
      exit(2);
    }
    // On initialise
    memset((char *)&sin,0, sizeof(sin));
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(8888); //TODO : CHANGER
    sin.sin_family = AF_INET;
    // Bind
    if (bind(sock,(struct sockaddr *)&sin,sizeof(sin)) < 0) {
      perror("bind");
      exit(3);
    }
    struct sockaddr_in exp;
    memset(&exp, 0, sizeof(exp));
    printf("En attente de ping...\n");
    // On attend de recevoir un broadcast
    socklen_t size = sizeof(exp);
    if (recvfrom(sock,message,sizeof(char) * 4 ,0, (struct sockaddr *) &exp, &size) == -1) {
      perror("recvfrom");
      exit(4);
    }
    printf("Réception de %s depuis l'adresse %s : %d.\n", message,inet_ntoa(exp.sin_addr), (exp.sin_port));
    send_pong(&exp);
    // On ferme la socket et on recommence
    close(sock);
    memset(message, 0, sizeof(message));
}

void send_pong(struct sockaddr_in* addr) {
    int sock;
     struct sockaddr_in sin;
     
    if ((sock = socket(PF_INET,SOCK_DGRAM, IPPROTO_UDP)) == -1) {
      perror("socket"); 
      exit(1);
    }
    memset((char *)&sin,0, sizeof(sin));
    memcpy(&sin, addr, sizeof(addr));
    sin.sin_addr.s_addr = addr->sin_addr.s_addr;
    sin.sin_port = htons(PORT); 
    sin.sin_family = AF_INET;
    printf("Envoi de %s à %s : %d.\n", send_message, inet_ntoa(sin.sin_addr), sin.sin_port);
    socklen_t size = sizeof(sin);
    if (sendto(sock,send_message,sizeof(send_message) ,0, (struct sockaddr*) &sin, size) == -1) {
      perror("sendto"); 
      exit(1);
    } 
   close(sock);
}
