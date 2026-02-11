imap_readTimeoutCbk (TimeoutId id, void *data)
{
  Connection cxn = (Connection) data ;
  const char *peerName ;

  ASSERT (id == cxn->imap_readBlockedTimerId) ;

  peerName = hostPeerName (cxn->myHost) ;

  warn ("%s:%d cxnsleep non-responsive connection", peerName, cxn->ident) ;
  d_printf(0, "%s:%d shutting down non-responsive IMAP connection (%s)\n",
	   hostPeerName (cxn->myHost), cxn->ident,
	   imap_stateToString(cxn->imap_state));

  cxnLogStats (cxn,true);

  if (cxn->imap_state == IMAP_DISCONNECTED)
    {
      imap_Disconnect(cxn);
      lmtp_Disconnect(cxn);
      delConnection (cxn) ;
    }
  else {
      imap_Disconnect(cxn);
  }
}
