/* funcB.c - funcB */

#include <xinu.h>

unsigned long jumpback;

void funcB(void){
	kprintf("I am B\n");
        int five3 = 1; //turn off for 5.2
        if(five3){
        unsigned long jumper = jumpback;
        asm("movl %[jump], 4(%%ebp)\n\t"
                :
                : [jump] "r"(jumper)
                : );
        }
}
