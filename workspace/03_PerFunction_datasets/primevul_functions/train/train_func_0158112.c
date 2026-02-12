static void FindCallback( void *callbackData, OFBool cancelled, T_DIMSE_C_FindRQ * , DcmDataset *requestIdentifiers, int responseCount, T_DIMSE_C_FindRSP *response, DcmDataset **responseIdentifiers, DcmDataset **statusDetail )


{
  WlmDataSourceStatusType dbstatus;
  WlmFindContextType *context = NULL;
  WlmDataSource *dataSource = NULL;
  OFCmdUnsignedInt opt_sleepDuringFind = 0;


  context = (WlmFindContextType*)callbackData;
  dataSource = context->dataSource;
  opt_sleepDuringFind = context->opt_sleepDuringFind;


  dbstatus = context->priorStatus;


  if( responseCount == 1 )
  {

    DCMWLM_INFO("Find SCP Request Identifiers:" << OFendl
      << DcmObject::PrintHelper(*requestIdentifiers) << OFendl
      << "=============================");


    dbstatus = dataSource->StartFindRequest( *requestIdentifiers );
    if( !( dbstatus == WLM_PENDING || dbstatus == WLM_PENDING_WARNING || dbstatus == WLM_SUCCESS) )
      DCMWLM_DEBUG("Worklist Database: StartFindRequest() Failed (" << DU_cfindStatusString((Uint16)dbstatus) << ")");

    DCMWLM_INFO("=============================");
  }


  if( opt_sleepDuringFind > 0 )
  {
    DCMWLM_INFO("SLEEPING (during find): " << opt_sleepDuringFind << " secs");
    OFStandard::sleep((unsigned int)opt_sleepDuringFind);
  }


  if( cancelled && ( dbstatus == WLM_PENDING || dbstatus == WLM_PENDING_WARNING ) )
    dbstatus = dataSource->CancelFindRequest();


  if( dbstatus == WLM_PENDING || dbstatus == WLM_PENDING_WARNING )
  {

    *responseIdentifiers = dataSource->NextFindResponse( dbstatus );
  }


  if (DCM_dcmwlmLogger.isEnabledFor(OFLogger::INFO_LOG_LEVEL))
  {
    DCMWLM_INFO("Worklist Find SCP Response " << responseCount << " (" << DU_cfindStatusString((Uint16)dbstatus) << ")");
    if( *responseIdentifiers != NULL && (*responseIdentifiers)->card() > 0 )
    {
      DCMWLM_INFO(DcmObject::PrintHelper(**responseIdentifiers) << OFendl << "-----------------------------");
    }
  }


  response->DimseStatus = dbstatus;


  if( *statusDetail != NULL )
  {
    delete *statusDetail;
    *statusDetail = NULL;
  }


  switch( dbstatus )
  {
    case WLM_FAILED_IDENTIFIER_DOES_NOT_MATCH_SOP_CLASS:
    case WLM_FAILED_UNABLE_TO_PROCESS:
      DCMWLM_WARN(AddStatusDetail( statusDetail, dataSource->GetOffendingElements()));
      DCMWLM_WARN(AddStatusDetail( statusDetail, dataSource->GetErrorComments()));
      break;
    case WLM_REFUSED_OUT_OF_RESOURCES:

      DCMWLM_WARN(AddStatusDetail( statusDetail, dataSource->GetErrorComments()));
      break;
    default:

      break;
  }
}
