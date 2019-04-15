/* cbtest.c - cbtest, mycallback */

#include <xinu.h>

int32 mycallback(void);
//extern umsg32 ubuffer;

void cbtest(void){
	if(regcallback(&mycallback) != OK){
		kprintf("registration failed");
		return;
	}
	
}

umsg32 ubuffer;
int32 mycallback(void){
        ubuffer = receive();
        return (OK);
}

