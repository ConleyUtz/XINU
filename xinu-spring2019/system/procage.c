/* procage.c - procage */

#include <xinu.h>

syscall procage(pid32 pid){
	intmask mask;
	mask = disable();

	if(isbadpid(pid)){
		return SYSERR;
	}
	struct procent * prptr;
	prptr = &proctab[pid];

	restore(mask);

	return clktimefine-(prptr->prbdate);

}
