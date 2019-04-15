/* ipc.h - */

/* Send/Receive - Blocking/Non-blocking */

#define XDEBUG	0

#define	IPCSND	0
#define IPCRCV	1
#define IPCBLK	0
#define IPCNBK	1

/* pmessage struct */

struct pmessage {
	umsg32 sendermsg;
	pid32 senderid;
};
