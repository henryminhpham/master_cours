#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>

void* thread_exec(void* arg);

void main_handler(int signal);