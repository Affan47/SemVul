Curl_setup_transfer(
  struct Curl_easy *data,
  int sockindex,
  curl_off_t size,
  bool getheader,
  int writesockindex

  )
{
  struct SingleRequest *k = &data->req;
  struct connectdata *conn = data->conn;
  struct HTTP *http = data->req.p.http;
  bool httpsending = ((conn->handler->protocol&PROTO_FAMILY_HTTP) &&
                      (http->sending == HTTPSEND_REQUEST));
  DEBUGASSERT(conn != NULL);
  DEBUGASSERT((sockindex <= 1) && (sockindex >= -1));

  if(conn->bits.multiplex || conn->httpversion == 20 || httpsending) {

    conn->sockfd = sockindex == -1 ?
      ((writesockindex == -1 ? CURL_SOCKET_BAD : conn->sock[writesockindex])) :
      conn->sock[sockindex];
    conn->writesockfd = conn->sockfd;
    if(httpsending)

      writesockindex = FIRSTSOCKET;
  }
  else {
    conn->sockfd = sockindex == -1 ?
      CURL_SOCKET_BAD : conn->sock[sockindex];
    conn->writesockfd = writesockindex == -1 ?
      CURL_SOCKET_BAD:conn->sock[writesockindex];
  }
  k->getheader = getheader;

  k->size = size;


  if(!k->getheader) {
    k->header = FALSE;
    if(size > 0)
      Curl_pgrsSetDownloadSize(data, size);
  }

  if(k->getheader || !data->set.opt_no_body) {

    if(sockindex != -1)
      k->keepon |= KEEP_RECV;

    if(writesockindex != -1) {


      if((data->state.expect100header) &&
         (conn->handler->protocol&PROTO_FAMILY_HTTP) &&
         (http->sending == HTTPSEND_BODY)) {

        k->exp100 = EXP100_AWAITING_CONTINUE;
        k->start100 = Curl_now();


        Curl_expire(data, data->set.expect_100_timeout, EXPIRE_100_TIMEOUT);
      }
      else {
        if(data->state.expect100header)


          k->exp100 = EXP100_SENDING_REQUEST;


        k->keepon |= KEEP_SEND;
      }
    }
  }

}
