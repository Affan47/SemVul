static CURLcode create_conn(struct SessionHandle *data,
                            struct connectdata **in_connect,
                            bool *async)
{
  CURLcode result = CURLE_OK;
  struct connectdata *conn;
  struct connectdata *conn_temp = NULL;
  size_t urllen;
  char *user = NULL;
  char *passwd = NULL;
  char *options = NULL;
  bool reuse;
  char *proxy = NULL;
  bool prot_missing = FALSE;
  bool no_connections_available = FALSE;
  bool force_reuse = FALSE;
  size_t max_host_connections = Curl_multi_max_host_connections(data->multi);
  size_t max_total_connections = Curl_multi_max_total_connections(data->multi);

  *async = FALSE;


  if(!data->change.url) {
    result = CURLE_URL_MALFORMAT;
    goto out;
  }


  conn = allocate_conn(data);

  if(!conn) {
    result = CURLE_OUT_OF_MEMORY;
    goto out;
  }


  *in_connect = conn;


#define LEAST_PATH_ALLOC 256
  urllen=strlen(data->change.url);
  if(urllen < LEAST_PATH_ALLOC)
    urllen=LEAST_PATH_ALLOC;


  Curl_safefree(data->state.pathbuffer);
  data->state.path = NULL;

  data->state.pathbuffer = malloc(urllen+2);
  if(NULL == data->state.pathbuffer) {
    result = CURLE_OUT_OF_MEMORY;
    goto out;
  }
  data->state.path = data->state.pathbuffer;

  conn->host.rawalloc = malloc(urllen+2);
  if(NULL == conn->host.rawalloc) {
    Curl_safefree(data->state.pathbuffer);
    data->state.path = NULL;
    result = CURLE_OUT_OF_MEMORY;
    goto out;
  }

  conn->host.name = conn->host.rawalloc;
  conn->host.name[0] = 0;

  user = strdup("");
  passwd = strdup("");
  options = strdup("");
  if(!user || !passwd || !options) {
    result = CURLE_OUT_OF_MEMORY;
    goto out;
  }

  result = parseurlandfillconn(data, conn, &prot_missing, &user, &passwd,
                               &options);
  if(result)
    goto out;


  if(prot_missing) {


    char *reurl;

    reurl = aprintf("%s://%s", conn->handler->scheme, data->change.url);

    if(!reurl) {
      result = CURLE_OUT_OF_MEMORY;
      goto out;
    }

    if(data->change.url_alloc) {
      Curl_safefree(data->change.url);
      data->change.url_alloc = FALSE;
    }

    data->change.url = reurl;
    data->change.url_alloc = TRUE;
  }


  if((conn->given->flags&PROTOPT_NOURLQUERY)) {
    char *path_q_sep = strchr(conn->data->state.path, '?');
    if(path_q_sep) {


      path_q_sep[0] = 0;
    }
  }

  if(data->set.str[STRING_BEARER]) {
    conn->xoauth2_bearer = strdup(data->set.str[STRING_BEARER]);
    if(!conn->xoauth2_bearer) {
      result = CURLE_OUT_OF_MEMORY;
      goto out;
    }
  }

#ifndef CURL_DISABLE_PROXY


  if(conn->bits.proxy_user_passwd) {
    result = parse_proxy_auth(data, conn);
    if(result)
      goto out;
  }


  if(data->set.str[STRING_PROXY]) {
    proxy = strdup(data->set.str[STRING_PROXY]);

    if(NULL == proxy) {
      failf(data, "memory shortage");
      result = CURLE_OUT_OF_MEMORY;
      goto out;
    }
  }

  if(data->set.str[STRING_NOPROXY] &&
     check_noproxy(conn->host.name, data->set.str[STRING_NOPROXY])) {
    free(proxy);
    proxy = NULL;
  }
  else if(!proxy)
    proxy = detect_proxy(conn);

#ifdef USE_UNIX_SOCKETS
  if(proxy && data->set.str[STRING_UNIX_SOCKET_PATH]) {
    free(proxy);
    proxy = NULL;
  }
#endif

  if(proxy && (!*proxy || (conn->handler->flags & PROTOPT_NONETWORK))) {
    free(proxy);

    proxy = NULL;
  }


  if(proxy) {
    result = parse_proxy(data, conn, proxy);

    free(proxy);
    proxy = NULL;

    if(result)
      goto out;

    if((conn->proxytype == CURLPROXY_HTTP) ||
       (conn->proxytype == CURLPROXY_HTTP_1_0)) {
#ifdef CURL_DISABLE_HTTP

      result = CURLE_UNSUPPORTED_PROTOCOL;
      goto out;
#else


      if(!(conn->handler->protocol & PROTO_FAMILY_HTTP) &&
         !conn->bits.tunnel_proxy)
        conn->handler = &Curl_handler_http;

      conn->bits.httpproxy = TRUE;
#endif
    }
    else
      conn->bits.httpproxy = FALSE;
    conn->bits.proxy = TRUE;
  }
  else {

    conn->bits.proxy = FALSE;
    conn->bits.httpproxy = FALSE;
    conn->bits.proxy_user_passwd = FALSE;
    conn->bits.tunnel_proxy = FALSE;
  }

#endif


  if((conn->given->flags&PROTOPT_SSL) && conn->bits.httpproxy)
    conn->bits.tunnel_proxy = TRUE;


  result = parse_remote_port(data, conn);
  if(result)
    goto out;


  result = override_login(data, conn, &user, &passwd, &options);
  if(result)
    goto out;
  result = set_login(conn, user, passwd, options);
  if(result)
    goto out;


  result = setup_connection_internals(conn);
  if(result)
    goto out;

  conn->recv[FIRSTSOCKET] = Curl_recv_plain;
  conn->send[FIRSTSOCKET] = Curl_send_plain;
  conn->recv[SECONDARYSOCKET] = Curl_recv_plain;
  conn->send[SECONDARYSOCKET] = Curl_send_plain;


#ifndef CURL_DISABLE_FILE
  if(conn->handler->flags & PROTOPT_NONETWORK) {
    bool done;


    DEBUGASSERT(conn->handler->connect_it);
    result = conn->handler->connect_it(conn, &done);


    if(!result) {
      conn->data = data;
      conn->bits.tcpconnect[FIRSTSOCKET] = TRUE;

      ConnectionStore(data, conn);


      result = setup_range(data);
      if(result) {
        DEBUGASSERT(conn->handler->done);

        (void)conn->handler->done(conn, result, FALSE);
        goto out;
      }

      Curl_setup_transfer(conn, -1, -1, FALSE, NULL,
                          -1, NULL);
    }


    do_init(conn);

    goto out;
  }
#endif


  data->set.ssl.CApath = data->set.str[STRING_SSL_CAPATH];
  data->set.ssl.CAfile = data->set.str[STRING_SSL_CAFILE];
  data->set.ssl.CRLfile = data->set.str[STRING_SSL_CRLFILE];
  data->set.ssl.issuercert = data->set.str[STRING_SSL_ISSUERCERT];
  data->set.ssl.random_file = data->set.str[STRING_SSL_RANDOM_FILE];
  data->set.ssl.egdsocket = data->set.str[STRING_SSL_EGDSOCKET];
  data->set.ssl.cipher_list = data->set.str[STRING_SSL_CIPHER_LIST];
#ifdef USE_TLS_SRP
  data->set.ssl.username = data->set.str[STRING_TLSAUTH_USERNAME];
  data->set.ssl.password = data->set.str[STRING_TLSAUTH_PASSWORD];
#endif

  if(!Curl_clone_ssl_config(&data->set.ssl, &conn->ssl_config)) {
    result = CURLE_OUT_OF_MEMORY;
    goto out;
  }

  prune_dead_connections(data);


  if(data->set.reuse_fresh && !data->state.this_is_a_follow)
    reuse = FALSE;
  else
    reuse = ConnectionExists(data, conn, &conn_temp, &force_reuse);


  if(reuse && !force_reuse && IsPipeliningPossible(data, conn_temp)) {
    size_t pipelen = conn_temp->send_pipe->size + conn_temp->recv_pipe->size;
    if(pipelen > 0) {
      infof(data, "Found connection %ld, with requests in the pipe (%zu)\n",
            conn_temp->connection_id, pipelen);

      if(conn_temp->bundle->num_connections < max_host_connections &&
         data->state.conn_cache->num_connections < max_total_connections) {

        reuse = FALSE;

        infof(data, "We can reuse, but we want a new connection anyway\n");
      }
    }
  }

  if(reuse) {


    conn_temp->inuse = TRUE;

    reuse_conn(conn, conn_temp);
    free(conn);
    conn = conn_temp;
    *in_connect = conn;


    fix_hostname(data, conn, &conn->host);

    infof(data, "Re-using existing connection! (#%ld) with %s %s\n",
          conn->connection_id,
          conn->bits.proxy?"proxy":"host",
          conn->proxy.name?conn->proxy.dispname:conn->host.dispname);
  }
  else {


    struct connectbundle *bundle;

    bundle = Curl_conncache_find_bundle(conn, data->state.conn_cache);
    if(max_host_connections > 0 && bundle &&
       (bundle->num_connections >= max_host_connections)) {
      struct connectdata *conn_candidate;


      conn_candidate = find_oldest_idle_connection_in_bundle(data, bundle);

      if(conn_candidate) {

        conn_candidate->data = data;
        (void)Curl_disconnect(conn_candidate,  FALSE);
      }
      else
        no_connections_available = TRUE;
    }

    if(max_total_connections > 0 &&
       (data->state.conn_cache->num_connections >= max_total_connections)) {
      struct connectdata *conn_candidate;


      conn_candidate = find_oldest_idle_connection(data);

      if(conn_candidate) {

        conn_candidate->data = data;
        (void)Curl_disconnect(conn_candidate,  FALSE);
      }
      else
        no_connections_available = TRUE;
    }


    if(no_connections_available) {
      infof(data, "No connections available.\n");

      conn_free(conn);
      *in_connect = NULL;

      result = CURLE_NO_CONNECTION_AVAILABLE;
      goto out;
    }
    else {


      ConnectionStore(data, conn);
    }

#if defined(USE_NTLM)


    if((data->state.authhost.picked & (CURLAUTH_NTLM | CURLAUTH_NTLM_WB)) &&
       data->state.authhost.done) {
      infof(data, "NTLM picked AND auth done set, clear picked!\n");
      data->state.authhost.picked = CURLAUTH_NONE;
    }

    if((data->state.authproxy.picked & (CURLAUTH_NTLM | CURLAUTH_NTLM_WB)) &&
       data->state.authproxy.done) {
      infof(data, "NTLM-proxy picked AND auth done set, clear picked!\n");
      data->state.authproxy.picked = CURLAUTH_NONE;
    }
#endif
  }


  conn->inuse = TRUE;


  do_init(conn);


  result = setup_range(data);
  if(result)
    goto out;


  conn->fread_func = data->set.fread_func;
  conn->fread_in = data->set.in;
  conn->seek_func = data->set.seek_func;
  conn->seek_client = data->set.seek_client;


  result = resolve_server(data, conn, async);

  out:

  free(options);
  free(passwd);
  free(user);
  free(proxy);
  return result;
}
