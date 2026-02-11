setErrorString( QString const & str )
{
  Mutex::Lock _( errorStringMutex );

  errorString = str;
}
