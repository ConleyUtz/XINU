/* proccputime.c - proccputime */

#include <xinu.h>

uint32 proccputime(pid32 pid){
	intmask mask;
	mask = disable();

	if(isbadpid(pid)){
		return SYSERR;
	}
	struct procent * prptr;
	prptr = &proctab[pid];
	if(currpid==pid){
		restore(mask);
		return prptr->prcputime+(QUANTUM-preempt);
	}
	restore(mask);
	return prptr->prcputime;
}
