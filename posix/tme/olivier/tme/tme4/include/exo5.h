#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void process(int NB_PCS);

void wait_barrier(int NB_PCS);