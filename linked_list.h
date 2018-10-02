#ifndef NODE
#define NODE

typedef struct pcb_t {
  int pid;
  int arrival_time;
  int burst_time;
int something;
  
  int compTime;
  int waitTime;
  int turnTime;
  int respTime;
  int contextCount;
  
  int avgCompTime;
  int avgWaitTime;
  int avgTurnTime;
  int avgRespTime;
  int totContextCount;
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
    (*arg)->process->compTime = item->process->compTime;
    (*arg)->process->waitTime = item->process->waitTime;
    (*arg)->process->turnTime = item->process->turnTime;
    (*arg)->process->respTime = item->process->respTime;
    (*arg)->process->contextCount = item->process->contextCount;
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
  curPtr->next->process->compTime = item->process->compTime;
  curPtr->next->process->waitTime = item->process->waitTime;
  curPtr->next->process->turnTime = item->process->turnTime;
  curPtr->next->process->respTime = item->process->respTime;
  curPtr->next->process->contextCount = item->process->contextCount;
  curPtr->next->prev = curPtr;
  curPtr->next->data = counter;
 return;
}




// pop elememt from list at specif index
nodePtr pop( nodePtr * arg, int index)
{

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

  if (curPtr->next != NULL)
  {
    curPtr->next->prev = prev;
  }
  else
  { // we are at head of list to pop front
    (*arg) = (*arg)->next;
    (*arg)->prev = curPtr->prev;
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
   printf("compTime       %d\n ",curPtr->process->compTime    );
   printf("waitTime       %d\n ",curPtr->process->waitTime    );
   printf("turnTime       %d\n ",curPtr->process->turnTime    );
   printf("respTime       %d\n ",curPtr->process->respTime    );
   printf("contextCount   %d\n\n ",curPtr->process->contextCount);
  while (curPtr->next != NULL)
  {
   //printf("%d\n ",curPtr->data);
   printf("compTime      %d\n ",curPtr->next->process->compTime    );
   printf("waitTime      %d\n ",curPtr->next->process->waitTime    );
   printf("turnTime      %d\n ",curPtr->next->process->turnTime    );
   printf("respTime      %d\n ",curPtr->next->process->respTime    );
   printf("contextCount  %d\n\n ",curPtr->next->process->contextCount);
   curPtr = curPtr->next;
  }
   printf("\n\n");
}


#endif

