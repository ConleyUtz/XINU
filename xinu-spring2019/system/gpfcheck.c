/* gpfcheck.c - gpfcheck */

#include <xinu.h>

unsigned int cases;
void gpfcheck(unsigned int inum, long * sp){
	struct procent * gpfchecker = &proctab[currpid];
	if(gpfchecker->prxsiggpf){
		unsigned long * gpfaddr =(unsigned long *) &sp;
		if(*gpfaddr==8){
			gpfaddr--;
		}
		else{
			gpfaddr--;
			gpfaddr--;
		}
		cases = *gpfaddr;
		sigid = XSIGGPF;
		*gpfaddr = xruncb_lh;
	}
	else{
	
		asm("pushl 	%%ebp\n\t"
        	    "movl    %%esp,%%ebp\n\t"
        	    "pushal\n\t"
        	    "movl    %%esp, %%eax\n\t"
        	    "pushl %%eax\n\t"
		    "pushl $13\n\t"
		    "call trap\n\t" 
			:
			:
			:);
	}

}
