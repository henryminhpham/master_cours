#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define _POSIX_SOURCE 700
#define _NTH 4


int cpt=0;
int somme=0;


pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond_fin = PTHREAD_COND_INITIALIZER;


void* print_thread (void* parqam){
	printf("Moi j'attends...\n");
	pthread_mutex_lock(&mymutex);
	while (cpt < _NTH-1){
		pthread_cond_wait(&cond_fin, &mymutex);
	}
	pthread_mutex_unlock(&mymutex);
	printf("Somme de toutes les valeurs : %d\n",somme );
	return NULL;
}


void* thread_rand (void* param){


	int randval=(int) (5*((double)rand())/ RAND_MAX);
	srand((int) pthread_self());
	printf("\tValeur générée : %d, tid : %d\n",randval, (int)pthread_self());
	
	
	pthread_mutex_lock(&mymutex);
	somme+=randval;
	cpt++;
	if (cpt == _NTH-1){
		pthread_cond_signal(&cond_fin);
	}
	pthread_mutex_unlock(&mymutex);

	pthread_exit((void*)0);
	return NULL;
}



int main(int argc, char const *argv[])
{
	int i;
	pthread_t thread_id_table[_NTH];
	pthread_t tid_print;
	int* ret;
	for (i=0;i<_NTH;i++){
		pthread_create( &thread_id_table[i], NULL, thread_rand, NULL);
		pthread_detach( thread_id_table[i]);
		printf("thread : %d, i : %d\n", (int)thread_id_table[i], i);
	}
	pthread_create( &tid_print, NULL, print_thread, NULL);
	for (i=0;i<_NTH;i++){
		if (pthread_join(thread_id_table[i], (void**)&ret) != 0)
			printf("Erreur sur le retour du thread rand\n");
	}

	if (pthread_join(tid_print, (void**)&ret) != 0)
		printf("Erreur sur le retour du thread print\n");


	return EXIT_SUCCESS;
}