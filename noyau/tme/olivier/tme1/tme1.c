#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <signal.h>
#include "tme1.h"

// pointeur du bas de la pile
char *top_stack;
// id du processus elu
int elu = 0;

// structure de sauvegarde dd'un processus
struct Tproc {
  jmp_buf buff; // buffer de sauvegarde
  char stack[2048];// pile sauvegardée
  unsigned int  stack_size;// taille de la pile
  int flagi;// vaut 1 si le proc est "vivant", 0 sinon
} proc [5];

void commut (int no) {
  printf("========== execution de commut\n");
  int old = elu;
  printf ("----- Commutation vers la fonction %d\n", no);
  elu = no;
  if (mysetjmp(old) == 0)
    mylongjmp (elu);
}

// ELECTION
int election () {
  printf("========== execution de election\n");
  printf("----- elu actuel : %d\n", elu);
  int res = elu + 1;
  while (proc[res].flagi != 1) {
    printf("----- testing : %d\n", res);
    res = (res + 1) % 5;
  }
  printf("----- election de : %d\n", res);
  return res;
}

// ALARM HANDLER
void alarm_handler (int no) {
  printf("========== execution de alarm_handler\n");
  alarm (1);
  commut (election());
}

void init_sched () {
printf("========== execution de init_sched\n");
  // initialisation du stack pointer
  char var;
  top_stack = &var;
  // redefinition du handler pour le signal SIGALRM
  signal (SIGALRM, alarm_handler);
}

// MY SET JUMP
int mysetjmp (int idx) {
  printf("========== execution de mysetjmp %d\n", idx);
  if (sigsetjmp(proc[idx].buff, 3) == 0) {
    proc[idx].stack_size = (long)top_stack - (long)&idx;
    memcpy (proc[idx].stack, &idx, proc[idx].stack_size);
    return 0;
  } else {
    memcpy (top_stack - proc[elu].stack_size, proc[elu].stack, proc[elu].stack_size);
    return 1;
  }
}

// MY LONG JUMP
int mylongjmp (int idx) {
  printf("========== execution de mylongjmp %d\n", idx);
  elu = idx;
  siglongjmp (proc[elu].buff, 3);
}

// NEW PROC
void new_proc (void (*f)(int), int arg) {	
  printf("========== execution de new_proc\n");
  if (mysetjmp(arg) != 0) {
    f(arg);
    printf("%d a fini\n",arg);
    proc[arg].flagi = 0;
    commut (election());
  } else {
    proc[arg].flagi = 1;
  }
}

// START SCHED
void start_sched () {
  printf("========== execution de start_sched\n");
  alarm(1);
  commut (election());
}

void dummy_function (int arg) {
  int fin = (arg+2) * 2;
  int i = 0;

  while (i < fin) {
    printf ("\n\tje suis la fonction : %d | passage #%d/%d\n\n", arg, i++, fin);
    sleep (1);
  }
}

/************************************/
//							MAIN
/**********************************/

int main (int argc, char **argv) {
	init_sched ();
	
	void (*f1)(int);
	void (*f2)(int);
	void (*f3)(int);
	
	f1 = dummy_function;
	f2 = dummy_function;
	f3 = dummy_function;
	
	new_proc (f1, 0);
	new_proc (f2, 1);
	
	start_sched();
	
	printf ("FIN\n");
	
	return 0;
}
