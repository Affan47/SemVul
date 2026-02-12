static CURLcode imap_perform_starttls(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;


  result = imap_sendf(conn, "STARTTLS");

  if(!result)
    state(conn, IMAP_STARTTLS);

  return result;
}
