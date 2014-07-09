#include "sonar.h"
#define XOPEN_SOURCE 700

char send_message[] = "PING\0";
char recv_message[] = "PONG\0";

int main(int argc, char** argv) {
	pthread_t thread;
	if(pthread_create(&thread, NULL, recept_message, NULL) == -1) {
	  perror("Impossible de créer la thread"); 
	  return EXIT_FAILURE;
	}
	while(1) {
	  printf("Envoi d'un broadcast\n");
	  broadcast_message();
	  sleep(3);
	}
	return EXIT_SUCCESS;
}


void broadcast_message() {
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
    sin.sin_port = htons(8888); //TODO CHANGER LE PORT
    sin.sin_family = AF_INET;
    // On se connecte
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) == -1) {
      perror("connect"); 
      exit(1);
    }
    if (send(sock,send_message,sizeof(send_message) ,0) == -1) {
      perror("sendto"); 
      exit(1);
    } 
    close(sock);
}

void *recept_message(void* args) {
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
    sin.sin_port = htons(PORT);
    sin.sin_family = AF_INET;
    // Bind
    if (bind(sock,(struct sockaddr *)&sin,sizeof(sin)) < 0) {
      perror("bind");
      exit(3);
    }
  char message[4];
  while(1) {
    struct sockaddr_in exp;
    memset(&exp, 0, sizeof(exp));
    // On attend de recevoir un broadcast
    socklen_t size = sizeof(exp);
    if (recvfrom(sock,message,sizeof(char) * 4 ,0, (struct sockaddr *)  &exp, &size) == -1) {
      perror("recvfrom");
      exit(4);
    }
    printf("Réception de %s de la machine %s : %d.\n", message, inet_ntoa(exp.sin_addr), exp.sin_port);
  }
  pthread_exit((void*) 0);
  return 0;
}
