/* alrminsert.c - arlminsert */

#include <xinu.h>

struct alrmqueue * alrminsert(uint32 alrminterval, pid32 pid){
	intmask mask;
	struct procent * prptr;
	mask = disable();
	prptr = &proctab[currpid];
	struct alrmqueue * toinsert = (struct alrmqueue *)getmem(sizeof(struct alrmqueue));
	
	toinsert->alrmtime = alrminterval+clktimefine;
	toinsert->alrmpid = pid;
	toinsert->alrmnext = NULL;	

	struct alrmqueue * traverse = alrmqueue;
	while(traverse->alrmnext!=NULL && traverse->alrmnext->alrmtime <= (alrminterval+clktimefine)){
		traverse = traverse->alrmnext;
	}
	struct alrmqueue * temp;
	temp = traverse->alrmnext;
	traverse->alrmnext = toinsert;
	toinsert->alrmnext = temp;
	restore(mask);
}

pid32 alrmextract(){
	pid32 alrmpid;
	//move alarm queue
	//free then return
}
