#include "exo1.h"

int main(int argc, char** argv) {
  // Il faut au moins 1 nom de fichier
  if(argc == 1) {
    perror("Il faut spécifier au moins un fichier.");
    return EXIT_FAILURE;
  }
  pthread_t threads[argc - 1];
  int i,j;
  // On lance lest argc - 1 threads
  for(i = 1 ; i < argc ; i++) {
    if(pthread_create(&threads[i - 1], NULL, thread_action, argv[i]) != 0) {
      perror("Erreur durant la création d'une thread");
      return EXIT_FAILURE;
    }
  }
  // On attend la fin de ceux-ci. On s'assure que la tâche est finie.
  for(j = 0 ; j < argc ; j++) {
    pthread_join(threads[j], NULL);
  }
  return EXIT_SUCCESS;
}
void* thread_action(void* args) {
    FILE* fp1, *fp2; 
    int c = 1;
    // On récupère le nom du fichierprintf("%s\n", argv[i]);
    char* name = (char*) args;
    fp1= fopen (name, "r"); 
    fp2= fopen (name, "r+");
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
    return NULL;
}