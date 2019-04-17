#include <xinu.h>

extern uint32 flag;
extern uint32 flag2;
void lh_check(void) {
	intmask mask = disable();
	if (currpid == 7 && flag == 1) {
		flag = 0;
		flag2 = 1;
		kprintf("lower half: this should be printed before the receiver\n");
		//kprintf("lower half: this should be printed before alarm\n");
	}
	restore(mask);
	return;
}
