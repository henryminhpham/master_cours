#include "exo8.h"
#define XOPEN_SOURCE 700

int main (int argc, char** argv) { 
  if(argc != 2) {
    perror("Il faut 1 argument");
    return EXIT_FAILURE;
  }
  int fd_from, fd_to;
  if(-1 == (fd_from = open(argv[1], O_RDONLY, 0666))) {
    fprintf(stderr, "Impossible d'ouvrir le fichier %s.\n", argv[1]);
    return EXIT_FAILURE;
  }
  // On crée le nom <file>.inv
  char to_name[strlen(argv[1]) + 4];
  strcpy(to_name, argv[1]);
  strcat(to_name, ".inv");
  if(-1 == (fd_to = open(to_name, O_WRONLY | O_CREAT | O_TRUNC, 0666))) {
    fprintf(stderr, "Impossible d'ouvrir le fichier %s.\n", argv[1]);
    return EXIT_FAILURE;
  }
  // On lance la procédure
  reverse(fd_from, fd_to);
  close(fd_from);
  close(fd_to);
  return EXIT_SUCCESS;
}

void reverse(int fd_from, int fd_to) {
  int position;
  // On met le curseur à la fin et on récupère la position
  if(-1 == (position = lseek(fd_from, 0, SEEK_END))) {
      fprintf(stderr, "Impossible de repositionner le curseur.\n");
      exit(1);
  }
  // On décrémente le curseur de 1 pour récupérer le dernier char
  // lors du 1er read
  if(-1 == lseek(fd_from, --position, SEEK_SET)) {
      fprintf(stderr, "Impossible de repositionner le curseur.\n");
      exit(1);
  }
  char c;
  while(read(fd_from, &c, sizeof(c)) > 0) {
    // On écrit le caractère
    if(-1 == write(fd_to, &c, sizeof(c))) {
      fprintf(stderr, "Impossible d'écrire %c dans le fichier destination.\n", c);
      exit(1);
    }
    // Si la position est de 0, on vient d'écrire le dernier caractère,
    // on stoppe
    if(position == 0) {
      break;
    }
    // On décrémente le curseur.
    --position;
    if(-1 == lseek(fd_from, position, SEEK_SET)) {
      fprintf(stderr, "Impossible de repositionner le curseur.\n");
      exit(1);
    }
    
  } 
}