static CURLcode parse_remote_port(struct Curl_easy *data,
                                  struct connectdata *conn)
{
  char *portptr;
  char endbracket;


  if((1 == sscanf(conn->host.name, "[%*45[0123456789abcdefABCDEF:.]%c",
                  &endbracket)) &&
     (']' == endbracket)) {

    conn->bits.ipv6_ip = TRUE;

    conn->host.name++;
    portptr = strchr(conn->host.name, ']');
    if(portptr) {
      *portptr++ = '\0';
      if(*portptr) {
        if (*portptr != ':') {
          failf(data, "IPv6 closing bracket followed by '%c'", *portptr);
          return CURLE_URL_MALFORMAT;
        }
      }
      else
        portptr = NULL;
    }
  }
  else {
#ifdef ENABLE_IPV6
    struct in6_addr in6;
    if(Curl_inet_pton(AF_INET6, conn->host.name, &in6) > 0) {


      failf(data, "IPv6 numerical address used in URL without brackets");
      return CURLE_URL_MALFORMAT;
    }
#endif

    portptr = strchr(conn->host.name, ':');
  }

  if(data->set.use_port && data->state.allow_port) {

    conn->remote_port = (unsigned short)data->set.use_port;
    if(portptr)
      *portptr = '\0';

    if(conn->bits.httpproxy) {

      char *url;
      char type[12]="";

      if(conn->bits.type_set)
        snprintf(type, sizeof(type), ";type=%c",
                 data->set.prefer_ascii?'A':
                 (data->set.ftp_list_only?'D':'I'));


      url = aprintf("%s://%s%s%s:%hu%s%s%s", conn->given->scheme,
                    conn->bits.ipv6_ip?"[":"", conn->host.name,
                    conn->bits.ipv6_ip?"]":"", conn->remote_port,
                    data->state.slash_removed?"/":"", data->state.path,
                    type);
      if(!url)
        return CURLE_OUT_OF_MEMORY;

      if(data->change.url_alloc) {
        Curl_safefree(data->change.url);
        data->change.url_alloc = FALSE;
      }

      data->change.url = url;
      data->change.url_alloc = TRUE;
    }
  }
  else if(portptr) {


    char *rest;
    long port;

    port = strtol(portptr + 1, &rest, 10);

    if((port < 0) || (port > 0xffff)) {

      failf(data, "Port number out of range");
      return CURLE_URL_MALFORMAT;
    }

    if(rest[0]) {
      failf(data, "Port number ended with '%c'", rest[0]);
      return CURLE_URL_MALFORMAT;
    }

    if(rest != &portptr[1]) {
      *portptr = '\0';
      conn->remote_port = curlx_ultous(port);
    }
    else {


      *portptr = '\0';
    }
  }


  if(conn->remote_port < 0)
    conn->remote_port = (unsigned short)conn->given->defport;

  return CURLE_OK;
}
