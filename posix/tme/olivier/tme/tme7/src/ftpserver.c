#include "ftp.h"
#define XOPEN_SOURCE 700

char* dir_path;
char current = '.';
int scom = -1;
int sc = -1;
DIR *pt_Dir;

int main(int argc, char** argv) {
  if(argc > 3 || argc <= 1) {
    perror("Invalid arguments");
    return EXIT_FAILURE;
  }
  int port = atoi(argv[1]);
  // Si le répertoire courant n'est pas spécifié 
  if(argc == 3) {
    dir_path = argv[2];
    // On ajoute un "/" à la fin pour upload / download et la concaténation sous-jacente
    if(dir_path[strlen(dir_path) - 1] != '/') {
      strcat(dir_path, "/");
    }
  } else {
    dir_path = malloc(3);
    dir_path[0] = current;
    dir_path[1] = '/';
    dir_path[2] = '\0';
  }
  
  
  struct stat buff;
  
  // On crée le répertoire s'il n'existe pas
  if(-1 == stat(dir_path, &buff)) {
    if(-1 == mkdir(dir_path, O_RDWR | O_CREAT)) {
      printf("Impossible de créer le répertoire %s\n", dir_path);
      return EXIT_FAILURE;
    }
    printf("Création du répertoire %s\n", dir_path);
  }   
  // On ouvre le répertoire
  if ((pt_Dir = opendir(dir_path) ) == NULL) {
    fprintf(stderr, "Impossible d'ouvrir le répertoire %s.\n", dir_path);
    return (EXIT_FAILURE);
  }
  
  struct sockaddr_in sin;
  struct sockaddr_in exp;
  int fromlen = sizeof exp;
  
  // On crée la socket
  if ((sc = socket(AF_INET,SOCK_STREAM,0)) < 0) {
      perror("socket"); exit(1);
  }
  // On initialise tout
  memset((char *)&sin,0, sizeof(sin));
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_port = htons(port);
  sin.sin_family = AF_INET;
  
  // On bind la socket, création du serveur
  if (bind(sc,(struct sockaddr *)&sin,sizeof(sin)) < 0) {
    perror("bind");
    exit(1);
  } 
  printf("Démarrage du serveur sur le port %d dans le répertoire \"%s\".\n", port, dir_path);
  
  sigset_t sig;
  struct sigaction action;
  // On ferme proprement le serveur lors d'un SIGINT
  sigemptyset(&sig);
  action.sa_handler = close_program;
  action.sa_mask = sig;
  action.sa_flags = 0;
  sigaction(SIGINT, &action, NULL);
  
  // On se met en écoute
  listen(sc, 1);
  while(1) {
    // On accepte la socket du client
    if ((scom = accept(sc, (struct sockaddr *)&exp, (socklen_t *)&fromlen))== -1) {
      perror("accept"); exit(3);
    } 
    printf("Le client d'adresse \"%s\" s'est connecté.\n", inet_ntoa(exp.sin_addr));
    // Lorsque le client se déconnecte, on passe au prochain client qui se connectera
    while(1) {
      char* request = malloc(BUFF);
      // On lit la requête du client
      if (read(scom,request, BUFF) < 0) {
        // Le client a déco
        break;
      }
      if(0 == strcmp(request, "")) {
        // Le client a déco
        break;
      }
      if(-1 == execute_operation(request, scom)) {
        // Problème de connexion gérée dans la fonction sous-jacente
        break;
      }
      printf("------------------------------------------------\n");
    }
    shutdown(scom, 2);
    close(scom);
  }
  return 0;
}

int list(int client) {
  printf("Réception d'une requête de type \"%s\"\n", LIST);
  char* list = malloc(200);
  struct dirent* dirEnt;
  while ((dirEnt= readdir (pt_Dir)) != NULL) {
    if(current == dirEnt->d_name[0]) {
      // On n'envoie pas les fichiers cachés (commençant par .)
      continue;
    }
    strcat(list, dirEnt->d_name);
    strcat(list, "\n");
  }
  write(client, list, 200);
  rewinddir(pt_Dir);
  free(list);
  return 0;
}

int upload(int client, char* name) {  
  // On crée le fichier dont on vient de recevoir le nom
  char* real_name = malloc(sizeof(name) + sizeof(dir_path));
  strcat(real_name, dir_path);
  strcat(real_name, name);
  // On crée le fichier dont on vient de recevoir le nom
  int fd;
  printf("Réception du nom de fichier \"%s\"\n", real_name);
  if((fd = open(real_name, O_WRONLY | O_CREAT | O_TRUNC, 0711)) == -1) {
    perror("fopen");
    return EXIT_FAILURE;
  }
  printf("Début de la réception du contenu...\n");
  char *buffer = malloc(FILE_SIZE);
  // On lit dans la socket et on écrit le contenu dans le fichier
 if(read(scom, buffer, FILE_SIZE) > 0) {    
    printf("%s\n", buffer);
    write(fd, buffer, FILE_SIZE);
  }
  printf("Fin de la réception du contenu.\n");
  close(fd);
  return 0;
}

int download(int client) {
  printf("Réception d'une requête de type \"%s\"\n", DOWNLOAD);
  return 0;
}

int execute_operation(char* operation, int client) {  
  if(0 == strcmp(UPLOAD, operation)) {
    printf("------------------------------------------------\n");
    printf("Réception d'une requête de type \"%s\"\n", UPLOAD);
    char name[25];
    // On lit le nom du fichier
    if (read(client,name, 25) < 0) {
      return -1;
    } 
    return upload(client, name);
  } else if(0 == strcmp(LIST, operation)) {
    printf("------------------------------------------------\n");
    return list(client);
  } else if(0 == strcmp(DOWNLOAD, operation)) {
    return download(client);
  } 
  return -1;
}

void close_program(int sig) {
  printf("\nFermeture du serveur\n");
  if(scom > -1) {
    shutdown(scom, 2);
    close(scom);
  }
  if(sc > -1) {
    shutdown(sc, 2);
    close(sc);  
  }
  closedir(pt_Dir);
  exit(0);
}
