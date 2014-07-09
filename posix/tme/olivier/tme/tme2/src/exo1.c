#include "exo1.h"
#define XOPEN_SOURCE 700
#define NB_THREAD 3

static int process_args(int argc, char* argv[]);

int main(int argc, char* argv[]) {
  // On vérifie que les arguments sont valides
  int N = process_args(argc, argv);
  int i;
  pthread_t threads[N];
  // On crée N threads
  for(i = 0 ; i < N ; i++) {
    if(pthread_create(&threads[i], NULL, thread_rand, (void*)i) != 0) {
      perror("Une erreur est survenue durant la création d'une thread.\n");
      return EXIT_FAILURE;
    }
  }
  void* ret;
  int real_ret;
  // On boucle ici pour être sur que tous les threads sont lancés avant le join, sinon aucun
  // intérêt d'utiliser les threads.
  for(i = 0 ; i < N ; i++) {
    // On attend le thread n° i et on récupère sa valeur de retour
    pthread_join(threads[i], &ret);
    real_ret = (int) ret;
    // On affiche la valeur de retour
    printf("La valeur de retour de %ld est %d.\n", threads[i], real_ret);
  }
  return EXIT_SUCCESS;
}

void* thread_rand(void* info) {
  int real_info;
  // On sait que la méthode envoie un int
  real_info  = (int) info;
  // On affiche 
  printf("Je suis %ld et mon ordre est %d.\n", pthread_self(), real_info);
  // On retourne le produit par 2 de ce qui est passé en argument
  pthread_exit((void*) (2 * real_info));
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
