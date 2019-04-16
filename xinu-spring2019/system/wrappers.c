/* wrappers.c - xruncd_uh, xruncb_lh */

#include <xinu.h>

extern unsigned int cases;
uint32 sigid;

void xruncb_uh(void){
        intmask mask;
        mask = disable();
        struct procent * recproc = &proctab[currpid];
        asm("movl %[jump], 4(%%ebp)\n\t"
                :
                : [jump] "r"(cases)
                : );
	if(sigid==XSIGIPC){
	        int (*funcPt)() = recproc->fipc;
	        (funcPt)();
	}
	restore(mask);
}

void xruncb_lh(void){
        intmask mask;
        mask = disable();
        struct procent * recproc = &proctab[currpid];

        asm("movl %[jump], 4(%%ebp)\n\t"
                :
                : [jump] "r"(cases)
                : );

        if(sigid==XSIGIPC){
                int (*funcPt)() = recproc->fipc;
                (funcPt)();
        }
        else if(sigid==XSIGALRM){
                int (*funcPt)() = recproc->falrm;
                (funcPt)();
        }
        else if(sigid==XSIGGPF){
                int (*funcPt)() = recproc->fgpf;
                (funcPt)();
        }

        restore(mask);
}

