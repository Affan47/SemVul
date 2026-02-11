references_value_p (const_rtx x, int only_useless)
{
  const enum rtx_code code = GET_CODE (x);
  const char *fmt = GET_RTX_FORMAT (code);
  int i, j;

  if (GET_CODE (x) == VALUE
      && (! only_useless ||
	  (CSELIB_VAL_PTR (x)->locs == 0 && !PRESERVED_VALUE_P (x))))
    return 1;

  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e' && references_value_p (XEXP (x, i), only_useless))
	return 1;
      else if (fmt[i] == 'E')
	for (j = 0; j < XVECLEN (x, i); j++)
	  if (references_value_p (XVECEXP (x, i, j), only_useless))
	    return 1;
    }

  return 0;
}
