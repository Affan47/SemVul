ConnectionDone(struct SessionHandle *data, struct connectdata *conn)
{

  size_t maxconnects =
    (data->multi->maxconnects < 0) ? data->multi->num_easy * 4:
    data->multi->maxconnects;
  struct connectdata *conn_candidate = NULL;


  conn->inuse = FALSE;

  if(maxconnects > 0 &&
     data->state.conn_cache->num_connections > maxconnects) {
    infof(data, "Connection cache is full, closing the oldest one.\n");

    conn_candidate = find_oldest_idle_connection(data);

    if(conn_candidate) {

      conn_candidate->data = data;


      (void)Curl_disconnect(conn_candidate,  FALSE);
    }
  }

  return (conn_candidate == conn) ? FALSE : TRUE;
}
