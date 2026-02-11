pop3_state_command_resp(struct connectdata *conn,
                                        int pop3code,
                                        pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct POP3 *pop3 = data->req.protop;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  struct pingpong *pp = &pop3c->pp;

  (void)instate;

  if(pop3code != '+') {
    state(conn, POP3_STOP);
    return CURLE_RECV_ERROR;
  }


  pop3c->eob = 2;


  pop3c->strip = 2;

  if(pop3->transfer == FTPTRANSFER_BODY) {

    Curl_setup_transfer(conn, FIRSTSOCKET, -1, FALSE, NULL, -1, NULL);

    if(pp->cache) {


      if(!data->set.opt_no_body) {
        result = Curl_pop3_write(conn, pp->cache, pp->cache_size);
        if(result)
          return result;
      }


      Curl_safefree(pp->cache);


      pp->cache_size = 0;
    }
  }


  state(conn, POP3_STOP);

  return result;
}
