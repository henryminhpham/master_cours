#include "exo5.h"
#define XOPEN_SOURCE 700

int main(int argc, char** argv) {
  if(argc != 2) {
    perror("Vous devez spécifier en argument un nom de fichier");
    return EXIT_FAILURE;
  }
  int i;
  FILE* fd;
  char* name = argv[1];
  if((fd = fopen(name, "r")) == NULL) {
    perror("Le fichier n'existe pas");
    return EXIT_FAILURE;
  }
  for(i = 0 ; i < PROC ; i++) {
    pid_t pid;
    if((pid = fork()) == -1) exit(1);
    
    if(pid == 0) {
      return fread_file(fd);
    }
  }
  for(i = 0 ; i < PROC ; i++) {
    wait(NULL);
  }
  fclose(fd);
  return EXIT_SUCCESS;
}

int read_file(int fd) {
  return -1;
}

int fread_file(FILE* fd) {
  char c;
  pid_t pid = getpid();
  while((c = fgetc(fd)) != EOF) {
    printf("Je suis %d et j'ai lu \"%c\".\n", pid, c);
  } 
  return -1;
}