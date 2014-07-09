#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>

void receive_signal(int sig, siginfo_t* si, void* context);

void fork_child(int pos);

void bind_signal();
