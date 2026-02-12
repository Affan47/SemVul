DcmSCP::DcmSCP() :
  m_assoc(NULL),
  m_cfg()
{
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
