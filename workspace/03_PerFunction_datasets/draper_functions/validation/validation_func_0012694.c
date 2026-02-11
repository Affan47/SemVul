modeCmdIssued (EndPoint e, IoStatus i, Buffer *b, void *d)
{
  Connection cxn = (Connection) d ;

  ASSERT (e == cxn->myEp) ;

  clearTimer (cxn->writeBlockedTimerId) ;


  initReadBlockedTimeout (cxn) ;

  if (i != IoDone)
    {
      d_printf (1,"%s:%d MODE STREAM command failed to write\n",
               hostPeerName (cxn->myHost), cxn->ident) ;

      syswarn ("%s:%d cxnsleep can't write MODE STREAM",
               hostPeerName (cxn->myHost), cxn->ident) ;

      cxnSleepOrDie (cxn) ;
    }

  freeBufferArray (b) ;
}
