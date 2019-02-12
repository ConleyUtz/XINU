/* bonuslab2.c - process restart - may only be called from main */

#include <xinu.h>

syscall procinfo(pid32 pid){

	intmask mask;
	mask = disable();

	if(pid<2){
		restore(mask);
		return SYSERR;
	}

	struct procent * prprint;
	prprint = &proctab[pid];
	if(prprint==PR_FREE){
		restore(mask);
		return SYSERR;
	}
	
	kprintf("Process Name: %s\n",prprint->prname);
	kprintf("Process State: %d\n",prprint->prstate);
	kprintf("Process Priority: %d\n",prprint->prprio);
	kprintf("Saved Stack Pointer: %x\n",prprint->prstkptr);
	kprintf("Base of run time stack: %x\n",prprint->prstkbase);
	kprintf("Stack length in bytes: %d\n",prprint->prstklen);
	if(prprint->prsem){
		kprintf("Sempahore process is waiting for: %d\n",prprint->prsem);
	}
	kprintf("ID of the creating process: %d\n",prprint->prparent);

	restore(mask);
	return OK;
}
