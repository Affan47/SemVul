InheritanceLinksToCode(
  void *theEnv,
  FILE **classLinkFile,
  char *fileName,
  int fileID,
  int imageID,
  FILE *headerFP,
  int *fileCount,
  int maxIndices,
  DEFCLASS *theDefclass,
  int *classLinkArrayVersion,
  int *classLinkArrayCount,
  int *reopenClassLinkFile,
  struct CodeGeneratorFile *classLinkCodeFile)
  {
   register unsigned i;
   int inheritanceLinkCount,
       linkPrinted = FALSE;

   inheritanceLinkCount = theDefclass->directSuperclasses.classCount +
                          theDefclass->directSubclasses.classCount +
                          theDefclass->allSuperclasses.classCount;

   if (inheritanceLinkCount == 0)
     return(TRUE);

   *classLinkFile = OpenFileIfNeeded(theEnv,*classLinkFile,fileName,fileID,
                                      imageID,fileCount,
                                      *classLinkArrayVersion,headerFP,
                                      "DEFCLASS *",ClassLinkPrefix(),
                                      *reopenClassLinkFile,classLinkCodeFile);
   if (*classLinkFile == NULL)
     return(FALSE);

   for (i = 0 ; i < theDefclass->directSuperclasses.classCount ; i++)
     {
      if (linkPrinted)
        fprintf(*classLinkFile,",");
      PrintClassReference(theEnv,*classLinkFile,
                          theDefclass->directSuperclasses.classArray[i],
                          imageID,maxIndices);
      linkPrinted = TRUE;
     }
   for (i = 0 ; i < theDefclass->directSubclasses.classCount ; i++)
     {
      if (linkPrinted)
        fprintf(*classLinkFile,",");
      PrintClassReference(theEnv,*classLinkFile,
                          theDefclass->directSubclasses.classArray[i],
                          imageID,maxIndices);
      linkPrinted = TRUE;
     }
   for (i = 0 ; i < theDefclass->allSuperclasses.classCount ; i++)
     {
      if (linkPrinted)
        fprintf(*classLinkFile,",");
      PrintClassReference(theEnv,*classLinkFile,
                          theDefclass->allSuperclasses.classArray[i],
                          imageID,maxIndices);
      linkPrinted = TRUE;
     }
   *classLinkArrayCount += inheritanceLinkCount;
   *classLinkFile = CloseFileIfNeeded(theEnv,*classLinkFile,classLinkArrayCount,
                                       classLinkArrayVersion,maxIndices,
                                       reopenClassLinkFile,classLinkCodeFile);
   return(TRUE);
  }
