OFCondition DcmSCP::processAssociationRQ()
{
  DcmSCPActionType desiredAction = DCMSCP_ACTION_UNDEFINED;
  if ( (m_assoc == NULL) || (m_assoc->params == NULL) )
    return ASC_NULLKEY;


  notifyAssociationRequest(*m_assoc->params, desiredAction);
  if (desiredAction != DCMSCP_ACTION_UNDEFINED)
  {
    if (desiredAction == DCMSCP_ACTION_REFUSE_ASSOCIATION)
    {
      refuseAssociation( DCMSCP_INTERNAL_ERROR );
      dropAndDestroyAssociation();
      return EC_Normal;
    }
    else desiredAction = DCMSCP_ACTION_UNDEFINED;
  }


  if( m_cfg->getRefuseAssociation() )
  {
    refuseAssociation( DCMSCP_FORCED );
    dropAndDestroyAssociation();
    return EC_Normal;
  }


  char buf[BUFSIZ];
  OFCondition cond = ASC_getApplicationContextName( m_assoc->params, buf );
  if( cond.bad() || strcmp( buf, DICOM_STDAPPLICATIONCONTEXT ) != 0 )
  {
    refuseAssociation( DCMSCP_BAD_APPLICATION_CONTEXT_NAME );
    dropAndDestroyAssociation();
    return EC_Normal;
  }


  if (!checkCalledAETitleAccepted(m_assoc->params->DULparams.calledAPTitle))
  {
    refuseAssociation( DCMSCP_CALLED_AE_TITLE_NOT_RECOGNIZED );
    dropAndDestroyAssociation();
    return EC_Normal;
  }

  if (!checkCallingAETitleAccepted(m_assoc->params->DULparams.callingAPTitle))
  {
    refuseAssociation( DCMSCP_CALLING_AE_TITLE_NOT_RECOGNIZED );
    dropAndDestroyAssociation();
    return EC_Normal;
  }


  if (m_cfg->getRespondWithCalledAETitle())
    ASC_setAPTitles(m_assoc->params, NULL, NULL, m_assoc->params->DULparams.calledAPTitle);
  else
    ASC_setAPTitles(m_assoc->params, NULL, NULL, m_cfg->getAETitle().c_str());


  cond = negotiateAssociation();
  if( cond.bad() )
  {
    dropAndDestroyAssociation();
    return EC_Normal;
  }


  if( ASC_countAcceptedPresentationContexts( m_assoc->params ) == 0 )
  {

    OFString tempStr;
    DCMNET_INFO("No Acceptable Presentation Contexts");
    if (m_cfg->getVerbosePCMode())
      DCMNET_INFO(ASC_dumpParameters(tempStr, m_assoc->params, ASC_ASSOC_RJ));
    else
      DCMNET_DEBUG(ASC_dumpParameters(tempStr, m_assoc->params, ASC_ASSOC_RJ));
    refuseAssociation( DCMSCP_NO_PRESENTATION_CONTEXTS );
    dropAndDestroyAssociation();
    return EC_Normal;
  }


  cond = ASC_acknowledgeAssociation( m_assoc );
  if( cond.bad() )
  {
    dropAndDestroyAssociation();
    return EC_Normal;
  }
  notifyAssociationAcknowledge();


  OFString tempStr;
  DCMNET_INFO("Association Acknowledged (Max Send PDV: " << OFstatic_cast(Uint32, m_assoc->sendPDVLength) << ")");
  if (m_cfg->getVerbosePCMode())
    DCMNET_INFO(ASC_dumpParameters(tempStr, m_assoc->params, ASC_ASSOC_AC));
  else
    DCMNET_DEBUG(ASC_dumpParameters(tempStr, m_assoc->params, ASC_ASSOC_AC));


   handleAssociation();
   return EC_Normal;
}
