AnnounceDisconnection()
{
   if(!mCC->bFilePlayer && mCC->bConnected) {

      LinkedNode *pLink = pTransmitters;

      mCC->bConnected = FALSE;
      ConferenceClients--;

      while(pLink != NULL) {
         if(pLink->pTx->ConnectAnnouncements &&
            (!mCC->bIRLP || pLink->pTx->IRLPAnnouncements))
         {
            pLink->pTx->SayPhrase(NodeName,SAY_FLAG_CALLSIGN);
            pLink->pTx->SayPhrase("disconnected");
         }
         pLink = pLink->pNextTx;
      }
   }
}
