#include "mpi_server.h"

#define SIZE 128
#define TAG 0

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static server* the_server;
int rank;

void* execute_server(void* args);
void callback_fct(int tag, int source);

int main(int argc, char** argv) {
  int provided;
  int dest;
  int nb_proc;
  char message[SIZE];
  
  MPI_Init_thread(&argc, &argv, MPI_THREAD_SERIALIZED, &provided);
  MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  start_server(callback_fct);
  
  dest = (rank + 1) % nb_proc;
  sprintf(message, "Hello World ! Je suis %d.", rank);
  // Send
  MPI_Send(message, strlen(message)+1, MPI_CHAR, dest, TAG, MPI_COMM_WORLD); 
  pthread_mutex_lock(&mutex);
  pthread_cond_wait(&cond, &mutex);
  pthread_mutex_unlock(&mutex);
  destroy_server();
  MPI_Finalize();
  return 0;
}

void start_server(void (*callback)(int tag, int source)) {
  the_server = malloc(sizeof(server));
  the_server->callback = callback;
  the_server->mutex = mutex;
  if(-1 == pthread_create(&(the_server->listener), 0, execute_server, 0)) {
    MPI_Finalize();
    exit(-1);
  }
  printf("Démarrage du thread d'écoute de rang %d\n", rank);  
}

void destroy_server() {
  printf("Destruction du serveur de rang %d\n", rank);
  pthread_cancel(the_server->listener);
  free(the_server);
}

pthread_mutex_t* getMutex() {
  return &mutex;
}

void* execute_server(void* args) {
  int flag;
  MPI_Status status;
  while(1) {
    MPI_Iprobe(MPI_ANY_SOURCE, TAG, MPI_COMM_WORLD, &flag, &status);
    if(flag) {
      the_server->callback(status.MPI_TAG, status.MPI_SOURCE);
    }
  }
}


void callback_fct(int tag, int source) {
  // Receive
  char message[SIZE];
  MPI_Status status;
  MPI_Recv(message, SIZE, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
  printf("Réception du message \"%s\" de %d à %d\n", message, source, rank);
  pthread_mutex_lock(&mutex);
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&mutex);
}
