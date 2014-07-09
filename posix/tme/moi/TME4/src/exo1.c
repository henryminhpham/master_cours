#include "sys/types.h"
#include "sys/ipc.h"
#include "unistd.h"
#include "sys/sem.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "sys/msg.h"
#include <string.h>

#define SVID_SOURCE 1
#define NB_PROC 4

int main(int argc, char const *argv[])
{
	pid_t pid=1;
	int i=0, res=0;
	key_t mykey;
	int msgid;
	

	typedef struct msgbuf { 
		long mtype; /* type de message, doit être > 0 */ 
		int val; /* contenu du message */ 
	} msgbuf;

	msgbuf buf1;

	mykey=ftok(argv[0], 'a');
	msgid=msgget(mykey, IPC_CREAT | 0777);
	buf1.mtype=1;
	for(i=0;i<NB_PROC && pid; i++){
		pid=fork();
	}
	if (pid){
		for(i=0;i<NB_PROC && pid; i++){
			wait(NULL);
		}

		while(msgrcv(msgid, &buf1, sizeof(int) ,1, IPC_NOWAIT)!=-1){
			printf("J'ai extrait : %d\n", buf1.val);
			res+=buf1.val;
		}
		printf("Le resultat final : %d\n", res);
		

	}
	else {
		srand(time(NULL)*getpid());
		sleep(i);
		buf1.val=(int)(10*(float)rand()/ RAND_MAX);
		printf("Moi j'envoie : %d\n", buf1.val);
		msgsnd(msgid, &buf1, sizeof(int), 0);
	}

	return 0;
}