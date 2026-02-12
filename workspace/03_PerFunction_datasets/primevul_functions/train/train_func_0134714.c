static CURLcode imap_perform_login(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  char *user;
  char *passwd;


  if(!conn->bits.user_passwd) {
    state(conn, IMAP_STOP);

    return result;
  }


  user = imap_atom(conn->user, false);
  passwd = imap_atom(conn->passwd, false);


  result = imap_sendf(conn, "LOGIN %s %s", user ? user : "",
                      passwd ? passwd : "");

  free(user);
  free(passwd);

  if(!result)
    state(conn, IMAP_LOGIN);

  return result;
}
