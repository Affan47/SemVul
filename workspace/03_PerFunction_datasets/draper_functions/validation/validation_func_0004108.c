preproc_evaluate_integer(
  const char *cp, preproc_int_t *val, int *is_unsigned)
{
  const char *ep;
  int base = 0;
  ep = cp;

  if (cp[0] == '0' && (cp[1] == 'x' || cp[1] == 'X'))
    {
    cp += 2;
    base = 16;
    *is_unsigned = 1;
    ep = cp;
    while ((*ep >= '0' && *ep <= '9') ||
           (*ep >= 'a' && *ep <= 'f') ||
           (*ep >= 'A' && *ep <= 'F'))
      {
      ep++;
      }
    }
  else if (cp[0] == '0' && (cp[1] >= '0' && cp[1] <= '9'))
    {
    cp += 1;
    base = 8;
    *is_unsigned = 1;
    ep = cp;
    while (*ep >= '0' && *ep <= '7')
      {
      ep++;
      }
    }
  else
    {
    base = 10;
    *is_unsigned = 0;
    while (*ep >= '0' && *ep <= '9')
      {
      ep++;
      }
    }

  for (;;)
    {
    if (ep[0] == 'i' && ep[1] == '6' && ep[2] == '4') { ep += 3; }
    else if (*ep == 'u') { *is_unsigned = 1; ep++; }
    else if (*ep == 'l' || *ep == 'L') { ep++; }
    else { break; }
    }

  if (*is_unsigned)
    {
    *val = (preproc_int_t)string_to_preproc_uint(cp, base);
    }
  else
    {
    *val = string_to_preproc_int(cp, base);
    }

  if (*ep == '.' || *ep == 'e' || *ep == 'E')
    {
    return VTK_PARSE_PREPROC_DOUBLE;
    }

  return VTK_PARSE_OK;
}
