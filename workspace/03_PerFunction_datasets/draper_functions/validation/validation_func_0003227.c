hexdump (int level, char *comment, unsigned char *p, int l)
{
  int i;
  char line[128];
  char *ptr;

  if(DBG_LEVEL < level)
    return;

  DBG (level, "%s\n", comment);
  ptr = line;
  for (i = 0; i < l; i++, p++)
    {
      if ((i % 16) == 0)
        {
          if (ptr != line)
            {
              *ptr = '\0';
              DBG (level, "%s\n", line);
              ptr = line;
            }
          sprintf (ptr, "%3.3x:", i);
          ptr += 4;
        }
      sprintf (ptr, " %2.2x", *p);
      ptr += 3;
    }
  *ptr = '\0';
  DBG (level, "%s\n", line);
}
