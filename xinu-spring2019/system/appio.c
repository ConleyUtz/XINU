#include <xinu.h>

void appio(){

	int x, y; 
	x = 0; 
	y = clktimefine; 
	
	while(clktimefine - y < 29000) { 
		x++; 
		sleepms(20);
	} 
	intmask mask;
	mask = disable();
	kprintf("io-bound: %d %d %d\n", currpid, x, proctab[currpid].prcputime); 
	restore(mask);
}
