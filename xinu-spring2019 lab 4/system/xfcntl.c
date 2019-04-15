/* xfcntl.c - xfcntl */

#include <xinu.h>

syscall xfcntl(uint16 selector, uint16 mode){
	intmask mask;
	mask = disable();
	struct procent * currptr;

	if(selector!=IPCSND && selector!=IPCRCV){
		restore(mask);
		return SYSERR;
	}
	if(mode!=IPCBLK && mode!=IPCNBK){
		restore(mask);
		return SYSERR;
	}

	currptr = &proctab[currpid];

	if(selector==IPCRCV){
	//receive
		if(mode==IPCNBK){
		//no block
			currptr->prrcvblkflag = IPCNBK;
		}
		else{
		//block
			currptr->prrcvblkflag = IPCBLK;
		}
	}
	else{
	//send
		if(mode==IPCNBK){
			currptr->prsendmode = IPCNBK;
		//no block
		}
		else{
			currptr->prsendmode = IPCBLK;
		}
	}

	restore(mask);
	return OK; //return value
}
