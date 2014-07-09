#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>
#include <unistd.h>

#define SIZE_H_N 50

int main(int argc, char** argv) {
  int rank, p, source,dest, tag = 0;
  char message[100];
  MPI_Status status;
  char hostname[SIZE_H_N];
  
  gethostname(hostname, SIZE_H_N);
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  
  sprintf(message, "Coucou du processus #%d depuis #%s !", rank, hostname);
  dest = (rank + 1) % p;
  MPI_Ssend(message, strlen(message) + 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
  MPI_Recv(message, 100, MPI_CHAR, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
  printf("Sur %s, le processus #%d a reçu le message : %s\n", hostname, rank, message);  
  MPI_Finalize();
}
