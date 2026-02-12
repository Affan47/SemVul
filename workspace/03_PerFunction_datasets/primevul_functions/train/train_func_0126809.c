static CURLcode parseurlandfillconn(struct SessionHandle *data,
                                    struct connectdata *conn,
                                    bool *prot_missing,
                                    char **userp, char **passwdp,
                                    char **optionsp)
{
  char *at;
  char *fragment;
  char *path = data->state.path;
  char *query;
  int rc;
  char protobuf[16] = "";
  const char *protop = "";
  CURLcode result;
  bool rebuild_url = FALSE;

  *prot_missing = FALSE;


  if(strpbrk(data->change.url, "\r\n")) {
    failf(data, "Illegal characters found in URL");
    return CURLE_URL_MALFORMAT;
  }


  if((2 == sscanf(data->change.url, "%15[^:]:%[^\n]",
                  protobuf, path)) &&
     Curl_raw_equal(protobuf, "file")) {
    if(path[0] == '/' && path[1] == '/') {


      memmove(path, path + 2, strlen(path + 2)+1);
    }


    if(path[0] != '/') {


      char *ptr=strchr(path, '/');
      if(ptr) {


        if(ptr[1] && ('/' == ptr[1]))


          ptr++;


        memmove(path, ptr, strlen(ptr)+1);
      }
    }

    protop = "file";
  }
  else {

    path[0]=0;

    if(2 > sscanf(data->change.url,
                   "%15[^\n:]://%[^\n/?]%[^\n]",
                   protobuf,
                   conn->host.name, path)) {


      rc = sscanf(data->change.url, "%[^\n/?]%[^\n]", conn->host.name, path);
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
    else
      protop = protobuf;
  }


  at = strchr(conn->host.name, '@');
  if(at)
    query = strchr(at+1, '?');
  else
    query = strchr(conn->host.name, '?');

  if(query) {


    size_t hostlen = strlen(query);
    size_t pathlen = strlen(path);


    memmove(path+hostlen+1, path, pathlen+1);


    memcpy(path+1, query, hostlen);

    path[0]='/';
    rebuild_url = TRUE;

    *query=0;
  }
  else if(!path[0]) {

    strcpy(path, "/");
    rebuild_url = TRUE;
  }


  if(path[0] == '?') {


    memmove(&path[1], path, strlen(path)+1);
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

    size_t urllen = strlen(data->change.url);

    size_t prefixlen = strlen(conn->host.name);

    if(!*prot_missing)
      prefixlen += strlen(protop) + strlen("://");

    reurl = malloc(urllen + 2);
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


        memmove(percent, endp, strlen(endp)+1);
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


  return findprotocol(data, conn, protop);
}
