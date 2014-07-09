#define _POSIX_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <string.h>



void* toupper_thread(void* args){

	int c=1;
	char* filename = (char*) args;
	printf("fichier : %s\n", filename);

	FILE* fp1 = fopen(filename, "r");
	FILE* fp2 = fopen(filename, "r+");

	if ((fp1 == NULL)||(fp2 == NULL)){
		perror("fopen");
		exit(1);
	}

	while (c !=EOF) {
        c=fgetc(fp1);
        if (c!=EOF)
        fputc(toupper(c),fp2);
    }
    fclose(fp1);
    fclose(fp2);
    pthread_exit((void*)0);
    return NULL;
}


int main (int argc, char ** argv){
	if (argc < 2){
		perror("argc");
		exit(1);
	}
	pthread_t thread_id_table[argc-1];
	int i;


	for (i=0; i<argc-1 ; i++){
		char* filename = argv[i+1];
		pthread_create( &thread_id_table[i], NULL, toupper_thread, (void*) filename );
		printf("test : %s\n", argv[i+1]);
	}

	for (i=0;i<argc-1;i++){
		pthread_join(thread_id_table[i], NULL);
	}

    return EXIT_SUCCESS;
}