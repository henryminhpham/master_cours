#include "slp.h"

void tsleep(int* chan, int pri){
	printf("sleep\n");
	Tproc[elu].state=MSLEEP;
	Tproc[elu].wchan=chan;
	Tproc[elu].pri=pri;
	commut(0);
}

void twakeup(int* chan){
	printf("akeup\n");
	int *c = chan;
	int i;
	for (i=0; i<NB_PROC; i++){
		if (Tproc[i].wchan == c){
			Tproc[i].state=MRUNNABLE;
			if(Tproc[i].pri>Tproc[elu].pri){
				runrun++;
			}
		}
	}
	if(runrun){
		printf("runrun\n");
		commut(0);
	}
}


