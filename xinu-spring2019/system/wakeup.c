/* wakeup.c - wakeup */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  wakeup  -  Called by clock interrupt handler to awaken processes
 *------------------------------------------------------------------------
 */
void	wakeup(void)
{
	/* Awaken all processes that have no more time to sleep */

	resched_cntl(DEFER_START);
	int new;
	int prio;
	struct procent * newptr;

	while (nonempty(sleepq) && (firstkey(sleepq) <= 0)) {

		/* cutz - COMMENT4 START - ADDED CODE BLOCK FOR SCHEDULING STARTS 		*/

		new = dequeue(sleepq); 	    /* get PID of process that needs to be awoken 	*/
		newptr = &proctab[new];	    /* get process pointer from PID 			*/
		prio = getmincpu();	    /* get highest priority of lowest process 		*/
		newptr->prvcputime = prio;  /* Uses getmincpu() syscall to get the accurate
					       minimum CPU usage across all processes. See
					       system/getcpu.c for more details. 		*/
		newptr->prprio = 30000-prio;/* updates process's priority to the highest	*/
		ready(new);

		/* cutz - COMMENT 4 END - ADDED CODE BLOCK FOR SCHEDULING END */

		// ready(dequeue(sleepq));  /* old code */
	}

	resched_cntl(DEFER_STOP);
	return;
}
