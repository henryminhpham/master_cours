#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <ctype.h>

void* thread_action(void* args);

void convert_file(char* file);

int has_file();