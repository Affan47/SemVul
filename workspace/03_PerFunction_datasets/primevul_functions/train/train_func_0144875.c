cgiInitialize(void)
{
  const char	*method,
		*content_type,
		*cups_sid_cookie,
		*cups_sid_form;


  cupsSetPasswordCB(cgi_passwd);


  setlocale(LC_ALL, "");

#ifdef DEBUG


  setbuf(stdout, NULL);
#endif


  cgi_initialize_cookies();

  if ((cups_sid_cookie = cgiGetCookie(CUPS_SID)) == NULL)
  {
    fputs("DEBUG: " CUPS_SID " cookie not found, initializing!\n", stderr);
    cups_sid_cookie = cgi_set_sid();
  }

  fprintf(stderr, "DEBUG: " CUPS_SID " cookie is \"%s\"\n", cups_sid_cookie);


  method       = getenv("REQUEST_METHOD");
  content_type = getenv("CONTENT_TYPE");
  if (!method)
    return (0);


  if (!_cups_strcasecmp(method, "GET"))
    return (cgi_initialize_get());
  else if (!_cups_strcasecmp(method, "POST") && content_type)
  {
    const char *boundary = strstr(content_type, "boundary=");

    if (boundary)
      boundary += 9;

    if (content_type && !strncmp(content_type, "multipart/form-data; ", 21))
    {
      if (!cgi_initialize_multipart(boundary))
        return (0);
    }
    else if (!cgi_initialize_post())
      return (0);

    if ((cups_sid_form = cgiGetVariable(CUPS_SID)) == NULL ||
	strcmp(cups_sid_cookie, cups_sid_form))
    {
      if (cups_sid_form)
	fprintf(stderr, "DEBUG: " CUPS_SID " form variable is \"%s\"\n",
	        cups_sid_form);
      else
	fputs("DEBUG: " CUPS_SID " form variable is not present.\n", stderr);

      cgiClearVariables();
      return (0);
    }
    else
      return (1);
  }
  else
    return (0);
}
