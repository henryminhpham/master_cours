#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message {
  long type;
  int random;
}message;

int get_random(int max);

pid_t child(int number, int file);

int create_file(int number);
