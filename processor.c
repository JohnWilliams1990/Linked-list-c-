#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "linked_list.h"


// pop elememt from list at specif index
nodePtr popPid( nodePtr * arg, int index)
{

  node tmp;
  int counter = 0;
  nodePtr curPtr = (*arg);
  nodePtr prev = (*arg)->prev;

  if ((*arg) == NULL)
  {
    printf("HERE\n\n");
    return curPtr;
  }
  
  while (curPtr->next != NULL && curPtr->process->pid !=  index)
  {
    prev = curPtr;
    curPtr = curPtr->next;
    counter +=1;
  }
  if(prev != NULL) 
  {
    prev->next = curPtr->next;
  }
  else
  { // we are at head of list to pop front
    (*arg) = (*arg)->next;
    if ((*arg) != NULL) 
    { 
      (*arg)->prev = curPtr->prev;
    }
  }

  if (curPtr->next != NULL)
  {
    curPtr->next->prev = prev;
  }
    return curPtr; 
}

nodePtr sort(nodePtr header)
{

  nodePtr head = header;

  if( head == NULL) {exit(0);}

  nodePtr next = header->next;
  nodePtr tmp = NULL;

  bool swap = false;
  int index = 0;
  int processes = count(head);


do {
  print(&head);
    swap = false;

	header = head;
	if (next->next != NULL)
	{
		next = next->next;
	}
	else
	{
		next = head;
	}



	while (header->next != NULL)
    {
      printf("%d > %d \n",header->process->pid , next->process->pid );
      if (header->process->pid > next->process->pid )
      {

        index = header->process->pid;
      printf("index %d  \n",index );
//        tmp = pop(&head,index);
tmp = popPid( &head, index);

        push(&head,tmp,index);
// head means of pushing finto struct        
     	header = next;
        next = tmp; 
        swap = true; 
        printf("swap %d > %d\n", header->process->pid , next->process->pid );
      }
      header = header->next;
    } 

  print(&head);
//break;
  } while(true);
}

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

