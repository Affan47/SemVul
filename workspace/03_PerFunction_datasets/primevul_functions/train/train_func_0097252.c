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

  if(type != FOLLOW_FAKE)
    data->state.requests++;
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
        CURLU *u;
        char *referer = NULL;


        if(data->state.referer_alloc) {
          Curl_safefree(data->state.referer);
          data->state.referer_alloc = FALSE;
        }


        u = curl_url();
        if(!u)
          return CURLE_OUT_OF_MEMORY;

        uc = curl_url_set(u, CURLUPART_URL, data->state.url, 0);
        if(!uc)
          uc = curl_url_set(u, CURLUPART_FRAGMENT, NULL, 0);
        if(!uc)
          uc = curl_url_set(u, CURLUPART_USER, NULL, 0);
        if(!uc)
          uc = curl_url_set(u, CURLUPART_PASSWORD, NULL, 0);
        if(!uc)
          uc = curl_url_get(u, CURLUPART_URL, &referer, 0);

        curl_url_cleanup(u);

        if(uc || !referer)
          return CURLE_OUT_OF_MEMORY;

        data->state.referer = referer;
        data->state.referer_alloc = TRUE;
      }
    }
  }

  if((type != FOLLOW_RETRY) &&
     (data->req.httpcode != 401) && (data->req.httpcode != 407) &&
     Curl_is_absolute_url(newurl, NULL, 0))


    disallowport = TRUE;

  DEBUGASSERT(data->state.uh);
  uc = curl_url_set(data->state.uh, CURLUPART_URL, newurl,
                    (type == FOLLOW_FAKE) ? CURLU_NON_SUPPORT_SCHEME :
                    ((type == FOLLOW_REDIR) ? CURLU_URLENCODE : 0) |
                    CURLU_ALLOW_SPACE);
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


    if(!data->set.allow_auth_to_other_hosts && (type != FOLLOW_FAKE)) {
      char *portnum;
      int port;
      bool clear = FALSE;

      if(data->set.use_port && data->state.allow_port)

        port = (int)data->set.use_port;
      else {
        uc = curl_url_get(data->state.uh, CURLUPART_PORT, &portnum,
                          CURLU_DEFAULT_PORT);
        if(uc) {
          free(newurl);
          return Curl_uc_to_curlcode(uc);
        }
        port = atoi(portnum);
        free(portnum);
      }
      if(port != data->info.conn_remote_port) {
        infof(data, "Clear auth, redirects to port from %u to %u",
              data->info.conn_remote_port, port);
        clear = TRUE;
      }
      else {
        char *scheme;
        const struct Curl_handler *p;
        uc = curl_url_get(data->state.uh, CURLUPART_SCHEME, &scheme, 0);
        if(uc) {
          free(newurl);
          return Curl_uc_to_curlcode(uc);
        }

        p = Curl_builtin_scheme(scheme);
        if(p && (p->protocol != data->info.conn_protocol)) {
          infof(data, "Clear auth, redirects scheme from %s to %s",
                data->info.conn_scheme, scheme);
          clear = TRUE;
        }
        free(scheme);
      }
      if(clear) {
        Curl_safefree(data->state.aptr.user);
        Curl_safefree(data->state.aptr.passwd);
      }
    }
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

  infof(data, "Issue another request to this URL: '%s'", data->state.url);


  switch(data->info.httpcode) {


  default:


    break;
  case 301:


    if((data->state.httpreq == HTTPREQ_POST
        || data->state.httpreq == HTTPREQ_POST_FORM
        || data->state.httpreq == HTTPREQ_POST_MIME)
       && !(data->set.keep_post & CURL_REDIR_POST_301)) {
      infof(data, "Switch from POST to GET");
      data->state.httpreq = HTTPREQ_GET;
    }
    break;
  case 302:


    if((data->state.httpreq == HTTPREQ_POST
        || data->state.httpreq == HTTPREQ_POST_FORM
        || data->state.httpreq == HTTPREQ_POST_MIME)
       && !(data->set.keep_post & CURL_REDIR_POST_302)) {
      infof(data, "Switch from POST to GET");
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
      infof(data, "Switch to %s",
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
