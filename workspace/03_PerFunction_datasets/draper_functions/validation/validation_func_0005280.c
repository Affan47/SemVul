strinresp ( char *s )
{
  char *p, *r = 0 ;

  for ( p=responses ; p<lresponse && !r ; p += strlen(p) + 1 )
    if ( strncmp ( p, "AT", 2 ) )
      r = strstr ( p, s ) ;

  return r ;
}
