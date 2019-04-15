/* funcBB.c - funcBB */
  
#include <xinu.h>

unsigned long jumpback;

void funcBB(void){
        kprintf("I am BB\n");
	kill(currpid);
}

