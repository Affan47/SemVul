SlotReferenceVar(
  void *theEnv,
  EXPRESSION *varexp,
  void *userBuffer)
  {
   struct token itkn;
   int oldpp;
   SLOT_DESC *sd;

   if ((varexp->type != SF_VARIABLE) && (varexp->type != MF_VARIABLE))
     return(0);
   if ((strncmp(ValueToString(varexp->value),SELF_STRING,SELF_LEN) == 0) ?
               (ValueToString(varexp->value)[SELF_LEN] == SELF_SLOT_REF) : FALSE)
     {
      OpenStringSource(theEnv,"hnd-var",ValueToString(varexp->value) + SELF_LEN + 1,0);
      oldpp = GetPPBufferStatus(theEnv);
      SetPPBufferStatus(theEnv,OFF);
      GetToken(theEnv,"hnd-var",&itkn);
      SetPPBufferStatus(theEnv,oldpp);
      CloseStringSource(theEnv,"hnd-var");
      if (itkn.type != STOP)
        {
         sd = CheckSlotReference(theEnv,(DEFCLASS *) userBuffer,itkn.type,itkn.value,
                                 FALSE,NULL);
         if (sd == NULL)
           return(-1);
         GenHandlerSlotReference(theEnv,varexp,HANDLER_GET,sd);
         return(1);
        }
     }
   return(0);
  }
