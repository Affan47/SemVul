PlaceMEAActivation(
  void *theEnv,
  ACTIVATION *actPtr,
  ACTIVATION *newActivation)
  {
   int salience;
   unsigned long timetag;
   ACTIVATION *lastAct;
   int flag;
   long int cWhoset, oWhoset;

   if (newActivation->sortedBasis == NULL)
     { newActivation->sortedBasis = SortPartialMatch(theEnv,newActivation->basis); }


   timetag = newActivation->timetag;
   salience = newActivation->salience;
   lastAct = NULL;


   while (actPtr != NULL)
     {
      if (actPtr->salience > salience)
        {
         lastAct = actPtr;
         actPtr = actPtr->next;
        }
      else if (actPtr->salience < salience)
        { return(lastAct); }
      else
        {
         cWhoset = -1;
         oWhoset = -1;
         if (GetMatchingItem(newActivation,0) != NULL)
           { cWhoset = GetMatchingItem(newActivation,0)->timeTag; }
         if (GetMatchingItem(actPtr,0) != NULL)
           { oWhoset = GetMatchingItem(actPtr,0)->timeTag; }
         if (oWhoset < cWhoset)
           {
            if (cWhoset > 0) flag = GREATER_THAN;
            else flag = LESS_THAN;
           }
         else if (oWhoset > cWhoset)
           {
            if (oWhoset > 0) flag = LESS_THAN;
            else flag = GREATER_THAN;
           }
         else
           { flag = ComparePartialMatches(theEnv,actPtr,newActivation); }

         if (flag == LESS_THAN)
           {
            lastAct = actPtr;
            actPtr = actPtr->next;
           }
         else if (flag == GREATER_THAN)
           { return(lastAct); }
         else
           {
            if (timetag > actPtr->timetag)
              {
               lastAct = actPtr;
               actPtr = actPtr->next;
              }
            else
             { return(lastAct); }
           }
        }
     }


   return(lastAct);
  }
