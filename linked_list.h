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

	//curPtr->next = NULL;
	//curPtr->prev = NULL;
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
  //curPtr->next = NULL;
  //curPtr->prev = NULL;
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
printf("\n| %10s | %10s | %10s | %10s | %10s | %10s | %10s |%10s| \n","Process ID", "Arrival", "CPU Burst", "Finish", "Wait", "Turn Time", "Responce", "# of Context" );

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

  // printf("Time Remaining: %d\n\n",timeRemaining);
  // printf("---------------------- time %d-----------------------------\n ", time);
  // printf("-----------------------------------------------------------\n ");
  // printf("pid            %d\n "  ,currentPCB->process->pid         );
  // printf("arrivalTime   %d\n "  ,currentPCB->process->arrivalTime);
  // printf("burst_time     %d\n "  ,currentPCB->process->burstTime  );
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
      currentPCB->process->turnTime = currentPCB->process->finishTime - currentPCB->process->arrivalTime;
      currentPCB->process->respTime = currentPCB->process->waitTime;
    }
  } 
  push_back(&head, currentPCB); 
  return head;
}



#endif

