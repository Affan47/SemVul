static CURLcode imap_perform_list(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct IMAP *imap = data->req.protop;
  char *mailbox;

  if(imap->custom)

    result = imap_sendf(conn, "%s%s", imap->custom,
                        imap->custom_params ? imap->custom_params : "");
  else {

    mailbox = imap->mailbox ? imap_atom(imap->mailbox, true) : strdup("");
    if(!mailbox)
      return CURLE_OUT_OF_MEMORY;


    result = imap_sendf(conn, "LIST \"%s\" *", mailbox);

    free(mailbox);
  }

  if(!result)
    state(conn, IMAP_LIST);

  return result;
}
