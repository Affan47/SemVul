static CURLcode set_login(struct connectdata *conn,
                          const char *user, const char *passwd,
                          const char *options)
{
  CURLcode result = CURLE_OK;


  if((conn->handler->flags & PROTOPT_NEEDSPWD) && !conn->bits.user_passwd) {

    conn->user = strdup(CURL_DEFAULT_USER);


    if(conn->user)
      conn->passwd = strdup(CURL_DEFAULT_PASSWORD);
    else
      conn->passwd = NULL;


  }
  else {

    conn->user = strdup(user);


    if(conn->user)
      conn->passwd = strdup(passwd);
    else
      conn->passwd = NULL;
  }

  if(!conn->user || !conn->passwd)
    result = CURLE_OUT_OF_MEMORY;


  if(!result && options[0]) {
    conn->options = strdup(options);

    if(!conn->options)
      result = CURLE_OUT_OF_MEMORY;
  }

  return result;
}
