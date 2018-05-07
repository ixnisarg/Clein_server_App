#include"test.h"
#include<pthread.h>
frame head_th;
int app_thread(int);
void *PrintHello(void *);
void msq_thread_recv(void)
{
	int size=sizeof(frame);
	if(msgrcv(msgget(3,IPC_CREAT | 0666), &head_th, sizeof(frame), 0, 0)<0)
	{perror("msgrcv");return;}
	puts("Message Received IN APP_Thread\n");
	if(head_th.ch==2)
	{
		int status=app_thread((int)head_th.payload);
		if(status==-1){puts("thread creation error\n");exit(0);}
	}
	if (msgsnd(msgget(3,IPC_CREAT | 0666), &head_th, size, 0) < 0)
	{perror("msgsnd");return ;}
	
		puts("Back to main\n");
}

int app_thread(int NUM_THREADS)
 {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    for(t=0; t<NUM_THREADS; t++){
       printf("In main: creating thread %ld\n", t);
       rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
       if (rc){
          printf("ERROR; return code from pthread_create() is %d\n", rc);
          exit(-1);
       }
    }
    pthread_exit(NULL);
 }
 
void *PrintHello(void *threadid)
{
    long tid;
    tid = (long)threadid;
    printf("Hello World! It's me, thread #%ld!\n", tid);
    pthread_exit(NULL);
}