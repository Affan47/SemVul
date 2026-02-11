viewctltype( Type )

  ctltype_list *Type;
{
  long Index;

  fprintf( stdout, "\n--> Type" );

  viewctlline( Type->LINE );

  fprintf( stdout, "\n\t\tNAME     : %s",  Type->NAME  );
  fprintf( stdout, "\n\t\tINDEX    : %ld", Type->INDEX );
  fprintf( stdout, "\n\t\tLEFT     : %ld", Type->LEFT  );
  fprintf( stdout, "\n\t\tRIGHT    : %ld", Type->RIGHT );
  fprintf( stdout, "\n\t\tCLASS    : %c" , Type->CLASS );
  fprintf( stdout, "\n\t\tSIZE     : %ld", Type->SIZE  );

  if ( Type->BASE != (ctltype_list *)0 )
  {
    fprintf( stdout, "\n\t\tBASE     : %s", Type->BASE->NAME  );
  }

  fprintf( stdout, "\n\t\tVALUE    : " );

  for ( Index = 0; Index < Type->SIZE; Index++ )
  {
    fprintf( stdout, "%s ", Type->VALUE[ Index ] );
  }

  fprintf( stdout, "\n\t\tFLAGS    : %lx", Type->FLAGS );
  fprintf( stdout, "\n\t\tUSER     : %lx", (long)Type->USER );

  fprintf( stdout, "\n<-- Type" );
}
