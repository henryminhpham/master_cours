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
	int sig;
	int fd, fd2;
	struct aiocb a;
	sigset_t sig_proc;
	char buf[BUF_SIZE];
	if(argc != 3){
		printf("Invalid Arguments\n");
		exit(1);
	}
	if((fd=open(argv[1], O_CREAT | O_TRUNC | O_RDWR, 0777))==-1){
		perror("open");
		exit(1);
	}
	sigemptyset(&sig_proc);
	sigaddset(&sig_proc, SIGRTMIN);
	sigprocmask(SIG_BLOCK, &sig_proc, 0);
	a.aio_fildes = fd;
	a.aio_buf = (char*) argv[2];
	a.aio_nbytes = strlen(argv[2]);
	a.aio_offset = 0;
	a.aio_reqprio = 0;
	a.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
	a.aio_sigevent.sigev_signo = SIGRTMIN;
	aio_write(&a);

	
	if((fd2=open(argv[1],O_RDWR, 0777))==-1){
		perror("open");
		exit(1);
	}
	if(sigwait(&sig_proc, &sig)==-1){
		perror("sigwait");
		exit(1);
	}
	while(read(fd2, buf, BUF_SIZE)){
		printf("%s\n", buf);
	}


	return 0;
}