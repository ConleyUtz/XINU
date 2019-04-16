/* clkhandler.c - clkhandler */

#include <xinu.h>

/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */
struct procent * clkptr;
struct alrmqueue * alrmqueue;
uint32 sigid;
unsigned int cases;
uint32 flag;
void	clkhandler()
{
	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/

	clkptr = &proctab[currpid];
	if(clkptr->prxsigipc || clkptr->prxsigalrm || clkptr->prxsiggpf){
                asm("movl %%ebp,%0\n\t"
                  :"=r"(clkptr->clkdispaddr)
                  :
                  :
                );
                clkptr->clkdispaddr = clkptr->clkdispaddr+10;
        }

	/* Decrement the ms counter, and see if a second has passed */

	if((--count1000) <= 0) {

		/* One second has passed, so increment seconds count */

		clktime++;

		/* Reset the local ms counter for the next second */

		count1000 = 1000;
	}

	clktimefine++;

	/* Handle sleeping processes if any exist */

	if(!isempty(sleepq)) {

		/* Decrement the delay for the first process on the	*/
		/*   sleep queue, and awaken if the count reaches zero	*/

		if((--queuetab[firstid(sleepq)].qkey) <= 0) {
			wakeup();
		}
	}

	while(alrmqueue->alrmnext != NULL && alrmqueue->alrmnext->alrmtime<=clktimefine){
			pid32 alrmpid = alrmextract();
			clkptr = &proctab[alrmpid];
			clkptr->pralrmraised = 1;
	}

	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */

	if((--preempt) <= 0) {
		preempt = QUANTUM;
		resched();
	}
	
	clkptr = &proctab[currpid];
	if(clkptr->pralrmraised){
		cases = *(clkptr->clkdispaddr);
		*(clkptr->clkdispaddr) = xruncb_lh;
		sigid = XSIGALRM;
		clkptr->pralrmraised = 0;
		flag = 1;
	}

}
