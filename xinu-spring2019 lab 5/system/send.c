/* send.c - send */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  send  -  Pass a message to a process and start recipient if waiting
 *------------------------------------------------------------------------
 */

unsigned int case1;
unsigned int case2;
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
	prptr->prmsg = msg;             /* Deliver message              */
        prptr->prhasmsg = TRUE;         /* Indicate message is waiting  */
	if (prptr->prcbreg){
		if(prptr->prstate==PR_SLEEP){
//			kprintf("1\n");
                        unsigned int * stackReceive =(unsigned int *) prptr->prstkptr;
			stackReceive += 30;
			case1 = *stackReceive;
			void (*funcPtr)(void) = &xruncb_uh;
			*stackReceive = (unsigned int)(funcPtr);
			//get return address of sleepms
			//change return address of sleepms to funcptr
			//sleep
		}
		else{
//			kprintf("\nSENDER:%d, PID%d\n",currpid,pid,prptr->clkdispaddr);
  //                      kprintf("dispaddr: %d\n",*(prptr->clkdispaddr));

			case2 = *(prptr->clkdispaddr); //global variable
//			printf("case2: %d\n",case2);

			void * func = xruncb_lh;
			*(prptr->clkdispaddr) = func;
			//void (*funcPtr)(void) = 
			//clkhandler
			//get return address of clkdisp
			//save return address of clkdisp in global var
			//change return address of clkdisp to funcptr
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
