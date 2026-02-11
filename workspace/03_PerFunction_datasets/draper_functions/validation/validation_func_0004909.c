mailimap_examine(mailimap * session, const char * mb)
{
  struct mailimap_response * response;
  int r;
  int error_code;

  if ((session->imap_state != MAILIMAP_STATE_AUTHENTICATED) &&
      (session->imap_state != MAILIMAP_STATE_SELECTED))
    return MAILIMAP_ERROR_BAD_STATE;

  r = mailimap_send_current_tag(session);
  if (r != MAILIMAP_NO_ERROR)
    return r;

  r = mailimap_examine_send(session->imap_stream, mb);
  if (r != MAILIMAP_NO_ERROR)
    return r;

  r = mailimap_crlf_send(session->imap_stream);
  if (r != MAILIMAP_NO_ERROR)
    return r;

  if (mailstream_flush(session->imap_stream) == -1)
    return MAILIMAP_ERROR_STREAM;

  if (mailimap_read_line(session) == NULL)
    return MAILIMAP_ERROR_STREAM;

  if (session->imap_selection_info != NULL)
    mailimap_selection_info_free(session->imap_selection_info);
  session->imap_selection_info = mailimap_selection_info_new();

  r = mailimap_parse_response(session, &response);
  if (r != MAILIMAP_NO_ERROR)
    return r;

  error_code = response->rsp_resp_done->rsp_data.rsp_tagged->rsp_cond_state->rsp_type;

  mailimap_response_free(response);

  switch (error_code) {
  case MAILIMAP_RESP_COND_STATE_OK:
    session->imap_state = MAILIMAP_STATE_SELECTED;
    return MAILIMAP_NO_ERROR;

  default:
    mailimap_selection_info_free(session->imap_selection_info);
    session->imap_selection_info = NULL;
    session->imap_state = MAILIMAP_STATE_AUTHENTICATED;
    return MAILIMAP_ERROR_EXAMINE;
  }
}
