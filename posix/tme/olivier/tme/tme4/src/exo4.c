#include "exo4.h"
#define SVID_SOURCE 1
#define NB_FORK 3

int MAX_SIZE = sizeof(int);

int main(int argc, char** argv) {
  int i;
  // On crée la file du processus principal
  int file = create_file(0);
  for(i = 0 ; i < NB_FORK ; i++) {
    // On crée et on lance le fils
    pid_t pid = child(i, file);
    if(0 >= pid){
      return EXIT_SUCCESS;
    }
  }
  struct message msg;
  struct message ask[NB_FORK];
  // On recoit la demande de n messages pour chaque fils
  for(i = 0 ; i < NB_FORK ; i++) {
    if(-1 == msgrcv(file, &msg, MAX_SIZE, 0L, 0)) {
      perror("erreur receive");      
    }
    // On copie le message dans le tableau
    memcpy(&ask[i], &msg, sizeof(msg));
  }  
  printf("Réception de tous les messages envoyés par les fils !\n");
  printf("-------------------------------\n");
  struct message response;
  int j;
  // On a reçu tous les messages. On va envoyer ce que chaque message à demander
  for(i = 0 ; i < NB_FORK ; i++) {
    msg = ask[i];
    response.type = msg.type;
    printf("Envoi de %d messages à %ld\n", msg.random, msg.type);
    // On envoie N messages dans la file d'un fils
    for(j = 0 ; j < msg.random ; j++) {
      // On génère un random
      response.random = get_random(100);
      // On envoie un message
      printf("J'envoie %d au processus %ld\n",response.random, msg.type);
      if(-1 == msgsnd(file, &response, MAX_SIZE, 0)) {
        msgctl(file, IPC_RMID, NULL);
        perror("Send !!!");
      }
    }
    printf("-------------------------------\n");
  }
  // On attend la terminaison de tous les fils
  for(i = 0 ; i < NB_FORK ; i++) {
    wait(NULL);
  }
  // On détruit la file
  msgctl(file, IPC_RMID, NULL);
  return EXIT_SUCCESS;
}

int get_random(int max) {
  return (int) (max * (float)rand()/ RAND_MAX);
}

pid_t child(int number, int file) {
  pid_t pid;
  // On crée un nouveau processus
  if((pid = fork()) == -1) {
    perror("Create fork");
    exit(EXIT_FAILURE);
  } else if(pid == 0) {     
    // On crée un message à envoyer
     struct message msg;
     int random;
     msg.type = getpid();
     // On génère le nombre de messages que l'on souhaite recevoir
     random = get_random(++number); 
     random = (0 == random) ? 1 : random;
     msg.random = random;
     printf("Je suis %ld et mon random est %d avec %d\n", msg.type, msg.random, number);
     // On envoie au père le nombre de messages que l'on souhaite
     if(-1 == msgsnd(file, &msg, MAX_SIZE, 0)) {
       msgctl(file, IPC_RMID, NULL);
       perror("Send !!!");
    }
    // On attend de recevoir random messages
    int i;
    int final_sum = 0;
    for(i = 0 ; i < random ; i++) {
      if(-1 == msgrcv(file, &msg, MAX_SIZE, getpid(), 0)) {
        msgctl(file, IPC_RMID, NULL);
        perror("erreur receive");      
      }
      // On fait la somme de tous les randoms reçus
      final_sum += msg.random;
    }
    // On affiche le résultat
    printf("Je suis %d et la somme totale est %d\n", getpid(), final_sum);
  }
  return pid;
}

int create_file(int number) {
  key_t key = ftok("/tmp", number);
  int file;
  if((file = msgget(key, 0777 | IPC_CREAT)) == -1) {perror("Create File : ");exit(EXIT_FAILURE);}
  
  return file;
}
