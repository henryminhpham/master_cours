#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
	int fdin, fdout;
	struct stat stat_infos;
	int shmid, *mine;
	if (argc < 3){
		printf("Invalid Arguments\n");
		exit(1);
	}
	errno=0;
	if((fdin=open(argv[1], O_RDWR, 0600))==-1){
		perror("open");
		return EXIT_FAILURE;
	}
	errno=0;
	if ((fdout=open(argv[2], O_RDWR|O_CREAT|O_EXCL, 0600))==-1){
		perror("open");
		if(errno == EEXIST){
			printf("Le fichier existe déjà\n");
		}
		close(fdin);
		return EXIT_FAILURE;
	}
	if (stat(argv[1], &stat_infos)==-1){
		perror("stat");
		return EXIT_FAILURE;
	}
	if(!S_ISREG(stat_infos.st_mode)){
		printf("Le fichier n'est pas régulier\n");
		perror("ISREG");
		close(fdin);
		close(fdout);
		return EXIT_FAILURE;
	}

	mine=mmap(NULL, stat_infos.st_size*sizeof(char), PROT_READ|PROT_WRITE, MAP_SHARED, fdin, 0);

	if(write(fdout, mine, stat_infos.st_size)==-1){
		perror("write");
		close(fdin);
		close(fdout);
		return EXIT_FAILURE;
	}
	close(fdin);
	close(fdout);

	return 0;
}