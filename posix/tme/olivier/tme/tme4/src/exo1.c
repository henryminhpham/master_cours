#include "exo1.h"
#define SVID_SOURCE 1
#define NB_FORK 3

const int MAX_SIZE = sizeof(int);


int main(int argc, char** argv) {
  key_t key;
  int file, i;
  key = ftok("/tmp", 0);
  file = msgget(key, 0777 | IPC_CREAT);
  if(file == -1) {
    perror("Create File : ");
    exit(EXIT_FAILURE);
  }
  for(i = 0 ; i < NB_FORK ; i++) {
    pid_t pid = child(file);
    if(0 >= pid) {
      return EXIT_SUCCESS;
    }
  }
  for(i = 0 ; i < NB_FORK ; i++) {
    wait(NULL);
  }
  message msg;
  int final_random = 0;
  for(i = 0 ; i < NB_FORK ; i++) {
    if(-1 == msgrcv(file, &msg, MAX_SIZE, 0L, 0)) {
      perror("erreur receive");
    }
    final_random += msg.random;
  }
  printf("Random final %d\n", final_random);
  msgctl(file, IPC_RMID, NULL);
  return EXIT_SUCCESS;
}

int get_random() {
  return (int) (10*(float)rand()/ RAND_MAX);
}

pid_t child(int file) {
  pid_t pid;
  if((pid = fork()) == -1) {
    perror("Create fork");
    exit(EXIT_FAILURE);
  } else if(pid == 0) {
     message msg;
     msg.type = get_random();
     msg.random = msg.type; 
     printf("Je suis %d et mon random est %d\n", getpid(), msg.random);
     if(-1 == msgsnd(file, &msg, MAX_SIZE, 0)) {
       perror("Send !!!");
    }
  }
  return pid;
}
