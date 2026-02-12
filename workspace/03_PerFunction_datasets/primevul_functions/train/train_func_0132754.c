_g_locale_charset_raw (void)
{
  const char *codeset;

#if !(defined WIN32_NATIVE || defined OS2)

# if HAVE_LANGINFO_CODESET


  codeset = nl_langinfo (CODESET);

#  ifdef __CYGWIN__


  if (codeset != NULL && strcmp (codeset, "US-ASCII") == 0)
    {
      const char *locale;
      static char buf[2 + 10 + 1];

      locale = getenv ("LC_ALL");
      if (locale == NULL || locale[0] == '\0')
	{
	  locale = getenv ("LC_CTYPE");
	  if (locale == NULL || locale[0] == '\0')
	    locale = getenv ("LANG");
	}
      if (locale != NULL && locale[0] != '\0')
	{


	  const char *dot = strchr (locale, '.');

	  if (dot != NULL)
	    {
	      const char *modifier;

	      dot++;

	      modifier = strchr (dot, '@');
	      if (modifier == NULL)
		return dot;
	      if (modifier - dot < sizeof (buf))
		{
		  memcpy (buf, dot, modifier - dot);
		  buf [modifier - dot] = '\0';
		  return buf;
		}
	    }
	}


      sprintf (buf, "CP%u", GetACP ());
      codeset = buf;
    }
#  endif

# else


  const char *locale = NULL;


#  if 0
  locale = setlocale (LC_CTYPE, NULL);
#  endif
  if (locale == NULL || locale[0] == '\0')
    {
      locale = getenv ("LC_ALL");
      if (locale == NULL || locale[0] == '\0')
	{
	  locale = getenv ("LC_CTYPE");
	  if (locale == NULL || locale[0] == '\0')
	    locale = getenv ("LANG");
	}
    }


  codeset = locale;

# endif

#elif defined WIN32_NATIVE

  static char buf[2 + 10 + 1];


  sprintf (buf, "CP%u", GetACP ());
  codeset = buf;

#elif defined OS2

  const char *locale;
  static char buf[2 + 10 + 1];
  ULONG cp[3];
  ULONG cplen;


  locale = getenv ("LC_ALL");
  if (locale == NULL || locale[0] == '\0')
    {
      locale = getenv ("LC_CTYPE");
      if (locale == NULL || locale[0] == '\0')
	locale = getenv ("LANG");
    }
  if (locale != NULL && locale[0] != '\0')
    {

      const char *dot = strchr (locale, '.');

      if (dot != NULL)
	{
	  const char *modifier;

	  dot++;

	  modifier = strchr (dot, '@');
	  if (modifier == NULL)
	    return dot;
	  if (modifier - dot < sizeof (buf))
	    {
	      memcpy (buf, dot, modifier - dot);
	      buf [modifier - dot] = '\0';
	      return buf;
	    }
	}


      codeset = locale;
    }
  else
    {

      if (DosQueryCp (sizeof (cp), cp, &cplen))
	codeset = "";
      else
	{
	  sprintf (buf, "CP%u", cp[0]);
	  codeset = buf;
	}
    }

#endif

  return codeset;
}
