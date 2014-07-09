#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


int main (void) {

  sigset_t sig_proc;
  int fd1, fd2, fd3;
  pid_t pid;
  sigfillset(&sig_proc);
  sigdelset(&sig_proc, SIGUSR1);
  if ((fd1 = open ("./fich1", O_RDWR| O_CREAT | O_TRUNC,0600)) == -1)
    return EXIT_FAILURE;
  if (write (fd1,"abcde", strlen ("abcde")) == -1) /* A */
    return EXIT_FAILURE;


  if ((pid=fork ()) == 0) {
    if ((fd2 = open ("./fich1", O_RDWR)) == -1){
      printf("FAIL\n");
      return EXIT_FAILURE;
    }
    if (write (fd1,"123", strlen ("123")) == -1) /* B */
      return EXIT_FAILURE;
    if (write (fd2,"45", strlen ("45")) == -1) /* C */
      return EXIT_FAILURE;
    printf("Envoi signal\n");
    close(fd2);
  } 


  else {
    fd3 = dup(fd1);
    sigsuspend(&sig_proc);
    printf("Reprise\n");
    if (lseek (fd3,0,SEEK_SET) == -1) /* D */
      return EXIT_FAILURE;
    if (write (fd3,"fg", strlen ("fg")) == -1) /* E */
      return EXIT_FAILURE;
    if (write (fd1,"hi", strlen ("hi")) == -1) /* F */
      return EXIT_FAILURE;
    wait(NULL);
    close(fd1);
    close(fd3);
  }
  return EXIT_SUCCESS;
}