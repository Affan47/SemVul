cp_keyword(const String &str, String *result, String *rest)
{
  const char *s = str.data();
  const char *end = str.end();


  for (; s < end; s++)
    switch (*s) {

     case ' ':
     case '\f':
     case '\n':
     case '\r':
     case '\t':
     case '\v':
      goto done;


     case '_':
     case '.':
     case ':':
     case '?':
     case '!':
      break;

     default:
      if (!isalnum((unsigned char) *s))
	return false;
      break;

    }

 done:
  if (s == str.begin() || (!rest && s < end))
    return false;
  else {
    *result = str.substring(str.begin(), s);
    if (rest) {
      for (; s < end; s++)
	if (!isspace((unsigned char) *s))
	  break;
      *rest = str.substring(s, end);
    }
    return true;
  }
}
