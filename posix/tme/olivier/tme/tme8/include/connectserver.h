#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <fcntl.h>

#define FILENAME "cxlog"

void init_socket(int* array, int size, char** argv);

void close_socket(int sig);

void write_file(char* addr);

