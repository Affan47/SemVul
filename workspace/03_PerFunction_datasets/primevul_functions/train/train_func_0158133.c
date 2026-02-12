WlmActivityManager::WlmActivityManager(
    WlmDataSource *dataSourcev,
    OFCmdUnsignedInt opt_portv,
    OFBool opt_refuseAssociationv,
    OFBool opt_rejectWithoutImplementationUIDv,
    OFCmdUnsignedInt opt_sleepAfterFindv,
    OFCmdUnsignedInt opt_sleepDuringFindv,
    OFCmdUnsignedInt opt_maxPDUv,
    E_TransferSyntax opt_networkTransferSyntaxv,
    OFBool opt_failInvalidQueryv,
    OFBool opt_singleProcessv,
    int opt_maxAssociationsv,
    T_DIMSE_BlockingMode opt_blockModev,
    int opt_dimse_timeoutv,
    int opt_acse_timeoutv,
    OFBool opt_forkedChildv,
    int argcv,
    char *argvv[] )


  : dataSource( dataSourcev ), opt_port( opt_portv ), opt_refuseAssociation( opt_refuseAssociationv ),
    opt_rejectWithoutImplementationUID( opt_rejectWithoutImplementationUIDv ),
    opt_sleepAfterFind( opt_sleepAfterFindv ), opt_sleepDuringFind( opt_sleepDuringFindv ),
    opt_maxPDU( opt_maxPDUv ), opt_networkTransferSyntax( opt_networkTransferSyntaxv ),
    opt_failInvalidQuery( opt_failInvalidQueryv ),
    opt_singleProcess( opt_singleProcessv ),  opt_forkedChild( opt_forkedChildv ), cmd_argc( argcv ),
    cmd_argv( argvv ), opt_maxAssociations( opt_maxAssociationsv ),
    opt_blockMode(opt_blockModev), opt_dimse_timeout(opt_dimse_timeoutv), opt_acse_timeout(opt_acse_timeoutv),
    supportedAbstractSyntaxes( NULL ), numberOfSupportedAbstractSyntaxes( 0 ),
    processTable( )
{

  supportedAbstractSyntaxes = new char*[2];
  supportedAbstractSyntaxes[0] = new char[ strlen( UID_VerificationSOPClass ) + 1 ];
  strcpy( supportedAbstractSyntaxes[0], UID_VerificationSOPClass );
  supportedAbstractSyntaxes[1] = new char[ strlen( UID_FINDModalityWorklistInformationModel ) + 1 ];
  strcpy( supportedAbstractSyntaxes[1], UID_FINDModalityWorklistInformationModel );
  numberOfSupportedAbstractSyntaxes = 2;


  dcmEnableAutomaticInputDataCorrection.set( OFFalse );
  if (!opt_forkedChild)
    DCMWLM_WARN("(notice: dcmdata auto correction disabled.)");

#ifdef HAVE_GUSI_H

  GUSISetup( GUSIwithSIOUXSockets );
  GUSISetup( GUSIwithInternetSockets );
#endif

#ifdef HAVE_WINSOCK_H
  WSAData winSockData;

  WORD winSockVersionNeeded = MAKEWORD( 1, 1 );
  WSAStartup(winSockVersionNeeded, &winSockData);
#endif

}
