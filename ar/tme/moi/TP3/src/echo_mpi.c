#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

/* TAG DEFINITIONS */
#define TAGINIT 0
#define UP 1
#define DOWN 2


#define NB_SITE 6

void simulateur(void) {
   int i;

   /* nb_voisins[i] est le nombre de voisins du site i */
   int nb_voisins[NB_SITE+1] = {-1, 3,3,2,3,5,2};
   int min_local[NB_SITE+1] = {-1, 12, 11, 1, 4, 5, 2};

   /* liste des voisins */
   int voisins[NB_SITE+1][5] = {{-1, -1,-1,-1,-1},
         {2, 5, 3, -1, -1}, {1, 4, 5, -1, -1}, 
         {1, 5, -1}, {6, 2, 5, -1, -1},
         {1, 2, 6, 4, 3}, {4, 5, -1, -1, -1}};
                               
   for(i=1; i<=NB_SITE; i++){
      MPI_Send(&nb_voisins[i], 1, MPI_INT, i, TAGINIT, MPI_COMM_WORLD);    
      MPI_Send(voisins[i],nb_voisins[i], MPI_INT, i, TAGINIT, MPI_COMM_WORLD);
      MPI_Send(&min_local[i], 1, MPI_INT, i, TAGINIT, MPI_COMM_WORLD); 
   }
}

void echo_min (int rang){
   int i;
   int min_local=0;
   int nb_voisins;
   int *voisins;
   int *c_voisins;
   int val_recue;
   int *recu;
   int fils[7] = {-1, 0, 0, 0, 0, 0, 0};
   int pere=0;
   int cpt;
   MPI_Status status;

   /* RECEPTION DES PARAMETRES */

   MPI_Recv(&nb_voisins, 1, MPI_INT, MPI_ANY_SOURCE, TAGINIT, MPI_COMM_WORLD, &status);    

   voisins = (int*) malloc(nb_voisins*sizeof(int));
   c_voisins = (int*) malloc(nb_voisins*sizeof(int));
   recu = (int*) malloc(nb_voisins*sizeof(int));

   MPI_Recv(voisins, nb_voisins, MPI_INT, MPI_ANY_SOURCE, TAGINIT, MPI_COMM_WORLD, &status);

   for(i=0; i<nb_voisins; i++){
      c_voisins[i] = voisins[i];
   }

   MPI_Recv(&min_local, 1, MPI_INT, MPI_ANY_SOURCE, TAGINIT, MPI_COMM_WORLD, &status);

   /* DEROULEMENT */

   if (rang == 1){


      /* Noeud initiateur */
      for(i=0; i<nb_voisins; i++){
         MPI_Send(&min_local, 1, MPI_INT, voisins[i], DOWN, MPI_COMM_WORLD);
      }
      cpt=0;
      while ( 1 ){
         MPI_Recv(&val_recue, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);


         if(val_recue < min_local){
            min_local = val_recue;
         }

         for(i=0; i<nb_voisins; i++){
            if(voisins[i] == status.MPI_SOURCE){
               recu[i] = 1;
            }
         }

         
         if ( status.MPI_TAG == UP ){
            fils[status.MPI_SOURCE]=1;
/*            printf("received : %d\n", val_recue);
            cpt++;
            if (cpt==nb_voisins)
            {
               break;
            }*/
         }

         for(i=0; i<nb_voisins; i++){
            if(recu[i]==1){
               cpt++;
            }
         }
         /*if(cpt == nb_voisins){
            break;         
         }*/
      }
      printf("The smallest value is : %d\n", min_local);
   }

   else{
      /* Noeud non-initiateur */
      while(1){
         cpt = 0;
         MPI_Recv(&val_recue, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
         printf("%D received : %d from %d\n", rang, val_recue, status.MPI_SOURCE);


         if(val_recue < min_local)
            min_local=val_recue;



         for(i=0; i<nb_voisins; i++){
            if(voisins[i] == status.MPI_SOURCE){
               recu[i] = 1;
            }
         }


         if (pere == 0){
            pere = status.MPI_SOURCE;
            printf("father %d : %d\n",rang, pere );
            for(i=0; i<nb_voisins; i++){
               if(voisins[i] != status.MPI_SOURCE){
                  MPI_Send(&min_local, 1, MPI_INT, voisins[i], DOWN, MPI_COMM_WORLD);
               }
            }         
         }

         for(i=0; i<nb_voisins; i++){
            if(recu[i]==1){
               cpt++;
            }
         }
         if(cpt == nb_voisins){
            MPI_Send(&min_local, 1, MPI_INT, pere, UP, MPI_COMM_WORLD);
         }
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
  
   if (rang == 0) {
      simulateur();
   } 
   else {
      echo_min(rang);
   }
  
   MPI_Finalize();
   return 0;
}
