#include "exo1.h"
#define XOPEN_SOURCE 700
// On considère N = (5 - 0), donc on ne définit pas de MIN MAX
#define N 5

int main(int argc, char** argv) {
  int i;
  int politique;
  struct sched_param sp;
  pid_t pid;
  for(i = 0 ; i < N ; i++) {
    pid = fork();
    if(pid == 0) {
      // On récupère la politique
      if((politique = sched_getscheduler(0)) == -1) {
        perror("Get scheduler");
        return EXIT_FAILURE;
      }  
      // On modifie la politique d'ordonnancement
      if(politique != SCHED_FIFO) {
        // On met tous les processus à la priorité min
        sp.sched_priority = sched_get_priority_min(SCHED_FIFO);
        if(-1 == sched_setscheduler(0, SCHED_FIFO, &sp)) {
          perror("Set scheduler");
          return EXIT_FAILURE;
        }
      }
      // Le dernier processus a la priorité la plus haute
      sp.sched_priority += i;
      // On met à jour la priorité
      sched_setparam(0, &sp);
      // On force un réordonnancement
      sched_yield();
      printf("fils %d -- pid %d\n", i, getpid());
      return EXIT_SUCCESS;
    }
  }
  for(i = 0 ; i < N ; i++) {
    wait(0);
  }
  return EXIT_SUCCESS;
}