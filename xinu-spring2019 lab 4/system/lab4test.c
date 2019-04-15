/* lab4test.c - lab4test */

#include <xinu.h>
pid32   rcvrPID;
#include <stdlib.h>
void lab4test(void){
/*	kprintf("Receive No Block\n");
	xfcntl(IPCRCV,IPCNBK);
	kprintf("Receive Block\n");
	xfcntl(IPCRCV,IPCBLK);
	kprintf("Send No Block\n");
	xfcntl(IPCSND,IPCNBK);
	kprintf("Send Block\n");
	xfcntl(IPCSND,IPCBLK);
	kprintf("SYSERR1\n");
	xfcntl(5,IPCBLK);
	kprintf("SYSERR2\n");
	xfcntl(IPCSND,5);
*/
	umsg32 newmsg = receive();
	kprintf("%c",newmsg);
	newmsg = receive();
	kprintf("%c",newmsg);
	newmsg = receive();
	kprintf("%c",newmsg);
}

void lab4test2(void){
	xfcntl(IPCSND,IPCBLK);	
	send(rcvrPID,'H');
}

void lab4test3(void){
	xfcntl(IPCSND,IPCBLK);
	send(rcvrPID,'I');
}

void lab4test4(void){
	xfcntl(IPCSND,IPCBLK);
	send(rcvrPID,'!');
}

struct pmessage * wow;
struct pmessage wow3;

void lab4test5(void){ //preceive error
	struct	procent * tester;
	tester = &proctab[currpid];
	tester->prmsg = 'c';
	tester->prsenderid = 3;
	wow = &wow3;
	preceive(wow);
}

void lab4test6(void){ //preceive working
        struct  procent * tester;
        tester = &proctab[currpid];
        tester->prmsg = 'c';
        tester->prsenderid = 3;
        struct pmessage * wow2;
	struct pmessage wow4;
	wow2 = &wow4;
        preceive(wow2);
        kprintf("%c\n",wow2->sendermsg);
        kprintf("%d\n",wow2->senderid);
}

