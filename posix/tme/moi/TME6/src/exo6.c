#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

extern int errno;

#define _XOPEN_SOURCE 700
#define TAILLE_PATH 100

char buff_path [TAILLE_PATH];
DIR *pt_Dir;
struct dirent* dirEnt;

int main (int argc, char* argv []) {
	
	int found=0, cur_rech=0;
	struct stat stat_infos;
	char filewithpath[25];

	if (argc ==2 ) {
		printf("Recherche dans repertoir courant\n");
		/* repertoir courant : obtenir le nom */
		cur_rech=1;
		if (getcwd (buff_path, TAILLE_PATH) == NULL ) {
			perror ("erreur getwcd \n");
			exit (1);
		}
	}
	else
		memcpy (buff_path,argv[2],strlen(argv[2]));
	
	if ( ( pt_Dir = opendir (buff_path) ) == NULL) {
		perror ("erreur opendir \n");
		exit (1);
	}
	/* lire répertoire */
	while ((dirEnt= readdir (pt_Dir)) !=NULL) {

		if(strstr(dirEnt->d_name, argv[1])){

			if(!cur_rech){
				strcpy(filewithpath, buff_path);
				strcat(filewithpath, dirEnt->d_name);
			}
			else
				strcpy(filewithpath, dirEnt->d_name);

			if (stat(filewithpath, &stat_infos)==-1){
				perror("stat");
				return EXIT_FAILURE;
			}
			if(S_ISREG(stat_infos.st_mode)){
				printf ("Trouvé : %s\n", filewithpath);
				found++;
			}
		}
	}
	if(!found){
		printf("Aucun fichier valide\n");
	}
	else
		printf("Trouvé %d fichier(s)\n",found);
	closedir (pt_Dir);
	
	return 0;
}