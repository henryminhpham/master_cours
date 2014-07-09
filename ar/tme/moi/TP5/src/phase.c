#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define TAGINIT 0
#define NB_SITE 6
#define INITIATEUR 1


#define DIAMETRE 5	/* !!!!! valeur a initialiser !!!!! */

void simulateur(void) {
   int i;

   /* nb_voisins_in[i] est le nombre de voisins entrants du site i */
   /* nb_voisins_out[i] est le nombre de voisins sortants du site i */
   int nb_voisins_in[NB_SITE+1] = {-1, 2, 1, 1, 2, 1, 1};
   int nb_voisins_out[NB_SITE+1] = {-1, 2, 1, 1, 1, 2, 1};

   int min_local[NB_SITE+1] = {-1, 4, 7, 4, 6, 2, 9};

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
      MPI_Send(voisins_in[i], nb_voisins_in[i], MPI_INT, i, TAGINIT, MPI_COMM_WORLD);    
      MPI_Send(voisins_out[i], nb_voisins_out[i], MPI_INT, i, TAGINIT, MPI_COMM_WORLD);    
      MPI_Send(&min_local[i], 1, MPI_INT, i, TAGINIT, MPI_COMM_WORLD); 
   }
}


void calcul_min (int rang){
   int *voisins_in, *voisins_out, nb_voisins_in, nb_voisins_out, min_local, *received, sent=0;
   int i;
   MPI_Status status;

   /* INIT */
   MPI_Recv(&nb_voisins_in, 1, MPI_INT, MPI_ANY_SOURCE, TAGINIT, MPI_COMM_WORLD, &status);   
   MPI_Recv(&nb_voisins_out, 1, MPI_INT, MPI_ANY_SOURCE, TAGINIT, MPI_COMM_WORLD, &status);   
   voisins_in = (int*)malloc(nb_voisins_in*sizeof(int));
   voisins_out = (int*)malloc(nb_voisins_out*sizeof(int));
   received = (int*)malloc(nb_voisins_in*sizeof(int));
   for (i=0; i<nb_voisins_in; i++){
      received[i] = 0;
   }
   MPI_Recv(voisins_in, nb_voisins_in, MPI_INT, MPI_ANY_SOURCE, TAGINIT, MPI_COMM_WORLD, &status);
   MPI_Recv(voisins_out, nb_voisins_out, MPI_INT, MPI_ANY_SOURCE, TAGINIT, MPI_COMM_WORLD, &status);
   MPI_Recv(&min_local, 1, MPI_INT, MPI_ANY_SOURCE, TAGINIT, MPI_COMM_WORLD, &status);
   printf("Simulator receptions done.\n");
   /*End INIT*/



   if (rang == INITIATEUR){
      for(i=0; i<nb_voisins_out; i++){
         MPI_Send(&min_local, 1, MPI_INT, voisins_out[i], 2, MPI_COMM_WORLD); 
      }
   }
   int flag=1, val_recu, cpt=0;


   while(1){
      cpt=0;
      flag=1;
      printf("%d : recu\n",rang);

      MPI_Recv(&val_recu, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      if(val_recu < min_local){
         min_local = val_recu;
      }
      for (i=0; i<nb_voisins_in; i++){
         if(voisins_in[i] == status.MPI_SOURCE){
            received[i]++;
         }
      }
      for (i=0; i<nb_voisins_in; i++){
         if (received[i] < sent){
            flag=0;
            break;
         }
         if(received[i] >= DIAMETRE){
            cpt++;
         }
      }
      if(flag){
         for(i=0; i<nb_voisins_out; i++){
            MPI_Send(&min_local, 1, MPI_INT, voisins_out[i], 2, MPI_COMM_WORLD); 
         }
         sent++;
      }
      if(cpt == nb_voisins_in){
         break;
      }
   }
   printf("%d : min = %d\n", rang, min_local);
   free(voisins_out);
   free(voisins_in);
   free(received);
   return;
}



/******************************************************************************/

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
  
   if (rang == 0) {
      simulateur();
   } else {
      calcul_min(rang);
   }
  
   MPI_Finalize();
   return 0;
}
