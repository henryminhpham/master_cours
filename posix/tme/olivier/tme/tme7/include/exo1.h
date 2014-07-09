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
#define PROC 5

pid_t child();
