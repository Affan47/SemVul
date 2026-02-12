OFCondition WlmActivityManager::WaitForAssociation( T_ASC_Network * net )


{
  T_ASC_Association *assoc = NULL;
  char buf[BUFSIZ];
  int timeout;


  if( opt_singleProcess )
    timeout = 1000;
  else
  {
    if( processTable.size() > 0 )
      timeout = 1;
    else
      timeout = 1000;
  }


  OFCondition cond = ASC_receiveAssociation( net, &assoc, opt_maxPDU, NULL, NULL, OFFalse, DUL_NOBLOCK, timeout );


  if ( ( cond.code() == DULC_FORKEDCHILD ) || ( cond == DUL_NOASSOCIATIONREQUEST ) )
    return EC_Normal;


  if( cond.bad() && !opt_singleProcess )
  {
    ASC_dropAssociation( assoc );
    ASC_destroyAssociation( &assoc );
    return EC_Normal;
  }

  DCMWLM_INFO("Association Received ("
    << assoc->params->DULparams.callingPresentationAddress
    << ":" << assoc->params->DULparams.callingAPTitle
    << " -> " << assoc->params->DULparams.calledAPTitle << ")");


  OFString temp_str;
  DCMWLM_DEBUG("Parameters:" << OFendl << ASC_dumpParameters(temp_str, assoc->params, ASC_ASSOC_RQ));


  if( opt_refuseAssociation )
  {
    RefuseAssociation( &assoc, WLM_FORCED );
    if( !opt_singleProcess )
    {
      ASC_dropAssociation( assoc );
      ASC_destroyAssociation( &assoc );
    }
    return( EC_Normal );
  }


  cond = ASC_getApplicationContextName( assoc->params, buf );
  if( cond.bad() || strcmp( buf, DICOM_STDAPPLICATIONCONTEXT ) != 0 )
  {
    RefuseAssociation( &assoc, WLM_BAD_APP_CONTEXT );
    if( !opt_singleProcess )
    {
      ASC_dropAssociation( assoc );
      ASC_destroyAssociation( &assoc );
    }
    return( EC_Normal );
  }


  if( opt_rejectWithoutImplementationUID && strlen( assoc->params->theirImplementationClassUID ) == 0 )
  {
    RefuseAssociation( &assoc, WLM_NO_IC_UID );
    if( !opt_singleProcess )
    {
      ASC_dropAssociation( assoc );
      ASC_destroyAssociation( &assoc );
    }
    return( EC_Normal );
  }


  if( (int)processTable.size() >= opt_maxAssociations )
  {
    RefuseAssociation( &assoc, WLM_TOO_MANY_ASSOCIATIONS );
    if( !opt_singleProcess )
    {
      ASC_dropAssociation( assoc );
      ASC_destroyAssociation( &assoc );
    }
    return( EC_Normal );
  }


  dataSource->SetCalledApplicationEntityTitle( assoc->params->DULparams.calledAPTitle );
  if( !dataSource->IsCalledApplicationEntityTitleSupported() )
  {
    RefuseAssociation( &assoc, WLM_BAD_AE_SERVICE );
    if( !opt_singleProcess )
    {
      ASC_dropAssociation( assoc );
      ASC_destroyAssociation( &assoc );
    }
    return( EC_Normal );
  }


  cond = NegotiateAssociation( assoc );
  if( cond.bad() )
  {
    if( !opt_singleProcess )
    {
      ASC_dropAssociation( assoc );
      ASC_destroyAssociation( &assoc );
    }
    return( EC_Normal );
  }


  if( ASC_countAcceptedPresentationContexts( assoc->params ) == 0 )
  {
    DCMWLM_INFO("No Acceptable Presentation Contexts");
    RefuseAssociation( &assoc, WLM_FORCED );
    if( !opt_singleProcess )
    {
      ASC_dropAssociation( assoc );
      ASC_destroyAssociation( &assoc );
    }
    return( EC_Normal );
  }


  cond = ASC_acknowledgeAssociation( assoc );
  if( cond.bad() )
  {
    if( !opt_singleProcess )
    {
      ASC_dropAssociation( assoc );
      ASC_destroyAssociation( &assoc );
    }
    return( EC_Normal );
  }


  DCMWLM_INFO("Association Acknowledged (Max Send PDV: " << assoc->sendPDVLength << ")");


  DCMWLM_DEBUG(ASC_dumpParameters(temp_str, assoc->params, ASC_ASSOC_AC));


  if( opt_singleProcess || opt_forkedChild )
  {

    HandleAssociation( assoc );
  }
#ifdef HAVE_FORK
  else
  {

    int pid = (int)(fork());
    if( pid < 0 )
    {
      RefuseAssociation( &assoc, WLM_CANNOT_FORK );
      if( !opt_singleProcess )
      {
        ASC_dropAssociation( assoc );
        ASC_destroyAssociation( &assoc );
      }
      return( EC_Normal );
    }
    else if( pid > 0 )
    {


      AddProcessToTable( pid, assoc );


      ASC_dropAssociation( assoc );
      ASC_destroyAssociation( &assoc );
    }
    else
    {


      HandleAssociation( assoc );


      exit(0);
    }
  }
#endif

  return( EC_Normal );
}
