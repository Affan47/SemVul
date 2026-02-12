static CURLcode parse_url_login(struct Curl_easy *data,
                                struct connectdata *conn,
                                char **user, char **passwd, char **options)
{
  CURLcode result = CURLE_OK;
  char *userp = NULL;
  char *passwdp = NULL;
  char *optionsp = NULL;


  char *ptr = strchr(conn->host.name, '@');
  char *login = conn->host.name;

  DEBUGASSERT(!**user);
  DEBUGASSERT(!**passwd);
  DEBUGASSERT(!**options);
  DEBUGASSERT(conn->handler);

  if(!ptr)
    goto out;


  conn->host.name = ++ptr;


  if(data->set.use_netrc == CURL_NETRC_REQUIRED)
    goto out;


  result =
    Curl_parse_login_details(login, ptr - login - 1,
                             &userp, &passwdp,
                             (conn->handler->flags & PROTOPT_URLOPTIONS)?
                             &optionsp:NULL);
  if(result)
    goto out;

  if(userp) {
    char *newname;


    conn->bits.userpwd_in_url = TRUE;
    conn->bits.user_passwd = TRUE;


    result = Curl_urldecode(data, userp, 0, &newname, NULL, FALSE);
    if(result) {
      goto out;
    }

    free(*user);
    *user = newname;
  }

  if(passwdp) {

    char *newpasswd;
    result = Curl_urldecode(data, passwdp, 0, &newpasswd, NULL, FALSE);
    if(result) {
      goto out;
    }

    free(*passwd);
    *passwd = newpasswd;
  }

  if(optionsp) {

    char *newoptions;
    result = Curl_urldecode(data, optionsp, 0, &newoptions, NULL, FALSE);
    if(result) {
      goto out;
    }

    free(*options);
    *options = newoptions;
  }


  out:

  free(userp);
  free(passwdp);
  free(optionsp);

  return result;
}
