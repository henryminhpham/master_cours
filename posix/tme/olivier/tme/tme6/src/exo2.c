#include "exo2.h"
#define XOPEN_SOURCE 700
#define BUFF 4096 * 64 
// On met un gros buffer

int main(int argc, char** argv) {
  if(argc != 3) {
    perror("Vous devez spécifier 2 chemins de fichiers !");
    return EXIT_FAILURE;
  }
  char* name_from = argv[1];
  char* name_to = argv[2];
  
  struct stat stat_from;
  struct stat stat_to;
  // On teste si le fichier source existe
  if(-1 == stat(name_from, &stat_from)) {
    perror("Le fichier f1 n'existe pas.");
    return EXIT_FAILURE;
  }
  // On vérifie que c'est un fichier régulier
  if(S_ISREG(stat_from.st_mode) == 0) {
    perror("Le fichier n'est pas un fichier régulier");
    return EXIT_FAILURE;
  }  
  // On vérifie que le fichier n'existe pas
  if(-1 != stat(name_to, &stat_to)) {
    perror("Le fichier f2 existe déjà.");
    return EXIT_FAILURE;
  }
  int fd_from, fd_to;
  fd_from = open(name_from, O_RDONLY, 0666);
  fd_to = open(name_to, O_WRONLY | O_CREAT | O_SYNC, 0777);
  if(fd_from == -1 || fd_to == -1) {
    perror("Impossible d'ouvrir un des fichiers");
    return EXIT_FAILURE;
  }
  return cp(fd_from, fd_to);
}


int cp(int from, int to) {
  char tampon[BUFF];
  int n;
  if((n = read(from, tampon, BUFF)) <= 0) {
    perror("Impossible de lire le fichier f1");
    exit(1);
  }
  if(-1 == write(to, tampon, n)) {
    perror("Impossible d'écrire dans le fichier f2");
    exit(1);
  }
  close(from);
  close(to);
  return EXIT_SUCCESS;  
}
