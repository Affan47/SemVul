static struct connectdata *allocate_conn(struct Curl_easy *data)
{
  struct connectdata *conn;
  size_t connsize = sizeof(struct connectdata);

#ifdef USE_SSL

#define SSLBK_MAX_ALIGN 32


  size_t paddingsize = sizeof(struct connectdata) % SSLBK_MAX_ALIGN;
  size_t alignsize = paddingsize ? (SSLBK_MAX_ALIGN - paddingsize) : 0;
  size_t sslbksize = Curl_ssl->sizeof_ssl_backend_data;
  connsize += alignsize + (4 * sslbksize);
#endif

  conn = calloc(1, connsize);
  if(!conn)
    return NULL;

#ifdef USE_SSL


  {
    char *end = (char *)conn + connsize;
    conn->ssl[0].backend = ((void *)(end - (4 * sslbksize)));
    conn->ssl[1].backend = ((void *)(end - (3 * sslbksize)));
    conn->proxy_ssl[0].backend = ((void *)(end - (2 * sslbksize)));
    conn->proxy_ssl[1].backend = ((void *)(end - (1 * sslbksize)));
  }
#endif

  conn->handler = &Curl_handler_dummy;


  conn->sock[FIRSTSOCKET] = CURL_SOCKET_BAD;
  conn->sock[SECONDARYSOCKET] = CURL_SOCKET_BAD;
  conn->tempsock[0] = CURL_SOCKET_BAD;
  conn->tempsock[1] = CURL_SOCKET_BAD;
  conn->connection_id = -1;
  conn->port = -1;
  conn->remote_port = -1;
#if defined(USE_RECV_BEFORE_SEND_WORKAROUND) && defined(DEBUGBUILD)
  conn->postponed[0].bindsock = CURL_SOCKET_BAD;
  conn->postponed[1].bindsock = CURL_SOCKET_BAD;
#endif


  connclose(conn, "Default to force-close");


  conn->created = Curl_now();

  conn->data = data;


  conn->http_proxy.proxytype = data->set.proxytype;
  conn->socks_proxy.proxytype = CURLPROXY_SOCKS4;

#ifdef CURL_DISABLE_PROXY

  conn->bits.proxy = FALSE;
  conn->bits.httpproxy = FALSE;
  conn->bits.socksproxy = FALSE;
  conn->bits.proxy_user_passwd = FALSE;
  conn->bits.tunnel_proxy = FALSE;

#else


  conn->bits.proxy = (data->set.str[STRING_PROXY] &&
                      *data->set.str[STRING_PROXY]) ? TRUE : FALSE;
  conn->bits.httpproxy = (conn->bits.proxy &&
                          (conn->http_proxy.proxytype == CURLPROXY_HTTP ||
                           conn->http_proxy.proxytype == CURLPROXY_HTTP_1_0 ||
                           conn->http_proxy.proxytype == CURLPROXY_HTTPS)) ?
                           TRUE : FALSE;
  conn->bits.socksproxy = (conn->bits.proxy &&
                           !conn->bits.httpproxy) ? TRUE : FALSE;

  if(data->set.str[STRING_PRE_PROXY] && *data->set.str[STRING_PRE_PROXY]) {
    conn->bits.proxy = TRUE;
    conn->bits.socksproxy = TRUE;
  }

  conn->bits.proxy_user_passwd =
    (data->set.str[STRING_PROXYUSERNAME]) ? TRUE : FALSE;
  conn->bits.tunnel_proxy = data->set.tunnel_thru_httpproxy;

#endif

  conn->bits.user_passwd = (data->set.str[STRING_USERNAME]) ? TRUE : FALSE;
  conn->bits.ftp_use_epsv = data->set.ftp_use_epsv;
  conn->bits.ftp_use_eprt = data->set.ftp_use_eprt;

  conn->ssl_config.verifystatus = data->set.ssl.primary.verifystatus;
  conn->ssl_config.verifypeer = data->set.ssl.primary.verifypeer;
  conn->ssl_config.verifyhost = data->set.ssl.primary.verifyhost;
  conn->proxy_ssl_config.verifystatus =
    data->set.proxy_ssl.primary.verifystatus;
  conn->proxy_ssl_config.verifypeer = data->set.proxy_ssl.primary.verifypeer;
  conn->proxy_ssl_config.verifyhost = data->set.proxy_ssl.primary.verifyhost;

  conn->ip_version = data->set.ipver;

#if !defined(CURL_DISABLE_HTTP) && defined(USE_NTLM) && \
    defined(NTLM_WB_ENABLED)
  conn->ntlm_auth_hlpr_socket = CURL_SOCKET_BAD;
  conn->ntlm_auth_hlpr_pid = 0;
  conn->challenge_header = NULL;
  conn->response_header = NULL;
#endif

  if(Curl_pipeline_wanted(data->multi, CURLPIPE_HTTP1) &&
     !conn->master_buffer) {

    conn->master_buffer = calloc(MASTERBUF_SIZE, sizeof(char));
    if(!conn->master_buffer)
      goto error;
  }


  Curl_llist_init(&conn->send_pipe, (curl_llist_dtor) llist_dtor);
  Curl_llist_init(&conn->recv_pipe, (curl_llist_dtor) llist_dtor);

#ifdef HAVE_GSSAPI
  conn->data_prot = PROT_CLEAR;
#endif


  if(data->set.str[STRING_DEVICE]) {
    conn->localdev = strdup(data->set.str[STRING_DEVICE]);
    if(!conn->localdev)
      goto error;
  }
  conn->localportrange = data->set.localportrange;
  conn->localport = data->set.localport;


  conn->fclosesocket = data->set.fclosesocket;
  conn->closesocket_client = data->set.closesocket_client;

  return conn;
  error:

  Curl_llist_destroy(&conn->send_pipe, NULL);
  Curl_llist_destroy(&conn->recv_pipe, NULL);

  free(conn->master_buffer);
  free(conn->localdev);
  free(conn);
  return NULL;
}
