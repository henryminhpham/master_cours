#include "exo6.h"
#define XOPEN_SOURCE 700
#define PROCS 4

static void bind_signal();

int random_value = 0;

int main(int argc, char** argv) {
  bind_signal();
  int i;
  for(i = 0 ; i < PROCS ; i++) {
    fork_child();
  }
  for(i = 0 ; i < PROCS ; i++) {
    wait(0);
  }
  printf("J'ai reçu %d\n", random_value);
  return EXIT_SUCCESS;	
}

void fork_child() {
  pid_t pid;
  if((pid = fork()) == -1) {
    perror("Fork");
    exit(1);
  }
  // Si c'est le père on sort
  if(pid != 0) return;
  
  union sigval val; 

  int random_val = (int) (10 * (float)rand()/ RAND_MAX);
  // On envoie le random
  printf("Je suis %d et j'envoie %d\n", getpid(), random_val);
  val.sival_int = random_val; 
  if (sigqueue(getppid(), SIGRTMIN, val) == -1) {
    perror("sigqueue");
  }
  exit(0);
}

void receive_signal(int sig, siginfo_t* si, void* context) {
  // On calcule le random
  int random = si->si_value.sival_int;
  random_value += random;
}

static void bind_signal() {
  sigset_t sig;
  sigemptyset(&sig);
  struct sigaction action;
  action.sa_flags = SA_SIGINFO;
  action.sa_sigaction = receive_signal;
  action.sa_mask = sig;
  sigaction(SIGRTMIN, &action, 0);
}
