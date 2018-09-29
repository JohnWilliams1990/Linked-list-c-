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

}pcb,* pcbPtr ;


typedef struct node {
  struct node* next;
  struct node* prev;
  int data;
  pcb process;
} node, *nodePtr;


void newNode( nodePtr * arg)
{
  (*arg) = calloc(1, sizeof(struct node));
  (*arg)->prev = NULL;
  (*arg)->next = NULL;
  (*arg)->data = 0;
  printf("Inside: %d\n",(*arg)->data);
}
// push element to back of list
void push_back( nodePtr * arg)
{
  int counter = 1;
  struct node* curPtr = (*arg);

if ( curPtr == NULL)
{
printf("HERE\n\n");
//newNode(arg);
(*arg) = calloc(1, sizeof(struct node));
(*arg)->prev = NULL;
(*arg)->next = NULL;
(*arg)->data = 0;


return;
}
  while (curPtr->next != NULL)
  {
    curPtr = curPtr->next;
    counter +=1;
  }
  curPtr->next = calloc(1, sizeof(struct node));
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
	  free((*arg));
	  (*arg) = NULL;
	  //free(curPtr);
	  //curPtr = NULL;
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
   printf("%d ",curPtr->data);
   //prev = curPtr;
   curPtr = curPtr->next;
  }
   printf("\n\n");
}

int main()
{

//struct node * head = NULL; 

nodePtr head = NULL;
//newNode(&head);

//  printf("outside:%d\n", head->data);
for(int i = 0; i < 10 ; i ++)
{
  push_back(&head);
  printf("pushed at iteration %d\n",i);
  print(&head);
}
 printf("outside:%d\n", head->data);

for(int i = 0; i < 10 ; i ++)
{
  pop_back(&head);
  printf("pushed at iteration %d\n",i);
  print(&head);
}

pop(&head,1);
print(&head);

//pop_back(&head);
//print(&head);
//pop_back(&head);

//print(&head);
return 0;


 
}

