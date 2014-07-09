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

char* get_value(char* value);

int set_value(char* key, char* value);

char* execute_request(char* request);

void send_to(char* message, struct sockaddr_in exp);
