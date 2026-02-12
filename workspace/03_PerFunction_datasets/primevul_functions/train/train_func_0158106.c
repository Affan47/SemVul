processCommands(T_ASC_Association * assoc)


{
  OFCondition cond = EC_Normal;
  T_DIMSE_Message msg;
  T_ASC_PresentationContextID presID = 0;
  DcmDataset *statusDetail = NULL;


  while( cond == EC_Normal || cond == DIMSE_NODATAAVAILABLE || cond == DIMSE_OUTOFRESOURCES )
  {

    if( opt_endOfStudyTimeout == -1 )
      cond = DIMSE_receiveCommand(assoc, DIMSE_BLOCKING, 0, &presID, &msg, &statusDetail);
    else
      cond = DIMSE_receiveCommand(assoc, DIMSE_NONBLOCKING, OFstatic_cast(int, opt_endOfStudyTimeout), &presID, &msg, &statusDetail);


    if( cond == DIMSE_NODATAAVAILABLE )
    {


      if( opt_endOfStudyTimeout != -1 && !lastStudyInstanceUID.empty() )
      {


        endOfStudyThroughTimeoutEvent = OFTrue;


        lastStudySubdirectoryPathAndName = subdirectoryPathAndName;


        executeEndOfStudyEvents();


        lastStudyInstanceUID.clear();


        subdirectoryPathAndName.clear();


        endOfStudyThroughTimeoutEvent = OFFalse;
      }
    }


    if (statusDetail != NULL)
    {
      OFLOG_DEBUG(storescpLogger, "Status Detail:" << OFendl << DcmObject::PrintHelper(*statusDetail));
      delete statusDetail;
    }


    if (cond == EC_Normal)
    {


      switch (msg.CommandField)
      {
        case DIMSE_C_ECHO_RQ:

          cond = echoSCP(assoc, &msg, presID);
          break;
        case DIMSE_C_STORE_RQ:

          cond = storeSCP(assoc, &msg, presID);
          break;
        default:
          OFString tempStr;

          cond = DIMSE_BADCOMMANDTYPE;
          OFLOG_ERROR(storescpLogger, "Expected C-ECHO or C-STORE request but received DIMSE command 0x"
               << STD_NAMESPACE hex << STD_NAMESPACE setfill('0') << STD_NAMESPACE setw(4)
               << OFstatic_cast(unsigned, msg.CommandField));
          OFLOG_DEBUG(storescpLogger, DIMSE_dumpMessage(tempStr, msg, DIMSE_INCOMING, NULL, presID));
          break;
      }
    }
  }
  return cond;
}
