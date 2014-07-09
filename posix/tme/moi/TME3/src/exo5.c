#include "pthread.h"
#include "signal.h"
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"

#define _NTH 6

void* thread_sig (void* args){
	int sig;
	sigset_t myens;
	sigemptyset(&myens);
	sigaddset(&myens, SIGUSR1);

	sigwait(&myens,&sig);

	printf("Je suis sorti de l'attente\n");

	pthread_exit((void*)0);
	return NULL;

}


int main(int argc, char const *argv[])
{
	sigset_t ens;
	pthread_t thread_id_table[_NTH];
	int i, sig;
	sigfillset(&ens);
	pthread_sigmask(SIG_SETMASK, &ens, NULL);



	for (i=0;i<_NTH;i++){
		int* val = malloc(sizeof(int));
		*(val)=i;
		pthread_create( &thread_id_table[i], NULL, thread_sig, NULL);
	}
	printf("Tous mes descendants sont créés\n");

	sigemptyset(&ens);
	sigaddset(&ens, SIGINT);
	sigwait(&ens, &sig);

	printf("\nJ'ai été débloqué avec le signal %d\n", sig);
	for (i=0;i<_NTH;i++){
		pthread_kill(thread_id_table[i], SIGUSR1);
	}

	for (i=0;i<_NTH;i++){
		pthread_join(thread_id_table[i], NULL);
	}
	printf("Fin du main thread\n");

	return 0;
}