PatternNodeToCode(
  void *theEnv,
  FILE *theFile,
  struct factPatternNode *thePatternNode,
  int imageID,
  int maxIndices)
  {
   fprintf(theFile,"{");


   PatternNodeHeaderToCode(theEnv,theFile,&thePatternNode->header,imageID,maxIndices);


   fprintf(theFile,",0,%d,%d,%d,",thePatternNode->whichField,
                             thePatternNode->whichSlot,
                             thePatternNode->leaveFields);


   PrintHashedExpressionReference(theEnv,theFile,thePatternNode->networkTest,imageID,maxIndices);


   if (thePatternNode->nextLevel == NULL)
     { fprintf(theFile,",NULL,"); }
   else
     {
      fprintf(theFile,",&%s%d_%ld[%ld],",FactPrefix(),
                 imageID,(thePatternNode->nextLevel->bsaveID / maxIndices) + 1,
                         thePatternNode->nextLevel->bsaveID % maxIndices);
     }


   if (thePatternNode->lastLevel == NULL)
     { fprintf(theFile,"NULL,"); }
   else
     {
      fprintf(theFile,"&%s%d_%ld[%ld],",FactPrefix(),
              imageID,(thePatternNode->lastLevel->bsaveID / maxIndices) + 1,
                   thePatternNode->lastLevel->bsaveID % maxIndices);
     }


   if (thePatternNode->leftNode == NULL)
     { fprintf(theFile,"NULL,"); }
   else
     {
      fprintf(theFile,"&%s%d_%ld[%ld],",FactPrefix(),
             imageID,(thePatternNode->leftNode->bsaveID / maxIndices) + 1,
                  thePatternNode->leftNode->bsaveID % maxIndices);
     }


   if (thePatternNode->rightNode == NULL)
     { fprintf(theFile,"NULL}"); }
   else
     {
      fprintf(theFile,"&%s%d_%ld[%ld]}",FactPrefix(),
            imageID,(thePatternNode->rightNode->bsaveID / maxIndices) + 1,
                thePatternNode->rightNode->bsaveID % maxIndices);
     }
  }
