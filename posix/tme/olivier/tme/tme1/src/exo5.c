#include "exo5.h"

static const int FIRST = SIGUSR1;
static const int SECOND = SIGUSR2;

/**
 * Pour cet exercice, j'ai fais le choix de passer par l'utilisation de 2 signaux. 
 * Une autre manière de faire aurait été d'utiliser un simple compteur (ou autre), néanmoins
 * en utilisant deux signaux distincts, on s'assure de la bonne réception de ceux-ci. Il s'agit
 * d'un choix personnel.
 */
int main(void) {
  sigset_t sig_proc;
  struct sigaction action;
  
  // On attend tous les signaux de type SIGUSR1 et SIGUSR2
  sigfillset(&sig_proc);
  sigdelset(&sig_proc, FIRST);
  sigdelset(&sig_proc, SECOND);
  
  // On configure le handler 
  action.sa_flags = 0;
  action.sa_handler = execute;
  action.sa_mask = sig_proc;
  // On bind SIGUSR1 et SIGUSR2 
  sigaction(FIRST, &action, 0);  
  sigaction(SECOND, &action, 0);  
  
  pid_t init = getpid();
  if(fork() == 0) {
    if(fork() == 0) {
      // On envoie le premier signal pour signaler la création
      // de P3
      kill(init, FIRST);
    } else {
      // On attend que P3 soit mort. Logiquement, P1 a du recevoir le signal
      // de P3 (création)
      wait(NULL);
      // On envoie le second signal pour signaler la mort de P3
      kill(init, SECOND);
    }
  } else {
    // On attend la réception de 2 signaux (pour les 2 messages)
    sigsuspend(&sig_proc);
    sigsuspend(&sig_proc);
    // On s'assure que P1 n'a plus de fils pour réaliser l'affichage
    // de la mort de P2.
    wait(NULL);
    printf("Processus P2 terminé.\n");
  }
  return EXIT_SUCCESS;
}

/**
 * Fonction appelée lors de la réception d'un signal du type spécifié
 */
void execute(int signal) {
  if(signal == FIRST) {
   printf("Processus P3 créé.\n");
  } else if(signal == SECOND) {
   printf("Processus P3 terminé.\n");
  }
}