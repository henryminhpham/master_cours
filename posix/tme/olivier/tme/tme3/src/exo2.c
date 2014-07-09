#include "exo2.h"

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static int current_file = 0;
static char** data;
static int maximum;

static int get_nb_threads(int argc) {
  int result = (argc / 2);
  return (result <= 0) ? 1 : result;
}

int main(int argc, char** argv) {
  // Il faut au moins 1 nom de fichier
  if(argc == 1) {
    perror("Il faut spécifier au moins un fichier.");
    return EXIT_FAILURE;
  }
  data = argv;
  maximum = argc - 1;
  int nb_threads = get_nb_threads(argc - 1);
  printf("On crée %d threads !\n", nb_threads);
  pthread_t threads[nb_threads];
  int i,j;
  // On lance lest argc - 1 threads
  for(i = 0 ; i < nb_threads ; i++) {
    if(pthread_create(&threads[i], NULL, thread_action, NULL) != 0) {
      perror("Erreur durant la création d'une thread");
      return EXIT_FAILURE;
    }
  }
  // On attend la fin de ceux-ci. On s'assure que la tâche est finie.
  for(j = 0 ; j < nb_threads ; j++) {
    pthread_join(threads[j], NULL);
  }
  return EXIT_SUCCESS;
}

void* thread_action(void* args) {
    int file;
    if((file = has_file()) != -1) {
      printf("Je suis %ld et je convertis %s.\n", pthread_self(), data[file]);
      convert_file(data[file]);
      thread_action(args);
    } 
    return NULL;
}

int has_file() {
  pthread_mutex_lock(&mutex);
  current_file++;
  int result = (current_file <= maximum) ? current_file : -1;
  pthread_mutex_unlock(&mutex);
  return result;
}

void convert_file(char* file) {
    FILE* fp1, *fp2; 
    int c = 1;
    fp1= fopen (file, "r"); 
    fp2= fopen (file, "r+");
    if ((fp1== NULL) || (fp2== NULL)) {
        perror ("fopen");
        exit (1);
    }
  
    while (c !=EOF) {
        c=fgetc(fp1);
        if (c!=EOF)
        fputc(toupper(c),fp2);
    }
    fclose (fp1);
    fclose (fp2);
}
