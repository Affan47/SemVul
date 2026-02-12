static bool IsPipeliningPossible(const struct SessionHandle *handle,
                                 const struct connectdata *conn)
{

  if(conn->handler->protocol & PROTO_FAMILY_HTTP) {

    if(Curl_pipeline_wanted(handle->multi, CURLPIPE_HTTP1) &&
       (handle->set.httpversion != CURL_HTTP_VERSION_1_0) &&
       (handle->set.httpreq == HTTPREQ_GET ||
        handle->set.httpreq == HTTPREQ_HEAD))

      return TRUE;

    if(Curl_pipeline_wanted(handle->multi, CURLPIPE_MULTIPLEX) &&
       (handle->set.httpversion >= CURL_HTTP_VERSION_2))

      return TRUE;
  }
  return FALSE;
}
