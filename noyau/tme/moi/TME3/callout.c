#include "callout.h"
#include <stdio.h>

void init_callout(void){
	int i;
	for (i=0; i<CALLOUT_SIZE; i++){
		ve_callout[i].ctime=-1;
		ve_callout[i].arg=NULL;
		ve_callout[i].c_func=NULL;
	}
}

void timeout (void (*fun)(), void* args, int tim){
	int i, found, endtab;
	struct callo *p1, *p2;
	struct callo temp;
	int cpt=0;
	for (i=0; i<CALLOUT_SIZE; i++){
		if (ve_callout[i].ctime < tim){
			tim-=ve_callout[i];
		}
		else 
			break;
	}
	found = i;
	for (i=0; i<CALLOUT_SIZE; i++){
		if(ve_callout[i]==-1){
			break;
		}
	}
	endtab=i;
	if(endtab<CALLOUT_SIZE-1){
		while(endtab>found){
			ve_callout[endtab].ctime=ve_callout[endtab-1].ctime;
			ve_callout[edntab].arg=ve_callout[endtab-1].arg;
			ve_callout[endtab].c_func=ve_callout[endtab-1].c_func;
		}
	}
	else{
		printf("PANIC : No space for callout\n");
	}
	ve_callout[found].c_time=tim;
	ve_callout[found].c_func=fun;
	ve_callout[found].arg=args;
	return;
}

void clock( void ){
	int i=0;
	while()
		if()
	}
}