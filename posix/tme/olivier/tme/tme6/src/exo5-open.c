#include "exo5.h"
#define XOPEN_SOURCE 700

int main(int argc, char** argv) {
  if(argc != 2) {
    perror("Vous devez spécifier en argument un nom de fichier");
    return EXIT_FAILURE;
  }
  int i, fd;
  char* name = argv[1];
  if((fd = open(name, O_RDONLY, 0666)) == -1) {
    perror("Le fichier n'existe pas");
    return EXIT_FAILURE;
  }
  for(i = 0 ; i < PROC ; i++) {
    pid_t pid;
    if((pid = fork()) == -1) exit(1);
    
    if(pid == 0) {
      return read_file(fd);
    }
  }
  for(i = 0 ; i < PROC ; i++) {
    wait(NULL);
  }
  close(fd);
  return EXIT_SUCCESS;
}

int read_file(int fd) {
  char c;
  pid_t pid = getpid();
  while(0 < read(fd, &c, sizeof(char))) {
    printf("Je suis %d et j'ai lu \"%c\".\n", pid, c);
  }
  return EXIT_SUCCESS;
}

int fread_file(FILE* fd) {
  return -1;
}