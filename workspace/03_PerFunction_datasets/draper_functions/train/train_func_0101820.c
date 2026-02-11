ooManualProgress(const char *callToken)
{
   OOStackCommand cmd;
   OOH323CallData *call;

   if(!callToken)
   {
      return OO_STKCMD_INVALIDPARAM;
   }

   if(!(call = ooFindCallByToken(callToken))) {
      return OO_STKCMD_INVALIDPARAM;
   }

   if(call->CmdChan == 0)
   {
      if(ooCreateCallCmdConnection(call) != OO_OK)
         return OO_STKCMD_CONNECTIONERR;
   }

   if (call->h225version < 4)
      return OO_STKCMD_SUCCESS;

   memset(&cmd, 0, sizeof(OOStackCommand));
   cmd.type = OO_CMD_MANUALPROGRESS;
   cmd.param1 = (void*) malloc(strlen(callToken)+1);
   if(!cmd.param1)
   {
      return OO_STKCMD_MEMERR;
   }
   strcpy((char*)cmd.param1, callToken);
   cmd.plen1 = strlen(callToken);

   if(ooWriteCallStackCommand(call, &cmd) != OO_OK)
   {
      free(cmd.param1);
      return OO_STKCMD_WRITEERR;
   }

   free(cmd.param1);

   return OO_STKCMD_SUCCESS;
}
