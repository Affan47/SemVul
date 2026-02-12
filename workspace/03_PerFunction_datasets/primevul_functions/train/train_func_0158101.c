checkRequestAgainstDataset(
    T_DIMSE_C_StoreRQ *req,
    const char* fname,
    DcmDataset *dataSet,
    T_DIMSE_C_StoreRSP *rsp,
    OFBool opt_correctUIDPadding)
{
    DcmFileFormat ff;
    if (dataSet == NULL)
    {

      if (ff.loadFile(fname).bad())
      {
        OFLOG_ERROR(dcmpsrcvLogger, "Cannot open file: " << fname);
        rsp->DimseStatus = STATUS_STORE_Refused_OutOfResources;
        return;
      }
      dataSet = ff.getDataset();
    }


    DIC_UI sopClass;
    DIC_UI sopInstance;

    if (!DU_findSOPClassAndInstanceInDataSet(dataSet, sopClass, sopInstance, opt_correctUIDPadding))
    {
      OFLOG_ERROR(dcmpsrcvLogger, "Bad image file: " << fname);
      rsp->DimseStatus = STATUS_STORE_Error_CannotUnderstand;
    }
    else if (strcmp(sopClass, req->AffectedSOPClassUID) != 0)
    {
      rsp->DimseStatus = STATUS_STORE_Error_DataSetDoesNotMatchSOPClass;
    }
    else if (strcmp(sopInstance, req->AffectedSOPInstanceUID) != 0)
    {
      rsp->DimseStatus = STATUS_STORE_Error_DataSetDoesNotMatchSOPClass;
    }
    else if (strcmp(sopClass, UID_GrayscaleSoftcopyPresentationStateStorage) == 0)
    {

      DcmPresentationState pstate;
      if (EC_Normal != pstate.read(*dataSet))
      {
        OFLOG_ERROR(dcmpsrcvLogger, "Grayscale softcopy presentation state object cannot be displayed - rejected");
        rsp->DimseStatus = STATUS_STORE_Error_CannotUnderstand;
      }
    }
    return;
}
