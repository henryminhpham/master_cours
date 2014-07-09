#include "exo6.h"

static sigset_t add_signal();

const int GLOBAL_SIGNAL = SIGINT;

int main(int argc, char* argv[]) {
  // On vérifie qu'il y a un argument
  if(argc == 1) {
    perror("Vous devez spécifier un nombre de processus.\n");
    return EXIT_FAILURE;
  }
  // On convertit en nombre. Si c'est autre chose qu'un nombre,
  // atoi renverra 0 et sera considéré comme faux (aucun sens de vouloir créer 0 ici).
  char* number = argv[1];
  int real_number = atoi(number);
  if(real_number <= 0) {
    perror("Vous devez spécifier un nombre entier strictement positif en argument.\n");
    return EXIT_FAILURE;
  }
  // On crée un tableau qui stockera tous les pids et on met le pid du processus
  // courant. De plus, on ne stocke pas le ppid courant, l'énoncé dit que l'on doit
  // remonter jusqu'au processus initial. Le dernier processus n'affiche donc pas
  // le père du processus initial.
  pid_t pids[++real_number];
  pids[0] = getpid();
  // On démarre la récursivité
  fork_with_pid(0, real_number, pids);
  return EXIT_SUCCESS;
}

void fork_with_pid(int current, const int maximum, pid_t* pids) {
  // Condition d'arrêt, on a bouclé le maximum de fois, et donc créé "maximum" processus
  if(current >= maximum - 1) {
    int i;
    // On affiche tous les pids. Le pid courant a été donné par
    // le précédent fork, qui l'a mis dans le tableau.
    for(i = maximum - 1 ; i >= 0 ; i--) {
      printf("%d ", pids[i]);
    }
    printf("\n");
    // On est au dernier enfant, tous les parents attendent le signal.
    // On "remonte" la chaine en envoyant le signal.
    kill(getppid(), GLOBAL_SIGNAL);
    return;
  }
  sigset_t sig = add_signal();
  // On doit créer un fils
  pid_t new_pid;
  // On stocke le pid du fils
  new_pid = fork();
  if(new_pid == 0) {
    // Code exécuté par le fils. Il stocke son pid dans le tableau,
    // et ce de manière trié (puisque l'on incrémente à chaque fois, on remplit dans l'ordre 
    // ET on s'assure de ne pas boucler infiniment).
    pids[++current] = getpid();
    // On appelle de manière récursive. Si current == maximum -1 ici, alors on aura fini 
    // dès l'appel à cette méthode par la condition d'arrêt
    fork_with_pid(current, maximum, pids);
  } else {
    // Code exécuté par le père. On attend un signal pour continuer.
    sigsuspend(&sig);
    // Le père affiche le pid de son fils etc...
    printf("Fils %d - Courant %d - Père %d.\n", new_pid, getpid(), getppid());
    // On vérifie que ce n'est pas le processus initial. Celui-ci n'a pas à envoyer un signal
    // à son père
    if(current > 0) {
      // On continue de remonter la chaine. Si ce père n'est pas le processus initial
      // alors on doit remonter jusqu'au processus initial.
      kill(getppid(), GLOBAL_SIGNAL);
    }
  }
}

static sigset_t add_signal() {
 sigset_t sig;
 struct sigaction action;
 
 sigemptyset(&sig);
 
 action.sa_flags = 0;
 action.sa_mask = sig;
 action.sa_handler = execute_handler;
 sigaction(GLOBAL_SIGNAL, &action, 0);
 return sig;
}

void execute_handler(int signal) {
  
}