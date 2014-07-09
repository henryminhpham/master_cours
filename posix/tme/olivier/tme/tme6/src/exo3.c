#include "exo3.h"
#define XOPEN_SOURCE 700

int main(int argc, char **argv) {
  if(argc != 3) {
    perror("Vous devez spécifier 2 chemins de fichiers !");
    return EXIT_FAILURE;
  }
  int input, output;
  struct stat stat_from;
  struct stat stat_to;
  // On teste si le fichier source existe
  if((input = open(argv[1], O_RDONLY, 0777)) == -1) {
    perror("Impossible d'ouvrir le fichier f1\n"); 
    exit(1);
  }
  if(-1 == fstat(input, &stat_from)) {
    perror("fstat");
    return EXIT_FAILURE;
  }
  // On vérifie que c'est un fichier régulier
  if(S_ISREG(stat_from.st_mode) == 0) {
    perror("Le fichier n'est pas un fichier régulier");
    return EXIT_FAILURE;
  }  
  // On vérifie que le fichier n'existe pas
  if(-1 != stat(argv[2], &stat_to)) {
    perror("Le fichier f2 existe déjà.");
    return EXIT_FAILURE;
  }
  
 if((output = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, 0666)) == -1) {
  perror("Impossible d'ouvrir le fichier f2\n"); 
  exit(1);
 }
 
 return cp(input, output, stat_from.st_size);
}

int cp(int input, int output, off_t size) {
 void *source;

 if((source = mmap(NULL, size, PROT_READ, MAP_PRIVATE, input, 0)) == (void *) -1) {
  perror("Impossible de mapper f1\n");
  exit(1);
 }
 
 if(-1 == write(output, source, size)) {
   perror("Impossible d'écrire dans le fichier f2");
   exit(1);
 }
 
 munmap(source, size);
 
 close(input);
 close(output);

 return EXIT_SUCCESS;
}