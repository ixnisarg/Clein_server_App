#include"test.h"

void init_server(char *,char *);
int main(int argc,char **argv)
{
	if(argc<2){puts("Try this\nEXE portno1 portno2\n");return 0;}
	init_server(argv[1],argv[2]);
	puts("sent from server\n");
}