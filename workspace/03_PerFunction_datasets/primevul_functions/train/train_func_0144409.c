static CURLcode parseurlandfillconn(struct Curl_easy *data,
                                    struct connectdata *conn,
                                    bool *prot_missing,
                                    char **userp, char **passwdp,
                                    char **optionsp)
{
  char *at;
  char *fragment;
  char *path = data->state.path;
  char *query;
  int i;
  int rc;
  const char *protop = "";
  CURLcode result;
  bool rebuild_url = FALSE;
  bool url_has_scheme = FALSE;
  char protobuf[16];

  *prot_missing = FALSE;


  if(strpbrk(data->change.url, "\r\n")) {
    failf(data, "Illegal characters found in URL");
    return CURLE_URL_MALFORMAT;
  }


  if(data->change.url[0] == ':') {
    failf(data, "Bad URL, colon is first character");
    return CURLE_URL_MALFORMAT;
  }


#define STARTS_WITH_DRIVE_PREFIX(str) \
  ((('a' <= str[0] && str[0] <= 'z') || \
    ('A' <= str[0] && str[0] <= 'Z')) && \
   (str[1] == ':'))


#define STARTS_WITH_URL_DRIVE_PREFIX(str) \
  ((('a' <= (str)[0] && (str)[0] <= 'z') || \
    ('A' <= (str)[0] && (str)[0] <= 'Z')) && \
   ((str)[1] == ':' || (str)[1] == '|') && \
   ((str)[2] == '/' || (str)[2] == 0))


  if(STARTS_WITH_DRIVE_PREFIX(data->change.url) &&
     data->set.str[STRING_DEFAULT_PROTOCOL] &&
     strcasecompare(data->set.str[STRING_DEFAULT_PROTOCOL], "file")) {
    ;
  }
  else {
    for(i = 0; i < 16 && data->change.url[i]; ++i) {
      if(data->change.url[i] == '/')
        break;
      if(data->change.url[i] == ':') {
        url_has_scheme = TRUE;
        break;
      }
    }
  }


  if((url_has_scheme && strncasecompare(data->change.url, "file:", 5)) ||
     (!url_has_scheme && data->set.str[STRING_DEFAULT_PROTOCOL] &&
      strcasecompare(data->set.str[STRING_DEFAULT_PROTOCOL], "file"))) {
    if(url_has_scheme)
      rc = sscanf(data->change.url, "%*15[^\n/:]:%[^\n]", path);
    else
      rc = sscanf(data->change.url, "%[^\n]", path);

    if(rc != 1) {
      failf(data, "Bad URL");
      return CURLE_URL_MALFORMAT;
    }

    if(url_has_scheme && path[0] == '/' && path[1] == '/' &&
       path[2] == '/' && path[3] == '/') {


      failf(data, "SMB shares are not supported in file: URLs.");
      return CURLE_URL_MALFORMAT;
    }


    if(url_has_scheme && path[0] == '/' && path[1] == '/') {

      char *ptr = &path[2];


      if(ptr[0] != '/' && !STARTS_WITH_URL_DRIVE_PREFIX(ptr)) {


        if(!checkprefix("localhost/", ptr) &&
           !checkprefix("127.0.0.1/", ptr)) {
          failf(data, "Invalid file://hostname/, "
                      "expected localhost or 127.0.0.1 or none");
          return CURLE_URL_MALFORMAT;
        }
        ptr += 9;
      }


      if('/' == ptr[1])
        ptr++;


      memmove(path, ptr, strlen(ptr) + 1);
    }

#if !defined(MSDOS) && !defined(WIN32) && !defined(__CYGWIN__)


    if(('/' == path[0] && STARTS_WITH_URL_DRIVE_PREFIX(&path[1])) ||
       STARTS_WITH_URL_DRIVE_PREFIX(path)) {
      failf(data, "File drive letters are only accepted in MSDOS/Windows.");
      return CURLE_URL_MALFORMAT;
    }
#else

    if('/' == path[0] && STARTS_WITH_URL_DRIVE_PREFIX(&path[1])) {

      memmove(path, &path[1], strlen(&path[1]) + 1);
    }
#endif

    protop = "file";
    *prot_missing = !url_has_scheme;
  }
  else {

    char slashbuf[4];
    path[0] = 0;

    rc = sscanf(data->change.url,
                "%15[^\n/:]:%3[/]%[^\n/?#]%[^\n]",
                protobuf, slashbuf, conn->host.name, path);
    if(2 == rc) {
      failf(data, "Bad URL");
      return CURLE_URL_MALFORMAT;
    }
    if(3 > rc) {


      rc = sscanf(data->change.url, "%[^\n/?#]%[^\n]", conn->host.name, path);
      if(1 > rc) {


#if defined(__DJGPP__) && (DJGPP_MINOR == 4)
        if(!(rc == -1 && *conn->host.name))
#endif
        {
          failf(data, "<url> malformed");
          return CURLE_URL_MALFORMAT;
        }
      }


      protop = data->set.str[STRING_DEFAULT_PROTOCOL];
      if(!protop) {


        if(checkprefix("FTP.", conn->host.name))
          protop = "ftp";
        else if(checkprefix("DICT.", conn->host.name))
          protop = "DICT";
        else if(checkprefix("LDAP.", conn->host.name))
          protop = "LDAP";
        else if(checkprefix("IMAP.", conn->host.name))
          protop = "IMAP";
        else if(checkprefix("SMTP.", conn->host.name))
          protop = "smtp";
        else if(checkprefix("POP3.", conn->host.name))
          protop = "pop3";
        else
          protop = "http";
      }

      *prot_missing = TRUE;
    }
    else {
      size_t s = strlen(slashbuf);
      protop = protobuf;
      if(s != 2) {
        infof(data, "Unwillingly accepted illegal URL using %d slash%s!\n",
              s, s>1?"es":"");

        if(data->change.url_alloc)
          free(data->change.url);

        data->change.url = aprintf("%s://%s%s",
                                   protobuf, conn->host.name, path);
        if(!data->change.url)
          return CURLE_OUT_OF_MEMORY;
        data->change.url_alloc = TRUE;
      }
    }
  }


  at = strchr(conn->host.name, '@');
  if(at)
    query = strchr(at + 1, '?');
  else
    query = strchr(conn->host.name, '?');

  if(query) {


    size_t hostlen = strlen(query);
    size_t pathlen = strlen(path);


    memmove(path + hostlen + 1, path, pathlen + 1);


    memcpy(path + 1, query, hostlen);

    path[0]='/';
    rebuild_url = TRUE;

    *query = 0;
  }
  else if(!path[0]) {

    strcpy(path, "/");
    rebuild_url = TRUE;
  }


  if(path[0] != '/') {


    memmove(&path[1], path, strlen(path) + 1);
    path[0] = '/';
    rebuild_url = TRUE;
  }
  else if(!data->set.path_as_is) {

    char *newp = Curl_dedotdotify(path);
    if(!newp)
      return CURLE_OUT_OF_MEMORY;

    if(strcmp(newp, path)) {
      rebuild_url = TRUE;
      free(data->state.pathbuffer);
      data->state.pathbuffer = newp;
      data->state.path = newp;
      path = newp;
    }
    else
      free(newp);
  }


  if(rebuild_url) {
    char *reurl;

    size_t plen = strlen(path);

    size_t prefixlen = strlen(conn->host.name);

    if(!*prot_missing) {
      size_t protolen = strlen(protop);

      if(curl_strnequal(protop, data->change.url, protolen))
        prefixlen += protolen;
      else {
        failf(data, "<url> malformed");
        return CURLE_URL_MALFORMAT;
      }

      if(curl_strnequal("://", &data->change.url[protolen], 3))
        prefixlen += 3;

      else if(curl_strnequal("file:", data->change.url, 5))
        prefixlen += 1 + (data->change.url[5] == '/');
      else {
        failf(data, "<url> malformed");
        return CURLE_URL_MALFORMAT;
      }
    }

    reurl = malloc(prefixlen + plen + 1);
    if(!reurl)
      return CURLE_OUT_OF_MEMORY;


    memcpy(reurl, data->change.url, prefixlen);


    memcpy(&reurl[prefixlen], path, plen + 1);


    if(data->change.url_alloc) {
      Curl_safefree(data->change.url);
      data->change.url_alloc = FALSE;
    }

    infof(data, "Rebuilt URL to: %s\n", reurl);

    data->change.url = reurl;
    data->change.url_alloc = TRUE;
  }

  result = findprotocol(data, conn, protop);
  if(result)
    return result;


  result = parse_url_login(data, conn, userp, passwdp, optionsp);
  if(result)
    return result;

  if(conn->host.name[0] == '[') {


    char *percent = strchr(conn->host.name, '%');
    if(percent) {
      unsigned int identifier_offset = 3;
      char *endp;
      unsigned long scope;
      if(strncmp("%25", percent, 3) != 0) {
        infof(data,
              "Please URL encode %% as %%25, see RFC 6874.\n");
        identifier_offset = 1;
      }
      scope = strtoul(percent + identifier_offset, &endp, 10);
      if(*endp == ']') {


        memmove(percent, endp, strlen(endp) + 1);
        conn->scope_id = (unsigned int)scope;
      }
      else {

#if defined(HAVE_NET_IF_H) && defined(IFNAMSIZ) && defined(HAVE_IF_NAMETOINDEX)
        char ifname[IFNAMSIZ + 2];
        char *square_bracket;
        unsigned int scopeidx = 0;
        strncpy(ifname, percent + identifier_offset, IFNAMSIZ + 2);

        ifname[IFNAMSIZ + 1] = '\0';
        square_bracket = strchr(ifname, ']');
        if(square_bracket) {

          *square_bracket = '\0';
          scopeidx = if_nametoindex(ifname);
          if(scopeidx == 0) {
            infof(data, "Invalid network interface: %s; %s\n", ifname,
                  strerror(errno));
          }
        }
        if(scopeidx > 0) {
          char *p = percent + identifier_offset + strlen(ifname);


          memmove(percent, p, strlen(p) + 1);
          conn->scope_id = scopeidx;
        }
        else
#endif
          infof(data, "Invalid IPv6 address format\n");
      }
    }
  }

  if(data->set.scope_id)

    conn->scope_id = data->set.scope_id;


  fragment = strchr(path, '#');
  if(fragment) {
    *fragment = 0;


    fragment = strchr(data->change.url, '#');
    if(fragment)
      *fragment = 0;
  }


  return CURLE_OK;
}
