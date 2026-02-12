OFCondition DcmSCP::sendSTOREResponse(T_ASC_PresentationContextID presID,
                                      const T_DIMSE_C_StoreRQ &reqMessage,
                                      const Uint16 rspStatusCode)
{

  return sendSTOREResponse(presID, reqMessage.MessageID, reqMessage.AffectedSOPClassUID, reqMessage.AffectedSOPInstanceUID,
    rspStatusCode, NULL );
}
