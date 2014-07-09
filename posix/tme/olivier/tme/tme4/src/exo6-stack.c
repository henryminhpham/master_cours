#include "exo6-stack.h"
#define SVID_SOURCE 1
#define STACK_SIZE 100

static void op(int val);

char* shared;
char* size;
int shmid, semid, shm_sizeid;
struct sembuf sem;

/**
 * Fonction d'initialisation.
 * On utilise 2 shm : 1 pour les données et 1 pour la taille (afin de savoir quand dépiler / empiler)
 * Et 1 sem pour locker
 */
void init() {
  key_t key;
  if((key = ftok("/tmp", 0)) == -1){perror("Key create");exit(EXIT_FAILURE);}
  shmid = shmget(key, STACK_SIZE * sizeof(int), IPC_CREAT | 0666);
  if(-1 == shmid) {
    perror("Create error");
    exit(EXIT_FAILURE);
  }
  shared = shmat(shmid, (void*) 0, 0); 

  shm_sizeid = shmget(key, sizeof(int), IPC_CREAT | 0666);
  if(-1 == shm_sizeid) {
    perror("Create error");
    exit(EXIT_FAILURE);
  }
  size = shmat(shm_sizeid, (void*) 0, 0); 
  *size = 0;
  semid = semget(key, 1, IPC_CREAT | 0666);
  if(semid == -1) {perror("Create sem");destroy();}
  
  // On met val pour les sémaphores
  if(-1 == semctl(semid,0, SETVAL, 1)) {perror("Init sem");destroy();}
  sem.sem_num = 0;
  sem.sem_flg = 0;
}

/**
 * Fonction pour libérer toutes les IPC. Cette fonction est appelée
 * par le SIGINT, afin d'éviter des leaks
 */
void destroy() {
  shmdt(shared);
  shmctl(shmid, IPC_RMID, NULL);
  shmdt(size);
  shmctl(shm_sizeid, IPC_RMID, NULL);
  semctl(semid, 0, IPC_RMID, 0);
  exit(EXIT_SUCCESS);
}

void P() {
  op(-1);
}

void V() {
  op(1);
}

void Z() {
  op(0);
}

void* Producteur(void* arg) { 
    int c; 
    while ((c = getchar()) != EOF) { 
        Push(c); 
    } 
    return NULL;
}

void* Consommateur(void* arg) { 
    for (;;) { 
        putchar(Pop());
        fflush(stdout);
    } 
    return NULL;
}

int Pop() {
  // Si on ne peut plus rien dépiler on attend
  if((*size) < 0) {
    Z();
  }  
  // On lock
  P();
  // on dépile
  int retour = *shared--;
  // on décrémente la taille
  *size = *size - 1;
  // on libère le verrou
  V();
  return retour;
}

void Push(int c) {
  // On évite un débordement de mémoire (si on écrit MAX_SIZE char d'un coup par exemple).
  if((*size) >= STACK_SIZE) {
    Z();
  }  
  // lock
  P();
  // On empile un caractère
  *shared = (int) c;
  *shared++;
  *size = *size + 1;
  // unlock
  V();
}

static void op(int val) {
  sem.sem_op = val;
  semop(semid, &sem, 1);
}