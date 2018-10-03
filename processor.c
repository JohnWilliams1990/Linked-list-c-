#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "linked_list.h"


//sum function having issues across platforms---> use recursion ??

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
  nodePtr currentPCB = calloc(1, sizeof(struct node));
  currentPCB->process = calloc(1, sizeof(struct pcb_t));
  int index = 0;

  while (!feof (file)){
    index = 0;
    fscanf (file, "%d", &index);    
    currentPCB->process->pid = index;
    fscanf (file, "%d", &index);    
    currentPCB->process->arrival_time = index;
    fscanf (file, "%d", &index);    
    currentPCB->process->burst_time = index; 
    if (currentPCB->process->pid == 0){return head;}  
    push_back(&head, currentPCB);
    //print(&head);
  }
  return head;
}

int getTime(nodePtr head)
{
  int sum = 0;
  nodePtr curPtr = head;
//  sum += curPtr->process->burst_time;
//  printf("%d\n",  curPtr->process->burst_time);
  //while (curPtr->next != NULL)
  while (curPtr != NULL)
  {
  // printf("%d\n",  curPtr->process->burst_time);
   sum += curPtr->process->burst_time;
   curPtr = curPtr->next;
  // printf("\t\t%d\n",  curPtr->process->burst_time);
  }

return sum; 

}


nodePtr FCFS(nodePtr header) //; nodePtr RunningQueue)
{
nodePtr head = header;
  int time = 0;
  int curPcbVal = 0;
  //nodePtr currentPCB = calloc(1, sizeof(struct node));
  //currentPCB->process = calloc(1, sizeof(struct pcb_t));
  nodePtr currentPCB = NULL;// = calloc(1, sizeof(struct node));
  //  nodePtr currentPCB;
  int stop = getTime(head);
  //start loop early
  int timeRemaining = 0;
//  currentPCB = pop(&head, curPcbVal);
// sum up all burst times and decremet till then ??
// loop linked list and wait until we see duplocate pid

//  if (time >=currentPCB->process->){ // pop new process of of ready queue      
//  currentPCB = pop(&head, curPcbVal);
//  }

  while (time < stop )
  {
  if (timeRemaining == 0){ // pop new process of of ready queue      
    if (currentPCB != NULL && currentPCB->process->pid != 0)    
    { push_back(&head, currentPCB);}
     
     currentPCB = pop(&head, curPcbVal);
     timeRemaining =  currentPCB->process->burst_time;
     currentPCB->process->waitTime = time - currentPCB->process->arrival_time;
  }

//  print(&head);
   printf("Time Remaining: %d\n\n",timeRemaining);


   printf("---------------------- time %d-----------------------------\n ", time);
   printf("-----------------------------------------------------------\n ");
   printf("pid            %d\n "  ,currentPCB->process->pid         );
   printf("arrival_time   %d\n "  ,currentPCB->process->arrival_time);
   printf("burst_time     %d\n "  ,currentPCB->process->burst_time  );
   printf("finishTime     %d\n "  ,currentPCB->process->finishTime  );
   printf("waitTime       %d\n "  ,currentPCB->process->waitTime    );
   printf("turnTime       %d\n "  ,currentPCB->process->turnTime    );
   printf("respTime       %d\n "  ,currentPCB->process->respTime    );
   printf("contextCount   %d\n\n ",currentPCB->process->contextCount);
   printf("-----------------------------------------------------------\n ");

  time += 1;
  timeRemaining -= 1;
  
  if (timeRemaining == 0){ // pop new process of of ready queue      
  
     currentPCB->process->finishTime = time ;

     currentPCB->process->turnTime = currentPCB->process->finishTime - currentPCB->process->arrival_time;
     currentPCB->process->respTime = currentPCB->process->waitTime;
  }
  }
  
  push_back(&head, currentPCB); 
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
  //file = fopen ("input10", "r");
  file = fopen ("input5", "r");
  

//struct node * head = NULL; 

nodePtr head = NULL;
//newNode(&head);

head = (nodePtr) read_in_file( file, head);




int time = getTime( head);
printf("---->%d\n\n\n", time);



nodePtr currentPCB = calloc(1, sizeof(struct node));
currentPCB->process = calloc(1, sizeof(struct pcb_t));

head = FCFS(head);

  printf("~~~~~~~~~~~~~~~~~~~~~~~sdsd~~~~~~~~~~~~~~~~~~~~~\n ");
  print(&head);
  printf("~~~~~~~~~~~~~~~~~~~~~~~sdsd~~~~~~~~~~~~~~~~~~~~~\n ");
return 0;
 
}

