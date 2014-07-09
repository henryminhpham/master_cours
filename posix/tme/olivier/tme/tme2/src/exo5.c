#include "exo5.h"
#define XOPEN_SOURCE 700
#define NB_THREADS 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int global = 0;

int main(int argc, char* argv[]) {
  int i;
  pthread_t threads[NB_THREADS];
  // On crée NB_THREADS threads
  for(i = 0 ; i < NB_THREADS ; i++) {
    if(pthread_create(&threads[i], NULL, thread_rand, NULL) != 0) {
      perror("Une erreur est survenue durant la création d'une thread.\n");
      return EXIT_FAILURE;
    }
  }
  // On attend que toutes les threads soient bloquées
  while(global < NB_THREADS);
  
  // Une fois que toutes les threads sont bloquées, on les réveille
  pthread_cond_broadcast(&cond);
  for(i = 0 ; i < NB_THREADS ; i++) {
    // Bien que l'on fasse un pthread_exit, on s'assure que chaque thread finisse sa tâche
    // (le print de "après barrière"). Il pourra alors se tuer lui-même
    pthread_join(threads[i], NULL);
  }
  return EXIT_SUCCESS;
}

void* thread_rand(void* info) {
  printf ("avant barrière\n");
  wait_barrier (NB_THREADS);
  printf ("après barrière\n");
  pthread_exit ( (void*)0);
}

void wait_barrier(int N) {
  pthread_mutex_lock(&mutex);
  global++;
  pthread_cond_wait(&cond, &mutex);
  pthread_mutex_unlock(&mutex);
}
