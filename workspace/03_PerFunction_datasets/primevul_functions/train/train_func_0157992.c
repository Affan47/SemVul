OFCondition DcmSCP::sendSTOREResponse(const T_ASC_PresentationContextID presID,
                                      const Uint16 messageID,
                                      const OFString &sopClassUID,
                                      const OFString &sopInstanceUID,
                                      const Uint16 rspStatusCode,
                                      DcmDataset *statusDetail)
{
  OFCondition cond;
  OFString tempStr;


  T_DIMSE_Message response;

  bzero((char*)&response, sizeof(response));
  T_DIMSE_C_StoreRSP &storeRsp = response.msg.CStoreRSP;
  response.CommandField = DIMSE_C_STORE_RSP;
  storeRsp.MessageIDBeingRespondedTo = messageID;
  storeRsp.DimseStatus = rspStatusCode;
  storeRsp.DataSetType = DIMSE_DATASET_NULL;

  storeRsp.opts = O_STORE_AFFECTEDSOPCLASSUID | O_STORE_AFFECTEDSOPINSTANCEUID;
  OFStandard::strlcpy(storeRsp.AffectedSOPClassUID, sopClassUID.c_str(), sizeof(storeRsp.AffectedSOPClassUID));
  OFStandard::strlcpy(storeRsp.AffectedSOPInstanceUID, sopInstanceUID.c_str(), sizeof(storeRsp.AffectedSOPInstanceUID));

  if (DCM_dcmnetLogger.isEnabledFor(OFLogger::DEBUG_LOG_LEVEL))
  {
    DCMNET_INFO("Sending C-STORE Response");
    DCMNET_DEBUG(DIMSE_dumpMessage(tempStr, response, DIMSE_OUTGOING, NULL, presID));
  } else {
    DCMNET_INFO("Sending C-STORE Response (" << DU_cstoreStatusString(rspStatusCode) << ")");
  }


  cond = sendDIMSEMessage(presID, &response, NULL , statusDetail);
  if (cond.bad())
  {
    DCMNET_ERROR("Failed sending C-STORE response: " << DimseCondition::dump(tempStr, cond));
  }

  return cond;
}
