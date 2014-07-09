#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
       pid_t pid;
       int  j=0; int i = 0;
       while (i < 2) {
           i ++;
           if ((pid = fork ()) == -1) {
              perror ("fork");
              exit (1);
           }
          else if (pid == 0) j=i;
      }
      if (j == 2) {
	  char* arguments[] = {"sleep","2", (char*) NULL};
	  // On a remplacé le sleep par execv
          execv("/bin/sleep", arguments);
          printf ("sans fils \n");
      }
      else {
        printf ("%d fils \n", (i-j) );
        while (j < i) {
            j++;
            wait (NULL);
        } 
      }
      return EXIT_SUCCESS;
  }  
