mime_patmatch(const char *s,
              const char *pat)
{


  if (s == NULL || pat == NULL)
    return (0);


  while (*s != '\0' && *pat != '\0')
  {
    if (*pat == '*')
    {


      pat ++;
      if (*pat == '\0')
        return (1);


      while (*s != '\0')
      {
        if (mime_patmatch(s, pat))
	  return (1);

	s ++;
      }
    }
    else if (*pat == '?')
    {


      pat ++;
      s ++;
      continue;
    }
    else if (*pat == '[')
    {


      pat ++;
      while (*pat != ']' && *pat != '\0')
        if (*s == *pat)
	  break;
	else
	  pat ++;

      if (*pat == ']' || *pat == '\0')
        return (0);

      while (*pat != ']' && *pat != '\0')
        pat ++;

      if (*pat == ']')
        pat ++;

      continue;
    }
    else if (*pat == '\\')
    {


      pat ++;
    }


    if (*pat++ != *s++)
      return (0);
  }


  return (*s == *pat);
}
