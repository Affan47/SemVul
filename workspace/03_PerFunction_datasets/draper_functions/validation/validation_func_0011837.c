Curl_protocol_connect(struct connectdata *conn,
                               bool *protocol_done)
{
  CURLcode result=CURLE_OK;
  struct SessionHandle *data = conn->data;

  *protocol_done = FALSE;

  if(conn->bits.tcpconnect && conn->bits.protoconnstart) {


    if(!conn->curl_connecting)
      *protocol_done = TRUE;

    return CURLE_OK;
  }

  if(!conn->bits.tcpconnect) {

    Curl_pgrsTime(data, TIMER_CONNECT);

    if(data->set.verbose)
      verboseconnect(conn);
  }

  if(!conn->bits.protoconnstart) {
    if(conn->curl_connect) {


      conn->now = Curl_tvnow();


      result = conn->curl_connect(conn, protocol_done);
    }
    else
      *protocol_done = TRUE;


    if (!result)
      conn->bits.protoconnstart = TRUE;
  }

  return result;
}
