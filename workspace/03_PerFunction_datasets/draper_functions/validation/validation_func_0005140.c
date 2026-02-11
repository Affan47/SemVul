CancelPiece(size_t idx)
{
  PEERNODE *p;
  int t, r=0;

  for( p = m_head; p; p = p->next ){
    if( !PEER_IS_SUCCESS(p->peer) ) continue;

    t = p->peer->CancelPiece(idx);
    if( t ){
      r = 1;
      if( t < 0 ){
        if(arg_verbose) CONSOLE.Debug("close: CancelPiece");
        p->peer->CloseConnection();
      }
    }
  }
  return r;
}
