get_quoted_string(
            FILE* file,
   char* line
) { PROFILE(GET_QUOTED_STRING);

  bool found = FALSE;
  char c[128];
  int  i     = 0;


  while( ((c[i] = getc( file )) != EOF) && isspace( c[i] ) ) i++;


  if( c[i] == '"' ) {

    i = 0;
    while( ((line[i] = getc( file )) != EOF) && (line[i] != '"') ) i++;
    line[i]  = '\0';
    found = TRUE;


  } else {

    for( ; i >= 0; i-- ) {
      (void)ungetc( c[i], file );
    }

  }

  PROFILE_END;

  return( found );

}
