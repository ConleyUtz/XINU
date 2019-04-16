/* wrappers.c - xruncd_uh, xruncb_lh */

#include <xinu.h>

extern unsigned int case1;
void xruncb_uh(void){
        intmask mask;
        mask = disable();
        struct procent * recproc = &proctab[currpid];
        asm("movl %[jump], 4(%%ebp)\n\t"
                :
                : [jump] "r"(case1)
                : );
        int (*funcPt)() = recproc->fcb;
        (funcPt)();
        restore(mask);
}

extern unsigned int case2;
void xruncb_lh(void){
        intmask mask;
        mask = disable();
        struct procent * recproc = &proctab[currpid];
        asm("movl %[jump], 4(%%ebp)\n\t"
                :
                : [jump] "r"(case2)
                : );
        int (*funcPt)() = recproc->fcb;
        (funcPt)();
        restore(mask);
}

