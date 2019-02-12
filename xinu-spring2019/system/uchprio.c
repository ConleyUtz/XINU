/* uchprio.c - uchprio */

#include <xinu.h>

pri16 uchprio(pid32 pid, pri16 newprio){

	intmask mask;

	mask = disable(); //cli

	int a = pid;	//values to be loaded into registers	
	int b = newprio;
	int c;

	asm ("movl %[pid], %%ebx\n\t" 	  //moving value of pid in %ebx
	     "movl %[newprio], %%ecx\n\t" //moving value of newprio in %ecx
	     "int $36\n\t" 		  //calling _Xint36
	     "movl %%eax, %[oldPid]"	  //moving value of %eax (return value) to c-type integer
                : [oldPid] "=r"(c)     
                : [pid] "r"(a), [newprio] "r"(b)        
                : "%eax", "%ebx", "%ecx");
	
	restore(mask); //sti

	return c;	
}
