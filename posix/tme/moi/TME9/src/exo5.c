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


#define NB_PROC 4

int main(int argc, char const *argv[])
{
	pid_t pid=0;
	int i, sig;
	sigset_t sig_proc;
	union sigval s;
	s.sival_int=0;
	s.sival_ptr=NULL;
	for(i=0; i<NB_PROC && pid==0; i++){
		pid = fork();
	}
	if(pid){
		sigemptyset(&sig_proc);
		sigaddset(&sig_proc, SIGRTMIN);
		sigprocmask(SIG_BLOCK, &sig_proc, 0);
		if(sigwait(&sig_proc, &sig)==-1){
			perror("sigwait");
			exit(1);
		}
		printf("i : %d\n",i-1);
		if(i-1>0)
			sigqueue(getppid(), SIGRTMIN, s);
	}
	else{
		if(i==NB_PROC){
			printf("i : %d\n", i);
			sigqueue(getppid(), SIGRTMIN, s);
		}
	}
	return 0;
}