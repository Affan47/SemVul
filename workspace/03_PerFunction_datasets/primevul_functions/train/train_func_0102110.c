static CURLcode do_init(struct connectdata *conn)
{
  struct SessionHandle *data = conn->data;
  struct SingleRequest *k = &data->req;

  conn->bits.done = FALSE;
  conn->bits.do_more = FALSE;
  data->state.expect100header = FALSE;

  if(data->set.opt_no_body)

    data->set.httpreq = HTTPREQ_HEAD;
  else if(HTTPREQ_HEAD == data->set.httpreq)


    data->set.httpreq = HTTPREQ_GET;

  k->start = Curl_tvnow();
  k->now = k->start;
  k->header = TRUE;

  k->bytecount = 0;

  k->buf = data->state.buffer;
  k->uploadbuf = data->state.uploadbuffer;
  k->hbufp = data->state.headerbuff;
  k->ignorebody=FALSE;

  Curl_speedinit(data);

  Curl_pgrsSetUploadCounter(data, 0);
  Curl_pgrsSetDownloadCounter(data, 0);

  return CURLE_OK;
}
