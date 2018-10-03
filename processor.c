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



nodePtr read_in_file(FILE* file, nodePtr head){

  

//  nodePtr head = (*header);

  nodePtr currentPCB = calloc(1, sizeof(struct node));
  currentPCB->process = calloc(1, sizeof(struct pcb_t));
  //int index = 0;
  //fscanf (file, "%d", &index);    
  //matPtr->left.rows = index;
  //index =0;
  //fscanf (file, "%d", &index);    
  //matPtr->left.cols = index;  
  //populate_matrix(&matPtr->left);



  while (!feof (file)){

  int index = 0;
  fscanf (file, "%d", &index);    
  //printf("-->%d\n", index);
  currentPCB->process->pid = index;

  fscanf (file, "%d", &index);    
  //printf("-->%d\n", index);
  currentPCB->process->arrival_time = index;

  fscanf (file, "%d", &index);    
  //printf("-->%d\n", index);
  currentPCB->process->burst_time = index;

  // printf("pid            %d\n "  ,currentPCB->process->pid         );
  // printf("arrival_time   %d\n "  ,currentPCB->process->arrival_time);
  // printf("burst_time     %d\n "  ,currentPCB->process->burst_time  );

if (currentPCB->process->pid == 0){return head;}

  push_back(&head, currentPCB);

  //print(&head);

  }

return head;

}

int main(int argc, char *argv[])
{

//  if (argc < 3){
//    printf("Usage: %s input_file output_file\n", argv[0]);
//    exit(-1);
//  }




  FILE* file;
  //file = fopen (argv[1], "r");
  file = fopen ("input10", "r");
  

//struct node * head = NULL; 

nodePtr head = NULL;
//newNode(&head);

head = (nodePtr) read_in_file( file, head);

nodePtr currentPCB = calloc(1, sizeof(struct node));
currentPCB->process = calloc(1, sizeof(struct pcb_t));

//  printf("outside:%d\n", head->data);

// TESTING CODE 
//for(int i = 0; i < 10 ; i ++)
//{
//currentPCB->process->compTime = i;
//  push_back(&head, currentPCB);
//  printf("\tpush iteration %d\n",i);
//  print(&head);
//}
// printf("outside:%d\n", head->data);
//
//for(int i = 0; i < 10 ; i ++)
//{
////currentPCB = pop_back(&head, 0);
//currentPCB = pop(&head, i);
//
//   printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n ");
//   printf("compTime       %d\n "  ,currentPCB->process->compTime    );
//   printf("waitTime       %d\n "  ,currentPCB->process->waitTime    );
//   printf("turnTime       %d\n "  ,currentPCB->process->turnTime    );
//   printf("respTime       %d\n "  ,currentPCB->process->respTime    );
//   printf("contextCount   %d\n\n ",currentPCB->process->contextCount);
//   printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n ");
//
//  printf("\t\tpop iteration %d\n",i);
//  push_back(&head, currentPCB); 
//  print(&head);
//
//  
//}

for(int i = 0; i < 10 ; i ++)
{
//currentPCB = pop_back(&head, 0);
currentPCB = pop(&head, 0);

   printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n ");
   printf("pid            %d\n "  ,currentPCB->process->pid         );
   printf("arrival_time   %d\n "  ,currentPCB->process->arrival_time);
   printf("burst_time     %d\n "  ,currentPCB->process->burst_time  );
   printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n ");

  printf("\t\tpop iteration %d\n",i);
  push_back(&head, currentPCB); 

  print(&head);


}

//  printf("~~~~~~~~~~~~~~~~~~~~~~~sdsd~~~~~~~~~~~~~~~~~~~~~\n ");
//  print(&head);

return 0;
 
}

