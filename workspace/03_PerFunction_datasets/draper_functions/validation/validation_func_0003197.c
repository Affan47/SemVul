ooAddNewLogicalChannel(OOH323CallData *call, int channelNo,
                                         int sessionID, char *dir,
                                         ooH323EpCapability *epCap)
{
   OOLogicalChannel *pNewChannel=NULL, *pChannel=NULL;
   OOMediaInfo *pMediaInfo = NULL;
   OOTRACEDBGC5("Adding new media channel for cap %d dir %s (%s, %s)\n",
               epCap->cap, dir, call->callType, call->callToken);

   pNewChannel = (OOLogicalChannel*)memAlloc(call->pctxt,
                                                     sizeof(OOLogicalChannel));
   if(!pNewChannel)
   {
      OOTRACEERR3("ERROR:Memory - ooAddNewLogicalChannel - pNewChannel "
                  "(%s, %s)\n", call->callType, call->callToken);
      return NULL;
   }

   memset(pNewChannel, 0, sizeof(OOLogicalChannel));
   pNewChannel->channelNo = channelNo;
   pNewChannel->sessionID = sessionID;
   pNewChannel->state = OO_LOGICALCHAN_IDLE;
   pNewChannel->type = epCap->capType;

   strcpy(pNewChannel->dir, dir);

   pNewChannel->chanCap = epCap;
   OOTRACEDBGC4("Adding new channel with cap %d (%s, %s)\n", epCap->cap,
                call->callType, call->callToken);


   if(call->mediaInfo)
   {
      pMediaInfo = call->mediaInfo;
      while(pMediaInfo)
      {
         if(!strcmp(pMediaInfo->dir, dir) &&
            (pMediaInfo->cap == epCap->cap))
         {
            break;
         }
         pMediaInfo = pMediaInfo->next;
      }
   }

   if(pMediaInfo)
   {
      OOTRACEDBGC3("Using configured media info (%s, %s)\n", call->callType,
                   call->callToken);
      pNewChannel->localRtpPort = pMediaInfo->lMediaRedirPort ? pMediaInfo->lMediaRedirPort : pMediaInfo->lMediaPort;

      pNewChannel->localRtcpPort = pMediaInfo->lMediaRedirPort ? pMediaInfo->lMediaRedirCPort : pMediaInfo->lMediaCntrlPort;


      if(!strcmp(pMediaInfo->lMediaIP, "0.0.0.0") || !strcmp(pMediaInfo->lMediaIP, "::"))
         strcpy(pNewChannel->localIP, call->localIP);
      else
         strcpy(pNewChannel->localIP, pMediaInfo->lMediaIP);

      OOTRACEDBGC5("Configured media info (%s, %s) %s:%d\n", call->callType, call->callToken, pNewChannel->localIP, pNewChannel->localRtcpPort);
   }
   else{
      OOTRACEDBGC3("Using default media info (%s, %s)\n", call->callType,
                   call->callToken);
      pNewChannel->localRtpPort = ooGetNextPort (OORTP);


      if((pNewChannel->localRtpPort & 1) == 1)
        pNewChannel->localRtpPort = ooGetNextPort (OORTP);

      pNewChannel->localRtcpPort = ooGetNextPort (OORTP);
      strcpy(pNewChannel->localIP, call->localIP);
   }


   pNewChannel->next = NULL;
   if(!call->logicalChans) {
      call->logicalChans = pNewChannel;
   }
   else{
      pChannel = call->logicalChans;
      while(pChannel->next)  pChannel = pChannel->next;
      pChannel->next = pNewChannel;
   }


   call->noOfLogicalChannels++;
   OOTRACEINFO3("Created new logical channel entry (%s, %s)\n", call->callType,
                call->callToken);
   return pNewChannel;
}
