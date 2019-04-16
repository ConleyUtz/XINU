/* xsigaction.c - xsigaction */

#include <xinu.h>

//1st arg = signal type
//2nd arg = signal handler function pointer
//3rd arg = optional argument

//

syscall xsigaction(uint16 sigtype, int32 (* fp)(void), uint32 optarg){
	intmask mask;
	struct procent * currptr;
	mask = disable();
	currptr = &proctab[currpid];

	uint32 argaddr = (int)fp;
	if(argaddr>(uint32)&etext || argaddr<(uint32)&text){
		restore(mask);
		return SYSERR;
	}

	if(sigtype == XSIGIPC){
		currptr->prxsigipc = 1;
		currptr->fipc = (int*)argaddr;
		//asynchronous IPC
		//ignore third argument
	}
	else if(sigtype == XSIGALRM){
		currptr->prxsigalrm = 1;
		currptr->falrm = (int*)argaddr;
		alrminsert(optarg, currpid);
		//third arg = msec 
		//third arg + clktime fine added to alarm queue
		//new element sorted by non-decreasing order
	}
	else if(sigtype == XSIGGPF){
		currptr->prxsiggpf = 1;
		currptr->fgpf = (int*)argaddr;
		//raised when current process executes general protection fault
	}

}
