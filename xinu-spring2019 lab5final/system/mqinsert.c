/* mqinsert.c - mqinsert */

#include <xinu.h>

struct msgqueue * mqinsert(umsg32 m, pid32 recvpid){
        intmask mask;
        struct procent * prptr;
        mask = disable();
        prptr = &proctab[recvpid];

        struct msgqueue * toinsert = (struct msgqueue *)getmem(sizeof(struct msgqueue));
        toinsert->mqmsg = m;
        toinsert->mqnext = NULL;
        if(prptr->prmsgcount==0){
                //first enter
                prptr->prmsgcount = prptr->prmsgcount + 1;
                prptr->prmqhead = toinsert;
                prptr->prmqtail = toinsert;
                restore(mask);
                return prptr->prmqhead;
        }
        else{
                prptr->prmsgcount = prptr->prmsgcount + 1;
                prptr->prmqtail->mqnext = toinsert;
                prptr->prmqtail = toinsert;

                restore(mask);
                return toinsert;
        }
        //check for errors
        //getmem
        //returns pointer to new element of the receiver process
        //if empty, pointer is to the head of the list
        //prmessagecount++

}

