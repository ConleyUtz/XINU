/*  main.c  - main */

#include <xinu.h>

void progA(void);
void lab4test2(void);
void test51(void);
void test52(void);
void test53(void);
void test54(void);
void test55(void);
void test56(void);
void test57(void);
void test58(void);

void test511(void);
void test521(void);

void lab4test3(void);

int rcvrPID;
int rcvrPID2;

process	main(void)
{
	int totaltest = 1;
if(totaltest){
	int prob31 = 1;
if(prob31){
	kprintf("\n=== TEST 5-3, One receiver, multiple senders ===\n");
	rcvrPID = create(progA, 8192, 20, "test1", 1, CONSOLE);
        resume(create(lab4test2, 8192, 21, "test1", 1, CONSOLE));
        resume(create(lab4test2, 8192, 21, "test1", 1, CONSOLE));
        resume(create(lab4test2, 8192, 21, "test1", 1, CONSOLE));
        resume(create(lab4test2, 8192, 21, "test1", 1, CONSOLE));
        resume(create(lab4test2, 8192, 21, "test1", 1, CONSOLE));
        resume(create(lab4test2, 8192, 21, "test1", 1, CONSOLE));
        resume(create(lab4test2, 8192, 21, "test1", 1, CONSOLE));
        resume(create(lab4test2, 8192, 21, "test1", 1, CONSOLE));
        resume(create(lab4test2, 8192, 21, "test1", 1, CONSOLE));
	sleepms(200);
	resume(rcvrPID);
}
	sleepms(5000);
	int prob32 = 1;
if(prob32){
        kprintf("\n=== TEST 2 5-3 Multiple Senders, Multiple Receivers ===\n");
        rcvrPID = create(progA, 8192, 20, "test1", 1, CONSOLE);
        rcvrPID2 = create(progA, 8192, 20, "test1", 1, CONSOLE);
        resume(create(lab4test2, 8192, 21, "test1", 1, CONSOLE));
        resume(create(lab4test2, 8192, 21, "test1", 1, CONSOLE));
        resume(create(lab4test2, 8192, 21, "test1", 1, CONSOLE));
        resume(create(lab4test2, 8192, 21, "test1", 1, CONSOLE));
        resume(create(lab4test3, 8192, 21, "test1", 1, CONSOLE));
        resume(create(lab4test3, 8192, 21, "test1", 1, CONSOLE));
        resume(create(lab4test3, 8192, 21, "test1", 1, CONSOLE));
        resume(create(lab4test3, 8192, 21, "test1", 1, CONSOLE));
        resume(create(lab4test3, 8192, 21, "test1", 1, CONSOLE));
	resume(rcvrPID);
	resume(rcvrPID2);
}	
	sleepms(5000);
	int prob41 = 1;
if(prob41){
        kprintf("\n=== TEST 3 5-4 | sleepms |  One receiver, multiple senders ===\n");
	rcvrPID = create(test51, 8192, 20, "test1", 1, CONSOLE);
	resume(rcvrPID);
        resume(create(test52, 8192, 20, "test1", 1, CONSOLE));
	sleepms(1000);
        resume(create(test53, 8192, 20, "test1", 1, CONSOLE));
}
	sleepms(7000);
	int prob42 = 1;
if(prob42){
        kprintf("\n=== TEST 4 5-4 | clkdisp | One receiver, multiple senders ===\n");
	intmask mask;
	mask = disable();
        rcvrPID = create(test54, 4096, 20, "test1", 1, CONSOLE);
        resume(rcvrPID);
        resume(create(test55, 4096, 20, "test1", 1, CONSOLE)); 
	//create(test55, 4096, 20, "test1", 1, CONSOLE);
	//create(test57, 4096, 20, "test1", 1, CONSOLE);
	restore(mask);
}

	sleepms(10000);
	kill(rcvrPID);
	kprintf("\n=== TEST 5 5-4 | clkdisp | One receiver, send twice from one sender\n");
	rcvrPID = create(test54, 4096, 20, "test1", 1, CONSOLE);
	resume(rcvrPID);
        resume(create(test58, 4096, 20, "test1", 1, CONSOLE));

	sleepms(10000);
	kill(rcvrPID);
	kprintf("\n=== TEST 6 5-4 | sleepms | One receiver, send twice from one sender\n");
        rcvrPID = create(test511, 8192, 20, "test1", 1, CONSOLE);
        resume(rcvrPID);
        resume(create(test521, 4096, 21, "test1", 1, CONSOLE));
}
}

void progA(){
	uint32 msgcnt = getmsgcount();
	kprintf("Msgcount: %d\n",msgcnt);
	umsg32 a = receive3();
	kprintf("Msg1: %d\n",a);
	a = receive3();
        kprintf("Msg2: %d\n",a);
        a = receive3();
        kprintf("Msg3: %d\n",a);
        a = receive3();
        kprintf("Msg4: %d\n",a);
        a = receive3();
        kprintf("Msg5: %d\n",a);
        a = receive3();
        kprintf("Msg6: %d\n",a);
        a = receive3();
        kprintf("Msg7:%d\n",a);
}

void lab4test2(){
	send3(rcvrPID,'a');
}

void lab4test3(){
        send3(rcvrPID2,'b');
}


void test51(){
	if(regcallback(&mycallback) != OK){
		kprintf("FAILURE.");
		return;
	}
	sleepms(500);
//	kprintf("works!\n");
	kprintf("buf1: %d\n",ubuffer);
	sleepms(3500);
//	kprintf("really works!\n");
        kprintf("buf2: %d\n",ubuffer);

}

void test511(){
        if(regcallback(&mycallback) != OK){
                kprintf("FAILURE.");
                return;
        }
	sleepms(600);
	kprintf("buf1 %d\n",ubuffer);
	sleepms(800);
	kprintf("buf2 %d\n",ubuffer);
}

void test521(){
	send(rcvrPID,'H');
	sleepms(700);
	send(rcvrPID,'I');
}

void test52(){
	send(rcvrPID,'A');
//	kprintf("test 52 done\n");
}

void test53(){
        send(rcvrPID,'B');
  //      kprintf("test 53 done\n");
}
umsg32 ubuffer;
umsg32 ubuffer2 = 1;
int test544 = 0;
void test54(){
        if(regcallback(&mycallback) != OK){
                kprintf("FAILURE.");
                return;
        }
	ubuffer = 0;
	for(unsigned long i = 0; i < 1000000000000; i++){
        	if(ubuffer!=ubuffer2){
			ubuffer2 = ubuffer;
		kprintf("ubuffer: %d\n",ubuffer);
			if(test544==0){
				test544++;
			}
			else if(test544==1){
			        resume(create(test56, 4096, 20, "test1", 1, CONSOLE));
				test544++;
			}
			else if(test544==2){
                                resume(create(test57, 4096, 20, "test1", 1, CONSOLE));
				test544++;
			}
			else if(test544>=3){
				test544++;
				if(test544==8){
					test544 = 3;
					kill(currpid);
				}
			}
		}
	}
}
void test55(){
	send(rcvrPID,'a');
}//put chprio in test54

void test56(){
	sleepms(2);
        send(rcvrPID,'b');
}

void test57(){
	sleepms(2);
        send(rcvrPID,'c');
}

void test58(){
        sleepms(2);
        send(rcvrPID,'d');
	sleepms(5000);
	send(rcvrPID,'e');
}

