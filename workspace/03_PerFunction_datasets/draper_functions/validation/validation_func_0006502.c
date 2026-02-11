myatosq(char *nptr, char **endp, int base)
{
  char *s, *save;
  int negative, overflow;
  sqword_t cutoff, cutlim, i;
  unsigned char c;
  extern int errno;

  if (!nptr || !*nptr)
    panic("strtoll() passed a NULL string");

  s = nptr;


  while (isspace((int)(*s)))
    ++s;
  if (*s == '\0')
    goto noconv;

  if (base == 0)
    {
      if (s[0] == '0' && toupper(s[1]) == 'X')
	base = 16;
      else
	base = 10;
    }

  if (base <= 1 || base > 36)
    panic("bogus base: %d", base);


  if (*s == '-')
    {
      negative = 1;
      ++s;
    }
  else if (*s == '+')
    {
      negative = 0;
      ++s;
    }
  else
    negative = 0;

  if (base == 16 && s[0] == '0' && toupper(s[1]) == 'X')
    s += 2;


  save = s;

  cutoff = LL_MAX / (unsigned long int) base;
  cutlim = LL_MAX % (unsigned long int) base;

  overflow = 0;
  i = 0;
  for (c = *s; c != '\0'; c = *++s)
    {
      if (isdigit (c))
        c -= '0';
      else if (isalpha (c))
        c = toupper(c) - 'A' + 10;
      else
        break;
      if (c >= base)
        break;


      if (i > cutoff || (i == cutoff && c > cutlim))
        overflow = 1;
      else
        {
          i *= (unsigned long int) base;
          i += c;
        }
    }


  if (s == save)
    goto noconv;


  if (endp != NULL)
    *endp = (char *) s;

  if (overflow)
    {
      errno = ERANGE;
      return negative ? LL_MIN : LL_MAX;
    }
  else
    {
      errno = 0;


      return (negative ? -i : i);
    }

noconv:

  if (endp != NULL)
    *endp = (char *) nptr;
  return 0;
}
