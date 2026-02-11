GetNextPortItem(
  void *theEnv,
  struct defmodule **theDefmodule,
  struct portItem **thePortItem,
  int *importChecked,
  int *exportChecked)
  {


   if (*theDefmodule == NULL)
     {
      *theDefmodule = (struct defmodule *) EnvGetNextDefmodule(theEnv,NULL);
      *thePortItem = NULL;
      *importChecked = FALSE;
      *exportChecked = FALSE;
     }


   while (*theDefmodule != NULL)
     {


      if (*thePortItem != NULL) *thePortItem = (*thePortItem)->next;
      if (*thePortItem != NULL) return(*thePortItem);


      if (! (*importChecked))
        {
         *thePortItem = (*theDefmodule)->importList;
         *importChecked = TRUE;
         if (*thePortItem == NULL)
           {
            *thePortItem = (*theDefmodule)->exportList;
            *exportChecked = TRUE;
           }
        }


      else if (! (*exportChecked))
        {
         *exportChecked = TRUE;
         *thePortItem = (*theDefmodule)->exportList;
        }


      if (*thePortItem != NULL) return(*thePortItem);


      *theDefmodule = (struct defmodule *) EnvGetNextDefmodule(theEnv,*theDefmodule);
      *importChecked = FALSE;
      *exportChecked = FALSE;
     }


   return(NULL);
  }
