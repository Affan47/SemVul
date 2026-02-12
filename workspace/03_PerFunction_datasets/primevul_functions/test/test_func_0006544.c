struct CookieInfo *Curl_cookie_init(struct Curl_easy *data,
                                    const char *file,
                                    struct CookieInfo *inc,
                                    bool newsession)
{
  struct CookieInfo *c;
  FILE *fp = NULL;
  bool fromfile = TRUE;
  char *line = NULL;

  if(!inc) {

    c = calloc(1, sizeof(struct CookieInfo));
    if(!c)
      return NULL;
    c->filename = strdup(file?file:"none");
    if(!c->filename)
      goto fail;


    c->next_expiration = CURL_OFF_T_MAX;
  }
  else {

    c = inc;
  }
  c->running = FALSE;

  if(file && !strcmp(file, "-")) {
    fp = stdin;
    fromfile = FALSE;
  }
  else if(!file || !*file) {

    fp = NULL;
  }
  else {
    fp = fopen(file, FOPEN_READTEXT);
    if(!fp)
      infof(data, "WARNING: failed to open cookie file \"%s\"", file);
  }

  c->newsession = newsession;

  if(fp) {
    char *lineptr;
    bool headerline;

    line = malloc(MAX_COOKIE_LINE);
    if(!line)
      goto fail;
    while(Curl_get_line(line, MAX_COOKIE_LINE, fp)) {
      if(checkprefix("Set-Cookie:", line)) {

        lineptr = &line[11];
        headerline = TRUE;
      }
      else {
        lineptr = line;
        headerline = FALSE;
      }
      while(*lineptr && ISBLANK(*lineptr))
        lineptr++;

      Curl_cookie_add(data, c, headerline, TRUE, lineptr, NULL, NULL, TRUE);
    }
    free(line);


    remove_expired(c);

    if(fromfile && fp)
      fclose(fp);
  }

  c->running = TRUE;
  if(data)
    data->state.cookie_engine = TRUE;

  return c;

fail:
  free(line);


  if(!inc)
    Curl_cookie_cleanup(c);
  if(fromfile && fp)
    fclose(fp);
  return NULL;
}
