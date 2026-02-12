static bool disconnect_if_dead(struct connectdata *conn,
                               struct SessionHandle *data)
{
  size_t pipeLen = conn->send_pipe->size + conn->recv_pipe->size;
  if(!pipeLen && !conn->inuse) {


    bool dead;
    if(conn->handler->protocol & CURLPROTO_RTSP)

      dead = Curl_rtsp_connisdead(conn);
    else
      dead = SocketIsDead(conn->sock[FIRSTSOCKET]);

    if(dead) {
      conn->data = data;
      infof(data, "Connection %ld seems to be dead!\n", conn->connection_id);


      Curl_disconnect(conn, TRUE);
      return TRUE;
    }
  }
  return FALSE;
}
