#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void fork_with_pid(int current, const int maximum, pid_t* pids);
