/* receive3.c - receive */
  
#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive3  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */

umsg32 mqextract(void);
uint32 getmsgcount(void);

umsg32  receive3(void)
{
        intmask mask;                   /* Saved interrupt mask         */
        struct  procent *prptr;         /* Ptr to process's table entry */
        umsg32  msg;                    /* Message to return            */

        mask = disable();
        prptr = &proctab[currpid];

	if(!(getmsgcount())){
                prptr->prstate = PR_RECV;
                resched();              /* Block until message arrives  */
        }
        msg = mqextract();		/* Retrieve message             */
	restore(mask);
        return msg;
}
