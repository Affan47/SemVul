CURLcode Curl_follow(struct Curl_easy *data,
                     char *newurl,
                     followtype type)
{
#ifdef CURL_DISABLE_HTTP
  (void)data;
  (void)newurl;
  (void)type;

  return CURLE_TOO_MANY_REDIRECTS;
#else


  bool disallowport = FALSE;
  bool reachedmax = FALSE;
  CURLUcode uc;

  DEBUGASSERT(type != FOLLOW_NONE);

  if(type == FOLLOW_REDIR) {
    if((data->set.maxredirs != -1) &&
       (data->state.followlocation >= data->set.maxredirs)) {
      reachedmax = TRUE;
      type = FOLLOW_FAKE;

    }
    else {

      data->state.this_is_a_follow = TRUE;

      data->state.followlocation++;

      if(data->set.http_auto_referer) {


        if(data->state.referer_alloc) {
          Curl_safefree(data->state.referer);
          data->state.referer_alloc = FALSE;
        }

        data->state.referer = strdup(data->state.url);
        if(!data->state.referer)
          return CURLE_OUT_OF_MEMORY;
        data->state.referer_alloc = TRUE;
      }
    }
  }

  if((type != FOLLOW_RETRY) &&
     (data->req.httpcode != 401) && (data->req.httpcode != 407) &&
     Curl_is_absolute_url(newurl, NULL, MAX_SCHEME_LEN))


    disallowport = TRUE;

  DEBUGASSERT(data->state.uh);
  uc = curl_url_set(data->state.uh, CURLUPART_URL, newurl,
                    (type == FOLLOW_FAKE) ? CURLU_NON_SUPPORT_SCHEME :
                    ((type == FOLLOW_REDIR) ? CURLU_URLENCODE : 0) );
  if(uc) {
    if(type != FOLLOW_FAKE)
      return Curl_uc_to_curlcode(uc);


    newurl = strdup(newurl);
    if(!newurl)
      return CURLE_OUT_OF_MEMORY;
  }
  else {

    uc = curl_url_get(data->state.uh, CURLUPART_URL, &newurl, 0);
    if(uc)
      return Curl_uc_to_curlcode(uc);
  }

  if(type == FOLLOW_FAKE) {


    data->info.wouldredirect = newurl;

    if(reachedmax) {
      failf(data, "Maximum (%ld) redirects followed", data->set.maxredirs);
      return CURLE_TOO_MANY_REDIRECTS;
    }
    return CURLE_OK;
  }

  if(disallowport)
    data->state.allow_port = FALSE;

  if(data->state.url_alloc)
    Curl_safefree(data->state.url);

  data->state.url = newurl;
  data->state.url_alloc = TRUE;

  infof(data, "Issue another request to this URL: '%s'\n", data->state.url);


  switch(data->info.httpcode) {


  default:


    break;
  case 301:


    if((data->state.httpreq == HTTPREQ_POST
        || data->state.httpreq == HTTPREQ_POST_FORM
        || data->state.httpreq == HTTPREQ_POST_MIME)
       && !(data->set.keep_post & CURL_REDIR_POST_301)) {
      infof(data, "Switch from POST to GET\n");
      data->state.httpreq = HTTPREQ_GET;
    }
    break;
  case 302:


    if((data->state.httpreq == HTTPREQ_POST
        || data->state.httpreq == HTTPREQ_POST_FORM
        || data->state.httpreq == HTTPREQ_POST_MIME)
       && !(data->set.keep_post & CURL_REDIR_POST_302)) {
      infof(data, "Switch from POST to GET\n");
      data->state.httpreq = HTTPREQ_GET;
    }
    break;

  case 303:


    if(data->state.httpreq != HTTPREQ_GET &&
       ((data->state.httpreq != HTTPREQ_POST &&
         data->state.httpreq != HTTPREQ_POST_FORM &&
         data->state.httpreq != HTTPREQ_POST_MIME) ||
        !(data->set.keep_post & CURL_REDIR_POST_303))) {
      data->state.httpreq = HTTPREQ_GET;
      data->set.upload = false;
      infof(data, "Switch to %s\n",
            data->set.opt_no_body?"HEAD":"GET");
    }
    break;
  case 304:


    break;
  case 305:


    break;
  }
  Curl_pgrsTime(data, TIMER_REDIRECT);
  Curl_pgrsResetTransferSizes(data);

  return CURLE_OK;
#endif
}
