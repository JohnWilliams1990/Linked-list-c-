#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "linked_list.h"


nodePtr SRTF(nodePtr header)
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

    if (tmpPCB != NULL && currentPCB != NULL){
      if( tmpPCB->process->burstTime - tmpPCB->process->curRunningTime < currentPCB->process->burstTime - currentPCB->process->curRunningTime) {
        // preemptive context switch here...... oh yea 
 
       if (timeRemaining != 0) {
//          currentPCB->process->waitTime += (time - currentPCB->process->timeMarker -1);
          push_back(&queue, currentPCB);
          pidval = leastleft(queue);
          currentPCB = popPid(&queue, pidval);
          timeRemaining = currentPCB->process->burstTime;
          if (currentPCB->process->curRunningTime == 0)
	  {
            currentPCB->process->waitTime = time - currentPCB->process->arrivalTime;
          }
          else 
          {
		printf("asdasdasdasd\n");
            currentPCB->process->waitTime += (time - currentPCB->process->timeMarker -1);
          }
	//currentPCB->process->waitTime = time - currentPCB->process->arrivalTime;
// value of y here 	 
        }


      }
    }

    if (timeRemaining == 0 ){ 
      if (currentPCB != NULL && currentPCB->process->curRunningTime == currentPCB->process->burstTime) {
	// process is finished so stop...........

        if (time == stop)
        { break; }
        // take task and put back into main list 
         push_back(&head, currentPCB); 
         pidval = leastleft(queue);
         currentPCB = popPid(&queue,pidval);
	 timeRemaining = currentPCB->process->burstTime - currentPCB->process->curRunningTime;
         currentPCB->process->waitTime = time - currentPCB->process->arrivalTime -1;
         currentPCB->process->timeMarker = time;
      }
      else if (currentPCB == NULL) { 
	// start process 1
        pidval = leastleft(queue);
        currentPCB = popPid(&queue,pidval);
	timeRemaining = currentPCB->process->burstTime - currentPCB->process->curRunningTime;
        currentPCB->process->waitTime = time - currentPCB->process->arrivalTime;
        currentPCB->process->timeMarker = time;
      }
    }
	if (queue != NULL) {

		pidval = leastleft(queue);
		tmpPCB = popPid(&queue, pidval);
		push_back(&queue, tmpPCB);
		//print(&queue);
	}
	printf("~~~~~~~~~~~~~~~~~time %d~~~~~~~~~~~~~~~~~~~~~\n", time);
	printf("PID: %d\n", currentPCB->process->pid);
	printf("Waiting Time: %d\n", currentPCB->process->waitTime);
	
	time += 1;
    timeRemaining -= 1;
    currentPCB->process->curRunningTime +=1;    
    if (timeRemaining == 0)
    {
      currentPCB->process->finishTime = time ;
      currentPCB->process->turnTime = currentPCB->process->finishTime - currentPCB->process->arrivalTime;
      currentPCB->process->respTime = currentPCB->process->waitTime;
    }
  } 
  push_back(&head, currentPCB); 
  head = sort(head);
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
  //file = fopen ("inputHW", "r");
  //file = fopen ("input10", "r");
  //file = fopen ("input100", "r");
  nodePtr head = NULL;
  head = (nodePtr) read_in_file( file, head);

//  printf("~~~~~~~~~~>>>>FCFS\n");
  head = FCFS(head);
  print(&head);
//
//
  head =  SRTF(head);
  print(&head);
//  head =  SJF(head);
//  print(&head);


  int quantum = 1;
//  printf("~~~~~~~~~~>>>>Round robin with quantum of size: %d\n",quantum);
  head = RoundRobin(head, quantum);
//  print(&head);



//if (argv[1] != NULL)
//{
//long menu = atoi(argv[1]);
//
//printf("%s ", argv[1]);
//if (menu == 0){head = FCFS(head);  printf("~~~~~~~~~~>>>>FCFS\n");}
//else if (menu == 1){ head =  SJF(head); printf("~~~~~~~~~~>>>>SJF\n");}
//else if (menu == 2){printf("asdasd"); printf("~~~~~~~~~~>>>>SRTF\n");}
//else if (menu == 3){head = RoundRobin(head, quantum); printf("~~~~~~~~~~>>>>RR\n");}
//  print(&head);
//}
//
  return 0;
  
}

