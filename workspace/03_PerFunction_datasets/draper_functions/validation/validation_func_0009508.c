InstallDeftemplate(
  void *theEnv,
  struct deftemplate *theDeftemplate)
  {
   struct templateSlot *slotPtr;
   struct expr *tempExpr;

   IncrementSymbolCount(theDeftemplate->header.name);

   for (slotPtr = theDeftemplate->slotList;
        slotPtr != NULL;
        slotPtr = slotPtr->next)
     {
      IncrementSymbolCount(slotPtr->slotName);
      tempExpr = AddHashedExpression(theEnv,slotPtr->defaultList);
      ReturnExpression(theEnv,slotPtr->defaultList);
      slotPtr->defaultList = tempExpr;
      slotPtr->constraints = AddConstraint(theEnv,slotPtr->constraints);
     }
  }
