#include "max_func.h"
#include <stdlib.h>
#include <stdio.h>

int max_func(int vector[], int size) {
  register int i;
  // On assigne comme maximum la première valeur du tableau
  // Si le tableau n'a qu'un élément, c'est bien le max sinon
  // on parcourt le tableau pour le trouver.
  int max = vector[0];
  for(i = 1 ; i < size ; i++) {
    if(max < vector[i]) {
      max = vector[i];
    }
  }
  return max;
}
