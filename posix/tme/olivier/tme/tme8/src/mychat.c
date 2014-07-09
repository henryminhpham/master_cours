#include "mychat.h"
#define XOPEN_SOURCE 700

char* addr;
int port;
char* pseudo;
int sock;
 struct sockaddr_in broadcastAddr;
  
int main(int argc, char** argv) {
  if(argc != 4) {
    perror("Arguments - <addr> <port> <pseudo>");
    return EXIT_FAILURE;
  }
  
  addr = argv[1];
  port = atoi(argv[2]);
  pseudo = argv[3];
  if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0){  
      perror("socket");                              
      exit(1);                                         
   }     
   
    struct ip_mreq imr; /* Structure pour setsockopt */    
    imr.imr_multiaddr.s_addr = inet_addr(addr);
    imr.imr_interface.s_addr = INADDR_ANY;      
    if (setsockopt(sock,  IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &imr,  sizeof(imr)) < 0) {
      perror("setsocketopt"); 
      exit(1);
    }
    
    // Initialisation
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));
    broadcastAddr.sin_family = AF_INET;
    broadcastAddr.sin_addr.s_addr = inet_addr(addr);
    broadcastAddr.sin_port = htons(port);
  printf("Lancement de la thread de lecture...\n");
  pthread_t thread;
  if(-1 == pthread_create(&thread, 0, reader, 0)) {
    perror("Impossible de créer la thread de lecture");
    return EXIT_FAILURE;
  }
  printf("Connexion avec le pseudo %s à l'adresse %s:%d\n", pseudo, addr, port);
  char* message = malloc(sizeof(char) * 200);
  while(1) {
    gets(message);
    send_message(pseudo, message);
    memset(message, 0, sizeof(message));
  }
	return EXIT_SUCCESS;
}

void send_message(char* pseudo, char* message) {
    char* real_message = malloc(strlen(message) + strlen(pseudo) + 5);
    // On attend de recevoir le message
    strcat(real_message, "<");
    strcat(real_message, pseudo);
    strcat(real_message, "> : ");
    strcat(real_message, message);
    int size = strlen(real_message);
    // On envoie
    if (sendto(sock, real_message, size , 0, (struct sockaddr *)  &broadcastAddr, sizeof(broadcastAddr)) != size) {
      perror("Send");
      exit(1);
     }
     free(real_message);
    close(sock);
}


void* reader(void* args) {
   char message[256];
   // On prépare la socket d'écoute
   struct sockaddr_in sin;                                            
   if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0){  
    perror("socket");                              
    exit(1);                                         
  }                                              
  // On initialise
  memset((char *)&sin,0, sizeof(sin));
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_port = htons(port);
  sin.sin_family = AF_INET;
  // Bind
  if (bind(sock,(struct sockaddr *)&sin,sizeof(sin)) < 0) {
    perror("bind");
    exit(3);
  }
  printf("Thread de lecture prêt\n");
  while(1) {
    if (recvfrom(sock,message,sizeof(char) * 256 ,0,NULL,NULL) == -1) {
      perror("recvfrom");
      exit(4);
    }
    printf("%s\n", message);
    memset(message, 0, sizeof(message));
  }
  close(sock);
}
