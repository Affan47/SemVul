static CURLcode setstropt_userpwd(char *option, char **userp, char **passwdp)
{
  CURLcode result = CURLE_OK;
  char *user = NULL;
  char *passwd = NULL;


  if(option) {
    result = parse_login_details(option, strlen(option),
                                 (userp ? &user : NULL),
                                 (passwdp ? &passwd : NULL),
                                 NULL);
  }

  if(!result) {

    if(userp) {
      if(!user && option && option[0] == ':') {

        user = strdup("");
        if(!user)
          result = CURLE_OUT_OF_MEMORY;
      }

      Curl_safefree(*userp);
      *userp = user;
    }


    if(passwdp) {
      Curl_safefree(*passwdp);
      *passwdp = passwd;
    }
  }

  return result;
}
