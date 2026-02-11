__strtoul_internal (const char *nptr, char **endptr, int base, int group)
{
  unsigned long int result = 0;
  long int sign = 1;
  unsigned max_digit;

  while (*nptr == ' ' || *nptr == '\t')
    ++nptr;

  if (*nptr == '-')
    {
      sign = -1;
      ++nptr;
    }
  else if (*nptr == '+')
    ++nptr;

  if (*nptr < '0' || *nptr > '9')
    {
      if (endptr != NULL)
	*endptr = (char *) nptr;
      return 0UL;
    }

  assert (base == 0);
  base = 10;
  max_digit = 9;
  if (*nptr == '0')
    {
      if (nptr[1] == 'x' || nptr[1] == 'X')
	{
	  base = 16;
	  nptr += 2;
	}
      else
	{
	  base = 8;
	  max_digit = 7;
	}
    }

  while (1)
    {
      unsigned long int digval;
      if (*nptr >= '0' && *nptr <= '0' + max_digit)
        digval = *nptr - '0';
      else if (base == 16)
        {
	  if (*nptr >= 'a' && *nptr <= 'f')
	    digval = *nptr - 'a' + 10;
	  else if (*nptr >= 'A' && *nptr <= 'F')
	    digval = *nptr - 'A' + 10;
	  else
	    break;
	}
      else
        break;

      if (result > ULONG_MAX / base
	  || (result == ULONG_MAX / base && digval > ULONG_MAX % base))
	{
	  errno = ERANGE;
	  if (endptr != NULL)
	    *endptr = (char *) nptr;
	  return ULONG_MAX;
	}
      result *= base;
      result += digval;
      ++nptr;
    }

  if (endptr != NULL)
    *endptr = (char *) nptr;
  return result * sign;
}
