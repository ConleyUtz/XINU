/*  main.c  - main */

#include <xinu.h>

extern void myapp(void);

void sndA(void), sndB(void);

void appcpu(void);
void appio(void);

process	main(void)
{
	int XTESTA = 0;
	int XTESTB = 0;
	int XTESTC = 1;
	int XTESTD = 0;
if(XTESTA){
	resume( create(appcpu, 1024, 21, "process 1", 0) );
        resume( create(appcpu, 1024, 20, "process 2", 0) );
        resume( create(appcpu, 1024, 20, "process 3", 0) );
        resume( create(appcpu, 1024, 20, "process 4", 0) );
        resume( create(appcpu, 1024, 20, "process 5", 0) );
}
if(XTESTB){
        resume( create(appio, 1024, 20, "process 1", 0) );
        resume( create(appio, 1024, 20, "process 2", 0) );
        resume( create(appio, 1024, 20, "process 3", 0) );
        resume( create(appio, 1024, 20, "process 4", 0) );
        resume( create(appio, 1024, 20, "process 5", 0) );
}
if(XTESTC){
        resume( create(appcpu, 1024, 20, "process 1", 0) );
        resume( create(appcpu, 1024, 20, "process 2", 0) );
        resume( create(appcpu, 1024, 20, "process 3", 0) );
        resume( create(appcpu, 1024, 20, "process 4", 0) );
        resume( create(appcpu, 1024, 20, "process 5", 0) );
        resume( create(appio, 1024, 20, "process 6", 0) );
        resume( create(appio, 1024, 20, "process 7", 0) );
        resume( create(appio, 1024, 20, "process 8", 0) );
        resume( create(appio, 1024, 20, "process 9", 0) );
        resume( create(appio, 1024, 20, "process 10", 0) );
}
if(XTESTD){
        resume( create(appcpu, 1024, 20, "process 1", 0) );
	sleepms(5000);
        resume( create(appcpu, 1024, 20, "process 2", 0) );
	sleepms(5000);
        resume( create(appcpu, 1024, 20, "process 3", 0) );
	sleepms(5000);
        resume( create(appcpu, 1024, 20, "process 4", 0) );
	sleepms(5000);
        resume( create(appcpu, 1024, 20, "process 5", 0) );
        sleepms(5000);
}
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
