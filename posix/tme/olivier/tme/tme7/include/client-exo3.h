#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 4568
#define PORT_CLIENT 4567

char* create_request(char* request, char* key, char* value); 

int bind_response(struct sockaddr_in sin);
