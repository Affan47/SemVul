cmd_time (const char *com, const char *val, void *place)
{
  double number, mult;
  const char *end = val + strlen (val);


  while (val < end && c_isspace (end[-1]))
    --end;

  if (val == end)
    {
    err:
      fprintf (stderr, _("%s: %s: Invalid time period %s\n"),
               exec_name, com, quote (val));
      return false;
    }

  switch (c_tolower (end[-1]))
    {
    case 's':
      --end, mult = 1;
      break;
    case 'm':
      --end, mult = 60;
      break;
    case 'h':
      --end, mult = 3600;
      break;
    case 'd':
      --end, mult = 86400.0;
      break;
    case 'w':
      --end, mult = 604800.0;
      break;
    default:


      mult = 1;
    }


  while (val < end && c_isspace (*val))
    ++val;
  while (val < end && c_isspace (end[-1]))
    --end;
  if (val == end)
    goto err;

  if (!simple_atof (val, end, &number))
    goto err;

  *(double *)place = number * mult;
  return true;
}
