#include<stdio.h>
#include<time.h>

void main()
{
		time_t time;
		struct tm *timeinfo;
		
		time(&time);
		timeinfo=localtime(&time);
		printf("Current Local time:%s\n",asctime(timeinfo));
	
}