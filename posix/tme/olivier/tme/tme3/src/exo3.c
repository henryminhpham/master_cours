#include "thread_stack-1.h"

int main(int argc, char** argv) {
  pthread_t threads[2];
  pthread_create(&threads[0], NULL, Consommateur, NULL);
  pthread_create(&threads[1], NULL, Producteur, NULL);
  
  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  return EXIT_SUCCESS;
}