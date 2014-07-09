#include "exo4-2.h"
#define XOPEN_SOURCE 700
#define NB_THREAD 3

static int process_args(int argc, char* argv[]);

int GLOBAL_RAND;
int current_thread_done;
int N;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t global_mutex;

int main(int argc, char* argv[]) {
  N = process_args(argc, argv);
  GLOBAL_RAND = 0;
  current_thread_done = 0;  
  int i;
  pthread_t threads[N];
  pthread_t print;
  pthread_attr_t attrib;
  pthread_attr_init(&attrib);
  pthread_attr_setdetachstate(&attrib, PTHREAD_CREATE_JOINABLE);
  pthread_mutex_init(&global_mutex, NULL);
  // On crée la thread print_thread qui se met en attente
  if(pthread_create(&print, NULL, print_thread, NULL) != 0) {
      perror("Une erreur est survenue durant la création de la thread print_thread.\n");
      return EXIT_FAILURE;
  }
  // On crée les N threads
  for(i = 0 ; i < N ; i++) {
    if(pthread_create(&threads[i], &attrib, thread_rand, NULL) != 0) {
      perror("Une erreur est survenue durant la création d'une thread.\n");
      return EXIT_FAILURE;
    }
  }
  pthread_attr_destroy(&attrib);
  // On attend la thread print_thread
  pthread_join(print, NULL);
  return EXIT_SUCCESS;
}

void* thread_rand(void* info) {
  // On lock
  pthread_mutex_lock(&mutex);
  int random_val;
  // On calcule le random
  random_val = (int) (10*((double)rand())/ RAND_MAX);
  GLOBAL_RAND += random_val;
  printf("Je suis %ld et j'ai généré %d.\n", pthread_self(), random_val);
  // On considère qu'une thread a fini son boulot. Si c'est la dernière elle notifie
  // print_thread pour qu'elle puisse print la valeur finale
  pthread_mutex_lock(&global_mutex);
  current_thread_done++;
  if(N == current_thread_done) {
	// On réveille thread print_thread
    pthread_cond_signal(&cond);
  }
  // On unlock
  pthread_mutex_unlock(&global_mutex);
  pthread_mutex_unlock(&mutex);
  pthread_exit((void*) 0);
  return NULL;
}

void* print_thread(void* info) {
  pthread_mutex_lock(&global_mutex);
  // On attend que la dernière thread réveille print_thread.
  if(N != current_thread_done) {
        pthread_cond_wait(&cond, &global_mutex);
  }
  // Affichage
  printf("La valeur finale est %d.\n", GLOBAL_RAND);
  pthread_mutex_unlock(&global_mutex);
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
