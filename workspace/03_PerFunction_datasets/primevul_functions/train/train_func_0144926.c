static CURLcode multi_reconnect_request(struct connectdata **connp)
{
  CURLcode result = CURLE_OK;
  struct connectdata *conn = *connp;
  struct Curl_easy *data = conn->data;


  infof(data, "Re-used connection seems dead, get a new one\n");

  connclose(conn, "Reconnect dead connection");
  result = multi_done(&conn, result, FALSE);


  *connp = NULL;


  if(!result || (CURLE_SEND_ERROR == result)) {
    bool async;
    bool protocol_done = TRUE;


    result = Curl_connect(data, connp, &async, &protocol_done);
    if(!result) {


      conn = *connp;
      if(async) {


        result = Curl_resolver_wait_resolv(conn, NULL);
        if(result)
          return result;


        result = Curl_async_resolved(conn, &protocol_done);
        if(result)
          return result;
      }
    }
  }

  return result;
}
