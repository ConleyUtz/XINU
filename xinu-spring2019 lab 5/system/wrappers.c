/* wrappers.c - xruncd_uh, xruncb_lh */

#include <xinu.h>

syscall regcallback(int32 (*fp)(void)){
	intmask mask;
	struct procent * currptr;
	mask = disable();
	currptr = &proctab[currpid];

	uint32 argaddr = (int)fp;

	if(argaddr>(uint32)&etext || argaddr<(uint32)&text){
		restore(mask);
		return SYSERR;
	}
	currptr->prcbreg = 1;
	currptr->fcb=(int *)argaddr;
	restore(mask);
	return OK;
}

unsigned int case1;
pid32 cbreceiver;
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

unsigned int case2;
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
