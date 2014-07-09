#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/**
 * Routine pour le signal SIGCONT
 */
void cont(int signal);

/**
 * Routine pour le signal SIGUSR1
 */
void usr1(int sig);

sigset_t create_signal(int signal);

void fork_with_pid(int current, const int maximum, pid_t* pids);

void kill_and_send(int send_usr1, pid_t* pids, int current);
