#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct message {
  long type;
  int random;
}message;

int get_random();

pid_t child(int file);