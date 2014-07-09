#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


#define _POSIX_SOURCE 700




void traitersignal (int sig){
	printf("%d : Mon fils m'a envoye le signal %d, je me tue donc.\n",getpid(), sig);
	kill(getppid(), SIGUSR1);
	exit(0);
}


int main(int argc, char const *argv[])
{


	int i=0, N=24;
	pid_t pid=0;
	pid_t* procs = malloc (N*sizeof(pid_t));

	while (i<N && pid==0){
		
		procs[i]=getpid();
		pid=fork();
		if(!pid){
			i++;
		}
	}


	if (pid){
		signal(SIGUSR1, traitersignal);
		pause();
	}

	printf("Liste des Processus créés : ");
	for(i=0;i<N;i++){
		printf("%d ",procs[i]);
	}
	printf("\n");
	kill(getppid(),SIGUSR1);
	return 0;
}