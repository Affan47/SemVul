quote_string(const char *s,
             char       *q,
             size_t     qsize)
{
  char	*qptr,
	*qend;


  qptr = q;
  qend = q + qsize - 5;

  if (qend < q)
  {
    *q = '\0';
    return (q);
  }

  *qptr++ = '\'';
  *qptr++ = '\"';

  while (*s && qptr < qend)
  {
    if (*s == '\\' || *s == '\"' || *s == '\'')
    {
      if (qptr < (qend - 4))
      {
	*qptr++ = '\\';
	*qptr++ = '\\';
	*qptr++ = '\\';
      }
      else
        break;
    }

    *qptr++ = *s++;
  }

  *qptr++ = '\"';
  *qptr++ = '\'';
  *qptr   = '\0';

  return (q);
}
