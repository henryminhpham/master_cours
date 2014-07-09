#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define _POSIX_SOURCE 700



int done;
pid_t pid;

void traiter_signal (int sig){
	if (!done){
		printf("Mon fils s'est stoppé, je me stoppe\n");
		kill(getpid(), SIGSTOP);
	}
	return;
}


void traiter_signal_pere (int sig){
	if(!done){
		printf("Tous les fils sont stoppés je ressucite mon premier fils\n");
		done=1;
		kill(pid, SIGCONT);
		return;
	}
	else{
		kill(getpid(), SIGCONT);
	}

}


int main(int argc, char const *argv[])
{
	int i=0, N=3;
	while (i<N && pid==0){
		pid=fork();
		if(!pid){
			i++;
		}
	}
	if (i==0){
		signal(SIGCHLD, traiter_signal_pere);
		pause();
	}
	if (pid){
		signal(SIGCHLD, traiter_signal);
		pause();
		done=1;
		printf("Je suis ressucité, je te ressucite fils !\n");
		kill(pid, SIGCONT);
		printf("Je me termine\n");
		return EXIT_SUCCESS;

	}
	printf("Je me stoppe \n");
	kill(getpid(), SIGSTOP);
	return EXIT_SUCCESS;
}