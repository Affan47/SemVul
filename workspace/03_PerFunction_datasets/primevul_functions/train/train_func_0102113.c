static struct connectdata *allocate_conn(struct SessionHandle *data)
{
  struct connectdata *conn = calloc(1, sizeof(struct connectdata));
  if(!conn)
    return NULL;

  conn->handler = &Curl_handler_dummy;


  conn->sock[FIRSTSOCKET] = CURL_SOCKET_BAD;
  conn->sock[SECONDARYSOCKET] = CURL_SOCKET_BAD;
  conn->tempsock[0] = CURL_SOCKET_BAD;
  conn->tempsock[1] = CURL_SOCKET_BAD;
  conn->connection_id = -1;
  conn->port = -1;
  conn->remote_port = -1;


  connclose(conn, "Default to force-close");


  conn->created = Curl_tvnow();

  conn->data = data;


  conn->proxytype = data->set.proxytype;

#ifdef CURL_DISABLE_PROXY

  conn->bits.proxy = FALSE;
  conn->bits.httpproxy = FALSE;
  conn->bits.proxy_user_passwd = FALSE;
  conn->bits.tunnel_proxy = FALSE;

#else


  conn->bits.proxy = (data->set.str[STRING_PROXY] &&
                      *data->set.str[STRING_PROXY])?TRUE:FALSE;
  conn->bits.httpproxy = (conn->bits.proxy &&
                          (conn->proxytype == CURLPROXY_HTTP ||
                           conn->proxytype == CURLPROXY_HTTP_1_0))?TRUE:FALSE;
  conn->bits.proxy_user_passwd =
    (NULL != data->set.str[STRING_PROXYUSERNAME])?TRUE:FALSE;
  conn->bits.tunnel_proxy = data->set.tunnel_thru_httpproxy;

#endif

  conn->bits.user_passwd = (NULL != data->set.str[STRING_USERNAME])?TRUE:FALSE;
  conn->bits.ftp_use_epsv = data->set.ftp_use_epsv;
  conn->bits.ftp_use_eprt = data->set.ftp_use_eprt;

  conn->verifypeer = data->set.ssl.verifypeer;
  conn->verifyhost = data->set.ssl.verifyhost;

  conn->ip_version = data->set.ipver;

#if !defined(CURL_DISABLE_HTTP) && defined(USE_NTLM) && \
    defined(NTLM_WB_ENABLED)
  conn->ntlm_auth_hlpr_socket = CURL_SOCKET_BAD;
  conn->ntlm_auth_hlpr_pid = 0;
  conn->challenge_header = NULL;
  conn->response_header = NULL;
#endif

  if(Curl_multi_pipeline_enabled(data->multi) &&
      !conn->master_buffer) {

    conn->master_buffer = calloc(BUFSIZE, sizeof (char));
    if(!conn->master_buffer)
      goto error;
  }


  conn->send_pipe = Curl_llist_alloc((curl_llist_dtor) llist_dtor);
  conn->recv_pipe = Curl_llist_alloc((curl_llist_dtor) llist_dtor);
  if(!conn->send_pipe || !conn->recv_pipe)
    goto error;

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

  Curl_llist_destroy(conn->send_pipe, NULL);
  Curl_llist_destroy(conn->recv_pipe, NULL);

  conn->send_pipe = NULL;
  conn->recv_pipe = NULL;

  free(conn->master_buffer);
  free(conn->localdev);
  free(conn);
  return NULL;
}
