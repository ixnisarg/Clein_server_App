#ifndef __CLIENT_DPENDENCY_H_ 
#define __CLIENT_DPENDENCY_H_

#include"test.h"
frame head;
int client_fd;
int client_u_fd;
struct sockaddr_in serv_addr;
int addr_size=sizeof(serv_addr);


int Tcp_client();
int Udp_client();

#endif