FlushCache()
{
  if(arg_verbose) CONSOLE.Debug("Flushing all cache");
  for( int i=0; i < m_npieces; i++ ){
    if( m_cache[i] ) FlushPiece(i);
    if( m_flush_failed ) break;
  }
}
