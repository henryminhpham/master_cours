#include "exo4.h"
#define XOPEN_SOURCE 700
#define NB_CHAR 10

int from, to;

int main(int argc, char** argv) {
  if(argc != 3) {
    perror("Arguments : <file1> <file2>");
    return EXIT_FAILURE;
  }
  if((from = open(argv[1], O_RDONLY, 0666)) == -1) {
    perror("Open first file");
    return EXIT_FAILURE;
  }
  if((to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
    perror("Open second file");
    return EXIT_FAILURE;
  }
  char buffer[NB_CHAR];
  memset(buffer, '\0', NB_CHAR);
  int offset = 0;
  // Tant que l'on arrive à lire quelque chose
  // On met > 1 volontairement pour éviter d
  while(read(from, buffer, NB_CHAR) > 1) {
    cp(to, buffer, offset);    
    offset += NB_CHAR;
    memset(buffer, '\0', NB_CHAR);
  }
  // On bloque volontairement pour s'assurer que tout est écrit. Crade.
  sleep(2);
  close(from);
  close(to);
  return EXIT_SUCCESS;
}

void cp(int to, char* buffer, int offset) {
  int i = 0;
  char* read_val = malloc(sizeof(buffer));
  strcpy(read_val, buffer);
  int size = strlen(buffer);
  struct aiocb* cb[NB_CHAR] ;
  for(i = 0 ; i < size ; i++) {
    struct aiocb* a = malloc(sizeof(struct aiocb));
    a->aio_fildes = to;
    a->aio_buf = &(read_val[i]);
    a->aio_nbytes = 1;
    a->aio_offset = (NB_CHAR - 1) - i + offset;
    a->aio_reqprio = i;
    a->aio_lio_opcode = LIO_WRITE;
    cb[i] = a;
    printf("Placement de \"%c\" à l'offset %d\n", read_val[i], (int) a->aio_offset);
  }
  if(-1 == lio_listio(LIO_NOWAIT, cb, NB_CHAR, 0)) {
    perror("Write");
    close(from);
    close(to);
    exit(1);
  }
}
