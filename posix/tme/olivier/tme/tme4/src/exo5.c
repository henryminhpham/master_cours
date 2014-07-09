#include "exo5.h"
#define SVID_SOURCE 1
#define NB_FORK 4

int semid;
struct sembuf sem[2];

int main(int argc, char** argv) {
  key_t key = ftok("/tmp", 0);
  // On initialise 
  semid = semget(key, 1, IPC_CREAT | 0666);
  if(semid == -1) {perror("Create sem");exit(EXIT_FAILURE);}
  
  // On met val pour les sémaphores
  if(-1 == semctl(semid,0, SETVAL, NB_FORK)) {
    semctl(semid, 0, IPC_RMID, 0);
    perror("Init sem");
    exit(EXIT_FAILURE);    
  }
  // Sem 0 sert à bloquer tous les fils, c'est la barrière. Le parent la débloque
  // Sem 1 sert à bloquer le parent. Le dernier fils va ainsi débloquer le père, se bloquer et le père 
  // le débloquera plus tard
  // On place tous les flags + num
  sem[0].sem_num = 0;
  sem[1].sem_num = 0;
  sem[0].sem_flg = 0;
  sem[1].sem_flg = 0;
  
  sem[0].sem_op = 0;
  int i;
  for(i = 0 ; i < NB_FORK ; i++) {
    if(fork() == 0) {
      // On bloque tous les fils
      process(NB_FORK);
    }
  }
  // Le père se bloque en attendant que ses fils le débloquent.
  sem[1].sem_op = 0;
  semop(semid, &sem[1], 1);
  
  // Le père incrémente le compteur de N processus pour les débloquer
  sem[0].sem_op = NB_FORK;
  semop(semid, &sem[0], 1);
  // On clear les informations relatives à la mort des fils
  for(i = 0 ; i < NB_FORK ; i++) {
    wait(NULL);
  }
  // On détruit le sémaphore
  semctl(semid, 0, IPC_RMID, 0);
  return EXIT_SUCCESS;
}


void process(int NB_PCS) {
   printf ("avant barrière\n");
   wait_barrier (NB_PCS);
   printf ("après barrière\n");
   exit (0);
}

void wait_barrier(int NB_PCS) {
  // Le fils décrémente. Arrivé au dernier fils, on aura débloqué de NB_FORK et le père
  // reprendra son exécution
  sem[1].sem_op = -1;
  semop(semid, &sem[1], 1);
  // On se bloque en attendant que le père débloque
  semop(semid, &sem[0], 1);
}