#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include "server.h"
#define SIZE 128

pthread_cond_t cond_fin= PTHREAD_COND_INITIALIZER;
int my_rank;

void callback (int source, int tag){
  MPI_Status status;
  char message[SIZE];
  pthread_mutex_t* mutex=getMutex();
  pthread_mutex_lock(mutex);
  MPI_Recv(message,SIZE, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
  printf("%d received : %s\n", my_rank, message);
  pthread_mutex_unlock(mutex);
  destroy_server();
  pthread_cond_signal(&cond_fin);
}


int main(int argc, char **argv){
  int nb_proc;
  int source;
  int dest;
  int prov;
  int tag =0;
  char message[SIZE];
  pthread_mutex_t* mutex;
  mutex=getMutex();
  MPI_Init_thread(&argc, &argv, MPI_THREAD_SERIALIZED, &prov);
  MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  start_server(callback);
  sprintf(message, "hello from %d", my_rank);
  MPI_Ssend(message, strlen(message)+1,MPI_CHAR,(my_rank+1)%nb_proc,tag,MPI_COMM_WORLD);
  pthread_cond_wait(&cond_fin, mutex);

  MPI_Finalize();
  return 0;
}

