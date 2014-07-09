#include "exo3.h"
#define SVID_SOURCE 1
#define NB_FORK 3

int file[NB_FORK + 1];
int MAX_SIZE = sizeof(int) * 2;

int main(int argc, char** argv) {
  int i;
  // On crée la file du processus principal
  file[0] = create_file(0);
  for(i = 1 ; i <= NB_FORK ; i++) {
    // On crée une nouvelle file par fils
    file[i] = create_file(i);
    // On crée et on lance le fils
    pid_t pid = child(i, file[0], file[i]);
    if(0 >= pid) {
      return EXIT_SUCCESS;
    }
  }
  struct message msg;
  struct message ask[NB_FORK];
  // On recoit la demande de n messages pour chaque fils
  for(i = 0 ; i < NB_FORK ; i++) {
    if(-1 == msgrcv(file[0], &msg, MAX_SIZE, 0L, 0)) {
      perror("erreur receive");      
    }
    // On copie le message dans le tableau
    memcpy(&ask[i], &msg, sizeof(msg));
  }  
  printf("Réception de tous les messages envoyés par les fils !\n");
  printf("-------------------------------\n");
  struct message response;
  response.type = getpid();
  response.file = file[0];
  int j;
  // On a reçu tous les messages. On va envoyer ce que chaque message à demander
  for(i = 0 ; i < NB_FORK ; i++) {
    msg = ask[i];
    printf("Envoi de %d messages à la file %d\n", msg.random, msg.file);
    // On envoie N messages dans la file d'un fils
    for(j = 0 ; j < msg.random ; j++) {
      // On génère un random
      response.random = get_random(100);
      // On envoie un message
      printf("J'envoie %d dans la file %d\n",response.random, msg.file);
      if(-1 == msgsnd(msg.file, &response, MAX_SIZE, 0)) {
        msgctl(msg.file, IPC_RMID, NULL);
        perror("Send !!!");
      }
    }
    printf("-------------------------------\n");
  }
  // On attend la terminaison de tous les fils
  for(i = 0 ; i < NB_FORK ; i++) {
    wait(NULL);
  }
  // On détruit toutes les files
  for(i = 0 ; i <= NB_FORK ; i++) {
    msgctl(file[i], IPC_RMID, NULL);
  }  
  return EXIT_SUCCESS;
}

int get_random(int max) {
  return (int) (max * (float)rand()/ RAND_MAX);
}

pid_t child(int number, int father_file, int file) {
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
     msg.file = file;
     // On génère le nombre de messages que l'on souhaite recevoir
     random = get_random(++number); 
     msg.random = random;
     printf("Je suis %ld et mon random est %d avec %d\n", msg.type, random, number);
     // On envoie au père le nombre de messages que l'on souhaite
     if(-1 == msgsnd(father_file, &msg, MAX_SIZE, 0)) {
       msgctl(file, IPC_RMID, NULL);
       msgctl(father_file, IPC_RMID, NULL);
       perror("Send !!!");
    }
    // On attend de recevoir random messages
    int i;
    int final_sum = 0;
    for(i = 0 ; i < random ; i++) {
      if(-1 == msgrcv(file, &msg, MAX_SIZE, 0L, 0)) {
        msgctl(father_file, IPC_RMID, NULL);
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
