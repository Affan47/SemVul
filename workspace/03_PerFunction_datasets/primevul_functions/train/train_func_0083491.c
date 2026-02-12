OFCondition WlmActivityManager::StartProvidingService()


{
  OFCondition cond = EC_Normal;
  T_ASC_Network *net = NULL;


  if( !dcmDataDict.isDictionaryLoaded() )
  {
    DCMWLM_WARN("no data dictionary loaded, check environment variable: " << DCM_DICT_ENVIRONMENT_VARIABLE);
  }

#ifndef DISABLE_PORT_PERMISSION_CHECK
#ifdef HAVE_GETEUID

  if( opt_port < 1024 && geteuid() != 0 )
    return( WLM_EC_InsufficientPortPrivileges );
#endif
#endif

#ifdef _WIN32

  if (opt_forkedChild)
  {

    DUL_markProcessAsForkedChild();

    char buf[256];
    DWORD bytesRead = 0;
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);


    if (ReadFile(hStdIn, buf, sizeof(buf), &bytesRead, NULL))
    {

      buf[bytesRead] = '\0';
        dcmExternalSocketHandle.set(atoi(buf));
    }
    else
    {
      DCMWLM_ERROR("cannot read socket handle: " << GetLastError());
      exit(0);
    }
  }
  else
  {

    if (!opt_singleProcess)
      DUL_requestForkOnTransportConnectionReceipt(cmd_argc, cmd_argv);
  }
#endif


  cond = ASC_initializeNetwork( NET_ACCEPTOR, OFstatic_cast(int, opt_port), opt_acse_timeout, &net );
  if( cond.bad() ) return( WLM_EC_InitializationOfNetworkConnectionFailed );

#if defined(HAVE_SETUID) && defined(HAVE_GETUID)


  setuid( getuid() );
#endif


  while( cond.good() )
  {


    cond = WaitForAssociation( net );


#ifdef HAVE_FORK
    if( !opt_singleProcess )
      CleanChildren();
#elif defined(_WIN32)


    if (DUL_processIsForkedChild()) break;
#endif
  }


  cond = ASC_dropNetwork( &net );
  if( cond.bad() ) return( WLM_EC_TerminationOfNetworkConnectionFailed );


  return( EC_Normal );
}
