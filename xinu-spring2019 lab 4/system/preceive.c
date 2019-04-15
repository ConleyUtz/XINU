/* preceive.c - preceive */

#include <xinu.h>

syscall preceive(struct pmessage * p){
	intmask mask;
	struct procent * currptr;
	mask = disable();
	currptr = &proctab[currpid];
	uint32 stackaddr = (int)(currptr->prstkbase);

//	uint32 argaddr = (int)&p;
	uint32 argaddr = (int)p;

	if(argaddr>stackaddr || argaddr<stackaddr-(currptr->prstklen)){
		restore(mask);
		return SYSERR;
	}
	p->sendermsg = currptr->prmsg;
	p->senderid = currptr->prsenderid;
	restore(mask);
	return OK;
}


//declare global variable and pass it to this function
