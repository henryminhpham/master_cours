#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void* Producteur(void* arg);

void* Consommateur(void* arg);

int Pop();

void Push(int c);