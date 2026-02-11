BloadStorage(
  void *theEnv)
  {
   unsigned long int space;


   GenReadBinary(theEnv,&space,(unsigned long) sizeof(unsigned long int));
   GenReadBinary(theEnv,&DeffactsBinaryData(theEnv)->NumberOfDeffacts,(unsigned long) sizeof(long int));
   GenReadBinary(theEnv,&DeffactsBinaryData(theEnv)->NumberOfDeffactsModules,(unsigned long) sizeof(long int));


   if (DeffactsBinaryData(theEnv)->NumberOfDeffactsModules == 0)
     {
      DeffactsBinaryData(theEnv)->DeffactsArray = NULL;
      DeffactsBinaryData(theEnv)->ModuleArray = NULL;
      return;
     }

   space = DeffactsBinaryData(theEnv)->NumberOfDeffactsModules * sizeof(struct deffactsModule);
   DeffactsBinaryData(theEnv)->ModuleArray = (struct deffactsModule *) genlongalloc(theEnv,space);


   if (DeffactsBinaryData(theEnv)->NumberOfDeffacts == 0)
     {
      DeffactsBinaryData(theEnv)->DeffactsArray = NULL;
      return;
     }

   space = (unsigned long) (DeffactsBinaryData(theEnv)->NumberOfDeffacts * sizeof(struct deffacts));
   DeffactsBinaryData(theEnv)->DeffactsArray = (struct deffacts *) genlongalloc(theEnv,space);
  }
