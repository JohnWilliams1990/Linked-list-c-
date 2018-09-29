#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// todo: mkae linked list functions have error checking;
// make linked list have ability to be substaciated without any elements
// ---> merge the push back with newNode

// make linked list have its own file
// setup for this top be transformed to fifo queue 
// make it circulary linked?? or only for round robin exercise??

typedef struct pcb_t {
int compTime;
int waitTime;
int turnTime;
int respTime;
int contextCount;
} pcb,* pcbPtr ;

typedef struct node {
  struct node* next;
  struct node* prev;
  int data;
  pcbPtr process;
} node, *nodePtr;

// push element to back of list
void push_back( nodePtr * arg, node* item)
{
  int counter = 1;
  struct node* curPtr = (*arg);

if ( curPtr == NULL)
{
  (*arg) = calloc(1, sizeof(struct node));
  (*arg)->prev = NULL;
  (*arg)->next = NULL;

  (*arg)->process = calloc(1, sizeof(struct pcb_t));
  (*arg)->process->compTime = item->process->compTime;
  (*arg)->process->waitTime = item->process->waitTime;
  (*arg)->process->turnTime = item->process->turnTime;
  (*arg)->process->respTime = item->process->respTime;
  (*arg)->process->contextCount = item->process->contextCount;

  (*arg)->data = 0;
  return;
}
  while (curPtr->next != NULL)
  {
    curPtr = curPtr->next;
    counter +=1;
  }
  curPtr->next = calloc(1, sizeof(struct node));

  curPtr->next->process = calloc(1, sizeof(struct pcb_t));
  curPtr->next->process->compTime = item->process->compTime;
  curPtr->next->process->waitTime = item->process->waitTime;
  curPtr->next->process->turnTime = item->process->turnTime;
  curPtr->next->process->respTime = item->process->respTime;
  curPtr->next->process->contextCount = item->process->contextCount;
  curPtr->next->prev = curPtr;
  curPtr->next->data = counter;
}

// pop elememt from list at specif index
void pop( nodePtr * arg, int index)
{

if ((*arg) == NULL)
{
printf("HERE\n\n");
return;
}


int counter = 0;
struct node* curPtr = (*arg);
struct node* prev = (*arg)->prev;

  while (curPtr->next != NULL && counter < index)
  {
    prev = curPtr;
    curPtr = curPtr->next;
    counter +=1;
  }
  prev->next = curPtr->next;
  curPtr->next->prev = prev;
  free(curPtr);
}

// pop element off of end
void pop_back( nodePtr * arg)
{
  int counter = 0;
  struct node* curPtr = (*arg);
  struct node* prev = (*arg)->prev;

  if (curPtr == NULL) { exit(0);  }
  if (curPtr->next == NULL && curPtr->prev == NULL)
  {
      
    free((*arg)->process);
    free((*arg));
    (*arg) = NULL;
    return;
  }

  while (curPtr->next != NULL)
  {
    prev = curPtr;
    curPtr = curPtr->next;
    counter +=1;
  }
  if (prev != NULL) {
	  prev->next = curPtr->next;
  }

  free(curPtr->process);
  curPtr->process = NULL;
  free(curPtr);
  curPtr = NULL;
}

void print( nodePtr * arg)
{
  struct node* curPtr = (*arg);

  if (curPtr == NULL)
  {
    return; 
  }
  while (curPtr->next != NULL)
  {
   //printf("%d\n ",curPtr->data);
   printf("compTime    %d\n ",curPtr->next->process->compTime    );
   printf("waitTime    %d\n ",curPtr->next->process->waitTime    );
   printf("turnTime    %d\n ",curPtr->next->process->turnTime    );
   printf("respTime    %d\n ",curPtr->next->process->respTime    );
   printf("contextCount%d\n\n ",curPtr->next->process->contextCount);
   curPtr = curPtr->next;
  }
   printf("\n\n");
}

int main()
{

//struct node * head = NULL; 

nodePtr head = NULL;
//newNode(&head);
nodePtr currentPCB = calloc(1, sizeof(struct node));
currentPCB->process = calloc(1, sizeof(struct pcb_t));
//  printf("outside:%d\n", head->data);
for(int i = 0; i < 10 ; i ++)
{
currentPCB->process->compTime = i;
  push_back(&head, currentPCB);
  printf("push iteration %d\n",i);
  print(&head);
}
 printf("outside:%d\n", head->data);

for(int i = 0; i < 10 ; i ++)
{
  pop_back(&head);
  printf("pop iteration %d\n",i);
  print(&head);
}

return 0;
 
}

