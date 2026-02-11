ExpressionSize(
  struct expr *testPtr)
  {
   long size = 0;

   while (testPtr != NULL)
     {
      size++;
      if (testPtr->argList != NULL)
        { size += ExpressionSize(testPtr->argList); }
      testPtr = testPtr->nextArg;
     }
   return(size);
  }
