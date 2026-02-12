static CURLcode imap_perform_select(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct IMAP *imap = data->req.protop;
  struct imap_conn *imapc = &conn->proto.imapc;
  char *mailbox;


  Curl_safefree(imapc->mailbox);
  Curl_safefree(imapc->mailbox_uidvalidity);


  if(!imap->mailbox) {
    failf(conn->data, "Cannot SELECT without a mailbox.");
    return CURLE_URL_MALFORMAT;
  }


  mailbox = imap_atom(imap->mailbox, false);
  if(!mailbox)
    return CURLE_OUT_OF_MEMORY;


  result = imap_sendf(conn, "SELECT %s", mailbox);

  free(mailbox);

  if(!result)
    state(conn, IMAP_SELECT);

  return result;
}
