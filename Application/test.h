#ifndef __TEST_H_
#define __TEST_H_

#include<stdio.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ipc.h> 
#include <sys/msg.h>
#pragma pack(1)

#define NRM  "\x1B[0m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define CYN  "\x1B[36m"
#define WHT  "\x1B[37m"
#define ULN  "\e[4m"
#define BOLD  "\e[1m"
#define ITALIC  "\e[3m"
#define STRIKE  "\e[9m"
#define END  "\e[0m"
#define BLINK "\e[5m"


typedef enum tag_a{tcp=1,udp}msg_type;
typedef enum tag_b{dll=1,Thread,Fork,ipc}msg_op;

typedef	struct tag{

	unsigned short int seq_num;	
	msg_type in;
	msg_type out;
	msg_op ch;
	unsigned int payload_size;
	void *payload;
}frame;

#endif