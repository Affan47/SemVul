printProcessCount( const char* cmd )
{
  (void)cmd;
  struct dirent* entry;
  ProcessCount = 0;
  rewinddir(procDir);
  while ( ( entry = readdir( procDir ) ) )
    if ( isdigit( entry->d_name[ 0 ] ) )
      ProcessCount++;


  output( "%d\n", ProcessCount );
}
