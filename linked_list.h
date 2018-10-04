#ifndef NODE
#define NODE

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
    (*arg)->process->pid         = item->process->pid         ;
    (*arg)->process->arrivalTime= item->process->arrivalTime;
    (*arg)->process->burstTime  = item->process->burstTime  ;
    (*arg)->process->contextCount = item->process->contextCount;

    (*arg)->process->finishTime = item->process->finishTime;
    (*arg)->process->waitTime = item->process->waitTime;
    (*arg)->process->turnTime = item->process->turnTime;
    (*arg)->process->respTime = item->process->respTime;
    (*arg)->process->contextCount = item->process->contextCount;
    (*arg)->process->curRunningTime = item->process->curRunningTime;;
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


#endif

