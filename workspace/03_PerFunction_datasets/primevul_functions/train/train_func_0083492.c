OFCondition DcmSCP::listen()
{


  dcmEnableAutomaticInputDataCorrection.set( OFFalse );

  OFCondition cond = EC_Normal;

  if( !dcmDataDict.isDictionaryLoaded() )
    DCMNET_WARN("No data dictionary loaded, check environment variable: " << DCM_DICT_ENVIRONMENT_VARIABLE);

#ifndef DISABLE_PORT_PERMISSION_CHECK
#ifdef HAVE_GETEUID

  if( m_cfg->getPort() < 1024 && geteuid() != 0 )
  {
    DCMNET_ERROR("No privileges to open this network port (" << m_cfg->getPort() << ")");
    return NET_EC_InsufficientPortPrivileges;
  }
#endif
#endif


  T_ASC_Network *network = NULL;
  cond = ASC_initializeNetwork( NET_ACCEPTOR, OFstatic_cast(int, m_cfg->getPort()), m_cfg->getACSETimeout(), &network );
  if( cond.bad() )
    return cond;

#if defined(HAVE_SETUID) && defined(HAVE_GETUID)


  setuid( getuid() );
#endif


  while( cond.good() && !stopAfterCurrentAssociation() )
  {


    cond = waitForAssociationRQ(network);
  }


  cond = ASC_dropNetwork( &network );
  network = NULL;


  return cond;
}
