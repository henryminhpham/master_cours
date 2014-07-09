#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define _POSIX_SOURCE 700
#define _NTH 4



int somme=0;


pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;




void* thread_rand (void* param){
	int randval=(int) (10*((double)rand())/ RAND_MAX);
	srand((int) pthread_self());
	printf("\tValeur générée : %d, tid : %d \n",randval, (int)pthread_self());
	pthread_mutex_lock(&mymutex);
	somme+=randval;
	pthread_mutex_unlock(&mymutex);
	pthread_exit((void*)0);
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
		pthread_create( &thread_id_table[i], NULL, thread_rand, NULL);
		printf("thread : %d, i : %d\n", (int)thread_id_table[i], i);
	}


	for (i=0;i<_NTH;i++){
		if (pthread_join(thread_id_table[i], (void**)&ret) != 0)
			printf("Erreur sur le retour du thread\n");
	}
	printf("La valeur totale : %d\n", somme);

	return EXIT_SUCCESS;
}