#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define _POSIX_SOURCE 700

int main(int argc, char const *argv[])
{
	int i,res, N=3;
	pid_t pid=0;
	pid_t* procs=malloc(N*sizeof(pid_t));
	int status;

printf("Processus pere : %d\n\n", getpid());


	for (i=0 ; i<N && pid==0 ; i++){
		sleep(1);
		printf("%d : Je suis vivant !\n", getpid());
		procs[i]=getpid();
		pid=fork();
	}


	if (pid){
		printf("%d : J'ai créé %d, j'attends..\n", getpid(), pid);
		res=wait(&status);


		printf("status : %d\n",WEXITSTATUS(status));
		sleep(1);
		printf("%d : Mon fils %d est mort\n", getpid(),res);

		if (getpid()==procs[0]){
			printf("Valuer de status : %d, proc %d\n", status, getpid());
			exit(0);
		}


		exit(WEXITSTATUS(status));

	}
	else{
		if(i==N){
			printf("Liste des Processus créés : ");
			for(i=0;i<N;i++){
				printf("%d ",procs[i]);
			}
			printf("\n");
			status=20;
			exit(status);

		}
	}
	return 0;

}