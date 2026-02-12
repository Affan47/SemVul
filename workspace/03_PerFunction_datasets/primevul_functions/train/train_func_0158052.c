OFCondition WlmActivityManager::HandleFindSCP( T_ASC_Association *assoc, T_DIMSE_C_FindRQ *request, T_ASC_PresentationContextID presID )


{

  OFString temp_str;
  WlmFindContextType context;
  context.dataSource = dataSource;
  context.priorStatus = WLM_PENDING;
  ASC_getAPTitles( assoc->params, NULL, context.ourAETitle, NULL );
  context.opt_sleepDuringFind = opt_sleepDuringFind;


  DCMWLM_INFO(DIMSE_dumpMessage(temp_str, *request, DIMSE_INCOMING, NULL, presID));


  OFCondition cond = DIMSE_findProvider( assoc, presID, request, FindCallback, &context, opt_blockMode, opt_dimse_timeout );
  if( cond.bad() )
    DCMWLM_ERROR("Find SCP Failed: " << DimseCondition::dump(temp_str, cond));


  if( opt_sleepAfterFind > 0 )
  {
    DCMWLM_INFO("Sleeping (after find): " << opt_sleepAfterFind << " secs");
    OFStandard::sleep( (unsigned int)opt_sleepAfterFind );
  }


  return cond;
}
