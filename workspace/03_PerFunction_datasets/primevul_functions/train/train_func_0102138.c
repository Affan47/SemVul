CURLcode Curl_done(struct connectdata **connp,
                   CURLcode status,

                   bool premature)
{
  CURLcode result;
  struct connectdata *conn;
  struct SessionHandle *data;

  DEBUGASSERT(*connp);

  conn = *connp;
  data = conn->data;

  if(conn->bits.done)

    return CURLE_OK;

  Curl_getoff_all_pipelines(data, conn);

  if((conn->send_pipe->size + conn->recv_pipe->size != 0 &&
      !data->set.reuse_forbid &&
      !conn->bits.close))


    return CURLE_OK;

  conn->bits.done = TRUE;


  free(data->req.newurl);
  data->req.newurl = NULL;
  free(data->req.location);
  data->req.location = NULL;

  Curl_resolver_cancel(conn);

  if(conn->dns_entry) {
    Curl_resolv_unlock(data, conn->dns_entry);
    conn->dns_entry = NULL;
  }

  switch(status) {
  case CURLE_ABORTED_BY_CALLBACK:
  case CURLE_READ_ERROR:
  case CURLE_WRITE_ERROR:


    premature = TRUE;
  default:
    break;
  }


  if(conn->handler->done)
    result = conn->handler->done(conn, status, premature);
  else
    result = status;

  if(!result && Curl_pgrsDone(conn))
    result = CURLE_ABORTED_BY_CALLBACK;


  free(data->state.tempwrite);
  data->state.tempwrite = NULL;


  if((data->set.reuse_forbid
#if defined(USE_NTLM)
      && !(conn->ntlm.state == NTLMSTATE_TYPE2 ||
           conn->proxyntlm.state == NTLMSTATE_TYPE2)
#endif
     ) || conn->bits.close || premature) {
    CURLcode res2 = Curl_disconnect(conn, premature);


    if(!result && res2)
      result = res2;
  }
  else {

    if(ConnectionDone(data, conn)) {

      data->state.lastconnect = conn;

      infof(data, "Connection #%ld to host %s left intact\n",
            conn->connection_id,
            conn->bits.httpproxy?conn->proxy.dispname:conn->host.dispname);
    }
    else
      data->state.lastconnect = NULL;
  }

  *connp = NULL;


  Curl_free_request_state(data);

  return result;
}
