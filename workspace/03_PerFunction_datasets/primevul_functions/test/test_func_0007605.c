static CURLUcode seturl(const char *url, CURLU *u, unsigned int flags)
{
  char *path;
  bool path_alloced = FALSE;
  bool uncpath = FALSE;
  char *hostname;
  char *query = NULL;
  char *fragment = NULL;
  CURLUcode result;
  bool url_has_scheme = FALSE;
  char schemebuf[MAX_SCHEME_LEN + 1];
  const char *schemep = NULL;
  size_t schemelen = 0;
  size_t urllen;

  DEBUGASSERT(url);


  urllen = strlen(url);
  if(urllen > CURL_MAX_INPUT_LENGTH)

    return CURLUE_MALFORMED_INPUT;

  path = u->scratch = malloc(urllen * 2 + 2);
  if(!path)
    return CURLUE_OUT_OF_MEMORY;

  hostname = &path[urllen + 1];
  hostname[0] = 0;

  if(Curl_is_absolute_url(url, schemebuf, sizeof(schemebuf))) {
    url_has_scheme = TRUE;
    schemelen = strlen(schemebuf);
  }


  if(url_has_scheme && !strcmp(schemebuf, "file")) {
    if(urllen <= 6)

      return CURLUE_BAD_FILE_URL;


    strcpy(path, &url[5]);

    u->scheme = strdup("file");
    if(!u->scheme)
      return CURLUE_OUT_OF_MEMORY;


    if(path[0] == '/' && path[1] == '/') {

      char *ptr = &path[2];


      if(ptr[0] != '/' && !STARTS_WITH_URL_DRIVE_PREFIX(ptr)) {


        if(checkprefix("localhost/", ptr) ||
           checkprefix("127.0.0.1/", ptr)) {
          ptr += 9;
        }
        else {
#if defined(WIN32)
          size_t len;


          path = strpbrk(ptr, "/\\:*?\"<>|");
          if(!path || *path != '/')
            return CURLUE_BAD_FILE_URL;

          len = path - ptr;
          if(len) {
            memcpy(hostname, ptr, len);
            hostname[len] = 0;
            uncpath = TRUE;
          }

          ptr -= 2;
#else


          return CURLUE_BAD_FILE_URL;
#endif
        }
      }

      path = ptr;
    }

    if(!uncpath)
        hostname = NULL;

#if !defined(MSDOS) && !defined(WIN32) && !defined(__CYGWIN__)


    if(('/' == path[0] && STARTS_WITH_URL_DRIVE_PREFIX(&path[1])) ||
       STARTS_WITH_URL_DRIVE_PREFIX(path)) {

      return CURLUE_BAD_FILE_URL;
    }
#else

    if('/' == path[0] && STARTS_WITH_URL_DRIVE_PREFIX(&path[1])) {

      memmove(path, &path[1], strlen(&path[1]) + 1);
    }
#endif

  }
  else {

    const char *p;
    const char *hostp;
    size_t len;
    path[0] = 0;

    if(url_has_scheme) {
      int i = 0;
      p = &url[schemelen + 1];
      while(p && (*p == '/') && (i < 4)) {
        p++;
        i++;
      }
      if((i < 1) || (i>3))

        return CURLUE_BAD_SLASHES;

      schemep = schemebuf;
      if(!Curl_builtin_scheme(schemep) &&
         !(flags & CURLU_NON_SUPPORT_SCHEME))
        return CURLUE_UNSUPPORTED_SCHEME;

      if(junkscan(schemep, flags))
        return CURLUE_BAD_SCHEME;
    }
    else {


      if(!(flags & (CURLU_DEFAULT_SCHEME|CURLU_GUESS_SCHEME)))
        return CURLUE_BAD_SCHEME;
      if(flags & CURLU_DEFAULT_SCHEME)
        schemep = DEFAULT_SCHEME;


      p = url;
    }
    hostp = p;


    while(*p && !HOSTNAME_END(*p))
      p++;

    len = p - hostp;
    if(len) {
      memcpy(hostname, hostp, len);
      hostname[len] = 0;
    }
    else {
      if(!(flags & CURLU_NO_AUTHORITY))
        return CURLUE_NO_HOST;
    }

    strcpy(path, p);

    if(schemep) {
      u->scheme = strdup(schemep);
      if(!u->scheme)
        return CURLUE_OUT_OF_MEMORY;
    }
  }

  if((flags & CURLU_URLENCODE) && path[0]) {

    char *newp = malloc(strlen(path) * 3);
    if(!newp)
      return CURLUE_OUT_OF_MEMORY;
    path_alloced = TRUE;
    strcpy_url(newp, path, TRUE);
    u->temppath = path = newp;
  }

  fragment = strchr(path, '#');
  if(fragment) {
    *fragment++ = 0;
    if(junkscan(fragment, flags))
      return CURLUE_BAD_FRAGMENT;
    if(fragment[0]) {
      u->fragment = strdup(fragment);
      if(!u->fragment)
        return CURLUE_OUT_OF_MEMORY;
    }
  }

  query = strchr(path, '?');
  if(query) {
    *query++ = 0;
    if(junkscan(query, flags))
      return CURLUE_BAD_QUERY;

    u->query = strdup(query);
    if(!u->query)
      return CURLUE_OUT_OF_MEMORY;
  }

  if(junkscan(path, flags))
    return CURLUE_BAD_PATH;

  if(!path[0])

    path = NULL;
  else {
    if(!(flags & CURLU_PATH_AS_IS)) {

      char *newp = Curl_dedotdotify(path);
      if(!newp)
        return CURLUE_OUT_OF_MEMORY;

      if(strcmp(newp, path)) {

        if(path_alloced)
          Curl_safefree(u->temppath);
        u->temppath = path = newp;
        path_alloced = TRUE;
      }
      else
        free(newp);
    }

    u->path = path_alloced?path:strdup(path);
    if(!u->path)
      return CURLUE_OUT_OF_MEMORY;
    u->temppath = NULL;
  }

  if(hostname) {
    char normalized_ipv4[sizeof("255.255.255.255") + 1];


    result = parse_hostname_login(u, &hostname, flags);
    if(result)
      return result;

    result = Curl_parse_port(u, hostname, url_has_scheme);
    if(result)
      return result;

    if(junkscan(hostname, flags))
      return CURLUE_BAD_HOSTNAME;

    if(0 == strlen(hostname) && (flags & CURLU_NO_AUTHORITY)) {

      u->host = strdup("");
    }
    else {
      if(ipv4_normalize(hostname, normalized_ipv4, sizeof(normalized_ipv4)))
        u->host = strdup(normalized_ipv4);
      else {
        result = decode_host(hostname, &u->host);
        if(result)
          return result;
        result = hostname_check(u, u->host);
        if(result)
          return result;
      }
    }
    if(!u->host)
      return CURLUE_OUT_OF_MEMORY;
    if((flags & CURLU_GUESS_SCHEME) && !schemep) {

      if(checkprefix("ftp.", hostname))
        schemep = "ftp";
      else if(checkprefix("dict.", hostname))
        schemep = "dict";
      else if(checkprefix("ldap.", hostname))
        schemep = "ldap";
      else if(checkprefix("imap.", hostname))
        schemep = "imap";
      else if(checkprefix("smtp.", hostname))
        schemep = "smtp";
      else if(checkprefix("pop3.", hostname))
        schemep = "pop3";
      else
        schemep = "http";

      u->scheme = strdup(schemep);
      if(!u->scheme)
        return CURLUE_OUT_OF_MEMORY;
    }
  }

  Curl_safefree(u->scratch);
  Curl_safefree(u->temppath);

  return CURLUE_OK;
}
