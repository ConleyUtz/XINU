/* uhello.c  -  uhello */

#include <xinu.h>

void uhello(){
	intmask mask;
	mask = disable();
	asm("int $35");
	restore(mask);
}
