CURLMcode Curl_multi_add_perform(struct Curl_multi *multi,
                                 struct Curl_easy *data,
                                 struct connectdata *conn)
{
  CURLMcode rc;

  rc = curl_multi_add_handle(multi, data);
  if(!rc) {
    struct SingleRequest *k = &data->req;


    Curl_init_do(data, NULL);


    multistate(data, CURLM_STATE_PERFORM);
    data->easy_conn = conn;
    k->keepon |= KEEP_RECV;
  }
  return rc;
}
