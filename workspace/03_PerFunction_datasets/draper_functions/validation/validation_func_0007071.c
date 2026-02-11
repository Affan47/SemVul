tftp_done(struct connectdata *conn, CURLcode status,
                          bool premature)
{
  CURLcode code = CURLE_OK;
  tftp_state_data_t *state = (tftp_state_data_t *)conn->proto.tftpc;

  (void)status;
  (void)premature;

  if(Curl_pgrsDone(conn))
    return CURLE_ABORTED_BY_CALLBACK;


  if(state)
    code = tftp_translate_code(state->error);

  return code;
}
