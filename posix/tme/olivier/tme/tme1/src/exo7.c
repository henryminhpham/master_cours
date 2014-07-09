#include "exo7.h"

pid_t new_pid;
int usr1_cpt = 0;

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
    perror("Vous devez spécifier un nombre entier en argument.\n");
    return EXIT_FAILURE;
  }
  sigset_t sig = create_signal(SIGUSR1);
  // On crée un tableau qui stockera tous les pids et on met le pid du processus
  // courant. De plus, on ne stocke pas le ppid courant, l'énoncé dit que l'on doit
  // remonter jusqu'au processus initial. Le dernier processus n'affiche donc pas
  // le père du processus initial.
  pid_t pids[++real_number];
  pids[0] = getpid();
  // On démarre la récursivité
  fork_with_pid(0, real_number, pids);
  // On attend de recevoir 2 SIGUSR1 pour stopper le processus
  sigsuspend(&sig);
  sigsuspend(&sig);
  return EXIT_SUCCESS;
}

void fork_with_pid(int current, const int maximum, pid_t* pids) {
  // Condition d'arrêt, on a bouclé le maximum de fois, et donc créé "maximum" processus
  if(current >= maximum - 1) {
    // On kill le processus courant et ICI on envoie un SIGUSR1 au processus initial
    // pour dire qu'ils sont tous stoppés
    kill_and_send(1, pids, current);
    int i;
    // On affiche tous les pids. Le pid courant a été donné par
    // le précédent fork, qui l'a mis dans le tableau.
    for(i = maximum - 1 ; i >= 0 ; i--) {
      printf("%d ", pids[i]);
    }
    printf("\n");
    // On envoie un SIGUSR1 au processus initial pour dire que tout le monde
    // est réveillé
    kill(pids[0], SIGUSR1);
    // Vu que l'on utilise pas de wait, on kill le processus courant manuellement
    exit(EXIT_SUCCESS);
  }
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
    // Code exécuté par le père.
    if(current > 0){
      // Tous les pères hormis le premier doivent avoir un handler pour le SIGCONT
      // Le handler permettra de réveiller le fils du processus courant. Donc le processus initial
      // n'en a pas besoin car il en est notifié par le SIGUSR1 du dernier processus, et le dernier processus
      // ne réveille personne, puisqu'il n'a pas de fils.
      create_signal(SIGCONT);
      // On kill le processus courant
      kill_and_send(0, pids, current);
      // On garde le principe de l'exercice 4, pour l'affichage. On affiche pids[current - 1] au lieu de
      // getppid car le père peut être mort avant le fils, et on affichera le pid 1 (à cause du rattachement),
      // plutôt que le PID de "l'ancien" père. Simple problème de synchro car pas de wait. Afficher l'ancien
      // père est juste un choix personnel.
      printf("Fils %d - Courant %d - Père %d.\n", new_pid, getpid(), pids[current - 1]);
      // Vu que l'on utilise pas de wait, on kill le processus courant manuellement
      exit(EXIT_SUCCESS);
    }
  }
}


void cont(int signal) {
  // On réveille fils. Cette méthode ne peut pas être appelé
  // par le dernier fils.
  kill(new_pid, SIGCONT);
}

void usr1(int sig) {
  // Si on reçoit le premier SIGUSR1
  if(usr1_cpt == 0) {
    // On s'assure de ne pas revenir ici
    usr1_cpt++;
    // On sleep pour s'assurer que le dernier fils est kill avant de réveiller tout le monde.
    // Cela est moche (voir le README)
    sleep(1);
    // On affiche le message demandé et le message de l'exercice 4
    printf("Tous les descendants sont suspendus.\nFils %d - Courant %d - Père %d.\n", new_pid, getpid(), getppid());
    // On réveille le premier fils
    cont(SIGCONT);
  } else {
    // Le programme est fini au 2ème SIGUSR1
    printf("Fin du programme.\n");
  }
}

sigset_t create_signal(int signal) {
  sigset_t sig;
  struct sigaction action;
  
  sigemptyset(&sig);
  action.sa_flags = 0;
  action.sa_mask = sig;
  if(signal == SIGUSR1) {
    action.sa_handler = usr1;
  } else if(signal == SIGCONT) {
    action.sa_handler = cont;
  } 
  sigaction(signal, &action, NULL);
  return sig;
} 

void kill_and_send(int send_usr1, pid_t* pids, int current) {
  // On kill le processus courant.
  // Si c'est le dernier on envoie un SIGUSR1 avant
  // pour dire que tout le monde est kill (cela est spécifié dans le README).
  printf("Je me tue %d\n", pids[current]);
  if(send_usr1) {
    kill(pids[0], SIGUSR1);
  }
  kill(pids[current], SIGSTOP);
}