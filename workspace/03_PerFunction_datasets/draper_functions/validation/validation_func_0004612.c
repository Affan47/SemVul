AddCPFunction(
  void *theEnv,
  char *name,
  void (*theFunction)(void *),
  int priority,
  struct cleanupFunction **head,
  intBool environmentAware)
  {
   struct cleanupFunction *newPtr, *currentPtr, *lastPtr = NULL;

   newPtr = get_struct(theEnv,cleanupFunction);

   newPtr->name = name;
   newPtr->ip = theFunction;
   newPtr->priority = priority;
   newPtr->environmentAware = (short) environmentAware;

   if (*head == NULL)
     {
      newPtr->next = NULL;
      *head = newPtr;
      return(1);
     }

   currentPtr = *head;
   while ((currentPtr != NULL) ? (priority < currentPtr->priority) : FALSE)
     {
      lastPtr = currentPtr;
      currentPtr = currentPtr->next;
     }

   if (lastPtr == NULL)
     {
      newPtr->next = *head;
      *head = newPtr;
     }
   else
     {
      newPtr->next = currentPtr;
      lastPtr->next = newPtr;
     }

   return(1);
  }
