#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define min(a,b) ((a) > (b)) ? (b) : (a)

#define TAGINIT 0
#define TAGRESPONSE 1
#define NB_SITE 6

int nb_voisin, minimum, msg_recv;
int final_min;
int* voisins;
int* didrecv;
int last, fin, a_envoye;

void simulateur(void) {
  int i;

  /* nb_voisins[i] est le nombre de voisins du site i */
  int nb_voisins[NB_SITE+1] = {-1, 2, 3, 2, 1, 1, 1};
  int min_local[NB_SITE+1] = {-1, 3, 11, 8, 14, 5, 17};

  /* liste des voisins */
  int voisins[NB_SITE+1][3] = {{-1, -1, -1},
			       {2, 3, -1}, {1, 4, 5}, 
			       {1, 6, -1}, {2, -1, -1},
			       {2, -1, -1}, {3, -1, -1}};
                               
  for(i=1; i<=NB_SITE; i++){
    MPI_Send(&nb_voisins[i], 1, MPI_INT, i, TAGINIT, MPI_COMM_WORLD);    
    MPI_Send(voisins[i],nb_voisins[i], MPI_INT, i, TAGINIT, MPI_COMM_WORLD);
    MPI_Send(&min_local[i], 1, MPI_INT, i, TAGINIT, MPI_COMM_WORLD); 
  }
}


void decide(int rang) {
  int i;
  printf("[%d] est decideur. Le minimum trouvé est %d\n", rang, final_min);

  // On envoie un message à tous le monde sauf le dernier émetteur
  for(i=0; i<nb_voisin; i++)
    if(voisins[i] != last) 
      MPI_Send(&final_min, 1, MPI_INT, voisins[i], TAGRESPONSE, MPI_COMM_WORLD);
  fin = 1;
}

void recoit(int rang) {
  MPI_Status status;
  int flag, i;
  
  // On vérifie que l'on a reçu un message
  MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
  if (!flag)
    return;
  
  // On récupère le message et on incrémente le nombre de messages reçus
  MPI_Recv(&minimum, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
  msg_recv++;
  // On stocke le dernier envoyé et on fait le minimum
  last =  status.MPI_SOURCE;
  final_min = min(final_min, minimum);
  
  // Si on a reçu un INIT, on note qui l'a envoyé
  if (status.MPI_TAG == TAGINIT) {
    for(i=0; i<nb_voisin; i++) {
      if(status.MPI_SOURCE == voisins[i]) {
	didrecv[i] = 1; // On met à vrai le processus qui nous a envoyé le message
      }
    }
    // Si on a reçu N messages, on décide. Le processus courant est donc décideur
    if(msg_recv == nb_voisin) {
      decide(rang);
    }
  } else {
    printf("[%d] n'est pas décideur. Le minimum trouvé est %d.\n", rang, final_min);
    // On envoie à tout le monde une réponse avec le minimum trouvé, sauf à l'émetteur
    for(i=0; i<nb_voisin; i++) 
      if(voisins[i] != last) {
	MPI_Send(&final_min, 1, MPI_INT, voisins[i], TAGRESPONSE, MPI_COMM_WORLD);
      }
    fin = 1;
  }
}


void envoie() {
    int i, sd;
    // On vérifie que l'on peut envoyer. 
    if (msg_recv < nb_voisin-1 || a_envoye)
      return;
  
    // On cherche le voisin qui n'a rien envoyé
    for(i=0; i<nb_voisin; i++) {
      if(didrecv[i] == 0)
	sd = voisins[i];
    }
    // Et on lui envoie le minimum que l'on a trouvé
    MPI_Send(&final_min, 1, MPI_INT, sd, TAGINIT, MPI_COMM_WORLD);
    a_envoye = 1;
  }

void calcul_min(int rang) {
    MPI_Status status;
    // Initialisation des valeurs
    MPI_Recv(&nb_voisin, 1, MPI_INT, MPI_ANY_SOURCE, TAGINIT, MPI_COMM_WORLD,
	     &status);
    voisins = malloc(nb_voisin * sizeof(int));
    MPI_Recv(voisins, nb_voisin, MPI_INT, MPI_ANY_SOURCE, TAGINIT,
	     MPI_COMM_WORLD, &status);
    MPI_Recv(&minimum, 1, MPI_INT, MPI_ANY_SOURCE, TAGINIT, MPI_COMM_WORLD,
	     &status);
    
    // On met tous les messages reçus ) 0
    int i;
    didrecv = malloc(sizeof(int)*nb_voisin);
    for(i=0; i<nb_voisin;i++)
      didrecv[i] = 0;
    
    last = -1;
    msg_recv = 0;
    fin = 0;
    a_envoye = 0;
    final_min = minimum;
    // On lance jusqu'à la fin
    while (!fin) {
      recoit(rang);
      envoie();
    }
  }
  int main (int argc, char* argv[]) {
    int nb_proc, rang;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);

    if (nb_proc != NB_SITE+1) {
      printf("Nombre de processus incorrect !\n");
      MPI_Finalize();
      exit(2);
    }
  
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);
  
    if (rang == 0) {
      simulateur();
    } else {
      calcul_min(rang);
    }
  
    MPI_Finalize();
    return 0;
  }
