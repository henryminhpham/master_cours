#include "server-exo3.h"
#define XOPEN_SOURCE 700
#define BUFF 4096

char* ERROR = "-1";

int main(int argc, char** argv) {
  struct sockaddr_in sin;
  struct sockaddr_in exp;
  int fromlen = sizeof(exp);
  int sc;
  char message[BUFF];
  
  while(1) {
    if((sc = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
      perror("Erreur de création de la socket");
      exit(1);
    }
    memset((void*) &sin, 0, sizeof(sin));
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(PORT);
    sin.sin_family = AF_INET;
    printf("En attente d'une connexion sur le port %d.\n", PORT);
    if (bind(sc,(struct sockaddr *)&sin,sizeof(sin)) < 0) {
      perror("bind"); 
      exit(2);
    }
    if (recvfrom(sc,&message,sizeof(message),0, (struct sockaddr *)&exp,(socklen_t *)&fromlen) == -1) {
      perror("recvfrom"); 
      exit(2);
    } 
    printf("Réception de la requête \"%s\".\n", message);
    char* result = execute_request(message);
    send_to(result, exp);
    close(sc);
  }
}

char* execute_request(char* message) {
    char request = message[0];
    if(request == 'S') {
      char * pch;
      char* key;
      char* value;
      if((pch = strtok (message," ")) == NULL) {
        return ERROR;
      }
      if((pch = strtok (NULL," ")) == NULL) {
        return ERROR;
      }
      key = pch;
      if((pch = strtok (NULL," ")) == NULL) {
        return ERROR;
      }
      value = pch;
      int tmp_result = set_value(key, value);
      char* result = malloc(sizeof(char));
      sprintf(result, "%d", tmp_result);
      return result;
    } else if(request == 'G') {
      char * pch;
      if((pch = strtok (message," ")) == NULL) {
        return ERROR;
      }
      if((pch = strtok (NULL," ")) == NULL) {
        return ERROR;
      }
      return get_value(pch);
    } 
    return ERROR;
}

void send_to(char* message, struct sockaddr_in exp) {
  struct sockaddr_in dest = exp;
  int sock;
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
  dest.sin_port = htons(PORT_CLIENT);
  printf("Envoi de la réponse \"%s\"\n", message);
  if (sendto(sock, message,sizeof(message) ,0, (struct sockaddr *)&dest, sizeof(dest)) == -1) {
    perror("sendto"); 
    exit(1);
  } 
  close(sock);
}

char* get_value(char* value) {
  char* result = getenv(value);
  if(result != NULL) {
    return result;
  }
  return ERROR;
}

int set_value(char* key, char* value) {
  return setenv(key, value, 1);
}

