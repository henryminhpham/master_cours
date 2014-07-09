#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_rand(void* info);

void wait_barrier(int N);
