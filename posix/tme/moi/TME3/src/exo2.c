#define _POSIX_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <string.h>



int doing=1;
int copy_argc;
char** copy_argv;

pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;


void* toupper_thread(void* args){

	int mine,finished=0,c=1;
	char* filename;

	FILE* fp1=NULL;
	FILE* fp2=NULL;

	while(!finished){

		pthread_mutex_lock(&mymutex);
		if(doing==copy_argc){
			finished=1;
			pthread_mutex_unlock(&mymutex);
		}
		else{
			mine=doing;
			doing++;
			pthread_mutex_unlock(&mymutex);

			filename = copy_argv[mine];
			fp1 = fopen(filename, "r");
			fp2 = fopen(filename, "r+");

			if ((fp1 == NULL)||(fp2 == NULL)){
				perror("fopen");
				exit(1);
			}

			while (c !=EOF) {
		        c=fgetc(fp1);
		        if (c!=EOF)
		        fputc(toupper(c),fp2);
		        
		    }
		    c=1;
		    fclose(fp1);
		    fclose(fp2);
		}
	}
	
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
	copy_argc=argc;
	copy_argv = argv;

	for (i=0; i<2 ; i++){
		char* filename = argv[i+1];
		pthread_create( &thread_id_table[i], NULL, toupper_thread, (void*) filename );
	}

	for (i=0;i<argc-1;i++){
		pthread_join(thread_id_table[i], NULL);
	}

    return EXIT_SUCCESS;
}