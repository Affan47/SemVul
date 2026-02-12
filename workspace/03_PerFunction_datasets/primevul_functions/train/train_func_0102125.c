static CURLcode setup_connection_internals(struct connectdata *conn)
{
  const struct Curl_handler * p;
  CURLcode result;
  struct SessionHandle *data = conn->data;


  Curl_free_request_state(data);

  memset(&data->req, 0, sizeof(struct SingleRequest));
  data->req.maxdownload = -1;

  conn->socktype = SOCK_STREAM;


  p = conn->handler;

  if(p->setup_connection) {
    result = (*p->setup_connection)(conn);

    if(result)
      return result;

    p = conn->handler;
  }

  if(conn->port < 0)


    conn->port = p->defport;


  if(conn->remote_port < 0)
    conn->remote_port = (unsigned short)conn->given->defport;

  return CURLE_OK;
}
