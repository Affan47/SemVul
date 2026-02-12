CURLcode Curl_pretransfer(struct Curl_easy *data)
{
  CURLcode result;

  if(!data->state.url && !data->set.uh) {

    failf(data, "No URL set");
    return CURLE_URL_MALFORMAT;
  }


  if(data->state.url_alloc) {

    Curl_safefree(data->state.url);
    data->state.url_alloc = FALSE;
  }

  if(!data->state.url && data->set.uh) {
    CURLUcode uc;
    free(data->set.str[STRING_SET_URL]);
    uc = curl_url_get(data->set.uh,
                      CURLUPART_URL, &data->set.str[STRING_SET_URL], 0);
    if(uc) {
      failf(data, "No URL set");
      return CURLE_URL_MALFORMAT;
    }
  }

  data->state.prefer_ascii = data->set.prefer_ascii;
  data->state.list_only = data->set.list_only;
  data->state.httpreq = data->set.method;
  data->state.url = data->set.str[STRING_SET_URL];


  result = Curl_ssl_initsessions(data, data->set.general_ssl.max_ssl_sessions);
  if(result)
    return result;

  data->state.wildcardmatch = data->set.wildcard_enabled;
  data->state.followlocation = 0;
  data->state.this_is_a_follow = FALSE;
  data->state.errorbuf = FALSE;
  data->state.httpwant = data->set.httpwant;
  data->state.httpversion = 0;
  data->state.authproblem = FALSE;
  data->state.authhost.want = data->set.httpauth;
  data->state.authproxy.want = data->set.proxyauth;
  Curl_safefree(data->info.wouldredirect);

  if(data->state.httpreq == HTTPREQ_PUT)
    data->state.infilesize = data->set.filesize;
  else if((data->state.httpreq != HTTPREQ_GET) &&
          (data->state.httpreq != HTTPREQ_HEAD)) {
    data->state.infilesize = data->set.postfieldsize;
    if(data->set.postfields && (data->state.infilesize == -1))
      data->state.infilesize = (curl_off_t)strlen(data->set.postfields);
  }
  else
    data->state.infilesize = 0;


  if(data->state.cookielist)
    Curl_cookie_loadfiles(data);


  if(data->state.resolve)
    result = Curl_loadhostpairs(data);

  if(!result) {


    data->state.allow_port = TRUE;

#if defined(HAVE_SIGNAL) && defined(SIGPIPE) && !defined(HAVE_MSG_NOSIGNAL)


    if(!data->set.no_signal)
      data->state.prev_signal = signal(SIGPIPE, SIG_IGN);
#endif

    Curl_initinfo(data);
    Curl_pgrsResetTransferSizes(data);
    Curl_pgrsStartNow(data);


    data->state.authhost.picked &= data->state.authhost.want;
    data->state.authproxy.picked &= data->state.authproxy.want;

#ifndef CURL_DISABLE_FTP
    if(data->state.wildcardmatch) {
      struct WildcardData *wc = &data->wildcard;
      if(wc->state < CURLWC_INIT) {
        result = Curl_wildcard_init(wc);
        if(result)
          return CURLE_OUT_OF_MEMORY;
      }
    }
#endif
    Curl_http2_init_state(&data->state);
    result = Curl_hsts_loadcb(data, data->hsts);
  }


  if(data->set.str[STRING_USERAGENT]) {
    Curl_safefree(data->state.aptr.uagent);
    data->state.aptr.uagent =
      aprintf("User-Agent: %s\r\n", data->set.str[STRING_USERAGENT]);
    if(!data->state.aptr.uagent)
      return CURLE_OUT_OF_MEMORY;
  }

  if(!result)
    result = Curl_setstropt(&data->state.aptr.user,
                            data->set.str[STRING_USERNAME]);
  if(!result)
    result = Curl_setstropt(&data->state.aptr.passwd,
                            data->set.str[STRING_PASSWORD]);
  if(!result)
    result = Curl_setstropt(&data->state.aptr.proxyuser,
                            data->set.str[STRING_PROXYUSERNAME]);
  if(!result)
    result = Curl_setstropt(&data->state.aptr.proxypasswd,
                            data->set.str[STRING_PROXYPASSWORD]);

  data->req.headerbytecount = 0;
  Curl_headers_cleanup(data);
  return result;
}
