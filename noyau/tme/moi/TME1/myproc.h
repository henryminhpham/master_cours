#include <setjmp.h>

#define NB_PROC 25
#define PZERO 0
#define MRUN 0
#define MSLEEP 1
#define MRUNNABLE 2
#define MZOMB 3



struct proc {
	int state;
	jmp_buf buf;
	char stack[65536];
	long unsigned int stacksize;
	int *p_wchan;
} Tproc[NB_PROC+1];

