static CURLcode imap_done(struct connectdata *conn, CURLcode status,
                          bool premature)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct IMAP *imap = data->req.protop;

  (void)premature;

  if(!imap)
    return CURLE_OK;

  if(status) {
    connclose(conn, "IMAP done with bad status");
    result = status;
  }
  else if(!data->set.connect_only && !imap->custom &&
          (imap->uid || data->set.upload ||
          data->set.mimepost.kind != MIMEKIND_NONE)) {

    if(!data->set.upload && data->set.mimepost.kind == MIMEKIND_NONE)
      state(conn, IMAP_FETCH_FINAL);
    else {

      result = Curl_pp_sendf(&conn->proto.imapc.pp, "%s", "");
      if(!result)
        state(conn, IMAP_APPEND_FINAL);
    }


    if(!result)
      result = imap_block_statemach(conn);
  }


  Curl_safefree(imap->mailbox);
  Curl_safefree(imap->uidvalidity);
  Curl_safefree(imap->uid);
  Curl_safefree(imap->section);
  Curl_safefree(imap->partial);
  Curl_safefree(imap->query);
  Curl_safefree(imap->custom);
  Curl_safefree(imap->custom_params);


  imap->transfer = FTPTRANSFER_BODY;

  return result;
}
