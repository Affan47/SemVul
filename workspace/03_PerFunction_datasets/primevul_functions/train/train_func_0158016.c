saveImageToDB(
    StoreContext *context,
    T_DIMSE_C_StoreRQ *req,
    const char *imageFileName,

    T_DIMSE_C_StoreRSP *rsp,
    DcmDataset **statusDetail)
{
    DcmQueryRetrieveDatabaseStatus dbStatus(STATUS_Success);


    if (context->status == STATUS_Success)
    {
      if (context->dbHandle->storeRequest(req->AffectedSOPClassUID, req->AffectedSOPInstanceUID,
          imageFileName, &dbStatus).bad())
      {
        OFLOG_ERROR(dcmpsrcvLogger, "storeSCP: Database: DB_storeRequest Failed ("
             << DU_cstoreStatusString(dbStatus.status()) << ")");
      }
      context->status = dbStatus.status();
    }

     rsp->DimseStatus = context->status;
    *statusDetail = dbStatus.extractStatusDetail();
    return;
}
