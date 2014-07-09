#include "exo2.h"
#define XOPEN_SOURCE 700

int size;
int fd;
char* filename;

int main(int argc, char** argv) {
  if(argc != 3) {
    perror("Vous devez spécifier un nom de fichier et un contenu");
    return EXIT_FAILURE;
  }
  
  // On bind le signal
  sigset_t sig;
  struct sigaction action;
  action.sa_flags = SA_SIGINFO;
  action.sa_sigaction = end_es;
  action.sa_mask = sig;
  sigaction(SIGRTMIN, &action, 0);
  
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
  a.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
  a.aio_sigevent.sigev_signo = SIGRTMIN;
  printf("Lancement de l'écriture...\n");
  // On écrit
  aio_write(&a);
  // On attend de recevoir un signal. On part du principe qu'on ne recevra que celui-la
  pause();
  printf("Libération des ressources en cours...\n");
  if(-1 == aio_error(&a)) {
    perror("Erreur d'E/S");
    return EXIT_FAILURE;
  }
  // On libère proprement les ressources
  aio_return(&a);
  return EXIT_SUCCESS;
}

void end_es(int sig, siginfo_t* si, void* context) {
  printf("Fin de l'écriture\n");
  // On ouvre le fichier en lecture
  int fd_second = open(filename, O_RDONLY, 0600);
  char buffer[size];
  // On lit
  if(-1 == read(fd_second, buffer, size)) {
    close(fd);
    close(fd_second);
    perror("Read");
  }
  // On affiche le résultat demandé
  printf("%s\n", buffer);
  // On libère les ressources
  close(fd);
  close(fd_second);
}