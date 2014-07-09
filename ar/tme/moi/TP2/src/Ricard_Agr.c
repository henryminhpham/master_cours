#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define REQUESTING 1
#define NON_DEMANDEUR 0
#define EN_SC 2
#define request 3
#define ack 4
#define fin 5

typedef struct lolo{  
  int mes_type;
  int hor;
  int id; 
}msg;

int nb_ack_i=0, date_req=0, h_i=0, etat=0, myrank, size, indic=0;
msg* file;

int max(int a, int b){
  if(a<b)
    return b;
  return a;
}

void Update_horloge(int* mon_horloge, int horloge_rec){
  /*Modification de l'horloge à la réception d'un message*/
  int mh=*(mon_horloge);
  *(mon_horloge) = max(mh, horloge_rec) + 1;  
  return;
}

int comp_horloge(int p1, int p2, int h1, int h2){

  if (h1==h2){
    if (p1<p2)
      return 1;
    else
      return 0;
  }

  if (h1<h2)
    return 1;
  else
    return 0;
}

void attendre_message(void){
  int h_j;
  MPI_Status status;

  while(etat!=EN_SC){
    MPI_Recv(&h_j, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    Update_horloge(&h_i, h_j);
    switch (status.MPI_TAG){

    case request:
      if( (etat==NON_DEMANDEUR) || ((etat == REQUESTING) && (comp_horloge(myrank, status.MPI_SOURCE, date_req, h_j)))){
        h_i++;
        MPI_Send(&h_i, 1, MPI_INT, status.MPI_SOURCE, ack, MPI_COMM_WORLD);
      }
      else{
        file[indic].mes_type=request;
        file[indic].hor=h_i;
        file[indic].id=status.MPI_SOURCE;
        indic++;
      }   
      // printf("%d received req from %d\n", myrank, status.MPI_SOURCE);
      break;

    case ack:
      nb_ack_i--;
      if(nb_ack_i == 0){
        etat=EN_SC;
      }
      // printf("%d received ack from %d\n", myrank, status.MPI_SOURCE);
      break;

    case fin:
      break;

    default:
      break;           
    }
  }
  // printf("sortie de while\n");
  return ;
}


void release_SC(void){
  h_i++;
  int i;
  for(i=0;i<indic; i++){
    // printf("test\n");
    MPI_Send(&file[i].hor, 1, MPI_INT, file[i].id, ack, MPI_COMM_WORLD);
  }
  etat=NON_DEMANDEUR; 
  indic=0;
}

void request_SC(){

  int i;
  /*Réception */
  etat=REQUESTING;
  h_i++;
  date_req=h_i;
  nb_ack_i=size-1;

  for(i=0; i<size; i++)
    if(i!=myrank)
      MPI_Send(&h_i, 1, MPI_INT, i, request, MPI_COMM_WORLD);
  attendre_message();
  // printf("La, ça plante. (?)\n");
}


int main(int argc, char* argv[]){
 
  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  file=malloc(sizeof(msg)*size);
 
  /*Je demande la SC*/
  while (1){
    srand(time(NULL)*getpid());
    request_SC();
    printf("%d : je suis en SC youhou youhou youh yuyo PI\n", myrank);
    sleep(rand()%3);
    release_SC();
  }

  MPI_Finalize();

  return 0;

}
