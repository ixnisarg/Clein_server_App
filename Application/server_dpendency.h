#ifndef __SERVER_DPENDENCY_H
#define __SERVER_DPENDENCY_H_
#include"test.h"



int server_fd = 0, connfd = 0;
int udp_fd=0;
struct sockaddr_in serv_addr;
struct sockaddr_in cli_addr;
int cli_size=sizeof(cli_addr);
int addr_size=sizeof(serv_addr);
void init_server();
void UDP_socket();
void TCP_socket();
void func1();
void func2();
void switchCHOICE();

int msq_server(void);
void msq_dll_recv(void);
void msq_thread_recv(void);
void msq_ipc_recv(void);


#endif