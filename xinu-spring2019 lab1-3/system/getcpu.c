/* getcpu.c - getmincpu, getmaxcpu */

#include <xinu.h>

qid16 readylist;

syscall getmincpu(){
	intmask mask;
	struct procent * minptr;
	mask = disable();
        minptr = &proctab[currpid];
	if(isempty(readylist)){ // If null process is the only process running,
		restore(mask);
		return minptr->prvcputime+QUANTUM-preempt;
	}
	int mincpu; //This holds the priority of the first process in the ready list, not the actually lowest prvcputime
	mincpu = firstkey(readylist);
	if((30000-mincpu)<=(minptr->prvcputime+QUANTUM-preempt)){ //determines if running process has higher priority than first in queue
		restore(mask);
		return 30000-mincpu;
	}
	restore(mask);
	return minptr->prvcputime+QUANTUM-preempt;
}

syscall getmaxcpu(){
	intmask mask;
	struct procent * maxptr;
	mask = disable();

	if(isempty(readylist)){
		restore(mask);
//		kprintf("Max CPU 1\n");
		return 0;
	}
	else if(firstid(readylist)==lastid(readylist)){ //checks to see if NULLPROC is the only process in the ready list
		maxptr = &proctab[currpid];
		restore(mask);
//		kprintf("Max CPU 2\n");
		return maxptr->prvcputime+QUANTUM-preempt; 
	}
	int maxcpu;
	qid16 curr = firstid(readylist);
	while(queuetab[curr].qkey != 0){
		curr = queuetab[curr].qnext;
	}
	curr = queuetab[curr].qprev;
	maxcpu = queuetab[curr].qkey;
//	kprintf("Max CPU 3\n");
	restore(mask);
	return 30000-maxcpu;
}
