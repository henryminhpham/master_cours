#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "../include/thread_stack.h"


#define _NTH 2

 

void* Producteur ( void* arg ){  
    int c;
    while ((c = getchar()) != EOF) { 
        Push(c);
    }
    return NULL;
}

void* Consommateur ( void* arg ) {
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
	pthread_create(&thread_id_table[0], NULL, Producteur, NULL);
	pthread_create(&thread_id_table[1], NULL, Consommateur, NULL);
	for (i=0;i<_NTH;i++){
		pthread_join(thread_id_table[i], NULL);
	}
	return 0;
}
