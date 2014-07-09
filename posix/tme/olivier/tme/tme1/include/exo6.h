#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void fork_with_pid(int current, const int maximum, pid_t* pids);

void execute_handler(int signal);