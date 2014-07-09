#include "../include/nfork.h"


int nfork (int number){
	int i=0;
	pid_t pid=getpid();
	for (i=0; i<number && pid!=0; i++){
		pid=fork();
	}
	if (pid==0){
		printf("Je suis le fils %d ,mon pere : %d\n", getpid(), getppid());
		return pid;
	}
	return i;
}