#include "extended-grep.h"
#define XOPEN_SOURCE 700
#define BUFF 4096 * 1024
#define SIZE_PATH 100 

char* expression;

int main (int argc, char* argv []) {
  if(argc <= 1 || argc > 3) {
    perror("extended-grep <expr> <path>");
    exit(1);
  }
  int current = (argc == 2);
  // On prend le répertoire courant ou le répertoire spécifié
  char path[SIZE_PATH];
  if(argc == 2) {
    if (getcwd (path, SIZE_PATH) == NULL ) {
      perror ("erreur getwcd \n");
      exit (1);
    }
  } else {
    memcpy(path, argv[2], strlen(argv[2]));
  }
  DIR *pt_Dir;
  struct dirent* dirEnt;  
  // On ouvre le répertoire
  if ((pt_Dir = opendir(path) ) == NULL) {
    fprintf(stderr, "Impossible d'ouvrir le répertoire %s\n", path);
    return EXIT_FAILURE;
  }
  // On compile la regexp
  regex_t regexp;
  if(regcomp(&regexp, argv[1], REG_EXTENDED) != 0) {
    fprintf(stderr, "Impossible de compiler l'expression régulière %s\n", argv[1]);
    return EXIT_FAILURE;
  }
  expression = argv[1];
  int result= 0; 
  int global = 0;
  char* real_name;
  while ((dirEnt= readdir (pt_Dir)) != NULL) {
    // On met le vrai nom car dirEnd->dName renvoie le nom du fichier, sans le path
    real_name = convert_path(dirEnt->d_name, current, path);
    // On effectue une recherche pour chaque fichier
    result = seek_expression(real_name, &regexp);
    // Si -1 : erreur - Si 0 : on a rien trouvé - sinon on a matché
    if(result > 0) {
      printf("L'expression %s a été trouvée dans %s.\n", argv[1], real_name);
      // On incrémente le nombre de fichier trouvé
      global++;
    }
  }
  regfree(&regexp);
  // Si aucun fichier trouvé, on l'affiche
  if(global == 0) {
    printf("Aucun fichier valide.\n");
  }
  closedir (pt_Dir);
  return EXIT_SUCCESS;
}


int isRegular(char* name) {
  // On vérifie que le fichier existe, que ce n'est pas un répertoire et
  // que c'est un fichier régulier
  struct stat stat_from;
  if(-1 == stat(name, &stat_from)) {
    fprintf(stderr, "Le fichier %s n'existe pas.\n", name);
    return -1;
  }
  if(S_ISDIR(stat_from.st_mode)) {
    return -1;
  }
  // On vérifie que c'est un fichier régulier
  return S_ISREG(stat_from.st_mode);
}

int seek_expression (char* filename, regex_t* regexp) {
  //On vérifie que c'est un fichier valide
  if(isRegular(filename) == -1) {
    return -1;
  }
  char buffer[BUFF];
  FILE* file;
  // On ouvre le fichier
  if((file = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "Impossible d'ouvrir le fichier %s\n", filename);
    exit(1);
  }
  // On essaye de matcher ligne par ligne
  while(NULL != fgets(buffer, BUFF, file)) {
    // Le code avec strstr --> if(NULL != strstr(buffer, expression))
    if(0 < find_regexp(regexp, buffer)) {
      return 1;
    }  
  }
  return 0;
  
}

int find_regexp(regex_t* regexp, char* content) {
  int match;
  match = regexec (regexp, content, 0, NULL, 0);
  // Afin de respecter le type de retour
  return (match == 0) ? 1 : 0;
}

char* convert_path(char* name, int is_current, char* directory) {
  if(is_current) {
    return name;
  }
  char* final_value = malloc(sizeof(directory));
  strcpy(final_value, directory);
  char last = directory[strlen(directory) - 1];
  if(last != '/') {
    strcat(final_value, "/");
  }
  strcat(final_value, name);
  return final_value;
}