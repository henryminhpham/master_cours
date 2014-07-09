#define _XOPEN_SOURCE 700
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "sys/types.h"
#include "time.h"
#include "fcntl.h"
#include "signal.h"
#include "aio.h"

#define BUF_SIZE 16

int main(int argc, char const *argv[])
{
	int fd, fd2;
	struct aiocb a;
	char c;
	int done=0;
	struct timespec rq;
	rq.tv_sec = 0;
	rq.tv_nsec = 50;

	if(argc != 3){
		printf("Invalid Arguments\n");
		exit(1);
	}
	if((fd=open(argv[1], O_CREAT | O_TRUNC | O_RDWR, 0777))==-1){
		perror("open");
		exit(1);
	}
	a.aio_fildes = fd;
	a.aio_buf = (char*) argv[2];
	a.aio_nbytes = strlen(argv[2]);
	a.aio_offset = 0;
	a.aio_reqprio = 0;
	a.aio_sigevent.sigev_notify = 0;
	a.aio_sigevent.sigev_signo = 0;
	aio_write(&a);
	
	if((fd2=open(argv[1],O_RDWR, 0777))==-1){
		perror("open");
		exit(1);
	}
	while(!done){
		clock_nanosleep(CLOCK_REALTIME, 0, &rq, NULL);
		if (aio_error(&a)==0)
			done=1;
	}
	printf("Sortie while\n");
	while(read(fd2, &c, sizeof(char))){
		printf("%c", c);
	}
	printf("\n");

	return 0;
}