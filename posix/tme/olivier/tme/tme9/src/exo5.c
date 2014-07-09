#include "exo5.h"
#define XOPEN_SOURCE 700
#define PROCS 4
#define SIGNAL SIGRTMIN

int main(int argc, char** argv) {
  printf("Je suis le processus créateur de pid %d\n", getpid());
  fork_child(0);
  return EXIT_SUCCESS;	
}

void fork_child(int pos) {
  union sigval val; 
  if(pos < 0||pos >= PROCS) {
    //Dernier fils
    printf("Je suis %d\n", getpid());
    val.sival_int = 4; 
    // On envoie 
    if (sigqueue(getppid(), SIGNAL, val) == -1) {
      perror("sigqueue");
    }
    exit(0);
  }
  // On bind
  bind_signal();
  pid_t pid;
  // On crée le fils
  if(0 == (pid = fork())) {
    fork_child(++pos);
  }
  sigset_t sig;
  sigemptyset(&sig);
  sigaddset(&sig, SIGNAL);
  int value = 0;
  // On attend la réception du signal du fils
  sigwait(&sig, &value);
  printf("Je suis %d\n", getpid());
  // Si ce n'est pas le premier processus, on envoie un signal au père
  if(pos != 0) {
    val.sival_int = 4; 
    if (sigqueue(getppid(), SIGNAL, val) == -1) {
      perror("sigqueue");
    }
  }
  exit(0);
}

void receive_signal(int sig, siginfo_t* si, void* context) {
  // Inutile, sert juste à binder le signal
}

void bind_signal() {
  sigset_t sig;
  sigemptyset(&sig);
  struct sigaction action;
  action.sa_flags = SA_SIGINFO;
  action.sa_sigaction = receive_signal;
  action.sa_mask = sig;
  sigaction(SIGNAL, &action, 0);
}
