_g_locale_charset_unalias (const char *codeset)
{
  const char *aliases;

  if (codeset == NULL)

    codeset = "";


  for (aliases = _g_locale_get_charset_aliases ();
       *aliases != '\0';
       aliases += strlen (aliases) + 1, aliases += strlen (aliases) + 1)
    if (strcmp (codeset, aliases) == 0
	|| (aliases[0] == '*' && aliases[1] == '\0'))
      {
	codeset = aliases + strlen (aliases) + 1;
	break;
      }


  if (codeset[0] == '\0')
    codeset = "ASCII";

  return codeset;
}
