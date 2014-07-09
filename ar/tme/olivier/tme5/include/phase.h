#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAGINIT 0
#define NB_SITE 6

#define DIAMETRE 5

#define MAX_VOISINS 2
#define min(a,b) ((a > b) ? b : a)

void calcul_min(int rank);

void __phase_on_receive(int rank);

int __phase_send(int rank);

void __init_phase();
