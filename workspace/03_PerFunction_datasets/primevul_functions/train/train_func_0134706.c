static CURLcode imap_setup_connection(struct connectdata *conn)
{
  struct Curl_easy *data = conn->data;


  CURLcode result = imap_init(conn);
  if(result)
    return result;


  conn->tls_upgraded = FALSE;
  data->state.path++;

  return CURLE_OK;
}
