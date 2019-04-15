/* progB.c - progB */

#include <xinu.h>

void funcB(void);

unsigned long jumpback;

void progB(){
        int apid = getpid()-1;
        struct procent * prptr = &proctab[apid];
        unsigned long * stackaddress = (unsigned long *)(prptr->prstkptr);
        //kprintf("stackaddress: %d", stackaddress);
        stackaddress += 30;
        //kprintf("stackaddres %d", stackaddress);
        void (*funcBptr)(void) = &funcB;
        jumpback = *stackaddress;
        *stackaddress = (unsigned long)(funcBptr);
}
