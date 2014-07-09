#include "chat.h"
#define XOPEN_SOURCE 700

typedef struct client {
  char* name;
  struct request* segment;
  sem_t* sem_client;
  char* sem_client_name;
}client;

client clients[MAX_CLIENT];

struct request* segment;
connexion_data* data;

static void send_to_one(struct request req, int type, client* cl);

int main(int argc, char** argv) {
  if(argc <= 1) {printf("Il faut spécifier un nom de segment.\n");exit(EXIT_FAILURE);}	
  
  if(ERROR_TYPE == pre_construct(argv[1])) {
    stop(SIGINT);
    return EXIT_FAILURE;
  }
  start();
  return EXIT_SUCCESS;	
}

void start() {
  int result = ERROR_TYPE;
  while(1) {
    sem_wait(data->sem);
    struct request req = segment[0];
    result = ERROR_TYPE;
    if(req.type == CONNEXION) {
      result = connexion(req);
    } else if(req.type == MESSAGE) {
      result = send_message(req, req.type);
    } else if(req.type == DECONNEXION) {
      result = deconnexion(req);
    }
    if(result == VALID_MESSAGE) {
      sem_post(data->sem_client);
    }
  }
}

int pre_construct(char* argv) {  
  int size = sizeof(struct request);
  data = malloc(sizeof(connexion_data));
  memcpy(data->semaphore_name, argv, strlen(argv));
  strcpy(data->server_name, data->semaphore_name);
  strcat(data->server_name, "_shm:0");
  
  if((data->shm = shm_open(data->server_name, O_RDWR | O_CREAT, 0777)) == -1) {perror("Impossible de créer le segment mémoire."); return ERROR_TYPE;}
  
  if(-1 == ftruncate(data->shm, size)){perror("Impossible de ftruncate."); return ERROR_TYPE;}
  if((segment = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, data->shm, 0)) == MAP_FAILED) {perror("Impossible de faire la projection mémoire."); return ERROR_TYPE;}
  printf("Création du serveur...\n");

  if(SEM_FAILED == (data->sem = sem_open(data->semaphore_name, O_RDWR | O_CREAT, 0777, 0))){perror("Impossible de créer un sémaphore"); return ERROR_TYPE;}
  
  
  if(SEM_FAILED == (data->sem_client = sem_open(SEM_CLIENT_NAME, O_RDWR | O_CREAT, 0777, 1))){perror("Impossible de créer un sémaphore"); return ERROR_TYPE;}

  printf("Lancement du serveur \"%s\"\n", data->server_name);
  sigset_t sig;
  struct sigaction action;
  sigemptyset(&sig);
  action.sa_flags = 0;
  action.sa_mask = sig;
  action.sa_handler = stop;
  sigaction(SIGINT, &action, NULL);
  return VALID_MESSAGE;
}

void stop(int sig) {
  munmap((caddr_t) segment, sizeof(struct request));
  shm_unlink(data->server_name);
  sem_close(data->sem);
  sem_unlink(data->semaphore_name);
  sem_close(data->sem_client);
  sem_unlink(SEM_CLIENT_NAME);
  printf("Fermeture du serveur de nom \"%s\"\n", data->server_name);
  exit(EXIT_SUCCESS);
}


int connexion(struct request req) {
  int i;
  for(i = 0 ; i < MAX_CLIENT; i++) {
    client cl = clients[i];
    if(cl.name == NULL) {
     cl.name = malloc(sizeof(req.content));
     strcpy(cl.name, req.content);
     int client_shm;
     
     if((client_shm = shm_open(cl.name, O_RDWR, 0777)) == -1) {perror("Impossible de récupérer le segment mémoire."); return ERROR_TYPE;}
     if((clients[i].segment = (struct request*) mmap(NULL, sizeof(struct request), PROT_READ | PROT_WRITE, MAP_SHARED, client_shm, 0)) == MAP_FAILED) {perror("Impossible de faire la projection mémoire."); return ERROR_TYPE;}
      
     cl.sem_client_name = malloc(sizeof(SEM_CLIENT_NAME) + sizeof(cl.name));
     strcpy(cl.sem_client_name, SEM_CLIENT_NAME);
     strcat(cl.sem_client_name, cl.name);
     
     if(SEM_FAILED == (cl.sem_client = sem_open(cl.sem_client_name, O_RDWR, 0777, 1))){perror("Impossible de créer un sémaphore"); return ERROR_TYPE;}
     
     printf("Le client d'identifiant \"%s\" s'est connecté.\n",cl.name);
     clients[i] = cl;
     return VALID_MESSAGE;
   }
 }
  printf("Le serveur est plein et ne peut plus recevoir de connexions.\n");
  return ERROR_TYPE;
}

int deconnexion(struct request req) {
 int i;
 for(i = 0 ; i < MAX_CLIENT ; i++) {
   if(clients[i].name != NULL && strcmp(clients[i].name, req.content) == 0) {
     printf("Le client d'identifiant \"%s\" s'est déconnecté.\n",clients[i].name);
     clients[i].name = NULL;
     clients[i].segment = NULL;
     free(clients[i].sem_client_name);
     sem_close(clients[i].sem_client);
     return VALID_MESSAGE;
   }
 }
 printf("Le client d'identifiant \"%s\" n'a pas été trouvé.\n",req.content);
 return ERROR_TYPE;
}

int send_message(struct request req, int type) {
  int i;
  for(i = 0 ; i < MAX_CLIENT ; i++) {
    if(clients[i].name == NULL) {
      continue;
    }
    client cl = clients[i];
    send_to_one(req, type, &cl);
  }
  return VALID_MESSAGE;
}

static void send_to_one(struct request req, int type, client* cl) {
    struct request* new_request = malloc(sizeof(struct request));
    strcpy(new_request->content, req.content);
    new_request->type = type;
    cl->segment = new_request;
    sem_post(cl->sem_client);
}