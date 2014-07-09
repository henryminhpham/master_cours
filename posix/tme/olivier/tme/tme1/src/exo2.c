#include "exo2.h"

int main(int arg, char* argv[]) {
  int p;
  int i = 1;
  int N = 3;
  do {
    p = nfork(i);
    if(p != 0) {
      printf("%d \n", p);
    }
  }while((p == 0) && (++i <= N));
  printf("FIN\n");
  return 1;
}
/*
 * 0 (print 1)
 * 	1
 * 		2
 * 			4 5 6
 * 		3
 * 			7 8 9
 * 
 * 
 */


int nfork(int nb_fils) {
  // On renvoie 0 si aucun fils n'a été créé
  if(nb_fils < 0) {
    return -1;
  }
  int children = 0;
  int i;
  pid_t child;
  // On crée nb_fils
  for(i = 0 ; i < nb_fils ; i++) {
    child = fork();
    if(child == 0) {
      // Si c'est le code du fils, on renvoie 0
      return 0;
    } else if(child == -1) {
      perror("Erreur dans la création d'un fils.\n");
      // Si on a créé aucun fils, on doit renvoyer -1
      if(children == 0) {
	return -1;
      } 
      // Sinon on renvoie le nombre de fils créés.
      return children;
    } else {
      // Le père augmente le nombre d'enfants créés.
      children++;
    }
  }
  return children;
}