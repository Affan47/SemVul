ourCopyAppendFile ( fromName , toName , operationType )
  char  * fromName ;
  char  * toName ;
  int  operationType ;
{
  int  flags ;
  int  fromFile ;
  int  toFile ;
  int  bytesRead ;
  char  theBuffer [ CopyBlockSize ] ;

  if ( CopyOperation == operationType )
    flags = O_WRONLY | O_CREAT ;
  else
    flags = O_WRONLY | O_APPEND | O_CREAT ;

#ifdef vms
  fromFile = open ( fromName , O_RDONLY, 0, "ctx=rec", "shr=get,put,upd" ) ;
#else
  fromFile = open ( fromName , O_RDONLY ) ;
#endif
  if ( -1 == fromFile )
    fileErrorHelp ( fromName , 1 ) ;
  toFile = open ( toName , flags , CopyAppendPerms ) ;
  if ( -1 == toFile )
    fileErrorHelp ( toName ,
		    ( CopyOperation == operationType ) ? 2 : 3 ) ;

  do
  {
    bytesRead = read ( fromFile , theBuffer , CopyBlockSize ) ;
    if ( 0 < bytesRead )
      if ( bytesRead != write ( toFile , theBuffer , bytesRead ) )
	fileErrorHelp ( toName , 4 ) ;
  }
  while ( 0 < bytesRead ) ;

  close ( fromFile ) ;
  close ( toFile ) ;
}
