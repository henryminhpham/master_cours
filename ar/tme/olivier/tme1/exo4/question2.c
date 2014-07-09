#include <stdio.h>
#include <string.h>
#include <mpi.h>

#define SIZE 128
#define TAG 0

int main(int argc, char **argv){
  int my_rank;
  int nb_proc;
  int dest;
  char message[SIZE];

  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

  dest = (my_rank + 1) % nb_proc;
  strcpy(message, "Hello World !");  
  MPI_Ssend(message, strlen(message)+1, MPI_CHAR,dest,TAG,MPI_COMM_WORLD); 
  MPI_Recv(message, SIZE, MPI_CHAR, MPI_ANY_SOURCE, TAG, MPI_COMM_WORLD, &status);
  printf("%s\n", message);
  MPI_Finalize();
  return 0;
}

