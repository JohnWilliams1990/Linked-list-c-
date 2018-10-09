#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "linked_list.h"


// pop elememt from list at specif index

int least(nodePtr head)
{
  nodePtr curPtr = head;
  int burst = curPtr->process->burstTime;
  int pid = curPtr->process->pid;
  while (curPtr != NULL)
  {
    if (curPtr->process->burstTime < burst)
    {
      burst = curPtr->process->burstTime;
      pid = curPtr->process->pid;
    }
    curPtr = curPtr->next;
  }
  return pid; 
}
<<<<<<< HEAD

=======
>>>>>>> 60815ad37796d07a3b22ecfd96e28bffc2b44f17





nodePtr SJF(nodePtr header)
{
  nodePtr head = header;
  int time = 0;
  int curPcbVal = 0;
  nodePtr currentPCB = NULL;
  nodePtr tmpPCB = NULL;
  int stop = getTime(head); 
  int processes = count(head);
  int remainingProcesses = 0;
  int timeRemaining = 0; // becomes process time in general 
  int timeMarker = 0;
  int pidval = 0;
  nodePtr queue = NULL;
  while (time <= stop)
  {
    // move ariving process to queue
    if (head != NULL && remainingProcesses != processes && time >=  head->process->arrivalTime) {

      tmpPCB = pop(&head, curPcbVal);
      push_back(&queue, tmpPCB);
      remainingProcesses += 1;
    } 
    if (timeRemaining == 0){
      if (currentPCB != NULL && currentPCB->process->curRunningTime == currentPCB->process->burstTime) {
        // take task and put back into main list 
         push_back(&head, currentPCB); 
         pidval = least(queue);
         printf("%d here \n\n", pidval);
         print(&queue);	
         currentPCB = popPid(&queue,pidval);
		 timeRemaining = currentPCB->process->burstTime;
      }
      else if (currentPCB == NULL) { 
        pidval = least(queue);
        printf("%d here \n\n", pidval);
        print(&queue);
        currentPCB = popPid(&queue,pidval);
		timeRemaining = currentPCB->process->burstTime;
      }
    }
	printf("~~~~~~~~~~~~~~~~~time %d~~~~~~~~~~~~~~~~~~~~~\n", time);
	printf("PID: %d\n", currentPCB->process->pid);
	//print(&queue);

    
    time += 1;
    timeRemaining -= 1;
    currentPCB->process->curRunningTime +=1;    


  } 
  push_back(&head, currentPCB); 
  head = sort(head);
  return head;
}




<<<<<<< HEAD
=======


>>>>>>> 60815ad37796d07a3b22ecfd96e28bffc2b44f17
int main(int argc, char *argv[])
{

//  if (argc < 3){
//    printf("Usage: %s input_file output_file\n", argv[0]);
//    exit(-1);
//  }




  FILE* file;
  //file = fopen (argv[1], "r");
  file = fopen ("input5", "r");
  //file = fopen ("inputHW", "r");
  //file = fopen ("input10", "r");
  //file = fopen ("input100", "r");
  nodePtr head = NULL;
  head = (nodePtr) read_in_file( file, head);
//
//  printf("~~~~~~~~~~>>>>FCFS\n");
//  head = FCFS(head);
//  print(&head);
//
//
//
//
//  int quantum = 1;
//  printf("~~~~~~~~~~>>>>Round robin with quantum of size: %d\n",quantum);
//  head = RoundRobin(head, quantum);
//  print(&head);


//
//for(int i = 0; i < 100; i++)
//{
//  int x = least(head); 
//
//  printf("%d\n", x);
//  popPid(&head,x);
//  print(&head);
//  
//}
//

//  head =  sort(head);
//  print(&head);
  print(&head);
  head =  SJF(head);
  print(&head);
<<<<<<< HEAD
//  print(&head);

=======



for(int i = 0; i < 100; i++)
{
int x = least(head); 
printf("%d\n", x);
pop(&head,x);

  print(&head);

}


//  print(&head);

//  head =  sort(head);
//  print(&head);
>>>>>>> 60815ad37796d07a3b22ecfd96e28bffc2b44f17
  return 0;
  
}

//nodePtr sort(nodePtr header)
//{
//
//  nodePtr head = header;
//
//  if( head == NULL) {exit(0);}
//
//  nodePtr next = header->next;
//  nodePtr tmp = NULL;
//
//  bool swap = false;
//  int index = 0;
//  int processes = count(head);
//
//
//do {
//
//    swap = false;
//
//	header = head;
//	
//
//
//
//	while (header->next != NULL)
//    {
//      printf("%d > %d \n",header->process->pid , next->process->pid );
//      if (header->process->pid > next->process->pid )
//      {
//
//        index = header->process->pid;
//      printf("\tindex %d  \n",index );
////        tmp = pop(&head,index);
//	  printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
//tmp = popPid( &head, index);
//print(&head);
//        push(&head,tmp,index);
//		print(&head);
//		printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
//// head means of pushing finto struct        
//     	header = next;
//        next = tmp; 
//        swap = true; 
//        printf("\tswap %d > %d\n", header->process->pid , next->process->pid );
//		
//      }
//      header = header->next;
//    } 
//	if (next->next != NULL)
//	{
//		next = next->next;
//	}
//	else
//	{
//		next = head;
//	}
//  print(&head);
////break;
//  } while(swap == true);
//}
//



