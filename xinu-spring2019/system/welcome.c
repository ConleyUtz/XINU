/* welcome.c - welcome */

#include <xinu.h>

void welcome(void){

        kprintf("\nHello World!\n");
	kprintf("\nThis is Conley Utz's (cutz@purdue.edu) version of XINU!\n");
        kprintf("\nI'm the first XINU app and running function main() in system/main.c.\n");
        kprintf("\nI was created by nulluser() in system/initialize.c using create().\n");
        kprintf("\nMy creator will turn itself into the do-nothing null process.\n");
        kprintf("\nI will create a second XINU app that runs shell() in shell/shell.c as an example.\n");
        kprintf("\nYou can do something else, or do nothing; it's completely up to you.\n");
        kprintf("\n...creating a shell\n");


}

