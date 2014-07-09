#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define _POSIX_SOURCE 700
#define _NTH 4


int cpt=0;


pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond_fin = PTHREAD_COND_INITIALIZER;


void wait_barrier (int nbt){
	pthread_mutex_lock(&mymutex);
	cpt++;
	if (cpt<nbt){
		pthread_cond_wait(&cond_fin, &mymutex);
	}
	else
		pthread_cond_broadcast(&cond_fin);
	pthread_mutex_unlock(&mymutex);
}


void* thread_func (void *arg) {
    printf ("avant barrière\n");
    wait_barrier(_NTH);
    printf ("après barrière\n");
    pthread_exit ( (void*)0);
}



int main(int argc, char const *argv[])
{
	int i;
	pthread_t thread_id_table[_NTH];
	int* ret;


	for (i=0;i<_NTH;i++){
		pthread_create( &thread_id_table[i], NULL, thread_func ,NULL);
		printf("thread : %d, i : %d\n", (int)thread_id_table[i], i);
	}


	for (i=0;i<_NTH;i++){
		if (pthread_join(thread_id_table[i], (void**)&ret) != 0)
			printf("Erreur sur le retour du thread rand\n");
	}


	printf("Fin main-thread\n");

	return EXIT_SUCCESS;
}