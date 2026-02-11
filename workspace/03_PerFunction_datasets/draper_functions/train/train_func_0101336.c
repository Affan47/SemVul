translate( char *name )
{
  char *ip, *jp;
  static char buffer[1024];

  for( ip = name, jp = buffer; *ip != '\0'; ++ip, ++jp )
    *jp = (*ip == 'a' ? '-' : *ip);
  *jp = '\0';
  return( buffer );
}
