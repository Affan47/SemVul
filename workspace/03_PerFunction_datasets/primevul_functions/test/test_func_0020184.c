bash_dequote_filename (text, quote_char)
     char *text;
     int quote_char;
{
  char *ret, *p, *r;
  int l, quoted;

  l = strlen (text);
  ret = (char *)xmalloc (l + 1);
  for (quoted = quote_char, p = text, r = ret; p && *p; p++)
    {

      if (*p == '\\')
	{

	  if (quoted == '\'')
	    *r++ = *p;


	  else if (quoted == '"' && ((sh_syntaxtab[(unsigned char)p[1]] & CBSDQUOTE) == 0))
	    *r++ = *p;

	  *r++ = *++p;
	  if (*p == '\0')
	    return ret;
	  continue;
	}

      if (quoted && *p == quoted)
	{
	  quoted = 0;
	  continue;
	}

      if (quoted == 0 && (*p == '\'' || *p == '"'))
	{
	  quoted = *p;
	  continue;
	}
      *r++ = *p;
    }
  *r = '\0';
  return ret;
}
