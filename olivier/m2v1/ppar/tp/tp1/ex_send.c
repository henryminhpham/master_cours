#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>
#include <unistd.h>

#define SIZE_H_N 50

int main(int argc, char** argv) {
  int rank, p, source,dest, tag = 0;
  int size = sizeof(char) * 100000;
  char* message = malloc(size);
  
  MPI_Status status;
  char hostname[SIZE_H_N];
  
  gethostname(hostname, SIZE_H_N);
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  memset( (void*) message, rank, size);
  dest = (rank + 1) % p;
  MPI_Send(message, size, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
  MPI_Recv(message, size, MPI_CHAR, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
  MPI_Finalize();
}
