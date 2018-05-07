#include"test.h"

void display();
void Sending_protocol(char *,char * );
void receveing_protocol(void);

int main(int argc,char **argv)
{
	if(argc<2){puts("Try this\nEXE portno1 portno2\n");exit(0);}
		display();
		Sending_protocol(argv[1],argv[2]);
		receveing_protocol();
}