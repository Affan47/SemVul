void DcmSCP::handleAssociation()
{
  if (m_assoc == NULL)
  {
    DCMNET_WARN("DcmSCP::handleAssociation() called but SCP actually has no association running, ignoring");
    return;
  }


  OFCondition cond = EC_Normal;
  T_DIMSE_Message message;
  T_ASC_PresentationContextID presID;


  while( cond.good() )
  {

    cond = DIMSE_receiveCommand( m_assoc, m_cfg->getDIMSEBlockingMode(), m_cfg->getDIMSETimeout(),
                                 &presID, &message, NULL );


    if( cond.good() )
    {
      DcmPresentationContextInfo pcInfo;
      getPresentationContextInfo(m_assoc, presID, pcInfo);
      cond = handleIncomingCommand(&message, pcInfo);
    }
  }

  if( cond == DUL_PEERREQUESTEDRELEASE )
  {
    notifyReleaseRequest();
    ASC_acknowledgeRelease(m_assoc);
  }
  else if( cond == DUL_PEERABORTEDASSOCIATION )
  {
    notifyAbortRequest();
  }
  else
  {
    notifyDIMSEError(cond);
    ASC_abortAssociation( m_assoc );
  }


  dropAndDestroyAssociation();


  DCMNET_DEBUG( "+++++++++++++++++++++++++++++" );
}
