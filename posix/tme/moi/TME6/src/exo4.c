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
#include <time.h>

#define NB_PROC 4

int main(int argc, char const *argv[])
{
	pid_t pid=1;
	int i=0;
	int fd;

	if((fd=open("./temp", O_RDWR|O_CREAT, 0600))==-1){
		perror("open");
		return EXIT_FAILURE;
	}


	for(i=0;i<NB_PROC && pid; i++){
		pid=fork();
	}
	if (pid){
		int res=0, randval;
		for(i=0;i<NB_PROC && pid; i++){
			wait(NULL);
		}
		if (lseek (fd,0,SEEK_SET) == -1) /* D */
			return EXIT_FAILURE;
			
		while(read(fd,&randval,sizeof(int))){
			res+=randval;
		}

		printf("Le resultat final : %d\n",res);
		unlink("./temp");
		close(fd);

	}
	else {
		int randval;
		srand(time(NULL)*getpid());
		sleep(i);
		randval=(int)(10*(float)rand()/ RAND_MAX);
		if(write(fd, &randval, sizeof(int))==-1)
			return EXIT_FAILURE;
		printf("Moi j'envoie : %d\n", randval);
		close(fd);
	}

	return 0;
}