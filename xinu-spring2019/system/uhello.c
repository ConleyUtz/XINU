/* uhello.c  -  uhello */

#include <xinu.h>

syscall uhello(){
	asm("int $35");
}
