ConstructJoins(
  void *theEnv,
  int logicalJoin,
  struct lhsParseNode *theLHS)
  {
   struct joinNode *lastJoin = NULL;
   struct patternNodeHeader *lastPattern;
   unsigned firstJoin = TRUE;
   int tryToReuse = TRUE;
   struct joinNode *listOfJoins;
   struct joinNode *oldJoin;
   int joinNumber = 1;
   int isLogical;
   struct joinNode *nandReconnect[32];
   int currentDepth = 1;
   int lastIteration = FALSE;
   int rhsType;
   int endDepth;


   AttachTestCEsToPatternCEs(theEnv,theLHS);


   while (theLHS != NULL)
     {
      if (theLHS->bottom == NULL) lastIteration = TRUE;


      while (theLHS->beginNandDepth > currentDepth)
        {
         nandReconnect[currentDepth-1] = lastJoin;
         currentDepth++;
        }


      rhsType = theLHS->patternType->positionInArray;
      lastPattern = (*theLHS->patternType->addPatternFunction)(theEnv,theLHS);


      if (joinNumber == logicalJoin) isLogical = TRUE;
      else isLogical = FALSE;


      if (firstJoin == TRUE)
        { listOfJoins = lastPattern->entryJoin; }
      else
        { listOfJoins = lastJoin->nextLevel; }


      endDepth = theLHS->endNandDepth;
      if ((tryToReuse == TRUE) &&
          ((oldJoin = FindShareableJoin(listOfJoins,(void *) lastPattern,firstJoin,
                                        theLHS->negated,isLogical,
                                        theLHS->networkTest,
                                        endDepth,currentDepth,
                                        lastIteration,nandReconnect)) != NULL) )
        {
#if DEBUGGING_FUNCTIONS
         if ((EnvGetWatchItem(theEnv,"compilations") == TRUE) && GetPrintWhileLoading(theEnv))
           { EnvPrintRouter(theEnv,WDIALOG,"=j"); }
#endif
         lastJoin = oldJoin;
        }
      else
        {
         tryToReuse = FALSE;
         lastJoin = CreateNewJoin(theEnv,theLHS->networkTest,
                                  lastJoin,lastPattern,
                                  FALSE,(int) theLHS->negated);
         lastJoin->rhsType = rhsType;
        }


      while (endDepth < currentDepth)
        {
         currentDepth--;

         if (lastJoin->nextLevel == NULL) tryToReuse = FALSE;

         if (tryToReuse)
           {
#if DEBUGGING_FUNCTIONS
            if ((EnvGetWatchItem(theEnv,"compilations") == TRUE) && GetPrintWhileLoading(theEnv))
              { EnvPrintRouter(theEnv,WDIALOG,"=j"); }
#endif
            lastJoin = lastJoin->nextLevel;
           }
         else
           {
            lastJoin = CreateNewJoin(theEnv,NULL,nandReconnect[currentDepth-1],
                                     lastJoin,TRUE,FALSE);
           }
        }


      theLHS = theLHS->bottom;
      joinNumber++;
      firstJoin = FALSE;
     }


#if DEBUGGING_FUNCTIONS
   if ((EnvGetWatchItem(theEnv,"compilations") == TRUE) && GetPrintWhileLoading(theEnv))
     { EnvPrintRouter(theEnv,WDIALOG,"\n"); }
#endif


   return(lastJoin);
  }
