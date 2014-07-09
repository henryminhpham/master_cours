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
	int fdin;
	char received;
	int i;
	pid_t pid=1;
	struct stat stat_infos;
	if (argc < 2){
		printf("Invalid Arguments\n");
		exit(1);
	}
	errno=0;
	if((fdin=open(argv[1], O_RDWR, 0600))==-1){
		perror("open");
		return EXIT_FAILURE;
	}
	errno=0;
	if (stat(argv[1], &stat_infos)==-1){
		perror("stat");
		return EXIT_FAILURE;
	}
	if(!S_ISREG(stat_infos.st_mode)){
		printf("Le fichier n'est pas régulier\n");
		perror("ISREG");
		close(fdin);
		return EXIT_FAILURE;
	}
	for(i=0;i<3 && pid;i++){
		pid=fork();
	}
	if(pid==0){
		while(read(fdin, &received, sizeof(char)))
			printf("proc %d : %c\n",getpid(), received);
	}
	else{
		while(wait(NULL)!=-1);
	}
	close(fdin);
	return 0;
}