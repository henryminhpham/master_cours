#include <stdio.h>
#include <stdlib.h>

#include <synch.h>
#include <sched.h>
#include <proc.h>
#include <callo.h>

/**
 * @fn int tsleep(int pri, void *obs)
 * Permet au processus de s'endormir sur une ressource
 * @param pri : priorité au reveil
 * @param obs : ressource observée
 * @return rend 0
 */
int tsleep(int pri, void *obs) {
  struct proc rp = Tproc[GetElecProc()];	
  rp.p_flag = SLEEP;
  rp.p_pri = pri;      
  rp.p_ptr = obs;
  commut(NULL);
  return 0;
}

/**
 * @fn int twakeup(void *obs)
 * Permet au processus de reveiller l'ensemble des processus endormis sur une certaine ressource 
 * @param obs : ressource observée
 * @return rend -1 en cas d'erreur sinon 0
 */
int twakeup(void *obs) {
  int i, most_pri = 0;
  struct proc current_proc = Tproc[GetElecProc()];
  for(i = 0 ; i < MAXPROC ; i++) {
  	  struct proc new_proc = proc[i];
      if(new_proc.p_ptr == obs) {
        new_proc.ptr = NULL;
        new_proc.p_flag = RUN;
        if(current_proc.p_pri < new_proc.p_pri) {
          most_pri++;
        }
      }
  }
  if(most_pri > 0) {
    commut(NULL);
  }
  return 0;
}


/**
 * @fn int tsleep_time(int sec)
 * Permet au processus de s'endormir pendant une durée exprimée en seconde
 * @param sec : durée de l'endormissement
 * @return rend -1 en cas d'erreur sinon 0
 */
int tsleep_time(int sec) {
  
  int p = GetElecProc();
  
  if (p == -1) {
    fprintf(stderr,"sleep - no current process\n");
    exit(1);
  }
  
  printf("SLEEP(%d);\n\n", sec);
  fflush(stdout);
  
  timeout((void*)twakeup, &Tproc[p], sec*Ticks_par_sec); 
  tsleep(MAXUSERPRIO, &Tproc[p]);
  
  printf("SLEEP(%d)... reveil\n\n", sec);
  fflush(stdout);

  return 0;
}
