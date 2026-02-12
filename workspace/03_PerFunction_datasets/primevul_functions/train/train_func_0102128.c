static CURLcode parse_proxy(struct SessionHandle *data,
                            struct connectdata *conn, char *proxy)
{
  char *prox_portno;
  char *endofprot;


  char *proxyptr;
  char *portptr;
  char *atsign;


  endofprot = strstr(proxy, "://");
  if(endofprot) {
    proxyptr = endofprot+3;
    if(checkprefix("socks5h", proxy))
      conn->proxytype = CURLPROXY_SOCKS5_HOSTNAME;
    else if(checkprefix("socks5", proxy))
      conn->proxytype = CURLPROXY_SOCKS5;
    else if(checkprefix("socks4a", proxy))
      conn->proxytype = CURLPROXY_SOCKS4A;
    else if(checkprefix("socks4", proxy) || checkprefix("socks", proxy))
      conn->proxytype = CURLPROXY_SOCKS4;

  }
  else
    proxyptr = proxy;


  atsign = strchr(proxyptr, '@');
  if(atsign) {
    char *proxyuser = NULL;
    char *proxypasswd = NULL;
    CURLcode result =
      parse_login_details(proxyptr, atsign - proxyptr,
                          &proxyuser, &proxypasswd, NULL);
    if(!result) {


      Curl_safefree(conn->proxyuser);
      if(proxyuser && strlen(proxyuser) < MAX_CURL_USER_LENGTH)
        conn->proxyuser = curl_easy_unescape(data, proxyuser, 0, NULL);
      else
        conn->proxyuser = strdup("");

      if(!conn->proxyuser)
        result = CURLE_OUT_OF_MEMORY;
      else {
        Curl_safefree(conn->proxypasswd);
        if(proxypasswd && strlen(proxypasswd) < MAX_CURL_PASSWORD_LENGTH)
          conn->proxypasswd = curl_easy_unescape(data, proxypasswd, 0, NULL);
        else
          conn->proxypasswd = strdup("");

        if(!conn->proxypasswd)
          result = CURLE_OUT_OF_MEMORY;
      }

      if(!result) {
        conn->bits.proxy_user_passwd = TRUE;
        atsign++;

        proxyptr = atsign;
      }
    }

    free(proxyuser);
    free(proxypasswd);

    if(result)
      return result;
  }


  portptr = proxyptr;


  if(*proxyptr == '[') {
    char *ptr = ++proxyptr;
    while(*ptr && (ISXDIGIT(*ptr) || (*ptr == ':') || (*ptr == '.')))
      ptr++;
    if(*ptr == '%') {

      if(strncmp("%25", ptr, 3))
        infof(data, "Please URL encode %% as %%25, see RFC 6874.\n");
      ptr++;

      while(*ptr && (ISALPHA(*ptr) || ISXDIGIT(*ptr) || (*ptr == '-') ||
                     (*ptr == '.') || (*ptr == '_') || (*ptr == '~')))
        ptr++;
    }
    if(*ptr == ']')

      *ptr++ = 0;
    else
      infof(data, "Invalid IPv6 address format\n");
    portptr = ptr;


  }


  prox_portno = strchr(portptr, ':');
  if(prox_portno) {
    *prox_portno = 0x0;
    prox_portno ++;

    conn->port = strtol(prox_portno, NULL, 10);
  }
  else {
    if(proxyptr[0]=='/')


      return CURLE_COULDNT_RESOLVE_PROXY;


    atsign = strchr(proxyptr, '/');
    if(atsign)
      *atsign = 0x0;

    if(data->set.proxyport)


      conn->port = data->set.proxyport;
  }


  conn->proxy.rawalloc = strdup(proxyptr);
  conn->proxy.name = conn->proxy.rawalloc;

  if(!conn->proxy.rawalloc)
    return CURLE_OUT_OF_MEMORY;

  return CURLE_OK;
}
