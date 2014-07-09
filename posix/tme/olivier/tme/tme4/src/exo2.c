#include "exo2.h"
#define SVID_SOURCE 1
#define NB_FORK 3

int main(int argc, char** argv) {
  int shmid;
  int i;
  char* shared;
  shmid = shmget(IPC_PRIVATE, NB_FORK * sizeof(int), IPC_CREAT | 0666);
  if(-1 == shmid) {
    perror("Create error");
    return EXIT_FAILURE;
  }
  shared = shmat(shmid, (void*) 0, 0); 
  for(i = 0 ; i < NB_FORK ; i++) {
    pid_t pid = child(shared);
    if(pid == 0) {
      return EXIT_SUCCESS;
    }
    *shared++;
  }
  
  for(i = 0 ; i < NB_FORK ; i++) {
    wait(NULL);
  }
  *shared--;
  int final_random = 0;
  for(i = 0 ; i < NB_FORK ; i++) {
    final_random += (int) *shared--;
  }
  printf("Le random final est %d\n", final_random);
  shmdt(shared);
  shmctl(shmid, IPC_RMID, NULL);
  return EXIT_SUCCESS;
}

int get_random() {
  return (int) (10*(float)rand()/ RAND_MAX);
}

pid_t child(char* addr) {
  pid_t pid;
  if((pid = fork()) == -1) {
    perror("Error create");
    exit(EXIT_FAILURE);
  }
  if(pid == 0) {
    *addr = get_random();
    printf("Je suis %d et j'ai généré %d\n", getpid(), *addr);
  }
  return pid;
}