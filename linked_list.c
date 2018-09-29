#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

// todo: mkae linked list functions have error checking;
// make linked list have ability to be substaciated without any elements
// ---> merge the push back with newNode

// make linked list have its own file
// setup for this top be transformed to fifo queue 
// make it circulary linked?? or only for round robin exercise??

struct node {
  struct node* next;
  struct node* prev;
  int data;
};


void newNode(struct node ** arg)
{
  (*arg) = calloc(1, sizeof(struct node));
  (*arg)->prev = NULL;
  (*arg)->next = NULL;
  (*arg)->data = 0;
  printf("Inside: %d\n",(*arg)->data);
}
// push element to back of list
void push_back(struct node ** arg)
{
int counter = 1;
struct node* curPtr = (*arg);
struct node* prev = (*arg)->prev;

  while (curPtr->next != NULL)
  {
   prev = curPtr;
   curPtr = curPtr->next;
   counter +=1;
  }
curPtr->next = calloc(1, sizeof(struct node));
curPtr->next->prev = curPtr;
curPtr->next->data = counter;
}

// pop elememt from list at specif index
void pop(struct node ** arg, int index)
{
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
void pop_back(struct node ** arg)
{
int counter = 0;
struct node* curPtr = (*arg);
struct node* prev = (*arg)->prev;

  while (curPtr->next != NULL)
  {
   prev = curPtr;
   curPtr = curPtr->next;
   counter +=1;
  }


prev->next = curPtr->next;
free(curPtr);
//curPtr->next->prev = prev;
}

void print(struct node ** arg)
{
struct node* curPtr = (*arg);
struct node* prev = (*arg)->prev;

  while (curPtr->next != NULL)
  {
   printf("%d ",curPtr->data);
   prev = curPtr;
   curPtr = curPtr->next;
  }

   printf("\n\n");


}

int main()
{

struct node * head; 
//head->data = 0;
//head = calloc(1, sizeof(struct node));
//  printf("outside:%d\n", head->data);
newNode(&head);

  printf("outside:%d\n", head->data);
push_back(&head);
  printf("\tpush one element:\n");
  printf("outside:%d\n", head->data);
 printf("outside next:%d\n\n", head->next->data);

  printf("\tpush one element:\n");

push_back(&head);
  printf("outside:%d\n", head->data);

print(&head);
 printf("outside next:%d\n", head->next->data);
 printf("outside next:%d\n", head->next->next->data);
  printf("\tpush one element:\n");
push_back(&head);
 printf("outside next:%d\n\n", head->next->next->next->data);

  printf("\tpop one element at position 2:\n");

pop(&head,2);

  printf("outside:%d\n", head->data);
 printf("outside next:%d\n", head->next->data);
 printf("outside next:%d\n\n\n", head->next->next->data);
// printf("outside next:%d\n", head->next->next->next->data);
  printf("\tpop back one element:\n");
pop_back(&head);
  printf("outside:%d\n", head->data);
 printf("outside next:%d\n", head->next->data);


  printf("\tpop back one element:\n");
pop_back(&head);
  printf("outside:%d\n", head->data);
 printf("outside next:%d\n", head->next->data);

return 0;


 //printf("outside next:%d\n", head->next->data);
 //printf("outside next:%d\n", head->next->next->data);
 //printf("outside next:%d\n", head->next->next->next->data);
}

