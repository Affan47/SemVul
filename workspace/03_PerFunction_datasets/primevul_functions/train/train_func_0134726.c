static CURLcode imap_perform_append(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct IMAP *imap = data->req.protop;
  char *mailbox;


  if(!imap->mailbox) {
    failf(data, "Cannot APPEND without a mailbox.");
    return CURLE_URL_MALFORMAT;
  }


  if(data->set.mimepost.kind != MIMEKIND_NONE) {

    data->set.mimepost.flags &= ~MIME_BODY_ONLY;


    curl_mime_headers(&data->set.mimepost, data->set.headers, 0);
    result = Curl_mime_prepare_headers(&data->set.mimepost, NULL,
                                       NULL, MIMESTRATEGY_MAIL);

    if(!result)
      if(!Curl_checkheaders(conn, "Mime-Version"))
        result = Curl_mime_add_header(&data->set.mimepost.curlheaders,
                                      "Mime-Version: 1.0");


    if(!result)
      result = Curl_mime_rewind(&data->set.mimepost);

    if(result)
      return result;

    data->state.infilesize = Curl_mime_size(&data->set.mimepost);


    data->state.fread_func = (curl_read_callback) Curl_mime_read;
    data->state.in = (void *) &data->set.mimepost;
  }


  if(data->state.infilesize < 0) {
    failf(data, "Cannot APPEND with unknown input file size\n");
    return CURLE_UPLOAD_FAILED;
  }


  mailbox = imap_atom(imap->mailbox, false);
  if(!mailbox)
    return CURLE_OUT_OF_MEMORY;


  result = imap_sendf(conn, "APPEND %s (\\Seen) {%" CURL_FORMAT_CURL_OFF_T "}",
                      mailbox, data->state.infilesize);

  free(mailbox);

  if(!result)
    state(conn, IMAP_APPEND);

  return result;
}
