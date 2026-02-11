makeCharClass(unsigned char *cclass)
{
  unsigned char  bits[32];
  setter         set;
  int            c, prev= -1;
  static char    string[256];
  char          *ptr;

  if ('^' == *cclass)
    {
      memset(bits, 255, 32);
      set= charClassClear;
      ++cclass;
    }
  else
    {
      memset(bits, 0, 32);
      set= charClassSet;
    }
  while (0 != (c= readChar(&cclass)))
    {
      if ('-' == c && *cclass && prev >= 0)
        {
          for (c= readChar(&cclass); prev <= c; ++prev)
            set(bits, prev);
          prev= -1;
        }
      else
  {
    set(bits, prev= c);
  }
    }

  ptr= string;
  for (c= 0;  c < 32;  ++c)
    ptr += sprintf(ptr, "\\%03o", bits[c]);

  return string;
}
