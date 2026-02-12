CURLcode Curl_disconnect(struct connectdata *conn, bool dead_connection)
{
  struct Curl_easy *data;
  if(!conn)
    return CURLE_OK;
  data = conn->data;

  if(!data) {
    DEBUGF(fprintf(stderr, "DISCONNECT without easy handle, ignoring\n"));
    return CURLE_OK;
  }


  if(!conn->bits.close &&
     (conn->send_pipe.size + conn->recv_pipe.size)) {
    DEBUGF(infof(data, "Curl_disconnect, usecounter: %d\n",
                 conn->send_pipe.size + conn->recv_pipe.size));
    return CURLE_OK;
  }

  if(conn->dns_entry != NULL) {
    Curl_resolv_unlock(data, conn->dns_entry);
    conn->dns_entry = NULL;
  }

  Curl_hostcache_prune(data);

#if !defined(CURL_DISABLE_HTTP) && defined(USE_NTLM)

  Curl_http_ntlm_cleanup(conn);
#endif

  if(conn->handler->disconnect)

    conn->handler->disconnect(conn, dead_connection);


  infof(data, "Closing connection %ld\n", conn->connection_id);
  Curl_conncache_remove_conn(data->state.conn_cache, conn);

  free_fixed_hostname(&conn->host);
  free_fixed_hostname(&conn->conn_to_host);
  free_fixed_hostname(&conn->http_proxy.host);
  free_fixed_hostname(&conn->socks_proxy.host);

  Curl_ssl_close(conn, FIRSTSOCKET);


  if(Curl_pipeline_wanted(data->multi, CURLPIPE_ANY)) {
    signalPipeClose(&conn->send_pipe, TRUE);
    signalPipeClose(&conn->recv_pipe, TRUE);
  }

  conn_free(conn);

  return CURLE_OK;
}
