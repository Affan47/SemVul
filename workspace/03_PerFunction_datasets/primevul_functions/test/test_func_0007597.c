static void strcpy_url(char *output, const char *url, bool relative)
{

  bool left = TRUE;
  const unsigned char *iptr;
  char *optr = output;
  const unsigned char *host_sep = (const unsigned char *) url;

  if(!relative)
    host_sep = (const unsigned char *) find_host_sep(url);

  for(iptr = (unsigned char *)url;
      *iptr;
      iptr++) {

    if(iptr < host_sep) {
      *optr++ = *iptr;
      continue;
    }

    if(*iptr == ' ') {
      if(left) {
        *optr++='%';
        *optr++='2';
        *optr++='0';
      }
      else
        *optr++='+';
      continue;
    }

    if(*iptr == '?')
      left = FALSE;

    if(urlchar_needs_escaping(*iptr)) {
      msnprintf(optr, 4, "%%%02x", *iptr);
      optr += 3;
    }
    else
      *optr++ = *iptr;
  }
  *optr = 0;

}
