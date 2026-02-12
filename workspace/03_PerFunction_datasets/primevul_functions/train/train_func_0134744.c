static CURLcode imap_do(struct connectdata *conn, bool *done)
{
  CURLcode result = CURLE_OK;

  *done = FALSE;


  result = imap_parse_url_path(conn);
  if(result)
    return result;


  result = imap_parse_custom_request(conn);
  if(result)
    return result;

  result = imap_regular_transfer(conn, done);

  return result;
}
