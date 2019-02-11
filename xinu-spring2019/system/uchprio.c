/* uchprio.c - uchprio */

#include <xinu.h>

pri16 uchprio(pid32 pid, pri16 newprio){
	int a = pid;
	int b = newprio;
	int c;
	kprintf("arrives right before ASM\n");
        
	asm ("movl %[pid], %%ebx\n\t" 
	     "movl %[newprio], %%ecx\n\t" 
	     "int $36\n\t" 
	     "movl %%eax, %[oldPid]"
                : [oldPid] "=r"(c)     
                : [pid] "r"(a), [newprio] "r"(b)        
                : "%eax", "%ebx", "%ecx");
	
	kprintf("After ASM: returing %d\n",c);
	return c;	
}
