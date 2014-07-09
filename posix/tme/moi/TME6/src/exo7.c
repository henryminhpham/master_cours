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
	int fdin, fdout;
	struct stat stat_infos;
	char dest[strlen(argv[1])+5];
	char recv;
	if (argc < 2){
		printf("Invalid Arguments\n");
		exit(1);
	}
	if((fdin=open(argv[1], O_RDWR, 0600))==-1){
		perror("open");
		return EXIT_FAILURE;
	}
	errno=0;
	strcpy(dest, argv[1]);
	strcat(dest,".inv");
	if ((fdout=open(dest, O_RDWR|O_CREAT|O_EXCL, 0600))==-1){
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

	lseek(fdin, 0, SEEK_END);
	lseek(fdin, -1, SEEK_CUR);
	while(lseek(fdin, 0, SEEK_CUR)>0){
		read(fdin, &recv, sizeof(char));
		write(fdout, &recv, sizeof(char));
		lseek(fdin, -2, SEEK_CUR);
	}
	lseek(fdin, 0, SEEK_SET);
	read(fdin, &recv, sizeof(char));
	write(fdout, &recv, sizeof(char));
	close(fdin);
	close(fdout);



	return 0;
}