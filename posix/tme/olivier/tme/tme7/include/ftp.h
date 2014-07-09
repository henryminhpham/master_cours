#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <sys/stat.h>

#define BUFF 4096L
#define FILE_SIZE 4096L
#define UPLOAD "UPLOAD"
#define DOWNLOAD "DOWNLOAD"
#define LIST "LIST"

int list(int client);

int upload(int client, char* name);

int download(int client);

int execute_operation(char* operation, int client);

void close_program(int sig);
