#include <mpi.h>
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

#define SIZE 128

int main(int argc, char *argv[])
{
	int myrank;
	int size;
	int tag=0;
	char message[SIZE];
	MPI_Status status;
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
    sprintf(message, "Hello People from %d", myrank);

	if (myrank!=5){
		MPI_Ssend(message, strlen(message)+1,MPI_CHAR,(myrank+1)%size,tag,MPI_COMM_WORLD);
	}
	else
		MPI_Send(message, strlen(message)+1,MPI_CHAR,(myrank+1)%size,tag,MPI_COMM_WORLD);

	MPI_Recv(message, SIZE, MPI_CHAR, (myrank-1)%size, tag, MPI_COMM_WORLD, &status);
	printf("%d %s\n", myrank, message);

	MPI_Finalize();

	return 0;
}