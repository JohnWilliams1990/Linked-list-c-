#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "linked_list.h"



nodePtr SJF(nodePtr header)
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
      timeRemaining =  currentPCB->process->burstTime;
      currentPCB->process->waitTime = time - currentPCB->process->arrivalTime;
    }
    time += 1;
    timeRemaining -= 1;
    
    if (timeRemaining == 0){ // do calculations for process     
      currentPCB->process->finishTime = time ;
      currentPCB->process->turnTime = currentPCB->process->finishTime - currentPCB->process->arrivalTime;
      currentPCB->process->respTime = currentPCB->process->waitTime;
    }
  } 
  push_back(&head, currentPCB); 
  return head;
}








nodePtr sort(nodePtr header)
{

  nodePtr head = header;
  int processes = count(head);

  if( head == NULL) {exit(0);}

  nodePtr next = header->next;
  nodePtr tmp = NULL;

bool swap = false;
int index = 0;
do {
  print(&head);
    swap = false;
    while (header->next != NULL)
    {
      printf("%d > %d \n",header->process->pid , next->process->pid );
      if (header->process->pid > next->process->pid )
      {
		  index = header->process->pid;
        tmp = pop(&head,index);
        push(&head,next,index);
// head means of pushing finto struct        
	header = next;
        next = tmp; 
        swap = true; 
        printf("swap %d > %d\n", header->process->pid , next->process->pid );
      }
      header = header->next;
      next = next->next;
    } 

break;
  } while(true);
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
//  print(&head);

  int x = count(head);
  printf("#########%d\n",x);


//  head =  SJF(head);
//  print(&head);


  int quantum = 1;
  head = RoundRobin(head, quantum);
  print(&head);


//  print(&head);

  head =  sort(head);
  print(&head);
  return 0;
  
}

