#include <mpi.h>
#include "stdio.h"
#include "stdlib.h"




int main(int argc, char *argv[])
{
	int myrank;
	int size;
	MPI_Status status;
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	printf("Processus %d sur %d : Hello f***ing MPI\n", myrank, size);

	MPI_Finalize();

	return 0;
}