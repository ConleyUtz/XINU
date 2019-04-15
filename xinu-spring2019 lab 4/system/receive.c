/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32	receive(void)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/
	umsg32	msg;			/* Message to return		*/
	struct	procent *sendptr;
	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE) {
		if(prptr->prrcvblkflag == 1){
			qid16 prqueue = prptr->prsenderqueue;
			pid32 pid = dequeue(prqueue);
			if(isempty(prqueue)){
			//	kprintf("also very sad\n");
				prptr->prrcvblkflag = FALSE;
			}
			sendptr = &proctab[pid];
			prptr->prmsg = sendptr->prsendmsg;
			//kprintf(" TEST - %d - TEST \n",pid);
			prptr->prhasmsg = TRUE;
			sendptr->prsendflag = FALSE;
			ready(pid);
		//since it would return here is it necessary to call receive again?
		}
		else{
//			kprintf("here sadly\n");
			prptr->prstate = PR_RECV;
			resched();		/* Block until message arrives	*/
		}
	}
	msg = prptr->prmsg;		/* Retrieve message		*/
	prptr->prhasmsg = FALSE;	/* Reset message flag		*/
	restore(mask);
	return msg;
}
