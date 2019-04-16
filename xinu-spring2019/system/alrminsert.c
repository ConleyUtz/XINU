/* alrminsert.c - arlminsert */

#include <xinu.h>

uint32 alrmqueuesize;
struct alrmqueue * alrmqueue;

struct alrmqueue * alrminsert(uint32 alrminterval, pid32 pid){
	intmask mask;
	mask = disable();
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
	alrmqueuesize++;
	restore(mask);
	return toinsert;
}

pid32 alrmextract(){
	intmask mask;
	mask = disable();
	struct alrmqueue * temp = alrmqueue->alrmnext;
	pid32 toreturn = temp->alrmpid;
	alrmqueue->alrmnext = temp->alrmnext;
	
	freemem((char*)(temp),sizeof(struct alrmqueue));
	alrmqueuesize--;
	restore(mask);
	return toreturn;
	//move alarm queue
	//free then return
}
