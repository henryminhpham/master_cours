#include "exo4.h"
#define XOPEN_SOURCE 700
#define FORK 5
#define FILENAME "tmp_file"

int main(int argc, char** argv) {
  int fd, i;
  fd = open(FILENAME, O_RDWR | O_CREAT | O_TRUNC, 0600);
  for(i = 0 ; i < FORK ; i++) {
    pid_t pid;
    if((pid = fork()) == -1) {
      perror("Fork");
      exit(1);
    }
    if(pid == 0) {
      return child_random(fd);
    }
  }
  for(i = 0 ; i < FORK ; i++) {
   wait(NULL); 
  }
  int size_read;
  char buffer[2048];
  if((size_read = pread(fd, buffer, 2048, 0L)) < 0) {
    perror("Impossible de lire le fichier tmp");
    clean(fd);
    return EXIT_FAILURE;
  }
  
  int final_random = 0;
  int tmp;
  for(i = 0 ; i < size_read ; i++) {
    tmp = buffer[i] - '0';
    final_random += tmp;
  }
  printf("La valeur finale est %d\n", final_random);
  clean(fd);
  return EXIT_SUCCESS;
}

int child_random(int fd) {
  char buffer[2];
  int random_val = (int) (10*(float)rand()/ RAND_MAX);
  sprintf(buffer, "%d", random_val);
  
  if (-1 == write(fd, buffer, strlen(buffer))) {
    perror("Impossible d'écrire le random dans le fichier");
    return EXIT_FAILURE;
  }
  printf("Je suis %d et j'ai généré %d\n", getpid(), random_val);
  return EXIT_SUCCESS;
}

void clean(int fd) {
  close(fd);
  remove(FILENAME);
}