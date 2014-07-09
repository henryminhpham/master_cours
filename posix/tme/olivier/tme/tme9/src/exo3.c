#include "exo3.h"
#define XOPEN_SOURCE 700

int size;
int fd;
char* filename;

int main(int argc, char** argv) {
  if(argc != 3) {
    perror("Vous devez spécifier un nom de fichier et un contenu");
    return EXIT_FAILURE;
  }  
  // On crée le fichier et on le vide s'il existe
  filename = argv[1];
  fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
  if(fd == -1) {
    perror("Impossible d'ouvrir le fichier");
    return EXIT_FAILURE;
  }
  
  // On prépare l'entrée sortie
  struct aiocb a;
  a.aio_fildes = fd;
  a.aio_buf = argv[2];
  size = strlen(argv[2]) + 1;
  a.aio_nbytes = size;
  a.aio_offset = 0;
  a.aio_reqprio = 0;
  
  const struct aiocb  *cb[] = {&a};
  struct timespec spec;
  spec.tv_nsec = 3;
  spec.tv_sec = 0;
  printf("Lancement de l'écriture...\n");
  // On écrit
  aio_write(&a);
  while(-1 == aio_suspend(&cb, 1, &spec)) {
    // On check toutes les 50ns en boucle
    printf("Check\n");
  }
  printf("Fin de l'écriture...\n");
  int fd_second = open(filename, O_RDONLY, 0600);
  char buffer[size];
  // On lit
  if(-1 == read(fd_second, buffer, size)) {
    close(fd);
    close(fd_second);
    perror("Read");
    return EXIT_FAILURE;
  }
  // On affiche le résultat demandé
  printf("%s\n", buffer);
  // On libère les ressources
  printf("Libération des ressources en cours...\n");
  close(fd);
  close(fd_second);
  if(-1 == aio_error(&a)) {
    perror("Erreur d'E/S");
    return EXIT_FAILURE;
  }
  // On libère proprement les ressources
  aio_return(&a);
  // On attend de recevoir un signal. On part du principe qu'on ne recevra que celui-la
  return EXIT_SUCCESS;
}