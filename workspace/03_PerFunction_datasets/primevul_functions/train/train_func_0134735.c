static CURLcode imap_perform_authenticate(struct connectdata *conn,
                                          const char *mech,
                                          const char *initresp)
{
  CURLcode result = CURLE_OK;

  if(initresp) {

    result = imap_sendf(conn, "AUTHENTICATE %s %s", mech, initresp);
  }
  else {

    result = imap_sendf(conn, "AUTHENTICATE %s", mech);
  }

  return result;
}
