#include "../include/nfork.h"

#include <stdio.h>
#include <stdlib.h>

#define _POSIX_SOURCE 700


int main(int argc, char const *argv[])
{
	int p;
	int i=1; int N = 3;
	do {
		p = nfork (i) ;
		if (p != 0 )
		printf ("%d \n",p); 
	} while ((p ==0) && (++i<=N));
	printf ("FIN %d\n",p);      
	return 0;

}