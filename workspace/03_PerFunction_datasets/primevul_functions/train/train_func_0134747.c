static CURLcode imap_perform(struct connectdata *conn, bool *connected,
                             bool *dophase_done)
{

  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct IMAP *imap = data->req.protop;
  struct imap_conn *imapc = &conn->proto.imapc;
  bool selected = FALSE;

  DEBUGF(infof(conn->data, "DO phase starts\n"));

  if(conn->data->set.opt_no_body) {

    imap->transfer = FTPTRANSFER_INFO;
  }

  *dophase_done = FALSE;


  if(imap->mailbox && imapc->mailbox &&
     !strcmp(imap->mailbox, imapc->mailbox) &&
     (!imap->uidvalidity || !imapc->mailbox_uidvalidity ||
      !strcmp(imap->uidvalidity, imapc->mailbox_uidvalidity)))
    selected = TRUE;


  if(conn->data->set.upload || data->set.mimepost.kind != MIMEKIND_NONE)

    result = imap_perform_append(conn);
  else if(imap->custom && (selected || !imap->mailbox))

    result = imap_perform_list(conn);
  else if(!imap->custom && selected && imap->uid)

    result = imap_perform_fetch(conn);
  else if(!imap->custom && selected && imap->query)

    result = imap_perform_search(conn);
  else if(imap->mailbox && !selected &&
         (imap->custom || imap->uid || imap->query))

    result = imap_perform_select(conn);
  else

    result = imap_perform_list(conn);

  if(result)
    return result;


  result = imap_multi_statemach(conn, dophase_done);

  *connected = conn->bits.tcpconnect[FIRSTSOCKET];

  if(*dophase_done)
    DEBUGF(infof(conn->data, "DO phase is complete\n"));

  return result;
}
