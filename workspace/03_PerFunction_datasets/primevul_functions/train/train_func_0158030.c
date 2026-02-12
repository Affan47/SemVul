void WlmActivityManager::AddProcessToTable( int pid, T_ASC_Association *assoc )


{
  WlmProcessSlotType *ps;


  ps = new WlmProcessSlotType ();


  ASC_getPresentationAddresses( assoc->params, ps->peerName, NULL );
  ASC_getAPTitles( assoc->params, ps->callingAETitle, ps->calledAETitle, NULL );
  ps->processId = pid;
  ps->startTime = time(NULL);
  ps->hasStorageAbility = OFFalse;


  processTable.push_back(ps);
}
