#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#define PROC 3

int read_file(int fd);

int fread_file(FILE* fd);
