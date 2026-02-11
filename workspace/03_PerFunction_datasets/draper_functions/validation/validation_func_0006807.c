my_fcvt(double x, int precision, char *to, my_bool *error)
{
  int decpt, sign, len, i;
  char *res, *src, *end, *dst= to;
  char buf[DTOA_BUFF_SIZE];
  DBUG_ASSERT(precision >= 0 && precision < NOT_FIXED_DEC && to != NULL);

  res= dtoa(x, 5, precision, &decpt, &sign, &end, buf, sizeof(buf));

  if (decpt == DTOA_OVERFLOW)
  {
    dtoa_free(res, buf, sizeof(buf));
    *to++= '0';
    *to= '\0';
    if (error != NULL)
      *error= TRUE;
    return 1;
  }

  src= res;
  len= end - src;

  if (sign)
    *dst++= '-';

  if (decpt <= 0)
  {
    *dst++= '0';
    *dst++= '.';
    for (i= decpt; i < 0; i++)
      *dst++= '0';
  }

  for (i= 1; i <= len; i++)
  {
    *dst++= *src++;
    if (i == decpt && i < len)
      *dst++= '.';
  }
  while (i++ <= decpt)
    *dst++= '0';

  if (precision > 0)
  {
    if (len <= decpt)
      *dst++= '.';

    for (i= precision - max(0, (len - decpt)); i > 0; i--)
      *dst++= '0';
  }

  *dst= '\0';
  if (error != NULL)
    *error= FALSE;

  dtoa_free(res, buf, sizeof(buf));

  return dst - to;
}
