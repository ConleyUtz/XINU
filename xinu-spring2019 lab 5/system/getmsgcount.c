/* getmsgcount.c - getmsgcount */

#include <xinu.h>

uint32 getmsgcount(void){
        //syscall
        //returns prmsgcount of currpid
        intmask mask;
        mask = disable();
        struct procent * prptr;
        prptr = &proctab[currpid];
        restore(mask);
        return prptr->prmsgcount;
}

