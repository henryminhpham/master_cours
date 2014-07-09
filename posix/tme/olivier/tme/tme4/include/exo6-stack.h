#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <signal.h>

void* Producteur(void* arg);

void* Consommateur(void* arg);

int Pop();

void Push(int c);

void init();

void destroy();

void P();

void V();