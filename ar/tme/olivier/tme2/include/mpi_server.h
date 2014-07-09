#ifndef MPI_SERVER
#define MPI_SERVER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <mpi.h>
 
struct server {
  pthread_t listener;
  pthread_mutex_t mtx;
  void (*callback)(int tag, int source); /* procedure de reception de message */
};

/* initialiser le serveur */
void init_server(void (*callback)(int tag, int source)); 

/* detruire le serveur    */
void destroy_server();

/* renvoyer une reference sur le mutex */
pthread_mutex_t* get_mtx();
#endif
