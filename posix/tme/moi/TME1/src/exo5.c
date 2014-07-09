#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define _POSIX_SOURCE 700


void signal_P1_handler(int sig){
	pid_t mypid = getpid();
	printf("%d : On m'a appelé, le signal : %d\n", mypid, sig);
	if (sig == SIGUSR1){
		printf("%d : Ok P2, tu es créé\n", mypid);
	}
	if (sig == SIGUSR2){
		printf("%d : Ok P1, P2 est mort, RIP petit-fiston\n", mypid);
	}
	return;
}



int main(int argc, char const *argv[])
{



	int i=0, N=2;
	pid_t pid=0;
	pid_t* procs=malloc(N*sizeof(pid_t));

	printf("Processus pere : %d\n\n", getpid());


	while (i<N && pid==0){
		
		procs[i]=getpid();
		sleep(1);
		pid=fork();
		if(!pid){
			i++;
		}
	}

	printf("Proc : %d , i : %d\n",getpid(), i);
	if (pid){ 

		if (i==0){ 
			signal(SIGUSR1, signal_P1_handler);
			signal(SIGUSR2, signal_P1_handler);
		}
		wait(NULL);
		if (i==1) {
			kill(procs[0], SIGUSR2); 
			exit(0);
		}
		if(i==0){
			printf("%d : P1 est mort, RIP fiston\n", getpid());
			printf("%d : Je peux partir\n", getpid());
			exit(0);
		}
	}
	sleep(1);
	kill(procs[0],SIGUSR1);
	return 0;
}