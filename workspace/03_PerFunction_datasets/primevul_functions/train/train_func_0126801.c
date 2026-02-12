static CURLcode resolve_server(struct SessionHandle *data,
                               struct connectdata *conn,
                               bool *async)
{
  CURLcode result=CURLE_OK;
  long timeout_ms = Curl_timeleft(data, NULL, TRUE);


  if(conn->bits.reuse)


    *async = FALSE;

  else {

    int rc;
    struct Curl_dns_entry *hostaddr;

#ifdef USE_UNIX_SOCKETS
    if(data->set.str[STRING_UNIX_SOCKET_PATH]) {


      const char *path = data->set.str[STRING_UNIX_SOCKET_PATH];

      hostaddr = calloc(1, sizeof(struct Curl_dns_entry));
      if(!hostaddr)
        result = CURLE_OUT_OF_MEMORY;
      else if((hostaddr->addr = Curl_unix2addr(path)) != NULL)
        hostaddr->inuse++;
      else {

        if(strlen(path) >= sizeof(((struct sockaddr_un *)0)->sun_path)) {
          failf(data, "Unix socket path too long: '%s'", path);
          result = CURLE_COULDNT_RESOLVE_HOST;
        }
        else
          result = CURLE_OUT_OF_MEMORY;
        free(hostaddr);
        hostaddr = NULL;
      }
    }
    else
#endif
    if(!conn->proxy.name || !*conn->proxy.name) {


      conn->port =  conn->remote_port;


      rc = Curl_resolv_timeout(conn, conn->host.name, (int)conn->port,
                               &hostaddr, timeout_ms);
      if(rc == CURLRESOLV_PENDING)
        *async = TRUE;

      else if(rc == CURLRESOLV_TIMEDOUT)
        result = CURLE_OPERATION_TIMEDOUT;

      else if(!hostaddr) {
        failf(data, "Couldn't resolve host '%s'", conn->host.dispname);
        result =  CURLE_COULDNT_RESOLVE_HOST;

      }
    }
    else {


      rc = Curl_resolv_timeout(conn, conn->proxy.name, (int)conn->port,
                               &hostaddr, timeout_ms);

      if(rc == CURLRESOLV_PENDING)
        *async = TRUE;

      else if(rc == CURLRESOLV_TIMEDOUT)
        result = CURLE_OPERATION_TIMEDOUT;

      else if(!hostaddr) {
        failf(data, "Couldn't resolve proxy '%s'", conn->proxy.dispname);
        result = CURLE_COULDNT_RESOLVE_PROXY;

      }
    }
    DEBUGASSERT(conn->dns_entry == NULL);
    conn->dns_entry = hostaddr;
  }

  return result;
}
