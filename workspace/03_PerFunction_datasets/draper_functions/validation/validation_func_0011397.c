ProcessFactAlphaMatch(
  void *theEnv,
  struct fact *theFact,
  struct multifieldMarker *theMarks,
  struct factPatternNode *thePattern)
  {
   struct partialMatch *theMatch;
   struct patternMatch *listOfMatches;
   struct joinNode *listOfJoins;


  theMatch = CreateAlphaMatch(theEnv,theFact,theMarks,(struct patternNodeHeader *) &thePattern->header);


  listOfMatches = (struct patternMatch *) theFact->list;
  theFact->list = (void *) get_struct(theEnv,patternMatch);
  ((struct patternMatch *) theFact->list)->next = listOfMatches;
  ((struct patternMatch *) theFact->list)->matchingPattern = (struct patternNodeHeader *) thePattern;
  ((struct patternMatch *) theFact->list)->theMatch = theMatch;


  for (listOfJoins = thePattern->header.entryJoin;
       listOfJoins != NULL;
       listOfJoins = listOfJoins->rightMatchNode)
     { NetworkAssert(theEnv,theMatch,listOfJoins,RHS); }
  }
