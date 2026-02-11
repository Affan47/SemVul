GetNextConstructItem(
  void *theEnv,
  struct constructHeader *theConstruct,
  int moduleIndex)
  {
   struct defmoduleItemHeader *theModuleItem;

   if (theConstruct == NULL)
     {
      theModuleItem = (struct defmoduleItemHeader *)
                      GetModuleItem(theEnv,NULL,moduleIndex);
      if (theModuleItem == NULL) return(NULL);
      return(theModuleItem->firstItem);
     }

   return(theConstruct->next);
  }
