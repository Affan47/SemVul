static CURLcode findprotocol(struct SessionHandle *data,
                             struct connectdata *conn,
                             const char *protostr)
{
  const struct Curl_handler * const *pp;
  const struct Curl_handler *p;


  for(pp = protocols; (p = *pp) != NULL; pp++) {
    if(Curl_raw_equal(p->scheme, protostr)) {

      if(!(data->set.allowed_protocols & p->protocol))

        break;


      if(data->state.this_is_a_follow &&
         !(data->set.redir_protocols & p->protocol))

        break;


      conn->handler = conn->given = p;


      return CURLE_OK;
    }
  }


  failf(data, "Protocol \"%s\" not supported or disabled in " LIBCURL_NAME,
        protostr);

  return CURLE_UNSUPPORTED_PROTOCOL;
}
