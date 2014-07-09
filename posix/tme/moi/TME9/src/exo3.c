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
#include "aio.h"
#include "signal.h"


#define NB_PROC 4

int main(int argc, char const *argv[])
{
	pid_t pid=1;
	int i=0, j;
	int fd;
	struct aiocb a;
	sigset_t sig_proc;
	int lect[NB_PROC];
	int sig;
		for(i=0; i<NB_PROC; i++){
			lect[i]=0;
}
	if((fd=open("./temp", O_RDWR|O_CREAT|O_TRUNC, 0600))==-1){
		perror("open");
		return EXIT_FAILURE;
	}


	for(i=0;i<NB_PROC && pid; i++){
		pid=fork();
	}
	if (pid){
		int res=0;
		for(i=0;i<NB_PROC && pid; i++){
			wait(NULL);
		}

		sigemptyset(&sig_proc);
		for(i=0; i<NB_PROC; i++){
			sigaddset(&sig_proc, SIGRTMIN+i);
		}
		sigprocmask(SIG_BLOCK, &sig_proc, 0);
		
		for(i=0; i<NB_PROC; i++){
			a.aio_fildes = fd;
			a.aio_buf = (int*) &lect[i];
			a.aio_nbytes = sizeof(int);
			a.aio_offset = i*sizeof(int);
			a.aio_reqprio = 0;
			a.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
			a.aio_sigevent.sigev_signo = SIGRTMIN+i;
			aio_read(&a);
			if(sigwait(&sig_proc, &sig)==-1){
			perror("sigwait");
			exit(1);
			}
			sigdelset(&sig_proc, sig);
			res+=lect[i];
		}
		printf("Le resultat final : %d\n",res);
		unlink("./temp");
		close(fd);
	}
	else {
		int randval;
		srand(time(NULL)*getpid());
		i--;
		sigemptyset(&sig_proc);
		sigaddset(&sig_proc, SIGRTMIN+i);
		sigprocmask(SIG_BLOCK, &sig_proc, 0);
		a.aio_fildes = fd;
		a.aio_buf = (int*) &randval;
		a.aio_nbytes = sizeof(int);
		a.aio_offset = i*sizeof(int);
		a.aio_reqprio = 0;
		a.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
		a.aio_sigevent.sigev_signo = SIGRTMIN+i;
		sleep(i);
		randval=(int)(10*(float)rand()/ RAND_MAX);
		aio_write(&a);
		printf("Moi j'envoie : %d\n", randval);
		if(sigwait(&sig_proc, &sig)==-1){
			perror("sigwait");
			exit(1);
		}
		close(fd);
	}
	return 0;
}