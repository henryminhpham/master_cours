#include "thread_stack-1.h"

int main(int argc, char** argv) {
  pthread_t threads[5];
  pthread_create(&threads[0], NULL, Consommateur, NULL);
  pthread_create(&threads[1], NULL, Producteur, NULL);
  pthread_create(&threads[2], NULL, Consommateur, NULL);
  pthread_create(&threads[3], NULL, Producteur, NULL);
  pthread_create(&threads[4], NULL, Consommateur, NULL);
  
  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  pthread_join(threads[2], NULL);
  pthread_join(threads[3], NULL);
  pthread_join(threads[4], NULL);
  return EXIT_SUCCESS;
}
