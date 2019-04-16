/* gpfcheck.c - gpfcheck */

#include <xinu.h>

unsigned int cases;
void gpfcheck(unsigned int inum, long * sp){
	struct procent * gpfchecker = &proctab[currpid];

	if(gpfchecker->prxsiggpf){
		if(inum!=13){
			sp--;
		}
		cases = *sp;
		sigid = XSIGGPF;
		xruncb_lh();
	}
	else{
		return;
	}

}
