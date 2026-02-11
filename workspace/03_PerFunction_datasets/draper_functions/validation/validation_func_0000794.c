chomp(char *buf)
{
  char *p;

  for(p=buf; *p != '\0'; p++);
  if(p != buf) { p--; }
  while(p>=buf && (*p == '\n' || *p == '\r'))
  {
    *p-- = '\0';
  }

  return(buf);
}
