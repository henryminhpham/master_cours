#include "exo7.h"
#define XOPEN_SOURCE 700
#define PROCS 4

static void bind_signal();

int barriere = 0;
pid_t pids[PROCS];

int main(int argc, char** argv) {
  bind_signal();
  int i;
  for(i = 0 ; i < PROCS ; i++) {
    fork_child();
  }
  for(i = 0 ; i < PROCS ; i++) {
    wait(0);
  }
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
  val.sival_int = getpid(); 
    // On envoie un signal au père et on se bloque
  if (sigqueue(getppid(), SIGRTMIN, val) == -1) {
    perror("sigqueue");
  }
  // blocage
  process(0);
  exit(0);
}

// Méthode apelée par les fils
void process (int NB_PCS) {
    printf ("avant barrière\n");
    wait_barrier (NB_PCS);
    printf ("après barrière\n");
    exit (0);
}

void wait_barrier(int NB_PCS) {
  sigset_t sig;
  sigemptyset(&sig);
  sigaddset(&sig, SIGRTMIN);
  int wait = 0;
  sigwait(&sig, &wait);
}

void receive_signal(int sig, siginfo_t* si, void* context) {
  // On récupère le pid du fils a débloqué
  pids[barriere++] = si->si_value.sival_int;
  // Si tous les fils ont envoyés un signal, on débloque
  if(barriere >= PROCS) {
    int i;
    for(i = 0 ; i < PROCS ; i++) {
       union sigval val; 
       val.sival_int = 0;
       // On envoie un signal à chaque fils pour le débloquer
       if (sigqueue(pids[i], SIGRTMIN, val) == -1) {
          perror("sigqueue");
      }
    }
  }
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
