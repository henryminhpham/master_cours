#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#define NPROC 10
#define delay 1000000

#define SNONE 0
#define SSLEEP 1
#define SRUN 2

char *top_stack; // top of all stack
int cur = -1; // current process

struct Tproc {
	int flag;
	jmp_buf buf;
	char stack[64356];
	size_t stack_size;
	int max_stack_size;
} proc[NPROC + 1] ; // l’entrée NPROC est utilisé pour sauvegarder le main

int mysetjmp(int idx)
{ 
  char end_stack;
  proc[idx].stack_size = top_stack - &end_stack;
  printf("Stack size %ld - from %ld to %ld\n", proc[idx].stack_size, top_stack, &end_stack);
  memcpy(proc[idx].stack, top_stack, proc[idx].stack_size);
  if(setjmp(proc[idx].buf) != 0) {
    memcpy(top_stack, proc[cur].stack, proc[cur].stack_size);
    return 1;
  }
  return 0;
}

void mylongjmp(int idx)
{
  cur = idx;
  longjmp(proc[cur].buf, 1);
}

int election(int old)
{
  int i = ++old;
  if(i >= NPROC) {
    i = 0;
  }
  while(proc[i].flag == SNONE){
    ++i;
  }
  return i;
}

void commut()
{
  int elu = election(cur);
  printf("Commutation !!! On passe de %d à %d\n", cur, elu);
  mysetjmp(cur);
  mylongjmp(elu);
}

void new_proc(int (*start) (char *), char* p)
{
  int i;
  for(i = 0 ; i < NPROC ; i++) {
    struct Tproc processus = proc[i];
    if(processus.flag == SNONE) {
      processus.flag = SSLEEP;
      if(mysetjmp(i) == 0) {
        start(p);        
      } 
      return;
    }
  }
}

int monProc(char *nom)
{
	int n = 0;
	int j;
	for (j = 0; j < 15; j++) {	// 20
		printf("%s : %d\n", nom, n++);
		usleep(500000);
		commut();
	}
	printf("Quit %s\n",nom);
	return 0;
}

int main()
{
	char tmp;
	top_stack = &tmp;
	new_proc(monProc, "p1");
	new_proc(monProc, "p2");
	printf("exit!!!\n");
	return 0;
}
