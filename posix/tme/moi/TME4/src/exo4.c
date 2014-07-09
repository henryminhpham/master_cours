#include "sys/types.h"
#include "sys/ipc.h"
#include "unistd.h"
#include "sys/sem.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "sys/msg.h"
#include "sys/shm.h"
#include <string.h>

#define SVID_SOURCE 1
#define NB_PROC 4



int main(int argc, char const *argv[])
{


	typedef struct msgbuf { 
		long mtype; /* type de message, doit être > 0 */ 
		int max_msg_i; /* contenu du message */ 
		int who;
		int val;
	} msgbuf;

	struct msqid_ds buf;
	


	int shmid;
	pid_t pid=1;
	int i=0, res=0;
	key_t mykey;
	int msgid;
	int *cpt;


	msgbuf buf1;


	mykey=ftok(argv[0], 'a' );
	msgid=msgget(mykey, IPC_CREAT | 0777);

	struct shmid_ds shmbuf;
	shmid=shmget(mykey, sizeof(int), IPC_CREAT | 0777);
	cpt=shmat(shmid, 0, 0);
	*cpt=0;
	shmdt(cpt);

	buf1.val=0;
	buf1.mtype=1;

	for(i=0;i<NB_PROC && pid; i++){
		printf("Je créé le %d fils\n", i);
		pid=fork();
	}


	if (pid){
		int j;
		for(j=0; j<NB_PROC; j++){

			msgrcv(msgid, &buf1, 3*sizeof(int) ,NB_PROC+1, 0);
			printf("Mon fils %d attend %d messages\n",buf1.who, buf1.max_msg_i );
			srand(time(NULL)*getpid()*i+1);
			buf1.mtype=buf1.who+1;
			printf("buf1.who : %d\n", buf1.who);
			for (i=0; i < buf1.max_msg_i; i++){
				buf1.val=(int)(10*(float)rand()/ RAND_MAX);
				printf("\tFils %d : J'envoie le %d eme message : %d\n", buf1.who, i, buf1.val);
				msgsnd(msgid, &buf1, 3*sizeof(int), 0);
			}
		}
		printf("FIN PERE\n");
	}

	else {
		srand(time(NULL)*getpid()*i);
		i--;
		int j, max;
		max=(int)(10*(float)rand()/ RAND_MAX);
		buf1.max_msg_i=max;
		buf1.who=i;
		buf1.mtype=NB_PROC+1;
		printf("Moi %d j'envoie : %d\n",i ,buf1.max_msg_i);
		msgsnd(msgid, &buf1, 3*sizeof(int), 0);

		for (j=0 ; j < max ; j++){
			msgrcv(msgid, &buf1, 3*sizeof(int), i+1, 0);
			printf("\t\t%d : J'ai reçu la valeur %d\n",i, buf1.val);
			res+=buf1.val;
		}

		printf("\t\t%d : Nombre total après toutes les receptions : %d\n", i, res);
		cpt=shmat(shmid, 0,0);
		printf("\t\t\t%d : Bye\n", *cpt);
		if ((*cpt)==(NB_PROC-1)){
			printf("fermeture msq %d\n",msgctl(msgid, IPC_RMID, &buf));
			printf("fermeture shm : %d\n", shmctl(shmid, IPC_RMID, &shmbuf));
		}
		*cpt+=1;
		shmdt(cpt);
	}

	return 0;
}