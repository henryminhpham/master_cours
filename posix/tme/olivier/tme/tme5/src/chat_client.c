#include "chat.h"
#define XOPEN_SOURCE 700

struct request* segment[2];
connexion_data* server_data;
char* name;
char* segment_name;
pthread_t* receiver;
sem_t* sem_client;
char* sem_client_name;
int shm;

static void clean();

static void* thread_on_message(void* data);

int main(int argc, char** argv) {
  if(argc <= 1) {printf("Il faut spécifier un identifiant.\n");exit(EXIT_FAILURE);}
  
  name = argv[1];
  segment_name = malloc(sizeof(REQUEST_SIZE));
  strcpy(segment_name, name);
  strcat(segment_name, "_shm:0");
  
  char buffer[REQUEST_SIZE];
  printf("Ecrivez vos messages au fur et à mesure. La réception en temps-réel d'autres messages peut arriver à tout moment !\nAttention à ne jamais couper le serveur avant un client, où celui-ci vous forcera à utiliser le kill !\n");
  printf("Veuillez indiquer le nom du serveur auquel se connecter : ");
  scanf("%s", buffer);
  if(ERROR_TYPE ==  pre_construct(buffer)) {
    return EXIT_FAILURE;
  }
  struct request req;
  if(ERROR_TYPE ==  connexion(req)) {
    printf("Impossible de se connecter au serveur \"%s\".", server_data->server_name);
    clean();
    return EXIT_FAILURE;
  }
  start();
  return EXIT_SUCCESS;
}


int pre_construct(char* argv){
  int size = sizeof(struct request);
  server_data = malloc(sizeof(connexion_data));
  memcpy(server_data->semaphore_name, argv, strlen(argv));
  strcpy(server_data->server_name, server_data->semaphore_name);
  strcat(server_data->server_name, "_shm:0");
  
  if((server_data->shm = shm_open(server_data->server_name, O_RDWR, 0777)) == -1) {perror("Impossible de se connecter au serveur (segment mémoire)"); return ERROR_TYPE;}
  
  if(-1 == ftruncate(server_data->shm, size)){perror("Ftruncate"); exit(1);}
  
  if((segment[0] = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, server_data->shm, 0)) == MAP_FAILED) {perror("Impossible de se connecter au serveur (segment mémoire)"); return ERROR_TYPE;}
  
  if((shm = shm_open(name, O_RDWR | O_CREAT, 0777)) == -1) {perror("Impossible de créer un segment mémoire"); return ERROR_TYPE;}
  
  if(-1 == ftruncate(shm, size)){perror("Ftruncate"); exit(1);}
  
  if((segment[1] = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, server_data->shm, 0)) == MAP_FAILED) {perror("Impossible de créer un segment mémoire"); return ERROR_TYPE;}
  
  if(SEM_FAILED == (server_data->sem = sem_open(server_data->semaphore_name, O_RDWR, 0777, 0))){perror("Impossible de récupérer le sémaphore du serveur"); clean();return ERROR_TYPE;}

  if(SEM_FAILED == (server_data->sem_client = sem_open(SEM_CLIENT_NAME, O_RDWR, 0777, 1))){perror("Impossible de récupérer le sémaphore server"); clean(); return ERROR_TYPE;}
  
  sem_client_name = malloc(sizeof(SEM_CLIENT_NAME) + sizeof(name));
  strcpy(sem_client_name, SEM_CLIENT_NAME);
  strcat(sem_client_name, name);
  
  if(SEM_FAILED == (sem_client = sem_open(sem_client_name, O_RDWR | O_CREAT, 0777, 0))){perror("Impossible de récupérer le sémaphore client"); clean(); return ERROR_TYPE;}
    
  sigset_t sig;
  struct sigaction action;
  sigemptyset(&sig);
  action.sa_flags = 0;
  action.sa_mask = sig;
  action.sa_handler = stop;
  sigaction(SIGINT, &action, NULL);
  
  receiver = malloc(sizeof(pthread_t));
  if(-1 == pthread_create(receiver, NULL, thread_on_message, NULL)){perror("Impossible de recevoir des messages"); clean(); return ERROR_TYPE;}
  
  pthread_detach(*receiver);
  return VALID_MESSAGE;
}

void stop(int sig){
  struct request req;
  deconnexion(req);
  clean();
  exit(EXIT_SUCCESS);
}

void start(){
  char buffer[REQUEST_SIZE];
  while(1) {
    scanf("%s", buffer);
    struct request req;
    strcpy(req.content, buffer);
    send_message(req, MESSAGE);
  }
}

int connexion(struct request req) {
  sem_wait(server_data->sem_client);
  strcpy(req.content, name);  
  req.type = CONNEXION;
  segment[0][0] = req;
  return (-1 == sem_post(server_data->sem)) ? ERROR_TYPE : VALID_MESSAGE;
}

int deconnexion(struct request req) {
  sem_wait(server_data->sem_client);
  printf("\nDéconnexion du serveur \"%s\".\n", server_data->server_name);
  strcpy(req.content, name);  
  req.type = DECONNEXION;
  segment[0][0] = req;
  return (-1 == sem_post(server_data->sem)) ? ERROR_TYPE : VALID_MESSAGE;
}

int send_message(struct request req, int type){
  sem_wait(server_data->sem_client);
  req.type = type;
  segment[0][0] = req;
  return (-1 == sem_post(server_data->sem)) ? ERROR_TYPE : VALID_MESSAGE;
}

static void clean() {
  sem_close(server_data->sem);
  sem_close(server_data->sem_client);
  sem_close(sem_client);
  sem_unlink(sem_client_name);
  munmap((caddr_t) segment[1], sizeof(struct request));
  shm_unlink(name);
  if(receiver != NULL) {
    pthread_cancel(*receiver);
  }
}

static void* thread_on_message(void* data) {
  while(1) {
    sem_wait(sem_client);
    struct request* req = (struct request*) segment[1];
    printf("%s\n", req[0].content);
  }
  return NULL;
}