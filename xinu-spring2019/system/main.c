#include <xinu.h>

uint32 flag = 0;
uint32 flag2 = 0;

int32 testcallback(void) {
	umsg32 ubuffer = receive();
	intmask mask = disable();
	kprintf("Receiver pid: %d  Message received:%d\n",  currpid, ubuffer);
	restore(mask); 
	return OK;
}

int32 testcallback2(void) {
	intmask mask = disable();
	kprintf("Made it to alarm callback!\n");
	restore(mask);
	return OK;
}

int32 testcallback3(void) {
	intmask mask = disable();
	kprintf("Made it to gpf callback!\n");
	restore(mask);
	return OK;
}

void receiverPart4uh(void) {
	if (xsigaction(XSIGIPC,&testcallback,0) != OK) {
		kprintf("registration failed\n");	
		return 1;
	}
	sleepms(100);
	kprintf("This should be printed after callback function\n\n");	
	sleepms(100);
	kprintf("This should be printed after callback function\n\n");
	kprintf("Epilogue of receiver reached\n");
}
void receiverPart4lh(void) {
        if (xsigaction(XSIGIPC,&testcallback,0) != OK) {
		kprintf("registration failed\n");	
		return 1;
	}
	int x = 0;
	for (int i = 0; i < 30000000; i++) {
		x++;
		if (flag2 == 1) {
			kprintf("lower half: this should be printed after the receiver\n\n");
			flag2 = 0;
		}
	}
	kprintf("Epilogue of lower half receiver reached\n");
}
void nonBlockingSendPart4(pid32 receiverProcess, umsg32 msg){
	int32 val = send(receiverProcess, 10);
	flag = 1;
	if(val != OK) {
		kprintf("Could not send: %d\n", 10);
	}
}
void nonBlockingSendPart4_sleep(pid32 receiverProcess, umsg32 msg){
	sleepms(150);
	int32 val = send(receiverProcess, 20);
	flag = 1;
	if(val != OK) {
		kprintf("Could not send: %d\n", 20);
	}
}
int alarmtest = 0;
void alarmProcess(void){
/*        if (xsigaction(XSIGALRM,&testcallback2,200) != OK) {
                kprintf("registration failed\n");
                return 1;
        }
	int x = 0;
	for(unsigned int i = 0; i < 300000000; i++){
		x++;
		if(flag2 == 1){			                        
		//	xsigaction(XSIGALRM,&testcallback2,20);
			kprintf("lower half: this should be printed after alarm\n\n");
			flag2 = 0;
//                        xsigaction(XSIGALRM,&testcallback2,200);

		}
		if(i % 30000000 == 0){
	                        xsigaction(XSIGALRM,&testcallback2,200);

		}
	}
	kprintf("lower half: this should be printed after alarm\n\n");
	kprintf("Epilogue of alarm process reached\n");
*/
	if (xsigaction(XSIGALRM,&testcallback2,1000) != OK) {
                kprintf("registration failed\n");
                return 1;
        }
	if (xsigaction(XSIGALRM,&testcallback2,2000) != OK) {
                kprintf("registration failed\n");
                return 1;
        }
        if (xsigaction(XSIGALRM,&testcallback2,3000) != OK) {
                kprintf("registration failed\n");
                return 1;
        }
        if (xsigaction(XSIGALRM,&testcallback2,4000) != OK) {
                kprintf("registration failed\n");
                return 1;
        }
	for(alarmtest=0; alarmtest<1000000000; alarmtest++){
	}
	kprintf("works!");	
}

void gpfProcess(void){
	if (xsigaction(XSIGGPF,&testcallback3,200) != OK) {
                kprintf("registration failed\n");
                return 1;
        }
//	asm("int $13");
	asm("jmp 0xFFFFFFFF");
	kprintf("testing testing 123");
}

process	main(void)
{

	intmask mask = disable();

	kprintf("\n\n\n");
	kprintf("Test 3 Part 4 Upper Half\n\n");
		
	pid32 receiverProcessuh = create(receiverPart4uh, 1024, 20, "receiveruh", 0);

	resume(receiverProcessuh);
	resume(create(nonBlockingSendPart4, 1024, 20, "NBS1", 2, receiverProcessuh, 1));
	resume(create(nonBlockingSendPart4_sleep, 1024, 20, "NBS1", 2, receiverProcessuh, 1));

	sleepms(2000);

	kprintf("\n\n\n");
	flag = 0;
	kprintf("Test 3 Part 4 Lower Half\n\n");
	pid32 receiverProcesslh = create(receiverPart4lh, 1024, 20, "receiverlh", 0); 
	resume(receiverProcesslh);
	resume(create(nonBlockingSendPart4, 1024, 20, "NBS1", 2, receiverProcesslh, 1));
	resume(create(nonBlockingSendPart4_sleep, 1024, 20, "NBS1", 2, receiverProcesslh, 1));

	sleepms(2000);
	kprintf("\n\n\n");
 //IPC TESTS ^

/*
	kprintf("Test Alarm\n\n");
	flag = 0;
	flag2 = 0;
	pid32 alarmprocesss = create(alarmProcess, 1024, 20, "alrm1", 0);
	resume(alarmprocesss);
*/
	//Alarm Tests^


//	sleepms(200);
/*
	kprintf("Test GPF\n\n");
	
	resume(create(gpfProcess, 1024, 20, "gpf1", 0));
*/
	restore(mask);
	
	return OK;
}
