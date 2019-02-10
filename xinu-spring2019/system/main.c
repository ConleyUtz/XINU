/*  main.c  - main */

#include <xinu.h>

extern void myapp(void);

void sndA(void), sndB(void);

process	main(void)
{
    
/*    	kprintf("\nHello World!\n");
    	kprintf("\nI'm the first XINU app and running function main() in system/main.c.\n");
    	kprintf("\nI was created by nulluser() in system/initialize.c using create().\n");
    	kprintf("\nMy creator will turn itself into the do-nothing null process.\n");
    	kprintf("\nI will create a second XINU app that runs shell() in shell/shell.c as an example.\n");
    	kprintf("\nYou can do something else, or do nothing; it's completely up to you.\n");
    	kprintf("\n...creating a shell\n");
*/// Removed original welcome message.

	/* Run the Xinu shell */

/*	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
*///removing shell
	/* Wait for shell to exit and recreate it */
/*
	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
*///removing shell
//	resume(create((void *)myapp, 4096, 20, "myapp", 1, CONSOLE));
//	resume( create(sndA, 1024, 20, "process 1", 0) );
//	resume( create(sndB, 1024, 20, "process 2", 0) );
//	chprio(4,-3);
#ifdef XDEBUG
	struct procent * current;
	current = &proctab[currpid];
	kprintf("main:\n");
        kprintf("prprio: %d\n",current->prprio);
	kprintf("preempt: %d\n",preempt);
	boost(4,5);
        kprintf("new prprio: %d\n",current->prprio);
        kprintf("new preempt: %d\n",preempt);
#endif
	uhello();
#ifdef XDEBUG
	kprintf("went to the right place!");
#endif
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
