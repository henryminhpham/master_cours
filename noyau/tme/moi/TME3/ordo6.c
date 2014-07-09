#include "myproc.h"
#include "slp.h"
#include "callout.h"
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include <string.h>
#include <unistd.h>


#define init_sched() ({char var; top_stack = &var;})


void print_table(void){
	int i;
	for (i=0; i<NB_PROC; i++){
		printf("proc i : %d, state : %d\n",i, Tproc[i].state );
	}
}


int mysetjmp ( int idx ){
	if (idx > 26) {
		printf("Erreur de setjmp %d\n", idx);
		exit(-1);
	}
	char var;
	bottom_stack = &var;
	if (setjmp(Tproc[idx].buf) == 0){
		if(Tproc[idx].state==MRUN){
			Tproc[idx].state=MRUNNABLE;
		}
		Tproc[idx].stacksize = top_stack - bottom_stack;
		memcpy(Tproc[idx].stack, &var, Tproc[idx].stacksize);
		return 0;
	}
	else{
		Tproc[elu].state=MRUN;//Le proc est Running
		memcpy(top_stack-Tproc[elu].stacksize, Tproc[elu].stack, Tproc[elu].stacksize);
		return 1;
	}
}

void mylongjmp ( int idx ){
	elu=idx;
	longjmp(Tproc[idx].buf,1);
}

void f(int arg){
	long n=arg;
	while(1){
		printf("execut F n= %ld\n", n);
		sleep(1);
		n++;
		if (n==12){
			twakeup(&cond);
		}
	}
}

void g(int arg){
	long m=1000+arg;
	while(1){
		printf("execute G, m=%ld O\n", m);
		sleep(1);
		m++;
		if(m==1003)
			tsleep(&cond,18);
	}
}

void h(int arg){
	long m=5000+arg;
	while(1){
		printf("execute H m=%ld Z\n", m);
		sleep(1);
		m++;
	}
}



void new_proc( void (*f)(int), int arg ){
	int i;
	for (i=0; i<NB_PROC; i++){
		if (Tproc[i].state==0){
			Tproc[i].state=MRUNNABLE;
			if (mysetjmp(i)==0){
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
	int i, max_pri=-1, who=-1;
	for (i=0; i<NB_PROC; i++){
		if(i!=elu){
			if (Tproc[i].state==MRUNNABLE){//Le proc est r'U'nnable
				if(Tproc[i].pri>max_pri){
					max_pri=Tproc[i].pri;
					who=i;
				}
			}
		}
	}
	if(who>=0)
		return who;
	else 
		return 25;
}


void commut(int no){
	printf("Commut\n");
	int next;
	if(!no){
		if(mysetjmp(elu)==0){
			next=election();
			Tproc[next].state=MRUNNABLE;
			mylongjmp(next);
		}
		else{
			return;
		}
	}
	printf("Processus %d fini\n", elu);
	mylongjmp(election());
}



void alrm_handler (int sig){
	alarm(1);
	clock();
	commut(0);
}

void start_sched( void ){
	signal(SIGALRM, alrm_handler);
	alarm(4);
	elu=-1;
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