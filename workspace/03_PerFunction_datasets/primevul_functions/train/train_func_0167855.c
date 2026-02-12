parse_bytes_helper (const char *val, double *result)
{
  double number, mult;
  const char *end = val + strlen (val);


  if (0 == strcmp (val, "inf"))
    {
      *result = 0;
      return true;
    }


  while (val < end && c_isspace (end[-1]))
    --end;
  if (val == end)
    return false;

  switch (c_tolower (end[-1]))
    {
    case 'k':
      --end, mult = 1024.0;
      break;
    case 'm':
      --end, mult = 1048576.0;
      break;
    case 'g':
      --end, mult = 1073741824.0;
      break;
    case 't':
      --end, mult = 1099511627776.0;
      break;
    default:


      mult = 1;
    }


  while (val < end && c_isspace (*val))
    ++val;
  while (val < end && c_isspace (end[-1]))
    --end;
  if (val == end)
    return false;

  if (!simple_atof (val, end, &number) || number < 0)
    return false;

  *result = number * mult;
  return true;
}
