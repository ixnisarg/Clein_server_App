#include"test.h"
#
frame head_ipc;
void add_ipc();

void msq_ipc_recv()
{
	int size=sizeof(frame),i;
	if(msgrcv(msgget(3,IPC_CREAT | 0666), &head_ipc, sizeof(frame), 0, 0)<0)
	{perror("msgrcv");return;}
	puts("Message Received IN APP_ipc\n");
	if(head_ipc.ch==4)
	{
		
		add_ipc();
	}
	if (msgsnd(msgget(3,IPC_CREAT | 0666), &head_ipc, size, 0) < 0)
	{perror("msgsnd");return ;}
			
	puts("Back to main\n");
}

void add_ipc()
{
		mkfifo("newfifo",0660);
		puts("named pipe created\n");
}