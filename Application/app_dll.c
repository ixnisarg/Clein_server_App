#include"test.h"

frame head_dll;

typedef struct dll{
      int data;
      struct dll *back;
      struct dll *next;
}node;

void msq_dll_recv();
void display_menu(void);
void add_front(node **,int);
void print(node *temp);

void msq_dll_recv()
{
      int size=sizeof(
      frame),i;
      node *head=NULL;
      if(msgrcv(msgget(3,IPC_CREAT | 0666), &head_dll, sizeof(frame), 0, 0)<0)
      {perror("msgrcv");return;}
      puts("Message Received IN APP_dll\n");
      if(head_dll.ch==1)
      {
            for(i=0;i<=(int)head_dll.payload;i++)
            add_front(&head,i);
            print(head);
      }
      if (msgsnd(msgget(3,IPC_CREAT | 0666), &head_dll, size, 0) < 0)
      {perror("msgsnd");return ;}
      
      puts("Back to main\n");
      

}

void print(node *temp)
{
      while(temp)
      {
            printf("%d->",temp->data);
            temp=temp->next;
      }
      printf("NULL\n");
}
void add_front(node **headref,int payload)
{
      node *nu=(node *)calloc(1,sizeof(node));
      nu->data=payload;

      if(headref==NULL)
      {
            nu->next=nu->back=NULL;
            *headref=nu;
      }
      else
      {	
            nu->back = NULL;
            nu->next=*headref;
            *headref=nu;
      }
}
