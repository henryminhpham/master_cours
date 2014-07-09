#include "phase.h"

int nb_voisins_in, nb_voisins_out;
int *voisins_in, *voisins_out;
int minimum;
int msend, *mrecv;
int fin;

void simulateur(void) {
  int i;

  /* nb_voisins_in[i] est le nombre de voisins entrants du site i */
  /* nb_voisins_out[i] est le nombre de voisins sortants du site i */
  int nb_voisins_in[NB_SITE+1] = {-1, 2, 1, 1, 2, 1, 1};
  int nb_voisins_out[NB_SITE+1] = {-1, 2, 1, 1, 1, 2, 1};

  int min_local[NB_SITE+1] = {-1, 4, 7, 1, 6, 2, 9};

  /* liste des voisins entrants */
  int voisins_in[NB_SITE+1][2] = {{-1, -1},
				  {4, 5}, {1, -1}, {1, -1},
				  {3, 5}, {6, -1}, {2, -1}};
                               
  /* liste des voisins sortants */
  int voisins_out[NB_SITE+1][2] = {{-1, -1},
				   {2, 3}, {6, -1}, {4, -1},
				   {1, -1}, {1, 4}, {5,-1}};

  for(i=1; i<=NB_SITE; i++){
    MPI_Send(&nb_voisins_in[i], 1, MPI_INT, i, TAGINIT, MPI_COMM_WORLD);    
    MPI_Send(&nb_voisins_out[i], 1, MPI_INT, i, TAGINIT, MPI_COMM_WORLD);    
    MPI_Send(voisins_in[i], nb_voisins_in[i], MPI_INT, i, TAGINIT,
	     MPI_COMM_WORLD);    
    MPI_Send(voisins_out[i], nb_voisins_out[i], MPI_INT, i, TAGINIT,
	     MPI_COMM_WORLD);    
    MPI_Send(&min_local[i], 1, MPI_INT, i, TAGINIT, MPI_COMM_WORLD); 
  }
}

int can_send(void) {
  int i;

  if (msend > DIAMETRE)
    return 0;
  
  for (i=0; i<nb_voisins_in; i++)
    if (mrecv[i] < msend)
      return 0;
  return 1;
}

void __init_phase(void) {
  int i;
  MPI_Status status;
  
  MPI_Recv(&nb_voisins_in, 1, MPI_INT, SIMULATEUR , TAGINIT,
	   MPI_COMM_WORLD, &status);
  voisins_in = malloc(sizeof(int) * nb_voisins_in); 

  MPI_Recv(&nb_voisins_out, 1, MPI_INT, SIMULATEUR , TAGINIT,
	   MPI_COMM_WORLD, &status);
  voisins_out = malloc(sizeof(int) * nb_voisins_out);

  MPI_Recv(voisins_in, nb_voisins_in, MPI_INT, SIMULATEUR , TAGINIT,
	   MPI_COMM_WORLD, &status);

  MPI_Recv(voisins_out, nb_voisins_out, MPI_INT, SIMULATEUR , TAGINIT,
	   MPI_COMM_WORLD, &status);

  MPI_Recv(&minimum, 1, MPI_INT, SIMULATEUR , TAGINIT,
	   MPI_COMM_WORLD, &status);

  mrecv = malloc(sizeof(int) * nb_voisins_in); 
  for (i=0; i<nb_voisins_in; i++)
    mrecv[i] = 0;
  msend = 0;
  fin = 0;
}

void calcul_min(int rang) {
  MPI_Status status;
  int i, minrecv;

  __init_phase();

  if (rang == INITIATEUR) {
    for (i=0; i<nb_voisins_out; i++)
      MPI_Send(&minimum, 1, MPI_INT, voisins_out[i], TAGEXEC, MPI_COMM_WORLD); 
    msend++;
  }


  while (!fin) {
    MPI_Recv(&minrecv, 1, MPI_INT, MPI_ANY_SOURCE, TAGEXEC,
	     MPI_COMM_WORLD, &status);
    minimum = min(minimum, minrecv);
    for(i=0; i<nb_voisins_in; i++) 
      if (voisins_in[i] == status.MPI_SOURCE)
	mrecv[i]++;
    
    if (can_send()) {
      for (i=0; i<nb_voisins_out; i++)
	MPI_Send(&minimum, 1, MPI_INT, voisins_out[i], TAGEXEC,
		 MPI_COMM_WORLD); 
      msend++;
    }
    if (msend > DIAMETRE) {
      printf("[%d] Le minimum est %d\n", rang, minimum);
      fin = 1;
    }
  }
  
}

int main (int argc, char* argv[]) {
  int nb_proc,rang;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);

  if (nb_proc != NB_SITE+1) {
    printf("Nombre de processus incorrect !\n");
    MPI_Finalize();
    exit(2);
  }
  
  MPI_Comm_rank(MPI_COMM_WORLD, &rang);
  
  if (rang == SIMULATEUR) {
    simulateur();
  } else {
    calcul_min(rang);
  }
  
  MPI_Finalize();
  return 0;
}
