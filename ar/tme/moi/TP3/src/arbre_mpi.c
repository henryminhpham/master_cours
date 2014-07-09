#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define TAGINIT 0
#define NB_SITE 6

void simulateur(void) {
   int i;

   /* nb_voisins[i] est le nombre de voisins du site i */
   int nb_voisins[NB_SITE+1] = {-1, 2, 3, 2, 1, 1, 1};
   int min_local[NB_SITE+1] = {-1, 14, 11, 8, 4, 5, 17};

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



void calcul_min(int rang){
   MPI_Status status;
   int cpt=0;
   int nb_voisins;
   int voisins[3] = {0,0,0};
   int c_voisins[3];
   int min_local, recu;
   int i;

   /* RECEPTION DES PARAMETRES */

   MPI_Recv(&nb_voisins, 1, MPI_INT, MPI_ANY_SOURCE, TAGINIT, MPI_COMM_WORLD, &status);    
   MPI_Recv(voisins, nb_voisins, MPI_INT, MPI_ANY_SOURCE, TAGINIT, MPI_COMM_WORLD, &status);
   MPI_Recv(&min_local, 1, MPI_INT, MPI_ANY_SOURCE, TAGINIT, MPI_COMM_WORLD, &status);

   /*I NITIALISATION */

   for (i=0; i<3; i++)
      c_voisins[i]=voisins[i];

   /* DEROULEMENT */
   cpt = nb_voisins;
   if(nb_voisins==1){
      MPI_Send(&min_local, 1, MPI_INT, voisins[0], 1, MPI_COMM_WORLD);
   }

      /* BOUCLE PRINCIPALE*/

   while ( 1 ){

      MPI_Recv(&recu, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      cpt--;
      if( recu < min_local ){
         /* Comparing the value we received to the local minimum */
         min_local=recu;
      }

      if( status.MPI_TAG == 1 ){
         /* We are in the calcul cycle of the minimum of the tree (tag = 1)
         We pull the neigbour wihch sent the message off the list of neigbours (don't 
         worry, we have a copy of them..) */
         for (i=0; i<3; i++){
            if(voisins[i] == status.MPI_SOURCE){
               voisins[i]=-1;
            }
         }
         if( cpt== 1 ){
            /* Here the node (or leaf) only has one message left to receive from 
            his last neighbour, so he sends him a message and will wait for 
            his response */
            for (i=0; i<nb_voisins; i++)
               if(voisins[i] != -1)
                  MPI_Send(&min_local, 1, MPI_INT, voisins[i], 1, MPI_COMM_WORLD);
         }
         if( cpt == 0 ){
            /* Here we received the last message we needed to receive from all our 
            neighbours, the we become one of the two leaders and diffuse the smallest 
            number (announce) */
            printf("%d : Leader\n", rang);
            for (i=0; i<nb_voisins; i++){
               if(c_voisins[i] != -1) // Send to all his neighbours
                  MPI_Send(&min_local, 1, MPI_INT, c_voisins[i], 2, MPI_COMM_WORLD);
            }
            break;
         }
      }
      else if (status.MPI_TAG == 2 ){
         /* Here we received the announce from one of our neigbours containing 
         the least value of the tree, we can now maybe share to neighbours, then get out */
         printf("%d : Receieved annonce\n", rang);
         if (nb_voisins > 1)
            /*If we are not leaf, which means that we have somebody to share the 
            anounce */
            for (i=0; i<nb_voisins; i++){
               if((c_voisins[i] != -1) && c_voisins[i] != status.MPI_SOURCE) // Send to all his neighbours except the process which sent us the announce
                  MPI_Send(&min_local, 1, MPI_INT, c_voisins[i], 2, MPI_COMM_WORLD);
         }
         break;
      }
   }
   printf("%d : min local = %d\n", rang, min_local);
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
