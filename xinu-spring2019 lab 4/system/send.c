/* send.c - send */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  send  -  Pass a message to a process and start recipient if waiting
 *------------------------------------------------------------------------
 */
syscall	send(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg		/* Contents of message		*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/
	struct	procent *currptr;
	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}
	currptr = &proctab[currpid];
	prptr = &proctab[pid];
	if(currptr->prsendmode==IPCBLK){ //should this be prptr?
		if (prptr->prhasmsg) {
			//see if msg is valid?
			currptr->prsendmsg = msg;
			currptr->prsendflag = TRUE;
			currptr->prstate = PR_SENDBLK;
			prptr->prrcvblkflag = TRUE;
			qid16 msgqueue = prptr->prsenderqueue;
			//need to check for prsenderqueue?
			//how to check if msg is valid?
			enqueue(currpid,msgqueue);
			//kprintf("here8\n");
			resched();
			restore(mask);
			return OK;
		}
		else{
			prptr->prmsg = msg;
			prptr->prhasmsg = TRUE;
			prptr->prsenderid = currpid;

		}
	}
	else{
	        if (prptr->prhasmsg) {
        	        restore(mask);
                	return SYSERR;
	        }
	        prptr->prmsg = msg;             /* Deliver message              */
	        prptr->prhasmsg = TRUE;         /* Indicate message is waiting  */
		prptr->prsenderid = currpid;
	}


	if (prptr->prstate == PR_RECV) {
		ready(pid);
	} else if (prptr->prstate == PR_RECTIM) {
		unsleep(pid);
		ready(pid);
	}
	restore(mask);		/* Restore interrupts */
	return OK;
}
