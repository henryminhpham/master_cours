#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define TAGINIT  0
#define TAGEXEC  1

#define NB_SITE  6
#define DIAMETRE 5

#define SIMULATEUR 0
#define INITIATEUR 1

#define min(a, b)  (a) < (b) ? (a) : (b)  

void simulateur(void);

int can_send(void);

void __init_phase(void);

void calcul_min(int rang);
