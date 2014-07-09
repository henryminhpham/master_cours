#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define _POSIX_SOURCE 700
#define _NTH 4


void* thread_rand (void* number){
	int *pt = malloc(sizeof(int));

	pt = (int*)number;
	printf("Le numero : %d, tid : %d \n",*pt, (int)pthread_self());
	*pt*=2;
	sleep(1);
	pthread_exit((void*)pt);
	return NULL;
}



int main(int argc, char const *argv[])
{
	int i;
	pthread_t thread_id_table[_NTH];
	int* ret;


	for (i=0;i<_NTH;i++){
		int* val = malloc(sizeof(int));
		*(val)=i;
		pthread_create( &thread_id_table[i], NULL, thread_rand, (void*) val );
		printf(" thread : %d, i : %d\n", (int)thread_id_table[i], i);
	}


	for (i=0;i<_NTH;i++){
		if (pthread_join(thread_id_table[i], (void**)&ret) == 0)
			printf("La valeur renvoyée par %d : %d\n",(int)thread_id_table[i], *ret);
		else
			printf("Erreur sur le retour du thread\n");
	}

	return EXIT_SUCCESS;
}