#include "thread_stack-1.h"
#define ARRAY 100

static char data[ARRAY];
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static int stack_size = -1;

void* Producteur(void* arg) { 
    int c; 
    while ((c = getchar()) != EOF) { 
        Push(c); 
    } 
    return NULL;
}

void* Consommateur(void* arg) { 
    for (;;) { 
        putchar(Pop()); 
        fflush(stdout); 
    } 
    return NULL;
}

int Pop() {
  pthread_mutex_lock(&mutex);
  // S'il n'y a plus rien on attend un signal
  if(stack_size <= -1) {
    pthread_cond_wait(&cond, &mutex);  
  }
  // on dépile
  int retour = data[stack_size--];
  pthread_mutex_unlock(&mutex);
  return retour;
}

void Push(int c) {
  pthread_mutex_lock(&mutex);
  // On empile un caractère
  data[++stack_size] = (int) c;
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&mutex);
}
