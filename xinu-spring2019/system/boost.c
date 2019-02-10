/*  boost.c  - boost */
  
#include <xinu.h>

syscall boost(uint32 priob, uint32 timeb)
{
	intmask mask;
	mask = disable(); //cli

	struct procent * current;

	current = &proctab[currpid];

	if(priob>5||timeb>5){ //Error condition 1
		restore(mask);
		return SYSERR;
	}	
	
	if(priob+(current->prprio)>100 || preempt+timeb>1000){ //Error condition 2
		restore(mask);
		return SYSERR;
	}
	current->prprio += priob; //change prio
	preempt += timeb; //change preempt
	
	restore(mask); //sti
	return OK;
}
