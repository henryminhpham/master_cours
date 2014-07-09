#include <stdio.h>
#include <stdlib.h>
#include <aio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <string.h>
#include <fcntl.h>

void cp(int to, char* read, int offset);
