#include "../include/max_func.h"
#include <stdio.h>
#include <stdlib.h>

int max_func (int* vect, int size){
	int max=vect[0],i;
	for(i=1;i<size;i++){
		if(vect[i]>max){
			max=vect[i];
		}
	}
	return max;
}