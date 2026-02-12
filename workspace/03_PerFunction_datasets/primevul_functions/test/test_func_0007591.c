static CURLUcode parse_hostname_login(struct Curl_URL *u,
                                      char **hostname,
                                      unsigned int flags)
{
  CURLUcode result = CURLUE_OK;
  CURLcode ccode;
  char *userp = NULL;
  char *passwdp = NULL;
  char *optionsp = NULL;
  const struct Curl_handler *h = NULL;


  char *ptr = strchr(*hostname, '@');
  char *login = *hostname;

  if(!ptr)
    goto out;


  *hostname = ++ptr;


  if(u->scheme)
    h = Curl_builtin_scheme(u->scheme);


  ccode = Curl_parse_login_details(login, ptr - login - 1,
                                   &userp, &passwdp,
                                   (h && (h->flags & PROTOPT_URLOPTIONS)) ?
                                   &optionsp:NULL);
  if(ccode) {
    result = CURLUE_BAD_LOGIN;
    goto out;
  }

  if(userp) {
    if(flags & CURLU_DISALLOW_USER) {

      result = CURLUE_USER_NOT_ALLOWED;
      goto out;
    }
    if(junkscan(userp, flags)) {
      result = CURLUE_BAD_USER;
      goto out;
    }
    u->user = userp;
  }

  if(passwdp) {
    if(junkscan(passwdp, flags)) {
      result = CURLUE_BAD_PASSWORD;
      goto out;
    }
    u->password = passwdp;
  }

  if(optionsp) {
    if(junkscan(optionsp, flags)) {
      result = CURLUE_BAD_LOGIN;
      goto out;
    }
    u->options = optionsp;
  }

  return CURLUE_OK;
  out:

  free(userp);
  free(passwdp);
  free(optionsp);
  u->user = NULL;
  u->password = NULL;
  u->options = NULL;

  return result;
}
