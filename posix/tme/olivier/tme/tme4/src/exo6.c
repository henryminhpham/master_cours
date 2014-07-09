#include "exo6-stack.h"
#define SVID_SOURCE 1

static void handler();

static void act(int act);

int main(int argc, char** argv) {
  // On crée un handler pour vider les IPC lors du SIGINT
 handler();
 // On crée toutes les structures
 init();
 
 // On lance un producer dans un autre processus
 if(fork() == 0) {
  Producteur(NULL);  
  // Au cas ou, on vide (mais inutile en soit)
  act(SIGINT);
 }
 // On lance le consumer
 Consommateur(NULL);
 // On vide les ressources malgré tout
 wait(NULL);
 return EXIT_SUCCESS;
}

static void handler() {
  sigset_t sig;
  struct sigaction action;
  sigemptyset(&sig);
  
  action.sa_flags = 0;
  action.sa_mask = sig;
  action.sa_handler = act;
  sigaction(SIGINT, &action, 0);
}

static void act(int act) {
  // Lors du SIGINT, on détruit toutes les IPC
  destroy();
  exit(EXIT_SUCCESS);
}