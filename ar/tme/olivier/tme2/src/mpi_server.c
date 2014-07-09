#include <pthread.h>
#include <mpi.h>

#include "mpi_server.h"

#define SIZE 128

static struct server server;

void *server_thread(void *arg __attribute__((unused))) {
  MPI_Status status;
  int flag;

  while (1) {
    pthread_mutex_lock(get_mtx());    
    MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
    pthread_mutex_unlock(get_mtx());    

    if(flag)
      server.callback(status.MPI_TAG, status.MPI_SOURCE);
  }
  pthread_exit((void *)0);
}

void init_server(void (*callback)(int tag, int source)) {
  pthread_mutex_init(&server.mtx, NULL);
  server.callback = callback;
  pthread_create(&server.listener, NULL, server_thread, NULL);
}

void destroy_server() {
  pthread_mutex_destroy(&server.mtx);
  pthread_cancel(server.listener);
}
 
pthread_mutex_t* get_mtx() {
  return &(server.mtx);
}
