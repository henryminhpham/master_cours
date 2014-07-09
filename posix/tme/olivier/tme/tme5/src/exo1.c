#include "exo1.h"
#define XOPEN_SOURCE 700
#define NB_FORK 3
#define SIZE NB_FORK * sizeof(int)

static int get_random();

int shm;
const char* name = "tmp_file";

int main(int argc, char** argv) {
	
	if((shm = shm_open(name, O_RDWR | O_CREAT, 0777)) == -1) {perror("create shm"); exit(1);}
	int* segment;

  if(-1 == ftruncate(shm, SIZE)){perror("Ftruncate"); exit(1);}
	
  if((segment = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0)) == MAP_FAILED) {perror("mmap"); exit(1);}
  
	int i;
	for(i = 0 ; i < NB_FORK ; i++) {
	  pid_t pid;
	  if((pid = fork()) == -1) {perror("Fork"); exit(1);}
	  
	  if(pid == 0) {
      int rand_value = get_random();
      printf("Je suis %d et random %d\n", getpid(), rand_value);
      segment[i] = rand_value;
      return 0;
	  }
	}
	for(i = 0 ; i < NB_FORK ; i++) {
	  wait(NULL);
	}
	int final_random = 0;
	for(i = 0 ; i < NB_FORK ; i++) {
    final_random += segment[i];
	}	
	printf("Random final %d\n", final_random);
	munmap((caddr_t) segment, SIZE);
	shm_unlink(name);
	return EXIT_SUCCESS;
	
}

static int get_random() {
  return (int) (10*(float)rand()/ RAND_MAX);
}
