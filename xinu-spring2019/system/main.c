/*  main.c  - main */

#include <xinu.h>

extern void myapp(void);

void sndA(void), sndB(void);

process	main(void)
{
//	resume( create(sndA, 1024, 20, "process 1", 0) );
//	resume( create(sndB, 1024, 20, "process 2", 0) );
//	chprio(4,-3);
if(XTEST){
	//Boost Test
	struct procent * current;
	current = &proctab[currpid];
	kprintf("---boost() TEST---\n");
        kprintf("Priority before boost(): %d\n",current->prprio);
	kprintf("Preempt before boost(): %d\n",preempt);
	kprintf("boost()\n");
	boost(4,5);
        kprintf("Priority after boost(): %d\n",current->prprio);
        kprintf("Preempt after boost(): %d\n",preempt);
}
if(XTEST){
	kprintf("\n\n---uhello() TEST---\n");
	uhello();
}
if(XTEST){
        struct procent * current;
        current = &proctab[currpid];
        kprintf("\n\n---uchprio TEST---\n");
        kprintf("Priority of %s before uchprio(): %d\n",current->prname,current->prprio);
	uchprio(currpid,18);
        kprintf("Priority of %s after uchprio(): %d\n",current->prname,current->prprio);
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
