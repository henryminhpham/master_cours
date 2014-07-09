#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "../include/thread_stack_shm.h"


#define _NTH 5

 

void* Producteur ( void* arg ){  
    int *c = (int*)arg;
    printf("Prod %d créé\n", *c);
    while(1){
    	Push(*c);
	    sleep((*c)+1);
    }

    return NULL;
}

void* Consommateur ( void* arg ) {
	printf("Le conso est créé\n");
    for (;;) { 
        putchar(Pop());
        fflush(stdout); 
    } 
}

int main(int argc, char const *argv[])
{
	pthread_t thread_id_table[_NTH];
	int i=0;
	initStack();
	for (i=0;i<_NTH-1;i++){
		int* val = malloc(sizeof(int));
		*(val)=i;
		pthread_create( &thread_id_table[i], NULL, Producteur, val);
	}
	pthread_create( &thread_id_table[i], NULL, Consommateur, NULL);

	for (i=0;i<_NTH;i++){
		pthread_join(thread_id_table[i], NULL);
	}
	return 0;
}