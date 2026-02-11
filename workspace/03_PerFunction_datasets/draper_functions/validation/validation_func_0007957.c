write( const void * buffer, size_t bufSize ) {
#ifndef NDEBUG

#endif
  if ( bufSize == 0 ) {
    return 0;
  }
  if ( !buffer ) {
     Error::setSystemError( GPG_ERR_EINVAL );
     return -1;
  }

  return mIO->write( static_cast<const char*>( buffer ), bufSize );
}
