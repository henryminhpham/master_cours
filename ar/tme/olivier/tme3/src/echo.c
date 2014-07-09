#include "echo.h"

int final_min;  // Le minimum calculé petit à petit
int minimum;    // Le minimum du noeud courant

int father;     // Le père du noeud courant
int* voisins;   // Les voisins du noeud courant
int nb_voisins; // Le nombre de voisins du noeud courant

int nb_children;// Nombre de fils (juste informatif afin d'afficher la topologie)
int* children;  // Les fils (juste informatif afin d'afficher la topologie)

static void simulateur(void) {
   int i;

   /* nb_voisins[i] est le nombre de voisins du site i */
   int nb_voisins[NB_SITE+1] = {-1, 3, 3, 2, 3, 5, 2};
   int min_local[NB_SITE+1] = {-1, 12, 11, 8, 14, 5, 17};

   /* liste des voisins */
   int voisins[NB_SITE+1][5] = {{-1, -1, -1, -1, -1},
            {2, 5, 3, -1, -1}, {4, 1, 5, -1, -1}, 
            {1, 5, -1, -1, -1}, {6, 2, 5, -1, -1},
            {1, 2, 6, 4, 3}, {4, 5, -1, -1, -1}};
                               
   for(i=1; i<=NB_SITE; i++){
      MPI_Send(&nb_voisins[i], 1, MPI_INT, i, TAGINIT, MPI_COMM_WORLD);    
      MPI_Send(voisins[i], nb_voisins[i], MPI_INT, i, TAGINIT, MPI_COMM_WORLD);    
      MPI_Send(&min_local[i], 1, MPI_INT, i, TAGINIT, MPI_COMM_WORLD); 
   }
}

void __init_echo(int rang) {
  MPI_Status status;
  // On considère que le noeud initiateur est son propre père.
  // Cela simplement pour économiser du code
  father = (is_initiateur(rang)) ? rang : -1;
  voisins = malloc(sizeof(int) * 6);
  children = malloc(sizeof(int) * 6);
  memset(children, -1, sizeof(int) * 6);
  nb_children = 0;
  MPI_Recv(&nb_voisins, 1, MPI_INT, MPI_ANY_SOURCE, TAGINIT, MPI_COMM_WORLD, &status);
  MPI_Recv(voisins, sizeof(voisins), MPI_INT, MPI_ANY_SOURCE, TAGINIT,MPI_COMM_WORLD, &status);
  MPI_Recv(&minimum, 1, MPI_INT, MPI_ANY_SOURCE, TAGINIT,MPI_COMM_WORLD, &status);
  final_min = minimum;
  
}

void calcul_min(int rang) {
  // On initialise
  __init_echo(rang);
  // Le noeud initiateur envoie à tous ses voisins un message
  if(is_initiateur(rang)) {
    __initiateur_send();
    __initiateur_recv();
    __initiateur_decide(rang);
  } else {
    // Les noeuds non initiateurs passent ici
    __not_initiateur_recv();
    __not_initiateur_send(rang);
  }
}

void __not_initiateur_send(int rang) {
  // On envoie au père le minimum calculé
  MPI_Send(&final_min, 1, MPI_INT, father, UP, MPI_COMM_WORLD);
  __not_initiateur_print_informations(rang);
}

void __not_initiateur_recv() {
  int tmp_min, i = 0;
  MPI_Status status;
  // On attend le message du père
  MPI_Recv(&tmp_min, 1, MPI_INT, MPI_ANY_SOURCE, DOWN, MPI_COMM_WORLD, &status);
  // On calcule le minimum entre le père et le noeud courant
  final_min = min(minimum, tmp_min);
  father = status.MPI_SOURCE;
  // On envoie un message à tout le monde sauf le père
  for(i = 0 ; i < nb_voisins ; i++) {
    // On n'envoie rien au père
    if(voisins[i] == father) {
      continue;
    }
    // Si on n'a plus de voisins, on a fini
    if(voisins[i] == -1) {
      break;
    }
    // On envoie à un potentiel fils un message
    MPI_Send(&minimum, 1, MPI_INT, voisins[i], DOWN, MPI_COMM_WORLD);
  }
  // On attend la réponse des voisins
  for(i = 0 ; i < nb_voisins ; i++) {
    // On n'envoie rien au père
    if(voisins[i] == father) {
      continue;
    }
    // Si on n'a plus de voisins, on a fini
    if(voisins[i] == -1) {
      break;
    }
    MPI_Recv(&tmp_min, 1, MPI_INT, voisins[i], MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    final_min = min(minimum, tmp_min);
    if(status.MPI_TAG == UP) {
      children[nb_children++] = status.MPI_SOURCE;
    }
  } 
}

void __initiateur_send() {
  int i = 0;
  while(i < nb_voisins && voisins[i] != -1) {
    // On envoie à tous les voisins notre minimum
    MPI_Send(&minimum, 1, MPI_INT, voisins[i], DOWN, MPI_COMM_WORLD);       
    i++;
  }  
}

void __initiateur_recv() {
  int i = 0;
  int tmp_minimum;
  MPI_Status status;
  while(i < nb_voisins && voisins[i] != -1) {
    // Le noeud initateur ne peut recevoir que des messages de ses enfants. On les ajoute.
    MPI_Recv(&tmp_minimum, 1, MPI_INT, voisins[i], UP, MPI_COMM_WORLD, &status);       
    // On recalcule le nouveau minimum
    final_min = min(final_min, tmp_minimum);
    children[nb_children++] = status.MPI_SOURCE;
    i++;
  }  
}

void __initiateur_decide(int rang) {
  // La décision se résume à faire de l'affichage
  __initiateur_print_informations(rang);
}


void __initiateur_print_informations(int rang) {
  int i;
  printf("[%d] Je suis un décideur. Le minimum est %d. Mes enfants sont : ", rang, final_min);
  for(i = 0 ; i < nb_children ; i++) {
    printf("\"%d\"", children[i]);
    if(i < (nb_children - 1)) {
      printf(" - ");
    }
  }  
  printf("\n");
}

void __not_initiateur_print_informations(int rang) {
  int i;
  printf("[%d] Je ne suis pas un décideur. Le minimum est %d. Mon père est %d.", rang, final_min, father);
  if(nb_children == 0) {
    printf(" Je n'ai pas d'enfants.");
  } else {
    printf(" Mes enfants sont : ");
    for(i = 0 ; i < nb_children ; i++) {
      printf("\"%d\"", children[i]);
      if(i < (nb_children - 1)) {
        printf(" - ");
      }
    }  
  }
  printf("\n");
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
   } else {
      calcul_min(rang);
   }
  
   MPI_Finalize();
   return 0;
}
