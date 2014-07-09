#include "exo2.h"
#define XOPEN_SOURCE 700
#define NB_THREAD 3

static int process_args(int argc, char* argv[]);

int GLOBAL_RAND;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char* argv[]) {
  // On vérifie les arguments
  int N = process_args(argc, argv);
  // On initialise à 0
  GLOBAL_RAND = 0;
  int i, j;
  // On crée N thread qu'on lance'
  pthread_t threads[N];
  for(i = 0 ; i < N ; i++) {
    if(pthread_create(&threads[i], NULL, thread_rand, NULL) != 0) {
      perror("Une erreur est survenue durant la création d'une thread.\n");
      return EXIT_FAILURE;
    }
  }
  // On attend tous les threads
  for(j = 0 ; j < N ; j++) {
    pthread_join(threads[j], NULL);
  }
  // On affiche la somme totale
  printf("La valeur finale est %d.\n", GLOBAL_RAND);
  return EXIT_SUCCESS;
}

void* thread_rand(void* info) {
  // On lock, une seule thread à un instant T peut modifier la variable globale.
  // Le mutex est global donc tous les threads le partage
  pthread_mutex_lock(&mutex);
  int random_val;
  // On calcule un random
  random_val = (int) (10*((double)rand())/ RAND_MAX);
  GLOBAL_RAND += random_val;
  printf("Je suis %ld et j'ai généré %d.\n", pthread_self(), random_val);
  // On déverrouille le lock
  pthread_mutex_unlock(&mutex);
  pthread_exit((void*) 0);
  return NULL;
}

static int process_args(int argc, char* argv[]) {
  if(argc == 1) {
    return NB_THREAD;
  }
  int N = atoi(argv[1]);
  if(N <= 0) {
    perror("Ce programme nécessite que l'argument spécifié soit un entier strictement supérieur à 0.");
    exit(EXIT_FAILURE);
  }
  return N;
}
