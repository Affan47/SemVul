sh_single_quote (string)
     const char *string;
{
  register int c;
  char *result, *r;
  const char *s;

  result = (char *)xmalloc (3 + (4 * strlen (string)));
  r = result;
  *r++ = '\'';

  for (s = string; s && (c = *s); s++)
    {
      *r++ = c;

      if (c == '\'')
	{
	  *r++ = '\\';
	  *r++ = '\'';
	  *r++ = '\'';
	}
    }

  *r++ = '\'';
  *r = '\0';

  return (result);
}
