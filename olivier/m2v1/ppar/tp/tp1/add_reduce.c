#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>
#include <unistd.h>

#define SIZE_H_N 50

int main(int argc, char** argv) {
  int rank, p, source,dest, tag = 0;
  int size = sizeof(rank);
  int loc_num;
  int step = 1;
  /* int actif = 1; */
  int somme, tmp;

  MPI_Status status;
  char hostname[SIZE_H_N];
  
  gethostname(hostname, SIZE_H_N);
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  somme = rank;
  loc_num = rank;

  MPI_Comm_size(MPI_COMM_WORLD, &p);
  /* nb_actif = p; */

  while (step < p){
    if (loc_num % 2){ /* émission */
      printf("rank=%d step=%d locnum=%d somme=%d\n", rank, step, loc_num, somme);
      MPI_Send(&somme, 1, MPI_INT, rank - step, tag, MPI_COMM_WORLD);
      break;
    }
    else{
      if (rank + step < p){ /* réception */
	MPI_Recv(&tmp, 1, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD,\
		 &status);	
	somme += tmp;
      }
    }
    step *= 2;
    loc_num /= 2;
  }
  if (rank == 0)
    printf("Résultat = %d\n", somme);
  MPI_Finalize();
}
