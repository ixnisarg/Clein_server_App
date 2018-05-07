#include"test.h"
#include"server_dpendency.h"
frame head;

void init_server(char *port,char *port1)
{
			UDP_socket(port);
			TCP_socket(port1);
	if(fork()==0)
	{
	if(recvfrom(udp_fd,(void *)&head,sizeof(head),0,(struct sockaddr *)&serv_addr, &addr_size)<0)
			{printf("\n Error :receiving error\n");return ;}
			else{
			puts("Recv UDP:");
			printf("%d | %d | %d | %d |...\n",head.seq_num,head.in,head.ch,head.out);
			}
	switchCHOICE();
	}//child
	else 
	{
	if(recv(connfd,(void *)&head,sizeof(head),0)<0)
			{printf("\n Error :receiving error\n");return ;}
			printf("Received TCP:");
			printf("%d | %d | %d | %d |...\n",head.seq_num,head.in,head.ch,head.out);
		switchCHOICE();
	}//parent

}

void switchCHOICE()
{
		if(head.out==tcp)
		{
			close(udp_fd);
			func1();	
		}
		else if(head.out==udp)
		{	close(connfd);
			func2();	
		}
		else
			puts("ERROR:switching sending Recvieng\n\n");
}
void UDP_socket(char *port)
{
	udp_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(udp_fd<0)	{perror("socket()");return;}	

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(*port); 
    if(bind(udp_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))<0)
	{perror("bind()");return;}	
	printf("UDP socket created:%d\n",udp_fd);
	
}

void TCP_socket(char *port1)
{
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fd<0)	{perror("socket()");return;}	
	dup2(server_fd,5);

	int on=1;
	if(setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))<0)
	{{perror("setsockopt()");return;}	}
	
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(*port1); 
    if(bind(server_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))<0)
	{perror("bind()");return;}	
    if(listen(server_fd, 10)<0) //’10’ specifies maximum number of client connections that server will queue
	{{perror("listen()");return;}	}
	printf("TCP socket created:%d\n",server_fd);
	connfd = accept(server_fd, (struct sockaddr*)&cli_addr,&cli_size); 
		if(connfd<0)	{{perror("accept()");printf("Accept FD:%d\n",connfd);return;}}
		
}
void func1()//TCP
{
		puts("FUNCTION:1\n");
		msq_server();
		if(send(connfd,(void *)&head,sizeof(head),0)<0){printf("\n Error :TCP_sending error\n");exit(0);}
		puts("This is TCP packets Sending\n");
		sleep(1);
}
void func2()//UDP
{
		puts("FUNCTION:2\n");
		msq_server();
		int addr_size=sizeof(serv_addr);
		if(sendto(udp_fd,(void *)&head,sizeof(frame),0,(struct sockaddr *)&cli_addr,cli_size)<0)
        {printf("\n Fd:%d Error :UDP_sending error Report\n",udp_fd);exit(0) ;}
		printf("\n Fd:%d This is UDP datagram Sending\n",udp_fd);
		sleep(1);
}
int msq_server()
{	
/*Here sending via Message queue to other File*/
		int size=sizeof(frame);
		if (msgsnd(msgget(3,IPC_CREAT | 0666), &head, size, 0) < 0){perror("msgsnd");return -1;}
		
		if(head.ch==1)
		{msq_dll_recv();}
		
		if(head.ch==2)
		{msq_thread_recv();}
	
		if(head.ch==4)
		{msq_ipc_recv();}
	
		if(msgrcv(msgget(3,IPC_CREAT | 0666), &head, sizeof(frame), 0, 0)<0)
		{perror("msgrcv");return -1;}		
}




