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
  int processes = count(head);
  int remainingProcesses = 0;
  int timeRemaining = 0;
  int timeMarker = 0;
  nodePtr queue = NULL;
  while (time <= stop)
  {


    // take task from operational STORAGE queue if applicable 
    // adjuest queues if head if line process has arived

    //ARRIVAL 
    if (head != NULL && remainingProcesses != processes && time >=  head->process->arrivalTime) {
      tmpPCB = pop(&head, curPcbVal);
      push_back(&queue, tmpPCB);
      remainingProcesses += 1;
      print(&queue);
    } 
    if (timeRemaining == 0 || currentPCB->process->curRunningTime == currentPCB->process->burstTime){ // pop new process of of ready queue      

        if (currentPCB != NULL)
        {
            if (currentPCB->process->ran == 0)
            {
              // get first waiting time for calculation 
              currentPCB->process->firstRun = time;
              currentPCB->process->waitTime = time - currentPCB->process->arrivalTime -1;
              printf("---$$$$$--------------------------------------------------%d-----------%d----\n",currentPCB->process->pid, currentPCB->process->waitTime);
              currentPCB->process->timeMarker = time;
        	currentPCB->process->ran = 1;
            }
        
            else if (currentPCB->process->ran == 1)
            {
               currentPCB->process->waitTime += (time - currentPCB->process->timeMarker - 1);
               currentPCB->process->timeMarker = time;
              printf("----------------------------------------------------------%d-----------%d----\n", currentPCB->process->pid, currentPCB->process->waitTime);
            }
        }

      if(currentPCB != NULL && currentPCB->process->curRunningTime == currentPCB->process->burstTime)
      { 
         // take the item off the running queue and put back onto storage queue
        printf("~~~~~~~~~~~~~~~>>>>>\aTask %d finished at time %d<<<<<<<<<<\n\n",  currentPCB->process->pid, time);

        currentPCB->process->finishTime = time;
        

        if (time == stop) {break; }
        push_back(&head, currentPCB); 
        // if this has taken place then currentPCB is in inconsistent State so refresh it. 
//        print(&queue);
        

	currentPCB = pop(&queue, curPcbVal);
        timeRemaining += quantum;
      }
      // context switch for process here
      else if (currentPCB != NULL && currentPCB->process->pid != 0)    
      {  
         push_back(&queue, currentPCB);// push back on working queue for current pcb
	 currentPCB = pop(&queue, curPcbVal); // get next job 
         timeRemaining += quantum; // increment quantum
      } 

      else 
      { // via logical deduction the only thing remaining is empty / null currentPCB
	 currentPCB = pop(&queue, curPcbVal); // get next job 
         timeRemaining += quantum; // increment quantum
      }   
    }

//  // //printf("Time Remaining:  %d\n\n" , timeRemaining                      );
//   printf("pid              %d\n"  , currentPCB->process->pid           );
//printf("currentPCB->process->waitTime: %d\n", currentPCB->process->waitTime);
//      //print(&queue);
//

    time += 1;
    timeRemaining -= 1;
    currentPCB->process->curRunningTime +=1;    

  printf("---------------------- time %d-----------------------------\n", time);
//    if (currentPCB->process->waitTime == 0)

//    if (currentPCB->process->firstRun == 0)
//    {
//      // get first waiting time for calculation 
//      currentPCB->process->firstRun = time;
//      currentPCB->process->waitTime = currentPCB->process->firstRun - currentPCB->process->arrivalTime -1;
//      printf("\t\t-----%d----\n", currentPCB->process->waitTime);
//    }



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

  //head = RoundRobin(head, 1);
  head = RoundRobin(head, 4);
  print(&head);
  return 0;
  
}

