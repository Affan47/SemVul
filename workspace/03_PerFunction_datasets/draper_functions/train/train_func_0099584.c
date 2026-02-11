Curl_pretransfer(struct SessionHandle *data)
{
  CURLcode result;
  if(!data->change.url) {

    failf(data, "No URL set!");
    return CURLE_URL_MALFORMAT;
  }


  result = Curl_ssl_initsessions(data, data->set.ssl.max_ssl_sessions);
  if(result)
    return result;

  data->set.followlocation=0;
  data->state.this_is_a_follow = FALSE;
  data->state.errorbuf = FALSE;
  data->state.httpversion = 0;

  data->state.authproblem = FALSE;
  data->state.authhost.want = data->set.httpauth;
  data->state.authproxy.want = data->set.proxyauth;
  Curl_safefree(data->info.wouldredirect);
  data->info.wouldredirect = NULL;


  if(data->change.cookielist)
    Curl_cookie_loadfiles(data);


  if(data->change.resolve)
    result = Curl_loadhostpairs(data);

  if(!result) {


    data->state.allow_port = TRUE;

#if defined(HAVE_SIGNAL) && defined(SIGPIPE) && !defined(HAVE_MSG_NOSIGNAL)


    if(!data->set.no_signal)
      data->state.prev_signal = signal(SIGPIPE, SIG_IGN);
#endif

    Curl_initinfo(data);
    Curl_pgrsStartNow(data);

    if(data->set.timeout)
      Curl_expire(data, data->set.timeout);

    if(data->set.connecttimeout)
      Curl_expire(data, data->set.connecttimeout);


    data->state.authhost.picked &= data->state.authhost.want;
    data->state.authproxy.picked &= data->state.authproxy.want;
  }

  return result;
}
