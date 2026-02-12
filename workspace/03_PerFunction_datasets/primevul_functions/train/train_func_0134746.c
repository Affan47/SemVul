static CURLcode imap_perform_capability(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct imap_conn *imapc = &conn->proto.imapc;

  imapc->sasl.authmechs = SASL_AUTH_NONE;
  imapc->sasl.authused = SASL_AUTH_NONE;
  imapc->tls_supported = FALSE;


  result = imap_sendf(conn, "CAPABILITY");

  if(!result)
    state(conn, IMAP_CAPABILITY);

  return result;
}
