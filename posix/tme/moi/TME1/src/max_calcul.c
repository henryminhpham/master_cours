#define _POSIX_SOURCE 700

#include "../include/max_func.h"


int main(int argc, char const *argv[])
{	
	if (argc < 1){
		printf("Il n'y a pas assez d'arguments");
		return 1;
	}
	int* vect = malloc((argc-2)*sizeof(int));
	int i=0,max=0;
	for (i=1 ; i<argc ; i++){
		vect[i]=atoi(argv[i]);
	}
	max=max_func(vect, argc);
	printf("Le max est : %d\n", max);

	return 0;
}