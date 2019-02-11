/* uhello.c  -  uhello */

#include <xinu.h>

void uhello(){
	asm("int $35");
}
