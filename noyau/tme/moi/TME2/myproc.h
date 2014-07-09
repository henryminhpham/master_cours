#ifndef __MYPROC
#define __MYPROC

#include <setjmp.h>

#define NB_PROC 25
#define PZERO 0
#define MRUN 1
#define MSLEEP 2
#define MRUNNABLE 3
#define MZOMB 4

int elu;


char* top_stack;
char* bottom_stack;



struct proc {
	int state;
	jmp_buf buf;
	char stack[65536];
	long unsigned int stacksize;
	int *wchan;
	int pri;
} Tproc[NB_PROC+1];


int mysetjmp( int );
void mylongjmp (int);
void new_proc( void (*f)(int), int arg );
int election( void );
void commut(int);
void alrm_handler(int);
void start_sched(void);

#endif