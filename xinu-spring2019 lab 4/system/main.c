/*  main.c  - main */

#include <xinu.h>

extern void progA(void);
extern void progB(void);
extern void progAA(void);
extern void progBB(void);
void lab4test(void);
void lab4test2(void);
void lab4test3(void);
void lab4test4(void);
        pid32   rcvrPID;
void lab4test5(void);
void lab4test6(void);


process	main(void)
{
    	kprintf("\nConley Utz - cutz - 0028748706\nLab 4 Results:\n\n");


	int prob5 = 0;
	if(prob5){ //using resched()
		resume(create(progA, 1024, 25, "progA", 1, CONSOLE));
		resume(create(progB, 1024, 20, "progB", 1, CONSOLE));
	}

	int lab4bonus = 0;
	if(lab4bonus){ //using CTXSW
        	resume(create(progAA, 1024, 25, "progAA", 1, CONSOLE));
	        resume(create(progBB, 1024, 20, "progBB", 1, CONSOLE));
	}

	int prob3 = 0;
	if(prob3 == 1){

		rcvrPID = create(lab4test,8192,20,"test",1,CONSOLE);
		resume(create(lab4test2, 8192, 21, "test1", 1, CONSOLE));
		sleepms(500);
		resume(create(lab4test3, 8192, 21, "test2", 1, CONSOLE));
		sleepms(500);
		resume(create(lab4test4, 8192, 21, "test4", 1, CONSOLE));
		sleepms(500);
		resume(rcvrPID);

	}
	int prob41 = 1;
	int prob42 = 0;
	if(prob41){ //preceive error - see lab4test.c
		resume(create(lab4test5, 1024,21,"test5",1,CONSOLE));
	}
        if(prob42){ //preceive success - see lab4test.c
        	resume(create(lab4test6, 1024,21,"test6",1,CONSOLE));
        }	


	return OK;
    
}
/*
//victim
void progAA(){
	kprintf("A: pt1\n");
	sleepms(500);
	kprintf("A: pt2\n");
}

//attacker
unsigned long jumpback;

void progBB(){
	int apid = getpid()-1;
	struct procent * prptr = &proctab[apid];
	unsigned long * stackaddress = (unsigned long *)(prptr->prstkptr);
	//kprintf("stackaddress: %d", stackaddress);
	stackaddress += 30;
	//kprintf("stackaddres %d", stackaddress);
	void (*funcBptr)(void) = &funcBB;
	jumpback = *stackaddress;
	*stackaddress = (unsigned long)(funcBptr);
}

void funcBB(){
	kprintf("I am B\n");
	int five3 = 1; //turn off for 5.2
	if(five3){
	unsigned long jumper = jumpback;
	asm("popl %%ebx\n\t"
	    "movl %[jump], %%ebx\n\t"
	    "pushl %%ebx\n\t"
	    //"jmp *(%%eax)\n\t"
		:
		: [jump] "r"(jumper)
		: "%ebx"); 
	}
}

*/
