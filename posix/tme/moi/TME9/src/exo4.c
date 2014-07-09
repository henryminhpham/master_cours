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

#define BUF_SIZE 10


int main(int argc, char const *argv[])
{
	int fdin, fdout;
	int i, done;
	char buf[BUF_SIZE];
	int myoffset=0;
	struct aiocb a[BUF_SIZE];
	struct aiocb* list[BUF_SIZE];

	if((fdin=open(argv[1], O_RDWR, 0777))==-1){
		perror("open");
		exit(1);
	}

	if((fdout=open("test2", O_CREAT | O_TRUNC | O_RDWR, 0777))==-1){
		perror("open");
		exit(1);
	}
	while((done = read(fdin, buf, BUF_SIZE*sizeof(char)))){
		for (i=0; i<done; i++){
			a[i].aio_fildes=fdout;
			a[i].aio_buf=&buf[done-i-1];
			a[i].aio_nbytes=sizeof(char);
			a[i].aio_offset=(myoffset+i)*sizeof(char);
			a[i].aio_reqprio=0;
			a[i].aio_sigevent.sigev_notify=SIGEV_NONE;
			a[i].aio_sigevent.sigev_signo=0;
			a[i].aio_lio_opcode=LIO_WRITE;
			list[i]=&a[i];
		}
		myoffset+=done;
		lio_listio(LIO_WAIT, list, done, NULL);
	}
	return 0;
}