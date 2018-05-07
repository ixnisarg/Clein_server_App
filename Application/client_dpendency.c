#include"test.h"
#include"client_dpendency.h"

frame head;
serial *ts;
void display()
{
	int cnt=0;
	cnt++;
	int data,i,sw;
	printf(": : MENU : :\n");
	printf("1)Communication Type?\n");
	printf("\t1.TCP/TCP\n\t2.TCP/UDP\n\t3.UDP/TCP\n\t4.UDP/UDP\n");
	scanf("%d",&sw);
	switch(sw)
	{
		case 1:	head.in=tcp;
				head.out=tcp;
				break;
		case 2:     head.in=tcp;
				head.out=udp;
				break;
		case 3:     head.in=udp;
				head.out=tcp;
				break;
		case 4:     head.in=udp;
				head.out=udp;
				break;
	}
	printf("2)Message Type?\n");
	printf("\t1.List\n\t2.Thread\n\t3.Fork\n\t4.IPC\n");
	scanf("%d",&i);
	switch(i)
	{
	case 1:	head.ch=dll;
				break;
	case 2:	head.ch=Thread;
				break;
	case 3:	head.ch=Fork;
				break;
	case 4:	head.ch=ipc;
				break;
	}
	puts("Frame Created\n");
}

void Sending_protocol(char *port,char *port1)
{
	Udp_client(port);//creates uDP socket
	Tcp_client(port1);//creates tcp socket	
	if(fork()==0)
	{
		if(head.in==udp)
		{
		if(sendto(client_u_fd,(void *)&head,sizeof(frame),0,(struct sockaddr *)&serv_addr,addr_size)<0)
	
        {printf("\n Error :sending error\n");exit(0);}
		printf("UDP Sending:");
		printf("%d | %d | %d | %d |...\n",head.seq_num,head.in,head.ch,head.out);
	}//child
	else
	{
		if(head.in==tcp)
		{
			if(send(client_fd, (void *)&head, sizeof(frame),0)<0)
			{printf("\n Error :sending error\n");exit(0);}
			puts("TCP Sending:");
			printf("%d | %d | %d | %d |...\n\n ",head.seq_num,head.in,head.ch,head.out);
		}
		}//parent
	}
}
void receveing_protocol(void)
{
	if(head.out==udp)
	{
		int addr_size=sizeof(serv_addr);
		if(recvfrom(client_u_fd,(void *)&head,sizeof(frame),0,0,0)<0)
		{perror("recvfrom");exit(0);}
		printf("received UDP:%d\n",client_u_fd);
		printf("%d | %d | %d | %d |...\n ",head.seq_num,head.in,head.ch,head.out);
		close(client_u_fd);
	}
	else
	{
			if(recv(client_fd, (void *)&head, sizeof(frame),0)<0){perror("recv");return ;}
			else {puts("received TCP:");}
			printf("%d | %d | %d | %d |...\n ",head.seq_num,head.in,head.ch,head.out);
			close(client_fd);
	}
}
int Tcp_client(char *port)
{
	if((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {printf("\n Error : Could not create socket \n"); return 1; } 

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(*port);
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");//inet_addr(argv[2])
	printf("TCP socket created:%d\n",client_fd);
	sleep(1);
	if( connect(client_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {printf("\n Error : Connect Failed \n");return 1;} 
	printf("Connected....\n");

}

int Udp_client(char *port1)
{
	if((client_u_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {printf("\n Error : Could not create socket \n"); return 1; } 
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(*port1);
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");//inet_addr(argv[2])
	printf("UDP socket created:%d\n",client_u_fd);
}








