#include "client-exo3.h"
#define XOPEN_SOURCE 700
#define BUFF 4096

int bind_response(struct sockaddr_in sin) {
  int sc;
  if((sc = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
      perror("Erreur de création de la socket");
      exit(1);
   }    
   
   memset((void*) &sin, 0, sizeof(sin));
   sin.sin_addr.s_addr = htonl(INADDR_ANY);
   sin.sin_port = htons(PORT_CLIENT);
   sin.sin_family = AF_INET;
   if (bind(sc,(struct sockaddr *)&sin,sizeof(sin)) < 0) {
      perror("bind"); 
      exit(2);
   }
   return sc;
}

int main(int argc, char** argv) {
  struct sockaddr_in dest;
  struct sockaddr_in sin;
  struct sockaddr_in exp;
  
  int fromlen = sizeof(sin);
  struct addrinfo *result;
  int sc;
  int sock;
  printf("Le serveur répond aux requêtes de la manière suivante :\n  - GET : La valeur ou -1 si pas trouvé.\n  - SET : 0 si la modification a eu lieue, -1 sinon.\n\n");
  
  if (getaddrinfo("127.0.0.1", 0, 0, &result) != 0) { 
    perror("getaddrinfo"); 
    exit(EXIT_FAILURE);
  }
  while(1) {
    
    puts("Ecrivez votre requête : ");
    char buffer[BUFF];
    gets(buffer);
    
    
    sc = bind_response(sin);
    if ((sock = socket(AF_INET,SOCK_DGRAM,0)) == -1) {
      perror("socket"); 
      exit(1);
    } 
  
    memset((char *)&dest,0, sizeof(dest));
    memcpy((void*)&((struct sockaddr_in*)result->ai_addr)->sin_addr, (void*)&dest.sin_addr, sizeof(dest));
  
    dest.sin_family = AF_INET;
    dest.sin_port = htons(PORT);
    printf("\nEnvoi de la requête \"%s\".\n", buffer);
    if (sendto(sock, buffer,sizeof(buffer) ,0, (struct sockaddr *)&dest, sizeof(dest)) == -1) {
      perror("sendto"); 
      exit(1);
    } 
    char message[BUFF];
    if (recvfrom(sc,&message,sizeof(message),0, (struct sockaddr *)&exp, (socklen_t *)&fromlen) == -1) {
      perror("recvfrom"); 
      exit(2);
    } 
    printf("Le serveur a renvoyé la réponse : \"%s\"\n", message);
    close(sock);
    close(sc);
    memset((char *)&exp,0, sizeof(exp));
  }
}

char* create_request(char* request, char* key, char* value) {
  if(strlen(request) > 1) {
    printf("La requête doit être S ou G.\n");  
    return NULL;
  }
  
  int isSet = (request[0] == 'S');
  
  if(isSet || request[0] == 'G')  {
    char* req = malloc(sizeof(key) + 1);
    strcat(req, request);
    strcat(req, " ");
    strcat(req, key);
    if(isSet) {
      strcat(req, " ");
      strcat(req, value);
    }
    return req;
  }
  printf("La requête doit être S ou G.\n");  
  return NULL;
}