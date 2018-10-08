#ifndef NODE
#define NODE

#include<stdbool.h>

typedef struct pcb_t {
  int pid;
  int arrivalTime;
  int burstTime;
  
  int finishTime;
  int waitTime;
  int turnTime;
  int respTime;
  int contextCount;
  
  int avgCompTime;
  int avgWaitTime;
  int avgTurnTime;
  int avgRespTime;
  int totContextCount;

  int timeMarker;
  int firstRun;
  bool ran;
  int curRunningTime;

} pcb,* pcbPtr ;

typedef struct node {
  struct node* next;
  struct node* prev;
  int data;
  pcbPtr process;
} node, *nodePtr;


void freeNode(nodePtr * arg) {
  free((*arg)->process);
  free((*arg));
  return;
}



// push element to back of list
void push_back( nodePtr * arg, node* item)
{
  int counter = 1;
  nodePtr curPtr = (*arg);

  if ( curPtr == NULL)
  {
    (*arg) = calloc(1, sizeof( node));
    (*arg)->prev = NULL;
    (*arg)->next = NULL;  
    (*arg)->process = calloc(1, sizeof(struct pcb_t));
    (*arg)->process->pid = item->process->pid;
    (*arg)->process->arrivalTime= item->process->arrivalTime;
    (*arg)->process->burstTime = item->process->burstTime  ;
    (*arg)->process->contextCount = item->process->contextCount;

    (*arg)->process->finishTime = item->process->finishTime;
    (*arg)->process->waitTime = item->process->waitTime;
    (*arg)->process->turnTime = item->process->turnTime;
    (*arg)->process->respTime = item->process->respTime;
    (*arg)->process->contextCount = item->process->contextCount;
    (*arg)->process->curRunningTime = item->process->curRunningTime;
    (*arg)->process->firstRun = item->process->firstRun;
    (*arg)->process->timeMarker = item->process->timeMarker;
    (*arg)->process->ran = item->process->ran;

    (*arg)->data = 0;
    return;
  }

  while (curPtr->next != NULL)
  {
    curPtr = curPtr->next;
    counter +=1;
  }
  curPtr->next = calloc(1, sizeof(struct node));
  curPtr->next->process = calloc(1, sizeof(struct pcb_t));
  curPtr->next->process->pid         = item->process->pid         ;
  curPtr->next->process->arrivalTime= item->process->arrivalTime;
  curPtr->next->process->burstTime  = item->process->burstTime  ;
  curPtr->next->process->contextCount = item->process->contextCount;

  curPtr->next->process->finishTime = item->process->finishTime;
  curPtr->next->process->waitTime = item->process->waitTime;
  curPtr->next->process->turnTime = item->process->turnTime;
  curPtr->next->process->respTime = item->process->respTime;
  curPtr->next->process->contextCount = item->process->contextCount;
  curPtr->next->process->curRunningTime = item->process->curRunningTime;;
   
  curPtr->next->process->firstRun = item->process->firstRun;
  curPtr->next->process->timeMarker = item->process->timeMarker;
  curPtr->next->process->ran = item->process->ran;
  curPtr->next->prev = curPtr;
  curPtr->next->data = counter;
 return;
}




// pop elememt from list at specif index
nodePtr pop( nodePtr * arg, int index)
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
  
  while (curPtr->next != NULL && counter < index)
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

// pop element off of end
nodePtr pop_back( nodePtr * arg)
{
  int counter = 0;
  nodePtr curPtr = (*arg);
  nodePtr prev = (*arg)->prev;

  if (curPtr == NULL) { exit(0);  }
  if (curPtr->next == NULL && curPtr->prev == NULL)
  {
    return curPtr;
  }

  while (curPtr->next != NULL)
  {
    prev = curPtr;
    curPtr = curPtr->next;
    counter +=1;
  }
  if (prev != NULL) {
    prev->next = curPtr->next;
  }

  return curPtr;
}

