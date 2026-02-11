MergePartialMatches(
  void *theEnv,
  struct partialMatch *list1,
  struct partialMatch *list2,
  int addActivationSlot,
  int addDependencySlot)
  {
   struct partialMatch *linker;
   short int i, j;

   linker = get_var_struct(theEnv,partialMatch,
                           sizeof(struct genericMatch) *
                            (list1->bcount + list2->bcount + addActivationSlot + addDependencySlot - 1));

   linker->next = NULL;
   linker->betaMemory = TRUE;
   linker->busy = FALSE;
   linker->activationf = addActivationSlot;
   linker->dependentsf = addDependencySlot;
   linker->notOriginf = FALSE;
   linker->counterf = FALSE;
   linker->bcount = list1->bcount + list2->bcount;

   for (i = 0; i < (int) list1->bcount; i++)
     { linker->binds[i] = list1->binds[i]; }

   for (i = (short) list1->bcount, j = 0; i < (short) linker->bcount; i++, j++)
     { linker->binds[i] = list2->binds[j]; }

   if (addActivationSlot) linker->binds[i++].gm.theValue = NULL;
   if (addDependencySlot) linker->binds[i].gm.theValue = NULL;

   return(linker);
  }
