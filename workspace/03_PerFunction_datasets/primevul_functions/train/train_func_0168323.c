parse_charset (const char *str)
{
  const char *end;
  char *charset;

  if (!str || !*str)
    return NULL;

  str = c_strcasestr (str, "charset=");
  if (!str)
    return NULL;

  str += 8;
  end = str;


  while (*end && !c_isspace (*end))
    end++;


  charset = strdupdelim (str, end);


  if (!check_encoding_name (charset))
    {
      xfree (charset);
      return NULL;
    }


  return charset;
}
