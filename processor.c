#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "linked_list.h"

// make linked list have its own file
// setup for this top be transformed to fifo queue 
// make pop in place correct for PCB as well. 
// how to duplicate queue??
	// reread file??
		// generate queue at onset of schedule specific function
		// via function and destroy as function goes??
		// mean generating an array to hold items--> dynamic array.....
//fixed:
// made the linked list pop_back return item. 
// try to push item back into queue. --> make sure that we can do it curcularly and make sure push takes in a PCB correctly






int main(int argc, char *argv[])
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
  printf("\tpush iteration %d\n",i);
  print(&head);
}
 printf("outside:%d\n", head->data);

for(int i = 0; i < 10 ; i ++)
{
//currentPCB = pop_back(&head, 0);
currentPCB = pop(&head, i);

   printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n ");
   printf("compTime       %d\n "  ,currentPCB->process->compTime    );
   printf("waitTime       %d\n "  ,currentPCB->process->waitTime    );
   printf("turnTime       %d\n "  ,currentPCB->process->turnTime    );
   printf("respTime       %d\n "  ,currentPCB->process->respTime    );
   printf("contextCount   %d\n\n ",currentPCB->process->contextCount);
   printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n ");

  printf("\t\tpop iteration %d\n",i);
  push_back(&head, currentPCB); 
  print(&head);

  
}


return 0;
 
}

