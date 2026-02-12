pwg_unppdize_name(const char *ppd,
		  char       *name,
                  size_t     namesize,
                  const char *dashchars)
{
  char	*ptr,
	*end;


  if (_cups_islower(*ppd))
  {


    const char *ppdptr;

    for (ppdptr = ppd + 1; *ppdptr; ppdptr ++)
      if (_cups_isupper(*ppdptr) || strchr(dashchars, *ppdptr))
        break;

    if (!*ppdptr)
    {
      strlcpy(name, ppd, namesize);
      return;
    }
  }

  for (ptr = name, end = name + namesize - 1; *ppd && ptr < end; ppd ++)
  {
    if (_cups_isalnum(*ppd) || *ppd == '-')
      *ptr++ = (char)tolower(*ppd & 255);
    else if (strchr(dashchars, *ppd))
      *ptr++ = '-';
    else
      *ptr++ = *ppd;

    if (!_cups_isupper(*ppd) && _cups_isalnum(*ppd) &&
	_cups_isupper(ppd[1]) && ptr < end)
      *ptr++ = '-';
    else if (!isdigit(*ppd & 255) && isdigit(ppd[1] & 255))
      *ptr++ = '-';
  }

  *ptr = '\0';
}