void print( nodePtr * arg)
{
  nodePtr curPtr = (*arg);

  if (curPtr == NULL)
  {
    return; 
  }
 printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
printf("| %10s | %10s | %10s | %10s | %10s | %10s | %10s |%10s| \n","Process ID", "Arrival", "CPU Burst", "Finish", "Wait", "Turn Time", "Responce", "# of Context" );

 printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  while (curPtr != NULL)
  {
printf("| %10d | %10d | %10d | %10d | %10d | %10d | %10d | %10d | \n",curPtr->process->pid, curPtr->process->arrivalTime, curPtr->process->burstTime, curPtr->process->finishTime, curPtr->process->waitTime, curPtr->process->turnTime, curPtr->process->respTime, curPtr->process->contextCount);
   curPtr = curPtr->next;
  }
 printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
   printf("\n\n");
}



// local funtions
nodePtr read_in_file(FILE* file, nodePtr head){
  nodePtr currentPCB = calloc(1, sizeof(struct node));
  currentPCB->process = calloc(1, sizeof(struct pcb_t));
  int index = 0;

  while (!feof (file)){
    index = 0;
    fscanf (file, "%d", &index);    
    currentPCB->process->pid = index;
    fscanf (file, "%d", &index);    
    currentPCB->process->arrivalTime = index;
    fscanf (file, "%d", &index);    
    currentPCB->process->burstTime = index; 
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
    sum += curPtr->process->burstTime;
    curPtr = curPtr->next;
  }
  return sum; 
}


int count(nodePtr head)
{
  int sum = 0;
  nodePtr curPtr = head;
  while (curPtr != NULL)
  {
    sum += 1;
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
    if (head != NULL && remainingProcesses != processes && time >=  head->process->arrivalTime) {

      tmpPCB = pop(&head, curPcbVal);
      push_back(&queue, tmpPCB);
      remainingProcesses += 1;
    } 
    if (timeRemaining == 0 || currentPCB->process->curRunningTime == currentPCB->process->burstTime ){ // pop new process of of ready queue      
      if (currentPCB != NULL)
      {
          if (currentPCB->process->ran == 0)
          {
            currentPCB->process->waitTime = currentPCB->process->firstRun - currentPCB->process->arrivalTime -1;
            currentPCB->process->timeMarker = time;
            currentPCB->process->ran = 1;
          }
      
          else if (currentPCB->process->ran == 1)
          {
             currentPCB->process->waitTime += (currentPCB->process->firstRun - currentPCB->process->timeMarker - 1);
             currentPCB->process->timeMarker = time;
          }

    currentPCB->process->contextCount += 1;
      }

      if(currentPCB != NULL && currentPCB->process->curRunningTime == currentPCB->process->burstTime)
      { //process is finished 
        currentPCB->process->finishTime = time;
        currentPCB->process->turnTime = currentPCB->process->finishTime - currentPCB->process->arrivalTime;

        if (time == stop) {break; }
        push_back(&head, currentPCB); 
       	// if this has taken place then currentPCB is in inconsistent State so refresh it. 
	currentPCB = pop(&queue, curPcbVal);
      }
      // context switch for process here
      else if (currentPCB != NULL && currentPCB->process->pid != 0)    
      { 
        push_back(&queue, currentPCB);// push back on working queue for current pcb
	currentPCB = pop(&queue, curPcbVal); // get next job 
      } 

      else 
      { // via logical deduction the only thing remaining is empty / null currentPCB
	 currentPCB = pop(&queue, curPcbVal); // get next job 
      }   
      timeRemaining = quantum; // increment quantum
      currentPCB->process->firstRun = time + 1;
      if (currentPCB->process->curRunningTime == 0)
      {
        currentPCB->process->respTime = time - currentPCB->process->arrivalTime;
      }

    }
    time += 1;
    timeRemaining -= 1;
    currentPCB->process->curRunningTime +=1;    


  } 
  push_back(&head, currentPCB); 
  return head;
}



