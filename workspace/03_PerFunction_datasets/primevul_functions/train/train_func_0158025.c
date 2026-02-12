void WlmActivityManager::HandleAssociation( T_ASC_Association *assoc )


{


  OFCondition cond = ReceiveAndHandleCommands( assoc );


  if( cond == DUL_PEERREQUESTEDRELEASE )
  {
    DCMWLM_INFO("Association Release");
    ASC_acknowledgeRelease( assoc );
    ASC_dropSCPAssociation( assoc );
  }
  else if( cond == DUL_PEERABORTEDASSOCIATION )
  {
    DCMWLM_INFO("Association Aborted");
  }
  else
  {
    OFString temp_str;
    DCMWLM_ERROR("DIMSE failure (aborting association): " << DimseCondition::dump(temp_str, cond));
    ASC_abortAssociation( assoc );
  }


  ASC_dropAssociation( assoc );
  ASC_destroyAssociation( &assoc );


  DCMWLM_INFO("+++++++++++++++++++++++++++++");
}
