#include "server.h"
#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"

static server the_server;

void start_server(void (*callback)(int tag, int source)){
	pthread_mutex_init(&(the_server.mymutex), NULL);
	the_server.callback=callback;
	pthread_create(&(the_server.listener), NULL, monServeurMain, NULL);
}

void destroy_server (){
	pthread_mutex_destroy(&(the_server.mymutex)); 
	pthread_join(the_server.listener, NULL);
}

pthread_mutex_t* getMutex (){
  return &(the_server.mymutex);
}

void* monServeurMain(void* args){
  MPI_Status status;
  int flag;
	int src;
 	int tag;
  while (1){
    pthread_mutex_lock(&(the_server.mymutex));
    MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
    src = status.MPI_SOURCE;
    tag = status.MPI_TAG;
    pthread_mutex_unlock(&(the_server.mymutex));
    if (flag != 0){
      printf("launching callback...\n");
      the_server.callback(src,tag);
      break;
    }
  }
  pthread_exit(NULL);
}