nodePtr push( nodePtr * arg, node* item, int index)
{
  int counter = 1;
  nodePtr curPtr = (*arg);
  nodePtr tmpPtr = NULL;


  if ( curPtr == NULL)
  {
    (*arg) = calloc(1, sizeof( node));
    (*arg)->prev = NULL;
    (*arg)->next = NULL;  
    (*arg)->process = calloc(1, sizeof(struct pcb_t));
    (*arg)->process->pid = item->process->pid;
    (*arg)->process->arrivalTime= item->process->arrivalTime;
    (*arg)->process->burstTime = item->process->burstTime  ;
    (*arg)->process->contextCount = item->process->contextCount;
    (*arg)->process->finishTime = item->process->finishTime;
    (*arg)->process->waitTime = item->process->waitTime;
    (*arg)->process->turnTime = item->process->turnTime;
    (*arg)->process->respTime = item->process->respTime;
    (*arg)->process->contextCount = item->process->contextCount;
    (*arg)->process->curRunningTime = item->process->curRunningTime;
    (*arg)->process->firstRun = item->process->firstRun;
    (*arg)->process->timeMarker = item->process->timeMarker;
    (*arg)->process->ran = item->process->ran;
    (*arg)->data = 0;
  }

  while (counter < index - 1 && curPtr->next != NULL)
  {
     curPtr = curPtr->next;
     counter += 1;
  }

  if (index == 1)
  {

    printf("asdasdasdsadsadasdasdasdsad\n\n\n");
  
    tmpPtr= calloc(1, sizeof( node));
    tmpPtr->prev = NULL;
    tmpPtr->next = NULL;
    tmpPtr->process = calloc(1, sizeof(struct pcb_t));
    tmpPtr->process->pid = item->process->pid;
    tmpPtr->process->arrivalTime= item->process->arrivalTime;
    tmpPtr->process->burstTime = item->process->burstTime  ;
    tmpPtr->process->contextCount = item->process->contextCount;
    tmpPtr->process->finishTime = item->process->finishTime;
    tmpPtr->process->waitTime = item->process->waitTime;
    tmpPtr->process->turnTime = item->process->turnTime;
    tmpPtr->process->respTime = item->process->respTime;
    tmpPtr->process->contextCount = item->process->contextCount;
    tmpPtr->process->curRunningTime = item->process->curRunningTime;
    tmpPtr->process->firstRun = item->process->firstRun;
    tmpPtr->process->timeMarker = item->process->timeMarker;
    tmpPtr->process->ran = item->process->ran;
    tmpPtr->data = 0;

    tmpPtr->prev = NULL;
    tmpPtr->next = curPtr;
    
    if (curPtr->prev != NULL)
    {
      curPtr->prev = tmpPtr;
    }

    return tmpPtr;
  }


else {

// grab item before overwriting it
  tmpPtr = curPtr->next;
  

  curPtr->next = calloc(1, sizeof(struct node));
  curPtr->next->process = calloc(1, sizeof(struct pcb_t));
  curPtr->next->process->pid         = item->process->pid         ;
  curPtr->next->process->arrivalTime= item->process->arrivalTime;
  curPtr->next->process->burstTime  = item->process->burstTime  ;
  curPtr->next->process->contextCount = item->process->contextCount;

  curPtr->next->process->finishTime = item->process->finishTime;
  curPtr->next->process->waitTime = item->process->waitTime;
  curPtr->next->process->turnTime = item->process->turnTime;
  curPtr->next->process->respTime = item->process->respTime;
  curPtr->next->process->contextCount = item->process->contextCount;
  curPtr->next->process->curRunningTime = item->process->curRunningTime;;
   
  curPtr->next->process->firstRun = item->process->firstRun;
  curPtr->next->process->timeMarker = item->process->timeMarker;
  curPtr->next->process->ran = item->process->ran;
  curPtr->next->prev = curPtr;
  curPtr->next->data = counter;
 
  curPtr = curPtr->next;
  curPtr->next = tmpPtr; 
  
  if (curPtr->next != NULL)
  {
    curPtr->next->prev = curPtr;
  }
}



return (*arg);

}













#endif



