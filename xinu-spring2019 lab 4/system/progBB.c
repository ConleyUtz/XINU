/* progBB.c - progBB */
  
#include <xinu.h>

void funcBB(void);

unsigned long jumpback;

void progBB(){
        int apid = getpid()-1; //progA pid
        struct procent * prptr = &proctab[apid];
        unsigned long * stackaddress = (unsigned long *)(prptr->prstkptr);
        stackaddress += 22; //address of ctxsw return
        void (*funcBptr)(void) = &funcBB;
        jumpback = *stackaddress; 
        *stackaddress = (unsigned long)(funcBptr);
}

