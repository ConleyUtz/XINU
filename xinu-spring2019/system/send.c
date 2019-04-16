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

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];
	if (prptr->prhasmsg) {
		restore(mask);
		return SYSERR;
	}
	prptr->prmsg = msg;		/* Deliver message		*/
	prptr->prhasmsg = TRUE;		/* Indicate message is waiting	*/

	if(prptr->prxsigipc){
		if(prptr->prstate==PR_SLEEP){
			unsigned int * stackReceive = (unsigned int *)prptr->prstkptr;
			stackReceive += 30;
			case1 = *stackReceive;
			*stackReceive = xruncb_uh;
		}
		else{
			case2 = *(prptr->clkdispaddr);
			*(prptr->clkdispaddr) = xruncb_lh;
		}
	}
	else{

		/* If recipient waiting or in timed-wait make it ready */

		if (prptr->prstate == PR_RECV) {
			ready(pid);
		} else if (prptr->prstate == PR_RECTIM) {
			unsleep(pid);
			ready(pid);
		}

	}

	restore(mask);		/* Restore interrupts */
	return OK;
}
