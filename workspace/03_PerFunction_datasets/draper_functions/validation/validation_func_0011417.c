setFileName( const QString& _txt )
{
  setFragment( QString() );
  int i = 0;
  while( i < _txt.length() && _txt[i] == QLatin1Char('/') )
      ++i;
  QString tmp = i ? _txt.mid( i ) : _txt;

  QString path = this->path();
  if ( path.isEmpty() )
#ifdef Q_OS_WIN
    path = isLocalFile() ? QDir::rootPath() : QLatin1String("/");
#else
    path = QDir::rootPath();
#endif
  else
  {
    int lastSlash = path.lastIndexOf( QLatin1Char('/') );
    if ( lastSlash == -1)
      path.clear();
    else if ( !path.endsWith( QLatin1Char('/') ) )
      path.truncate( lastSlash+1 );
  }

  path += tmp;
  setPath( path );

  cleanPath();
}
