#include <stdlib.h>
#include <stdio.h>
#include "max_func.h"

int main(int argv, char* argc[]) {
    // On vérifie qu'il y a au moins un nombre
    if(argv <= 1) {
      perror("Vous devez spécifier un ensemble de nombres entiers. Si vous spécifiez autre chose qu'un entier, . Example : ./max_calcul 5 1 8 3\n");
      return (EXIT_FAILURE);
    }
    int size, max, i;
    char *p_conv = NULL;
    size = argv - 1;
    // On convertit le tableau de char* en int
    int vector[size];
    for(i = 1 ; i < argv ; i++) {
      char* number = argc[i];
      // Conversion de la chaine en entier
      int real_number = (int)strtol(number, &p_conv, 10);
      //TODO : Vérifier si c'est bien un nombre
      vector[i - 1] = real_number;
    }
    // On cherche le max
    max = max_func(vector, size);
    printf("Le maximum est : %d\n", max);
    return (EXIT_SUCCESS)	;
}