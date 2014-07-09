#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_SITE 6
#define TAGINIT 0
#define DOWN 1
#define UP 2

// On considère que le noeud initiateur est le noeud numéro 2
#define INITIATEUR 2
#define is_initiateur(rank) (rank == INITIATEUR)
#define min(a,b) ((a) > (b)) ? (b) : (a)

void calcul_min(int rang);

// Démarrage 
void __init_echo(int rang);

// Les méthodes du noeud initiateur
void __initiateur_send(void);
void __initiateur_recv(void);
void __initiateur_decide(int rang);

// Les méthodes des noeuds non initiateur
void __not_initiateur_send(int rang);
void __not_initiateur_recv();

// Méthodes d'affichage
void __initiateur_print_informations(int rang);
void __not_initiateur_print_informations(int rang);