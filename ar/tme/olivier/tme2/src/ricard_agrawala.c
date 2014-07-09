#include <unistd.h>
#include "mpi_server.h"

#define MAX_CS 3

#define REQ 1
#define ACK 2
#define FIN 3

#define REQUESTING 0
#define NOT_REQUESTING 1
#define SC 2

#define max(a, b)  (a) < (b) ? (b): (a)

static int nb_ack;
static int clck, time_ask;
static int size, rank, fin, state;
static int *queue;
static int nb_queue;

static pthread_cond_t cwait  = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mwait  = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t synchro  = PTHREAD_MUTEX_INITIALIZER;

static pthread_cond_t cfin  = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mfin  = PTHREAD_MUTEX_INITIALIZER;

void sendm(int dst, int type) {
  pthread_mutex_lock(get_mtx());
  MPI_Send(&clck, 1, MPI_INT, dst, type, MPI_COMM_WORLD);
  pthread_mutex_unlock(get_mtx());
}

void enterCS() {
  // Demande d'entrée en section critique
  int i;
  pthread_mutex_lock(&synchro);
  clck++; // On incrémente l'horloge
  nb_ack = 0; // On remet le nombre d'acquittements reçus à 0
  time_ask = clck; // On stocke l'envoi
  state = REQUESTING; // On passe à l'état REQUESTING
  pthread_mutex_unlock(&synchro);
  printf("[%d] - Demande de section critique.\n", rank);
  // On envoie un REQ à tous les autres processus
  for (i=0; i<size; i++) {
    if (i == rank)
      continue;
    sendm(i, REQ);
  }
  // On attend que les processus envoient un ACK
  pthread_mutex_lock(&mwait);
  pthread_cond_wait(&cwait, &mwait);
  pthread_mutex_unlock(&mwait);
  printf("[%d] - Entrée en section critique.\n", rank);
  pthread_mutex_lock(&synchro);
  // On entre en section critique
  state = SC;
  pthread_mutex_unlock(&synchro);
}

void exitCS() {
  int i;
  // On sort de la section critique
  printf("[%d] - Sortie de la section critique.\n", rank);
  // On envoie un ACK à tous les processus en attente
  for (i=0; i<nb_queue; i++)
    sendm(queue[i], ACK); 
  
  // On vide la queue
  nb_queue = 0;
  time_ask = -1;
  // On change notre état
  state = NOT_REQUESTING;
}

void callback(int tag, int source) {
  int msg;
  MPI_Status status;
  pthread_mutex_lock(&synchro);
  pthread_mutex_lock(get_mtx());
  MPI_Recv(&msg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
  pthread_mutex_unlock(get_mtx());
  // On met à jour notre horloge avec la valeur reçue
  clck = max(clck, msg) + 1;

  switch (tag) {
  case REQ:
    /* Si on reçoit une demande, on envoie un ACK que si :
     *  - On est en NOT_REQUESTING
     *  - Si la demande est antérieure à la notre, il passe avant
     *  - Si les 2 demandes sont identiques, on le laisse passer si son rank est plus petit que le notre
     */
    if (state == NOT_REQUESTING ||
	msg < time_ask || 
       (msg == time_ask && source < rank)) {
      // On envoie un ACK et on incrémente l'horloge
      clck++;
      sendm(source, ACK);
    } else 
      // On le met dans la file d'attente si l'on est plus "prioritaire"
      queue[nb_queue++] = source;
    break;
    
  case ACK:
    // On incrémente le nombre d'ACK reçu
    nb_ack++; 
    // Si tous les processus ont envoyé un ACK, on peut passer en SC
    if (nb_ack == size-1) {
      pthread_mutex_lock(&mwait);
      pthread_cond_signal(&cwait);
      pthread_mutex_unlock(&mwait);
    }
    break;
  case FIN:
    fin++;
    // Si tous les processus (et nous) avons envoyé un FIN, on peut kill le processus courant
    if(fin == size) {
      pthread_mutex_lock(&mfin);
      pthread_cond_signal(&cfin);
      pthread_mutex_unlock(&mfin);
    } 
    break;
  default:
    printf("ERROR\n");
  }
  pthread_mutex_unlock(&synchro);
}

int main(int argc, char **argv) {
 int provide = 0;
 int i;

 MPI_Init_thread(&argc, &argv, MPI_THREAD_SERIALIZED, &provide);
 pthread_mutex_lock(get_mtx());
 MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 MPI_Comm_size(MPI_COMM_WORLD, &size);
 pthread_mutex_unlock(get_mtx());
 init_server(callback);
 /* init global variable */
 clck = 0;
 time_ask = -1;
 queue = malloc(sizeof(int) * size-1);
 nb_ack = 0;  
 state = NOT_REQUESTING;
 nb_queue = 0;
 fin = 0;
 /* -------------------- */
 for (i=0; i<MAX_CS; i++) {
   // On enchaine DEMANDE - ENTREE - SORTIE
   enterCS();
   sleep(1);
   exitCS();
 } 
 // Lorsque l'on a fini, on envoie un fin à tous les processus (et nous)
 for (i=0; i< size; i++)
    sendm(i, FIN);

 printf("[%d] - En attente de la fin des autres processus.\n", rank);
 pthread_mutex_lock(&mfin);
 // On attend d'avoir reçu tous les FIN
 pthread_cond_wait(&cfin, &mfin);
 pthread_mutex_unlock(&mfin);
 printf("[%d] - Fin du processus.\n", rank);
 destroy_server();
 MPI_Finalize();
 return EXIT_SUCCESS;
}
