#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
	FILE* fin;
	char received;
	int i;
	pid_t pid=1;
	if (argc < 2){
		printf("Invalid Arguments\n");
		exit(1);
	}
	if((fin=fopen(argv[1],"r"))==NULL){
		perror("open");
		return EXIT_FAILURE;
	}
	if(setvbuf(fin, NULL, _IONBF, 0)==-1){
		perror("setvbuf");
		fclose(fin);
		exit(1);

	}
	for(i=0;i<3 && pid;i++){
		pid=fork();
		if(pid) printf("pid : %d\n", pid);
	}
	if(pid==0){
		while((received=fgetc(fin))!=EOF){
			if(i==1)
				sleep(1);
			printf("proc %d : %c\n",getpid(), received);
		}
		printf("sortie\n");
	}
	else{
		while(wait(NULL)!=-1);
		fclose(fin);
	}
	return 0;
}