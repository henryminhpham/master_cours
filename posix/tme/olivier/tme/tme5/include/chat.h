#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/mman.h>    
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <semaphore.h>
#include <signal.h>
#include <pthread.h>

/*
 * Taille de la requête et le nombre maximum de clients simultanés
 */
#define REQUEST_SIZE 1024
#define MAX_CLIENT 10

/*
 * Message de connexion, déconnexion, texte pur
 */ 
#define CONNEXION 0
#define MESSAGE 1
#define DECONNEXION 2

/*
 * Type de retour des méthodes d'envois et de réception de messages
 */
#define VALID_MESSAGE 0
#define ERROR_TYPE -1

/*
 * Une requête
 */
struct request {
    long type;
    char content[REQUEST_SIZE];
};

/*
 * Définit toutes les informations relatives à la connexion.
 */
typedef struct connexion_data {
  char server_name[REQUEST_SIZE]; // Nom du serveur
  int shm; // identifiant du segment mémoire
  char semaphore_name[REQUEST_SIZE]; // Nom du sémpahore serveur
  sem_t* sem; // Sémaphore du serveur
  sem_t* sem_client; // Sémaphore du client
}connexion_data;

/*
 * Le nom par défaut des sémaphores créés par les clients
 */
const char* SEM_CLIENT_NAME = "sem_client";

/*
 * Initialise l'ensemble des données (connexion_data, ...) et des structures.
 */
int pre_construct(char* argv);

/*
 * Coupe le programme. Appelée par un SIGINT, elle ferme et détruit toutes les ressources partagées
 */
void stop(int sig);

/*
 * Démarre le programme
 */
void start();

/*
 * Gère la connexion. Le client utilise cette méthode pour envoyer une demande de connexion et le serveur
 * pour traiter une demande de connexion.
 */
int connexion(struct request req);

/*
 * Gère la déconnexion. Le client utilise cette méthode pour envoyer une demande de déconnexion (stop) et le serveur
 * pour traiter une demande de déconnexion.
 */
int deconnexion(struct request req);

/*
 * Envoie le message spécifié et lui associe le type spécifié
 */
int send_message(struct request req, int type);