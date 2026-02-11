load( QDataStream &ds)
{
   if (!parsedOptionList) parsedOptionList = new KCmdLineParsedOptions;
   if (!parsedArgList) parsedArgList = new KCmdLineParsedArgs;

   ds >> (*(parsedOptionList));
   ds >> (*(parsedArgList));

   if (parsedOptionList->count() == 0)
   {
      delete parsedOptionList;  parsedOptionList = 0;
   }
   if (parsedArgList->count() == 0)
   {
      delete parsedArgList;     parsedArgList = 0;
   }
}
