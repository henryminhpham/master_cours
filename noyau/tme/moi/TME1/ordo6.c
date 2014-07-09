#include "myproc.h"
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include <string.h>
#include <unistd.h>

int elu=-1;


char* top_stack;
char* bottom_stack;

#define init_sched() ({char var; top_stack = &var;})


void commut(int);




int mysetjmp ( int idx ){
	if (idx > 26) {
		printf("Erreur de setjmp %d\n", idx);
		exit(-1);
	}
	char var;
	bottom_stack = &var;
	// printf("top : %p, bottom : %p, idx : %d\n", top_stack, bottom_stack, idx);
	if (setjmp(Tproc[idx].buf) == 0){
		Tproc[idx].state=MRUNNABLE;
		Tproc[idx].stacksize = top_stack - bottom_stack;
		memcpy(Tproc[idx].stack, &var, Tproc[idx].stacksize);
		// printf("proc idx: %lu\n", Tproc[idx].stacksize);
		return 0;
	}
	else{
		// printf("Je passe par la aussi, elu : %d\n", elu);
		memcpy(top_stack-Tproc[elu].stacksize, Tproc[elu].stack, Tproc[elu].stacksize);
		return 1;
	}
}

void mylongjmp ( int idx ){
	elu=idx;
	// printf("Je passe par la\n");
	Tproc[idx].state=MRUN;//Le proc est Running 
	longjmp(Tproc[idx].buf,1);
}

void f(int arg){
	long n=arg;
	while(1){
		sleep(1);
		n++;
		// sleep(1);
		printf("execut F n= %ld\n", n);
	}
}

void g(int arg){
	long m=1000+arg;
	while(1){
		sleep(1);
		m++;
		printf("execute G, m=%ld O\n", m);
	}
}

void h(int arg){
	long m=5000+arg;
	while(1){
		sleep(1);
		m++;
		printf("execute H m=%ld Z\n", m);
	}
}



void new_proc( void (*f)(int), int arg ){
	int i;
	for (i=0; i<NB_PROC; i++){
		// printf(" state : %d\n", Tproc[i].state);
		if (Tproc[i].state==0){
			// printf("i : %d\n",i);
			if (mysetjmp(i)==0){
				// printf("test\n");
				return;
			}
			else{
				(*f)(arg);
				Tproc[elu].state=MZOMB;
				commut(1);
			}
		}
	}
}

int election(void){
	int idx=elu;
	int flag=0;
	while (1){
		idx++;
		if (Tproc[idx].state==MRUNNABLE){//Le proc est r'U'nnable
			return idx;
		}
		if (idx==24){
			if(flag){
				return 25;
			}
			idx=-1; //-1 pour pouvoir re-passer à 0 au debut de la boucle
			flag=1;
		}
	}
	return 0;
}


void commut(int no){
	if(!no){
		if(mysetjmp(elu)==0){
			mylongjmp(election());
		}
		else{
			return;
		}
	}
	printf("Processus %d fini\n", elu);
	mylongjmp(election());
}



void alrm_handler (int sig){
	alarm(4);
	commut(0);
}

void start_sched( void ){
	signal(SIGALRM, alrm_handler);
	alarm(1);

	if(mysetjmp(25)==0){
		mylongjmp(election());
	}
	else{
		return;
	}
}



int main(int argc, char const *argv[])
{
	init_sched();
	char foo;
	new_proc(f,0);
	new_proc(g,0);
	new_proc(h,0);
	start_sched();
	printf("EXTINCTION DES FEUX\n");

	return 0;
}