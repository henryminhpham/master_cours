#include "exo5.h"
#define NB_THREAD 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_t first;

int main(int argc, char** argv) {
  sigset_t sig;
  sigfillset(&sig);
  // On bloque tous les signaux
  sigprocmask(SIG_SETMASK, &sig, NULL);
  pthread_mutex_lock(&mutex);
  // On lance la chaine de création
  thread_exec(0);
  // On attend qu'elles soient toutes créées. La dernière thread fait un "signal"
  pthread_cond_wait(&cond, &mutex);
  // On print
  printf("Tous mes descendants ont été créés\n");
  pthread_mutex_unlock(&mutex);
  
  // On débloque SIGINT 
  sigdelset(&sig, SIGINT);
  // On modifie le masque
  sigprocmask(SIG_UNBLOCK, &sig, NULL);
  // On execute un handler dès la réception de SIGINT
  // Sinon le handler par défaut est de kill le processys
  struct sigaction action;
  action.sa_flags = 0;
  action.sa_handler = main_handler;
  action.sa_mask = sig;
  sigaction(SIGINT, &action, 0);
  // On attend le SIGINT
  sigsuspend(&sig);
  // Le handler se charge de réveiller les threads donc on attend la mort du premier fils
  // Les threads meurent du plus bas vers le plus haut, donc celui-ci est le dernier
  pthread_join(first, NULL);
  // On print
  printf("Tous mes descendants sont terminés\n");
  return EXIT_SUCCESS;
}

void* thread_exec(void* arg) {
  int cpt = (int) arg;
  // Si c'est la dernière thread
  if(cpt == NB_THREAD) {
    pthread_mutex_lock(&mutex);
    // On envoie un signal pour dire que toutes les threads sont créés
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    pthread_mutex_lock(&mutex);
    // On se bloque en attente d'un SIGINT. 
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
    printf("Je meurs\n");
    // On la tue
    pthread_exit((void*) 0);
  } else {
    // Si c'est un père on crée une nouvelle thread
    cpt++;
    pthread_t thread;
    if(pthread_create(&thread, NULL, thread_exec, (void*) cpt) != 0) {
      perror("Create thread");
      exit(1);
    }
    // Si la thread courante n'est pas le main, elle se bloque
    // en attendant la mort du fils
    if(cpt > 1) {
      pthread_join(thread, NULL);
      printf("Je meurs\n");
      pthread_exit((void*) 0);
    } else {
      // La thread main récupère son premier fils pour se bloquer dessus après le SIGINT
      first = thread;
    }
  }
  return NULL;
}

void main_handler(int signal) {
  // Exécuté lors d'un SIGINT, on réveille la dernière thread, qui va se
  // détruire, et réveillé son père et ainsi de suite jusqu'à la main.
  pthread_mutex_lock(&mutex);
  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutex);
}
