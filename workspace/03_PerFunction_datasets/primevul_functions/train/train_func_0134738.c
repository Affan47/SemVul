static CURLcode imap_state_append_resp(struct connectdata *conn, int imapcode,
                                       imapstate instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;

  (void)instate;

  if(imapcode != '+') {
    result = CURLE_UPLOAD_FAILED;
  }
  else {

    Curl_pgrsSetUploadSize(data, data->state.infilesize);


    Curl_setup_transfer(conn, -1, -1, FALSE, NULL, FIRSTSOCKET, NULL);


    state(conn, IMAP_STOP);
  }

  return result;
}
