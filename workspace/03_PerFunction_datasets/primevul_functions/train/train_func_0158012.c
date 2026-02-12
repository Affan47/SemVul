OFCondition DcmSCP::receiveSTORERequest(T_DIMSE_C_StoreRQ &reqMessage,
                                        const T_ASC_PresentationContextID presID,
                                        const OFString &filename)
{

  if (m_assoc == NULL)
    return DIMSE_ILLEGALASSOCIATION;

  OFCondition cond;
  OFString tempStr;

  T_ASC_PresentationContextID presIDdset = presID;


  if (DCM_dcmnetLogger.isEnabledFor(OFLogger::DEBUG_LOG_LEVEL))
    DCMNET_INFO("Received C-STORE Request");
  else
    DCMNET_INFO("Received C-STORE Request (MsgID " << reqMessage.MessageID << ")");


  if (reqMessage.DataSetType == DIMSE_DATASET_NULL)
  {
    DCMNET_DEBUG(DIMSE_dumpMessage(tempStr, reqMessage, DIMSE_INCOMING, NULL, presID));
    DCMNET_ERROR("Received C-STORE request but no dataset announced, aborting");
    return DIMSE_BADMESSAGE;
  }


  cond = receiveSTORERequestDataset(&presIDdset, reqMessage, filename);
  if (cond.bad())
  {
    DCMNET_DEBUG(DIMSE_dumpMessage(tempStr, reqMessage, DIMSE_INCOMING, NULL, presID));
    DCMNET_ERROR("Unable to receive C-STORE dataset on presentation context " << OFstatic_cast(unsigned int, presID));
    return cond;
  }


  DCMNET_DEBUG(DIMSE_dumpMessage(tempStr, reqMessage, DIMSE_INCOMING, NULL, presID));


  if (presIDdset != presID)
  {
    DCMNET_ERROR("Presentation Context ID of command (" << OFstatic_cast(unsigned int, presID)
      << ") and data set (" << OFstatic_cast(unsigned int, presIDdset) << ") differs");
    return makeDcmnetCondition(DIMSEC_INVALIDPRESENTATIONCONTEXTID, OF_error,
      "DIMSE: Presentation Contexts of Command and Data Set differ");
  }

  return cond;
}
