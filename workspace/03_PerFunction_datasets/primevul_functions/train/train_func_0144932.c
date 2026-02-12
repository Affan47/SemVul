static CURLcode multi_do(struct connectdata **connp, bool *done)
{
  CURLcode result=CURLE_OK;
  struct connectdata *conn = *connp;
  struct Curl_easy *data = conn->data;

  if(conn->handler->do_it) {

    result = conn->handler->do_it(conn, done);


    if((CURLE_SEND_ERROR == result) && conn->bits.reuse) {


      if(!data->multi) {
        result = multi_reconnect_request(connp);

        if(!result) {

          conn = *connp;

          result = conn->handler->do_it(conn, done);
        }
      }
      else
        return result;
    }

    if(!result && *done)

      do_complete(conn);
  }
  return result;
}
