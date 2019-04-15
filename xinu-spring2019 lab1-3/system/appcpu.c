#include <xinu.h>

void appcpu(){
	int x, y; 
	x = 0; 
	y = clktimefine; 

	while(clktimefine-y<29000){
		x++;
	}
	intmask mask;
	mask = disable();
	kprintf("cpu-bound: %d %d %d\n", currpid, x, proctab[currpid].prcputime); 
	restore(mask);
}

