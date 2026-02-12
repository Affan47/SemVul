OFCondition WlmActivityManager::HandleEchoSCP( T_ASC_Association *assoc, T_DIMSE_C_EchoRQ *req, T_ASC_PresentationContextID presId )


{
  OFString temp_str;


  DCMWLM_INFO("Received Echo Request");
  DCMWLM_DEBUG(DIMSE_dumpMessage(temp_str, *req, DIMSE_INCOMING, NULL, presId));


  OFCondition cond = DIMSE_sendEchoResponse( assoc, presId, req, STATUS_Success, NULL );
  if( cond.bad() )
    DCMWLM_ERROR("Echo SCP Failed: " << DimseCondition::dump(temp_str, cond));


  return cond;
}
