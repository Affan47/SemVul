OFCondition DcmSCP::handleSTORERequest(T_DIMSE_C_StoreRQ &reqMessage,
                                       const T_ASC_PresentationContextID presID,
                                       DcmDataset *&reqDataset)
{

  OFCondition cond = receiveSTORERequest(reqMessage, presID, reqDataset);

  if (cond.good())
  {

    const Uint16 rspStatusCode = checkSTORERequest(reqMessage, reqDataset);

    cond = sendSTOREResponse(presID, reqMessage, rspStatusCode);
  }

  return cond;
}
