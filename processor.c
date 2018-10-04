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
  while (curPtr != NULL)
  {
    sum += curPtr->process->burst_time;
    curPtr = curPtr->next;
  }
  return sum; 
}


nodePtr FCFS(nodePtr header)
{
  nodePtr head = header;
  int time = 0;
  int curPcbVal = 0;
  nodePtr currentPCB = NULL;//tmp pointer for item in queue
  int stop = getTime(head);
  
  int timeRemaining = 0;

  while (time < stop )
  {
    if (timeRemaining == 0){ // pop new process of of ready queue      
      if (currentPCB != NULL && currentPCB->process->pid != 0)    
      { push_back(&head, currentPCB);}
     
      currentPCB = pop(&head, curPcbVal);
      timeRemaining =  currentPCB->process->burst_time;
      currentPCB->process->waitTime = time - currentPCB->process->arrival_time;
    }

  // printf("Time Remaining: %d\n\n",timeRemaining);
  // printf("---------------------- time %d-----------------------------\n ", time);
  // printf("-----------------------------------------------------------\n ");
  // printf("pid            %d\n "  ,currentPCB->process->pid         );
  // printf("arrival_time   %d\n "  ,currentPCB->process->arrival_time);
  // printf("burst_time     %d\n "  ,currentPCB->process->burst_time  );
  // printf("finishTime     %d\n "  ,currentPCB->process->finishTime  );
  // printf("waitTime       %d\n "  ,currentPCB->process->waitTime    );
  // printf("turnTime       %d\n "  ,currentPCB->process->turnTime    );
  // printf("respTime       %d\n "  ,currentPCB->process->respTime    );
  // printf("contextCount   %d\n\n ",currentPCB->process->contextCount);
  // printf("-----------------------------------------------------------\n ");

    time += 1;
    timeRemaining -= 1;
    
    if (timeRemaining == 0){ // do calculations for process     
      currentPCB->process->finishTime = time ;
      currentPCB->process->turnTime = currentPCB->process->finishTime - currentPCB->process->arrival_time;
      currentPCB->process->respTime = currentPCB->process->waitTime;
    }
  } 
  push_back(&head, currentPCB); 
  return head;
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
nodePtr RoundRobin(nodePtr header, int quantum)
{
  nodePtr head = header;
  int time = 0;
  int curPcbVal = 0;
  nodePtr currentPCB = NULL;
  nodePtr tmpPCB = NULL;
  int stop = getTime(head); 
  int timeRemaining = 0;
  nodePtr queue = NULL;
  while (time < stop)
  {

    // adjuest queues if head if line process has arived
    if (head != NULL && time >=  head->process->arrival_time) {
      tmpPCB = pop(&head, curPcbVal);   
      push_back(&queue, tmpPCB); 
    }

    if (timeRemaining == 0){ // pop new process of of ready queue      

      if (currentPCB != NULL && currentPCB->process->pid != 0)    
      { push_back(&queue, currentPCB);} // push back on queue for current pcb

   printf("---------------------- time %d-----------------------------\n", time);
   printf("-----------------------------------------------------------\n");
     
     print(&queue);

      currentPCB = pop(&queue, curPcbVal);
      timeRemaining += quantum;
      //currentPCB->process->waitTime += time - currentPCB->process->arrival_time;
  

    }

   printf("Time Remaining: %d\n\n",timeRemaining);
   printf("pid            %d\n "  ,currentPCB->process->pid         );
   printf("arrival_time   %d\n "  ,currentPCB->process->arrival_time);
   printf("burst_time     %d\n "  ,currentPCB->process->burst_time  );
   printf("finishTime     %d\n "  ,currentPCB->process->finishTime  );
   printf("waitTime       %d\n "  ,currentPCB->process->waitTime    );
   printf("turnTime       %d\n "  ,currentPCB->process->turnTime    );
   printf("respTime       %d\n "  ,currentPCB->process->respTime    );
   printf("contextCount   %d\n\n ",currentPCB->process->contextCount);
   printf("-----------------------------------------------------------\n");

    time += 1;
    timeRemaining -= 1;
    
    if (timeRemaining == 0){ // do calculations for process     
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
  file = fopen ("input5", "r");
  //file = fopen ("input10", "r");
  //file = fopen ("input100", "r");
  nodePtr head = NULL;
  head = (nodePtr) read_in_file( file, head);
//  head = FCFS(head);

  head = RoundRobin(head, 1);
  print(&head);
  return 0;
  
}

