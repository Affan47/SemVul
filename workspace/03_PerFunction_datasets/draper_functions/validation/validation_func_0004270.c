DoForAllConstructs(
  void *theEnv,
  void (*actionFunction)(void *,struct constructHeader *,void *),
  int moduleItemIndex,
  int interruptable,
  void *userBuffer)
  {
   struct constructHeader *theConstruct;
   struct defmoduleItemHeader *theModuleItem;
   void *theModule;
   long moduleCount = 0L;


   SaveCurrentModule(theEnv);


   for (theModule = EnvGetNextDefmodule(theEnv,NULL);
        theModule != NULL;
        theModule = EnvGetNextDefmodule(theEnv,theModule), moduleCount++)
     {


      EnvSetCurrentModule(theEnv,(void *) theModule);


      theModuleItem = (struct defmoduleItemHeader *)
                      GetModuleItem(theEnv,(struct defmodule *) theModule,moduleItemIndex);

      for (theConstruct = theModuleItem->firstItem;
           theConstruct != NULL;
           theConstruct = theConstruct->next)
        {
         if (interruptable)
           {
            if (GetHaltExecution(theEnv) == TRUE)
              {
               RestoreCurrentModule(theEnv);
               return(-1L);
              }
           }

         (*actionFunction)(theEnv,theConstruct,userBuffer);
        }
     }


   RestoreCurrentModule(theEnv);


   return(moduleCount);
  }
