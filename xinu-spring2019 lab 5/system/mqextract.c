/* mqextract.c - mqextract */

#include <xinu.h>


umsg32 mqextract(void){
        intmask mask;
        mask = disable();
        struct procent * prptr;
        prptr = &proctab[currpid];
        umsg32 toreturn = prptr->prmqhead->mqmsg;
        prptr->prmsgcount = prptr->prmsgcount - 1;
        struct msgqueue * temp = prptr->prmqhead;
        temp = temp->mqnext;
        freemem((char*)((prptr->prmqhead)),sizeof(struct msgqueue));
//        prptr->prmqhead = prptr->prmqhead->mqnext;
        prptr->prmqhead = temp;
        restore(mask);
        return toreturn;
        //check to see if list is empty
        //returned using freemem()
        //prmsgcount is updated
}

