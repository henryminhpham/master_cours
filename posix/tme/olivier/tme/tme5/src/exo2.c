#include "exo2.h"
#define XOPEN_SOURCE 700
#define FORK 3

sem_t* sem1;
sem_t* sem2;
const char* name = "tmp_semaphore";
const char* name2 = "tmp_semaphore2";

int main(int argc, char** argv) {
  if(SEM_FAILED == (sem1 = sem_open(name, O_RDWR | O_CREAT, 0777, 0))){perror("Create sem1"); exit(1);}
  if(SEM_FAILED == (sem2 = sem_open(name2, O_RDWR | O_CREAT, 0777, 0))){perror("Create sem2"); exit(1);}
  
  int i;
  for(i = 0 ; i < FORK ; i++) {
    pid_t pid;
    if((pid = fork()) == -1) {perror("Fork"); exit(1);}
  
    if(pid == 0) {
      process(FORK);
      return 0;
    }
  }
  for(i = 0 ; i < FORK ; i++) {
    if(-1 == sem_wait(sem2)){perror("sem wait de sem2");}
  }
  for(i = 0 ; i < FORK ; i++) {
    if(-1 == sem_post(sem1)){perror("sem wait de sem1");}
  }
  for(i = 0 ; i < FORK ; i++) {
    wait(NULL);
  }	
  sem_close(sem1);
  sem_close(sem2);
  sem_unlink(name);
  sem_unlink(name2);
  return EXIT_SUCCESS;
}

void wait_barrier (int NB_PCS) {
  if(-1 == sem_post(sem2)){perror("sem post de sem2");}
  if(-1 == sem_wait(sem1)){perror("sem wait de sem1");};  
}

void process (int NB_PCS) {
    printf ("avant barrière\n");    
    wait_barrier (NB_PCS);
    printf ("après barrière\n");
    exit (0);
}
