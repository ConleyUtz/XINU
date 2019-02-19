/*  main.c  - main */

#include <xinu.h>

extern void myapp(void);

void sndA(void), sndB(void);

process	main(void)
{
	resume( create(sndA, 1024, 20, "process 1", 0) );
	resume( create(sndB, 1024, 20, "process 2", 0) );
        struct procent * current;
        current = &proctab[currpid];
	while(1){
	uint32 time = proccputime(currpid);
        kprintf("\n\n MAIN USE: %u\n",time);
	}
//	procinfo(3); HERE IS WHERE YOU CAN CALL THE BONUS FUNCTION
//	syscall procinfo(pid32 pid)
//	it prints all information about the process

	return OK;
}

void sndA(void)
{
	while( 1 )
		kprintf("A");
}

void sndB(void)
{
	while( 1 )
		kprintf("B");
}
