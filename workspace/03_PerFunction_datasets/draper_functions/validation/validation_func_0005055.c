SetClassDefaultsModeCommand(
  void *theEnv)
  {
   DATA_OBJECT argPtr;
   char *argument;
   unsigned short oldMode;

   oldMode = DefclassData(theEnv)->ClassDefaultsMode;


   if (EnvArgCountCheck(theEnv,"set-class-defaults-mode",EXACTLY,1) == -1)
     { return((SYMBOL_HN *) EnvAddSymbol(theEnv,GetClassDefaultsModeName(EnvGetClassDefaultsMode(theEnv)))); }

   if (EnvArgTypeCheck(theEnv,"set-class-defaults-mode",1,SYMBOL,&argPtr) == FALSE)
     { return((SYMBOL_HN *) EnvAddSymbol(theEnv,GetClassDefaultsModeName(EnvGetClassDefaultsMode(theEnv)))); }

   argument = DOToString(argPtr);


   if (strcmp(argument,"conservation") == 0)
     { EnvSetClassDefaultsMode(theEnv,CONSERVATION_MODE); }
   else if (strcmp(argument,"convenience") == 0)
     { EnvSetClassDefaultsMode(theEnv,CONVENIENCE_MODE); }
   else
     {
      ExpectedTypeError1(theEnv,"set-class-defaults-mode",1,
      "symbol with value conservation or convenience");
      return((SYMBOL_HN *) EnvAddSymbol(theEnv,GetClassDefaultsModeName(EnvGetClassDefaultsMode(theEnv))));
     }


   return((SYMBOL_HN *) EnvAddSymbol(theEnv,GetClassDefaultsModeName(oldMode)));
  }
