#include "myproc.h"
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include <string.h>
#include <unistd.h>

int elu;


char* top_stack;
char* bottom_stack;

#define init_sched() ({char var; top_stack = &var;})



int mysetjmp ( int idx ){
	if (idx > 24) {
		printf("Erreur de setjmp\n");
		exit(-1);
	}
	char var;
	bottom_stack = &var;
	printf("top : %p, bottom : %p, size : %lu\n", top_stack, bottom_stack, top_stack - bottom_stack);
	if (setjmp(Tproc[idx].buf) == 0){
		Tproc[idx].state='S';
		Tproc[idx].stacksize = top_stack - bottom_stack;
		memcpy(Tproc[idx].stack, &var, Tproc[idx].stacksize);
		printf("proc idx: %lu\n", Tproc[idx].stacksize);
		return 0;
	}
	else{
		printf("Je passe par la aussi, elu : %d\n", elu);
		memcpy(top_stack-Tproc[elu].stacksize, Tproc[elu].stack, Tproc[elu].stacksize);
		return 1;
	}
}

void mylongjmp ( int idx ){
	elu=idx;
	printf("Je passe par la\n");
	Tproc[idx].state='R';
	longjmp(Tproc[idx].buf,1);
}

void f(int){
	int n=0;
	int p=12;
	while(1){

		printf("Execute f: %d\n", n++);
		sleep(1);
		if (mysetjmp(1)==0){
			mylongjmp(2);
		}
	}
}

void g(){
	int m=1000;
	while(1){
		printf("Execute g: %d\n", m++);
		sleep(1);
		if(mysetjmp(2)==0){
			mylongjmp(1);
		}
	}
}




int main(int argc, char const *argv[])
{
	init_sched();
	char testt;
	int test=12;
	if ((test=mysetjmp(2))==0){
		printf("Passe dans test\n");
		f();
	}
	else{
		printf("Je ne passe par la\n");
		g();
	}
	printf("test : %d\n", test);
	printf("Erreur\n");
	return 0;
}