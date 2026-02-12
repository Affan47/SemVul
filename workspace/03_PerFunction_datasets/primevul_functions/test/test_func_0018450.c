CURLcode Curl_setopt(struct SessionHandle *data, CURLoption option,
                     va_list param)
{
  char *argptr;
  CURLcode result = CURLE_OK;
  long arg;
#ifndef CURL_DISABLE_HTTP
  curl_off_t bigsize;
#endif

  switch(option) {
  case CURLOPT_DNS_CACHE_TIMEOUT:
    data->set.dns_cache_timeout = va_arg(param, long);
    break;
  case CURLOPT_DNS_USE_GLOBAL_CACHE:

    arg = va_arg(param, long);
    data->set.global_dns_cache = (0 != arg)?TRUE:FALSE;
    break;
  case CURLOPT_SSL_CIPHER_LIST:

    result = setstropt(&data->set.str[STRING_SSL_CIPHER_LIST],
                       va_arg(param, char *));
    break;

  case CURLOPT_RANDOM_FILE:


    result = setstropt(&data->set.str[STRING_SSL_RANDOM_FILE],
                       va_arg(param, char *));
    break;
  case CURLOPT_EGDSOCKET:


    result = setstropt(&data->set.str[STRING_SSL_EGDSOCKET],
                       va_arg(param, char *));
    break;
  case CURLOPT_MAXCONNECTS:


    data->set.maxconnects = va_arg(param, long);
    break;
  case CURLOPT_FORBID_REUSE:


    data->set.reuse_forbid = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_FRESH_CONNECT:


    data->set.reuse_fresh = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_VERBOSE:


    data->set.verbose = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_HEADER:


    data->set.include_header = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_NOPROGRESS:


    data->set.hide_progress = (0 != va_arg(param, long))?TRUE:FALSE;
    if(data->set.hide_progress)
      data->progress.flags |= PGRS_HIDE;
    else
      data->progress.flags &= ~PGRS_HIDE;
    break;
  case CURLOPT_NOBODY:


    data->set.opt_no_body = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_FAILONERROR:


    data->set.http_fail_on_error = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_UPLOAD:
  case CURLOPT_PUT:


    data->set.upload = (0 != va_arg(param, long))?TRUE:FALSE;
    if(data->set.upload) {

      data->set.httpreq = HTTPREQ_PUT;
      data->set.opt_no_body = FALSE;
    }
    else


      data->set.httpreq = HTTPREQ_GET;
    break;
  case CURLOPT_FILETIME:


    data->set.get_filetime = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_FTP_CREATE_MISSING_DIRS:


    switch(va_arg(param, long)) {
    case 0:
      data->set.ftp_create_missing_dirs = 0;
      break;
    case 1:
      data->set.ftp_create_missing_dirs = 1;
      break;
    case 2:
      data->set.ftp_create_missing_dirs = 2;
      break;
    default:

      result = CURLE_UNKNOWN_OPTION;
      break;
    }
    break;
  case CURLOPT_SERVER_RESPONSE_TIMEOUT:


    data->set.server_response_timeout = va_arg( param , long ) * 1000;
    break;
  case CURLOPT_TFTP_BLKSIZE:


    data->set.tftp_blksize = va_arg(param, long);
    break;
  case CURLOPT_DIRLISTONLY:


    data->set.ftp_list_only = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_APPEND:


    data->set.ftp_append = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_FTP_FILEMETHOD:


    data->set.ftp_filemethod = (curl_ftpfile)va_arg(param, long);
    break;
  case CURLOPT_NETRC:


    data->set.use_netrc = (enum CURL_NETRC_OPTION)va_arg(param, long);
    break;
  case CURLOPT_NETRC_FILE:


    result = setstropt(&data->set.str[STRING_NETRC_FILE],
                       va_arg(param, char *));
    break;
  case CURLOPT_TRANSFERTEXT:


    data->set.prefer_ascii = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_TIMECONDITION:


    data->set.timecondition = (curl_TimeCond)va_arg(param, long);
    break;
  case CURLOPT_TIMEVALUE:


    data->set.timevalue = (time_t)va_arg(param, long);
    break;
  case CURLOPT_SSLVERSION:


    data->set.ssl.version = va_arg(param, long);
    break;

#ifndef CURL_DISABLE_HTTP
  case CURLOPT_AUTOREFERER:


    data->set.http_auto_referer = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_ACCEPT_ENCODING:


    argptr = va_arg(param, char *);
    result = setstropt(&data->set.str[STRING_ENCODING],
                       (argptr && !*argptr)?
                       (char *) ALL_CONTENT_ENCODINGS: argptr);
    break;

  case CURLOPT_TRANSFER_ENCODING:
    data->set.http_transfer_encoding = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_FOLLOWLOCATION:


    data->set.http_follow_location = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_UNRESTRICTED_AUTH:


    data->set.http_disable_hostname_check_before_authentication =
      (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_MAXREDIRS:


    data->set.maxredirs = va_arg(param, long);
    break;

  case CURLOPT_POSTREDIR:
  {


    int postRedir = curlx_sltosi(va_arg(param, long));
    data->set.keep_post = postRedir & CURL_REDIR_POST_ALL;
  }
  break;

  case CURLOPT_POST:


    if(va_arg(param, long)) {
      data->set.httpreq = HTTPREQ_POST;
      data->set.opt_no_body = FALSE;
    }
    else
      data->set.httpreq = HTTPREQ_GET;
    break;

  case CURLOPT_COPYPOSTFIELDS:


    argptr = va_arg(param, char *);

    if(!argptr || data->set.postfieldsize == -1)
      result = setstropt(&data->set.str[STRING_COPYPOSTFIELDS], argptr);
    else {


      if((data->set.postfieldsize < 0) ||
         ((sizeof(curl_off_t) != sizeof(size_t)) &&
          (data->set.postfieldsize > (curl_off_t)((size_t)-1))))
        result = CURLE_OUT_OF_MEMORY;
      else {
        char * p;

        (void) setstropt(&data->set.str[STRING_COPYPOSTFIELDS], NULL);


        p = malloc((size_t)(data->set.postfieldsize?
                            data->set.postfieldsize:1));

        if(!p)
          result = CURLE_OUT_OF_MEMORY;
        else {
          if(data->set.postfieldsize)
            memcpy(p, argptr, (size_t)data->set.postfieldsize);

          data->set.str[STRING_COPYPOSTFIELDS] = p;
        }
      }
    }

    data->set.postfields = data->set.str[STRING_COPYPOSTFIELDS];
    data->set.httpreq = HTTPREQ_POST;
    break;

  case CURLOPT_POSTFIELDS:


    data->set.postfields = va_arg(param, void *);

    (void) setstropt(&data->set.str[STRING_COPYPOSTFIELDS], NULL);
    data->set.httpreq = HTTPREQ_POST;
    break;

  case CURLOPT_POSTFIELDSIZE:


    bigsize = va_arg(param, long);

    if(data->set.postfieldsize < bigsize &&
       data->set.postfields == data->set.str[STRING_COPYPOSTFIELDS]) {

      (void) setstropt(&data->set.str[STRING_COPYPOSTFIELDS], NULL);
      data->set.postfields = NULL;
    }

    data->set.postfieldsize = bigsize;
    break;

  case CURLOPT_POSTFIELDSIZE_LARGE:


    bigsize = va_arg(param, curl_off_t);

    if(data->set.postfieldsize < bigsize &&
       data->set.postfields == data->set.str[STRING_COPYPOSTFIELDS]) {

      (void) setstropt(&data->set.str[STRING_COPYPOSTFIELDS], NULL);
      data->set.postfields = NULL;
    }

    data->set.postfieldsize = bigsize;
    break;

  case CURLOPT_HTTPPOST:


    data->set.httppost = va_arg(param, struct curl_httppost *);
    data->set.httpreq = HTTPREQ_POST_FORM;
    data->set.opt_no_body = FALSE;
    break;

  case CURLOPT_REFERER:


    if(data->change.referer_alloc) {
      Curl_safefree(data->change.referer);
      data->change.referer_alloc = FALSE;
    }
    result = setstropt(&data->set.str[STRING_SET_REFERER],
                       va_arg(param, char *));
    data->change.referer = data->set.str[STRING_SET_REFERER];
    break;

  case CURLOPT_USERAGENT:


    result = setstropt(&data->set.str[STRING_USERAGENT],
                       va_arg(param, char *));
    break;

  case CURLOPT_HTTPHEADER:


    data->set.headers = va_arg(param, struct curl_slist *);
    break;

  case CURLOPT_PROXYHEADER:


    data->set.proxyheaders = va_arg(param, struct curl_slist *);
    break;

  case CURLOPT_HEADEROPT:


    arg = va_arg(param, long);
    data->set.sep_headers = (arg & CURLHEADER_SEPARATE)? TRUE: FALSE;
    break;

  case CURLOPT_HTTP200ALIASES:


    data->set.http200aliases = va_arg(param, struct curl_slist *);
    break;

#if !defined(CURL_DISABLE_COOKIES)
  case CURLOPT_COOKIE:


    result = setstropt(&data->set.str[STRING_COOKIE],
                       va_arg(param, char *));
    break;

  case CURLOPT_COOKIEFILE:


    argptr = (char *)va_arg(param, void *);
    if(argptr) {
      struct curl_slist *cl;


      cl = curl_slist_append(data->change.cookielist, argptr);
      if(!cl) {
        curl_slist_free_all(data->change.cookielist);
        data->change.cookielist = NULL;
        return CURLE_OUT_OF_MEMORY;
      }
      data->change.cookielist = cl;
    }
    break;

  case CURLOPT_COOKIEJAR:


  {
    struct CookieInfo *newcookies;
    result = setstropt(&data->set.str[STRING_COOKIEJAR],
                       va_arg(param, char *));


    newcookies = Curl_cookie_init(data, NULL, data->cookies,
                                  data->set.cookiesession);
    if(!newcookies)
      result = CURLE_OUT_OF_MEMORY;
    data->cookies = newcookies;
  }
    break;

  case CURLOPT_COOKIESESSION:


    data->set.cookiesession = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_COOKIELIST:
    argptr = va_arg(param, char *);

    if(argptr == NULL)
      break;

    if(Curl_raw_equal(argptr, "ALL")) {

      Curl_share_lock(data, CURL_LOCK_DATA_COOKIE, CURL_LOCK_ACCESS_SINGLE);
      Curl_cookie_clearall(data->cookies);
      Curl_share_unlock(data, CURL_LOCK_DATA_COOKIE);
    }
    else if(Curl_raw_equal(argptr, "SESS")) {

      Curl_share_lock(data, CURL_LOCK_DATA_COOKIE, CURL_LOCK_ACCESS_SINGLE);
      Curl_cookie_clearsess(data->cookies);
      Curl_share_unlock(data, CURL_LOCK_DATA_COOKIE);
    }
    else if(Curl_raw_equal(argptr, "FLUSH")) {

      Curl_flush_cookies(data, 0);
    }
    else if(Curl_raw_equal(argptr, "RELOAD")) {

      Curl_cookie_loadfiles(data);
      break;
    }
    else {
      if(!data->cookies)

        data->cookies = Curl_cookie_init(data, NULL, NULL, TRUE);

      argptr = strdup(argptr);
      if(!argptr || !data->cookies) {
        result = CURLE_OUT_OF_MEMORY;
        Curl_safefree(argptr);
      }
      else {
        Curl_share_lock(data, CURL_LOCK_DATA_COOKIE, CURL_LOCK_ACCESS_SINGLE);

        if(checkprefix("Set-Cookie:", argptr))

          Curl_cookie_add(data, data->cookies, TRUE, argptr + 11, NULL, NULL);

        else

          Curl_cookie_add(data, data->cookies, FALSE, argptr, NULL, NULL);

        Curl_share_unlock(data, CURL_LOCK_DATA_COOKIE);
        free(argptr);
      }
    }

    break;
#endif

  case CURLOPT_HTTPGET:


    if(va_arg(param, long)) {
      data->set.httpreq = HTTPREQ_GET;
      data->set.upload = FALSE;
      data->set.opt_no_body = FALSE;
    }
    break;

  case CURLOPT_HTTP_VERSION:


    arg = va_arg(param, long);
#ifndef USE_NGHTTP2
    if(arg == CURL_HTTP_VERSION_2_0)
      return CURLE_UNSUPPORTED_PROTOCOL;
#endif
    data->set.httpversion = arg;
    break;

  case CURLOPT_HTTPAUTH:


  {
    int bitcheck;
    bool authbits;
    unsigned long auth = va_arg(param, unsigned long);

    if(auth == CURLAUTH_NONE) {
      data->set.httpauth = auth;
      break;
    }


    data->state.authhost.iestyle = (auth & CURLAUTH_DIGEST_IE)?TRUE:FALSE;

    if(auth & CURLAUTH_DIGEST_IE) {
      auth |= CURLAUTH_DIGEST;
      auth &= ~CURLAUTH_DIGEST_IE;
    }


#ifndef USE_NTLM
    auth &= ~CURLAUTH_NTLM;
    auth &= ~CURLAUTH_NTLM_WB;
#elif !defined(NTLM_WB_ENABLED)
    auth &= ~CURLAUTH_NTLM_WB;
#endif
#ifndef USE_SPNEGO
    auth &= ~CURLAUTH_NEGOTIATE;

#endif


    bitcheck = 0;
    authbits = FALSE;
    while(bitcheck < 31) {
      if(auth & (1UL << bitcheck++)) {
        authbits = TRUE;
        break;
      }
    }
    if(!authbits)
      return CURLE_NOT_BUILT_IN;

    data->set.httpauth = auth;
  }
  break;

  case CURLOPT_EXPECT_100_TIMEOUT_MS:


    data->set.expect_100_timeout = va_arg(param, long);
    break;

#endif

  case CURLOPT_CUSTOMREQUEST:


    result = setstropt(&data->set.str[STRING_CUSTOMREQUEST],
                       va_arg(param, char *));


    break;

#ifndef CURL_DISABLE_PROXY
  case CURLOPT_HTTPPROXYTUNNEL:


    data->set.tunnel_thru_httpproxy = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_PROXYPORT:


    data->set.proxyport = va_arg(param, long);
    break;

  case CURLOPT_PROXYAUTH:


  {
    int bitcheck;
    bool authbits;
    unsigned long auth = va_arg(param, unsigned long);

    if(auth == CURLAUTH_NONE) {
      data->set.proxyauth = auth;
      break;
    }


    data->state.authproxy.iestyle = (auth & CURLAUTH_DIGEST_IE)?TRUE:FALSE;

    if(auth & CURLAUTH_DIGEST_IE) {
      auth |= CURLAUTH_DIGEST;
      auth &= ~CURLAUTH_DIGEST_IE;
    }

#ifndef USE_NTLM
    auth &= ~CURLAUTH_NTLM;
    auth &= ~CURLAUTH_NTLM_WB;
#elif !defined(NTLM_WB_ENABLED)
    auth &= ~CURLAUTH_NTLM_WB;
#endif
#ifndef USE_SPNEGO
    auth &= ~CURLAUTH_NEGOTIATE;

#endif


    bitcheck = 0;
    authbits = FALSE;
    while(bitcheck < 31) {
      if(auth & (1UL << bitcheck++)) {
        authbits = TRUE;
        break;
      }
    }
    if(!authbits)
      return CURLE_NOT_BUILT_IN;

    data->set.proxyauth = auth;
  }
  break;

  case CURLOPT_PROXY:


    result = setstropt(&data->set.str[STRING_PROXY],
                       va_arg(param, char *));
    break;

  case CURLOPT_PROXYTYPE:


    data->set.proxytype = (curl_proxytype)va_arg(param, long);
    break;

  case CURLOPT_PROXY_TRANSFER_MODE:


    switch (va_arg(param, long)) {
    case 0:
      data->set.proxy_transfer_mode = FALSE;
      break;
    case 1:
      data->set.proxy_transfer_mode = TRUE;
      break;
    default:

      result = CURLE_UNKNOWN_OPTION;
      break;
    }
    break;
#endif

#if defined(HAVE_GSSAPI) || defined(USE_WINDOWS_SSPI)
  case CURLOPT_SOCKS5_GSSAPI_SERVICE:


    result = setstropt(&data->set.str[STRING_SOCKS5_GSSAPI_SERVICE],
                       va_arg(param, char *));
    break;

  case CURLOPT_SOCKS5_GSSAPI_NEC:


    data->set.socks5_gssapi_nec = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
#endif

  case CURLOPT_HEADERDATA:


    data->set.writeheader = (void *)va_arg(param, void *);
    break;
  case CURLOPT_ERRORBUFFER:


    data->set.errorbuffer = va_arg(param, char *);
    break;
  case CURLOPT_WRITEDATA:


    data->set.out = va_arg(param, void *);
    break;
  case CURLOPT_FTPPORT:


    result = setstropt(&data->set.str[STRING_FTPPORT],
                       va_arg(param, char *));
    data->set.ftp_use_port = (NULL != data->set.str[STRING_FTPPORT]) ?
                             TRUE:FALSE;
    break;

  case CURLOPT_FTP_USE_EPRT:
    data->set.ftp_use_eprt = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_FTP_USE_EPSV:
    data->set.ftp_use_epsv = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_FTP_USE_PRET:
    data->set.ftp_use_pret = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_FTP_SSL_CCC:
    data->set.ftp_ccc = (curl_ftpccc)va_arg(param, long);
    break;

  case CURLOPT_FTP_SKIP_PASV_IP:


    data->set.ftp_skip_ip = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_READDATA:


    data->set.in = va_arg(param, void *);
    break;
  case CURLOPT_INFILESIZE:


    data->set.filesize = va_arg(param, long);
    break;
  case CURLOPT_INFILESIZE_LARGE:


    data->set.filesize = va_arg(param, curl_off_t);
    break;
  case CURLOPT_LOW_SPEED_LIMIT:


    data->set.low_speed_limit=va_arg(param, long);
    break;
  case CURLOPT_MAX_SEND_SPEED_LARGE:


    data->set.max_send_speed=va_arg(param, curl_off_t);
    break;
  case CURLOPT_MAX_RECV_SPEED_LARGE:


    data->set.max_recv_speed=va_arg(param, curl_off_t);
    break;
  case CURLOPT_LOW_SPEED_TIME:


    data->set.low_speed_time=va_arg(param, long);
    break;
  case CURLOPT_URL:


    if(data->change.url_alloc) {

      Curl_safefree(data->change.url);
      data->change.url_alloc = FALSE;
    }
    result = setstropt(&data->set.str[STRING_SET_URL],
                       va_arg(param, char *));
    data->change.url = data->set.str[STRING_SET_URL];
    break;
  case CURLOPT_PORT:


    data->set.use_port = va_arg(param, long);
    break;
  case CURLOPT_TIMEOUT:


    data->set.timeout = va_arg(param, long) * 1000L;
    break;

  case CURLOPT_TIMEOUT_MS:
    data->set.timeout = va_arg(param, long);
    break;

  case CURLOPT_CONNECTTIMEOUT:


    data->set.connecttimeout = va_arg(param, long) * 1000L;
    break;

  case CURLOPT_CONNECTTIMEOUT_MS:
    data->set.connecttimeout = va_arg(param, long);
    break;

  case CURLOPT_ACCEPTTIMEOUT_MS:


    data->set.accepttimeout = va_arg(param, long);
    break;

  case CURLOPT_USERPWD:


    result = setstropt_userpwd(va_arg(param, char *),
                               &data->set.str[STRING_USERNAME],
                               &data->set.str[STRING_PASSWORD]);
    break;

  case CURLOPT_USERNAME:


    result = setstropt(&data->set.str[STRING_USERNAME],
                       va_arg(param, char *));
    break;

  case CURLOPT_PASSWORD:


    result = setstropt(&data->set.str[STRING_PASSWORD],
                       va_arg(param, char *));
    break;

  case CURLOPT_LOGIN_OPTIONS:


    result = setstropt(&data->set.str[STRING_OPTIONS],
                       va_arg(param, char *));
    break;

  case CURLOPT_XOAUTH2_BEARER:


    result = setstropt(&data->set.str[STRING_BEARER],
                       va_arg(param, char *));
    break;

  case CURLOPT_POSTQUOTE:


    data->set.postquote = va_arg(param, struct curl_slist *);
    break;
  case CURLOPT_PREQUOTE:


    data->set.prequote = va_arg(param, struct curl_slist *);
    break;
  case CURLOPT_QUOTE:


    data->set.quote = va_arg(param, struct curl_slist *);
    break;
  case CURLOPT_RESOLVE:


    data->set.resolve = va_arg(param, struct curl_slist *);
    data->change.resolve = data->set.resolve;
    break;
  case CURLOPT_PROGRESSFUNCTION:


    data->set.fprogress = va_arg(param, curl_progress_callback);
    if(data->set.fprogress)
      data->progress.callback = TRUE;
    else
      data->progress.callback = FALSE;
    break;

  case CURLOPT_XFERINFOFUNCTION:


    data->set.fxferinfo = va_arg(param, curl_xferinfo_callback);
    if(data->set.fxferinfo)
      data->progress.callback = TRUE;
    else
      data->progress.callback = FALSE;

    break;

  case CURLOPT_PROGRESSDATA:


    data->set.progress_client = va_arg(param, void *);
    break;

#ifndef CURL_DISABLE_PROXY
  case CURLOPT_PROXYUSERPWD:


    result = setstropt_userpwd(va_arg(param, char *),
                               &data->set.str[STRING_PROXYUSERNAME],
                               &data->set.str[STRING_PROXYPASSWORD]);
    break;
  case CURLOPT_PROXYUSERNAME:


    result = setstropt(&data->set.str[STRING_PROXYUSERNAME],
                       va_arg(param, char *));
    break;
  case CURLOPT_PROXYPASSWORD:


    result = setstropt(&data->set.str[STRING_PROXYPASSWORD],
                       va_arg(param, char *));
    break;
  case CURLOPT_NOPROXY:


    result = setstropt(&data->set.str[STRING_NOPROXY],
                       va_arg(param, char *));
    break;
#endif

  case CURLOPT_RANGE:


    result = setstropt(&data->set.str[STRING_SET_RANGE],
                       va_arg(param, char *));
    break;
  case CURLOPT_RESUME_FROM:


    data->set.set_resume_from = va_arg(param, long);
    break;
  case CURLOPT_RESUME_FROM_LARGE:


    data->set.set_resume_from = va_arg(param, curl_off_t);
    break;
  case CURLOPT_DEBUGFUNCTION:


    data->set.fdebug = va_arg(param, curl_debug_callback);


    break;
  case CURLOPT_DEBUGDATA:


    data->set.debugdata = va_arg(param, void *);
    break;
  case CURLOPT_STDERR:


    data->set.err = va_arg(param, FILE *);
    if(!data->set.err)
      data->set.err = stderr;
    break;
  case CURLOPT_HEADERFUNCTION:


    data->set.fwrite_header = va_arg(param, curl_write_callback);
    break;
  case CURLOPT_WRITEFUNCTION:


    data->set.fwrite_func = va_arg(param, curl_write_callback);
    if(!data->set.fwrite_func) {
      data->set.is_fwrite_set = 0;

      data->set.fwrite_func = (curl_write_callback)fwrite;
    }
    else
      data->set.is_fwrite_set = 1;
    break;
  case CURLOPT_READFUNCTION:


    data->set.fread_func = va_arg(param, curl_read_callback);
    if(!data->set.fread_func) {
      data->set.is_fread_set = 0;

      data->set.fread_func = (curl_read_callback)fread;
    }
    else
      data->set.is_fread_set = 1;
    break;
  case CURLOPT_SEEKFUNCTION:


    data->set.seek_func = va_arg(param, curl_seek_callback);
    break;
  case CURLOPT_SEEKDATA:


    data->set.seek_client = va_arg(param, void *);
    break;
  case CURLOPT_CONV_FROM_NETWORK_FUNCTION:


    data->set.convfromnetwork = va_arg(param, curl_conv_callback);
    break;
  case CURLOPT_CONV_TO_NETWORK_FUNCTION:


    data->set.convtonetwork = va_arg(param, curl_conv_callback);
    break;
  case CURLOPT_CONV_FROM_UTF8_FUNCTION:


    data->set.convfromutf8 = va_arg(param, curl_conv_callback);
    break;
  case CURLOPT_IOCTLFUNCTION:


    data->set.ioctl_func = va_arg(param, curl_ioctl_callback);
    break;
  case CURLOPT_IOCTLDATA:


    data->set.ioctl_client = va_arg(param, void *);
    break;
  case CURLOPT_SSLCERT:


    result = setstropt(&data->set.str[STRING_CERT],
                       va_arg(param, char *));
    break;
  case CURLOPT_SSLCERTTYPE:


    result = setstropt(&data->set.str[STRING_CERT_TYPE],
                       va_arg(param, char *));
    break;
  case CURLOPT_SSLKEY:


    result = setstropt(&data->set.str[STRING_KEY],
                       va_arg(param, char *));
    break;
  case CURLOPT_SSLKEYTYPE:


    result = setstropt(&data->set.str[STRING_KEY_TYPE],
                       va_arg(param, char *));
    break;
  case CURLOPT_KEYPASSWD:


    result = setstropt(&data->set.str[STRING_KEY_PASSWD],
                       va_arg(param, char *));
    break;
  case CURLOPT_SSLENGINE:


    argptr = va_arg(param, char *);
    if(argptr && argptr[0])
      result = Curl_ssl_set_engine(data, argptr);
    break;

  case CURLOPT_SSLENGINE_DEFAULT:


    result = Curl_ssl_set_engine_default(data);
    break;
  case CURLOPT_CRLF:


    data->set.crlf = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_INTERFACE:


    result = setstropt(&data->set.str[STRING_DEVICE],
                       va_arg(param, char *));
    break;
  case CURLOPT_LOCALPORT:


    data->set.localport = curlx_sltous(va_arg(param, long));
    break;
  case CURLOPT_LOCALPORTRANGE:


    data->set.localportrange = curlx_sltosi(va_arg(param, long));
    break;
  case CURLOPT_KRBLEVEL:


    result = setstropt(&data->set.str[STRING_KRB_LEVEL],
                       va_arg(param, char *));
    data->set.krb = (NULL != data->set.str[STRING_KRB_LEVEL])?TRUE:FALSE;
    break;
  case CURLOPT_GSSAPI_DELEGATION:


    data->set.gssapi_delegation = va_arg(param, long);
    break;
  case CURLOPT_SSL_VERIFYPEER:


    data->set.ssl.verifypeer = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_SSL_VERIFYHOST:


    arg = va_arg(param, long);


    if(1 == arg) {
      failf(data, "CURLOPT_SSL_VERIFYHOST no longer supports 1 as value!");
      return CURLE_BAD_FUNCTION_ARGUMENT;
    }

    data->set.ssl.verifyhost = (0 != arg)?TRUE:FALSE;
    break;
  case CURLOPT_SSL_CTX_FUNCTION:
#ifdef have_curlssl_ssl_ctx


    data->set.ssl.fsslctx = va_arg(param, curl_ssl_ctx_callback);
#else
    result = CURLE_NOT_BUILT_IN;
#endif
    break;
  case CURLOPT_SSL_CTX_DATA:
#ifdef have_curlssl_ssl_ctx


    data->set.ssl.fsslctxp = va_arg(param, void *);
#else
    result = CURLE_NOT_BUILT_IN;
#endif
    break;
  case CURLOPT_CERTINFO:
#ifdef have_curlssl_certinfo
    data->set.ssl.certinfo = (0 != va_arg(param, long))?TRUE:FALSE;
#else
    result = CURLE_NOT_BUILT_IN;
#endif
    break;
  case CURLOPT_PINNEDPUBLICKEY:


    result = setstropt(&data->set.str[STRING_SSL_PINNEDPUBLICKEY],
                       va_arg(param, char *));
    break;
  case CURLOPT_CAINFO:


    result = setstropt(&data->set.str[STRING_SSL_CAFILE],
                       va_arg(param, char *));
    break;
  case CURLOPT_CAPATH:
#ifdef have_curlssl_ca_path


    result = setstropt(&data->set.str[STRING_SSL_CAPATH],
                       va_arg(param, char *));
#else
    result = CURLE_NOT_BUILT_IN;
#endif
    break;
  case CURLOPT_CRLFILE:


    result = setstropt(&data->set.str[STRING_SSL_CRLFILE],
                       va_arg(param, char *));
    break;
  case CURLOPT_ISSUERCERT:


    result = setstropt(&data->set.str[STRING_SSL_ISSUERCERT],
                       va_arg(param, char *));
    break;
  case CURLOPT_TELNETOPTIONS:


    data->set.telnet_options = va_arg(param, struct curl_slist *);
    break;

  case CURLOPT_BUFFERSIZE:


    data->set.buffer_size = va_arg(param, long);

    if((data->set.buffer_size> (BUFSIZE -1 )) ||
       (data->set.buffer_size < 1))
      data->set.buffer_size = 0;

    break;

  case CURLOPT_NOSIGNAL:


    data->set.no_signal = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_SHARE:
  {
    struct Curl_share *set;
    set = va_arg(param, struct Curl_share *);


    if(data->share) {
      Curl_share_lock(data, CURL_LOCK_DATA_SHARE, CURL_LOCK_ACCESS_SINGLE);

      if(data->dns.hostcachetype == HCACHE_SHARED) {
        data->dns.hostcache = NULL;
        data->dns.hostcachetype = HCACHE_NONE;
      }

#if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_COOKIES)
      if(data->share->cookies == data->cookies)
        data->cookies = NULL;
#endif

      if(data->share->sslsession == data->state.session)
        data->state.session = NULL;

      data->share->dirty--;

      Curl_share_unlock(data, CURL_LOCK_DATA_SHARE);
      data->share = NULL;
    }


    data->share = set;
    if(data->share) {

      Curl_share_lock(data, CURL_LOCK_DATA_SHARE, CURL_LOCK_ACCESS_SINGLE);

      data->share->dirty++;

      if(data->share->hostcache) {

        data->dns.hostcache = data->share->hostcache;
        data->dns.hostcachetype = HCACHE_SHARED;
      }
#if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_COOKIES)
      if(data->share->cookies) {

        if(data->cookies)
          Curl_cookie_cleanup(data->cookies);

        data->cookies = data->share->cookies;
      }
#endif
      if(data->share->sslsession) {
        data->set.ssl.max_ssl_sessions = data->share->max_ssl_sessions;
        data->state.session = data->share->sslsession;
      }
      Curl_share_unlock(data, CURL_LOCK_DATA_SHARE);

    }


  }
  break;

  case CURLOPT_PRIVATE:


    data->set.private_data = va_arg(param, void *);
    break;

  case CURLOPT_MAXFILESIZE:


    data->set.max_filesize = va_arg(param, long);
    break;

#ifdef USE_SSL
  case CURLOPT_USE_SSL:


    data->set.use_ssl = (curl_usessl)va_arg(param, long);
    break;

  case CURLOPT_SSL_OPTIONS:
    arg = va_arg(param, long);
    data->set.ssl_enable_beast = arg&CURLSSLOPT_ALLOW_BEAST?TRUE:FALSE;
    break;

#endif
  case CURLOPT_FTPSSLAUTH:


    data->set.ftpsslauth = (curl_ftpauth)va_arg(param, long);
    break;

  case CURLOPT_IPRESOLVE:
    data->set.ipver = va_arg(param, long);
    break;

  case CURLOPT_MAXFILESIZE_LARGE:


    data->set.max_filesize = va_arg(param, curl_off_t);
    break;

  case CURLOPT_TCP_NODELAY:


    data->set.tcp_nodelay = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_FTP_ACCOUNT:
    result = setstropt(&data->set.str[STRING_FTP_ACCOUNT],
                       va_arg(param, char *));
    break;

  case CURLOPT_IGNORE_CONTENT_LENGTH:
    data->set.ignorecl = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_CONNECT_ONLY:


    data->set.connect_only = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_FTP_ALTERNATIVE_TO_USER:
    result = setstropt(&data->set.str[STRING_FTP_ALTERNATIVE_TO_USER],
                       va_arg(param, char *));
    break;

  case CURLOPT_SOCKOPTFUNCTION:


    data->set.fsockopt = va_arg(param, curl_sockopt_callback);
    break;

  case CURLOPT_SOCKOPTDATA:


    data->set.sockopt_client = va_arg(param, void *);
    break;

  case CURLOPT_OPENSOCKETFUNCTION:


    data->set.fopensocket = va_arg(param, curl_opensocket_callback);
    break;

  case CURLOPT_OPENSOCKETDATA:


    data->set.opensocket_client = va_arg(param, void *);
    break;

  case CURLOPT_CLOSESOCKETFUNCTION:


    data->set.fclosesocket = va_arg(param, curl_closesocket_callback);
    break;

  case CURLOPT_CLOSESOCKETDATA:


    data->set.closesocket_client = va_arg(param, void *);
    break;

  case CURLOPT_SSL_SESSIONID_CACHE:
    data->set.ssl.sessionid = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

#ifdef USE_LIBSSH2

  case CURLOPT_SSH_AUTH_TYPES:
    data->set.ssh_auth_types = va_arg(param, long);
    break;

  case CURLOPT_SSH_PUBLIC_KEYFILE:


    result = setstropt(&data->set.str[STRING_SSH_PUBLIC_KEY],
                       va_arg(param, char *));
    break;

  case CURLOPT_SSH_PRIVATE_KEYFILE:


    result = setstropt(&data->set.str[STRING_SSH_PRIVATE_KEY],
                       va_arg(param, char *));
    break;
  case CURLOPT_SSH_HOST_PUBLIC_KEY_MD5:


    result = setstropt(&data->set.str[STRING_SSH_HOST_PUBLIC_KEY_MD5],
                       va_arg(param, char *));
    break;
#ifdef HAVE_LIBSSH2_KNOWNHOST_API
  case CURLOPT_SSH_KNOWNHOSTS:


    result = setstropt(&data->set.str[STRING_SSH_KNOWNHOSTS],
                       va_arg(param, char *));
    break;

  case CURLOPT_SSH_KEYFUNCTION:


    data->set.ssh_keyfunc = va_arg(param, curl_sshkeycallback);
    break;

  case CURLOPT_SSH_KEYDATA:


    data->set.ssh_keyfunc_userp = va_arg(param, void *);
    break;
#endif

#endif

  case CURLOPT_HTTP_TRANSFER_DECODING:


    data->set.http_te_skip = (0 == va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_HTTP_CONTENT_DECODING:


    data->set.http_ce_skip = (0 == va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_NEW_FILE_PERMS:


    data->set.new_file_perms = va_arg(param, long);
    break;

  case CURLOPT_NEW_DIRECTORY_PERMS:


    data->set.new_directory_perms = va_arg(param, long);
    break;

  case CURLOPT_ADDRESS_SCOPE:


    data->set.scope_id = curlx_sltoui(va_arg(param, long));
    break;

  case CURLOPT_PROTOCOLS:


    data->set.allowed_protocols = va_arg(param, long);
    break;

  case CURLOPT_REDIR_PROTOCOLS:


    data->set.redir_protocols = va_arg(param, long);
    break;

  case CURLOPT_MAIL_FROM:

    result = setstropt(&data->set.str[STRING_MAIL_FROM],
                       va_arg(param, char *));
    break;

  case CURLOPT_MAIL_AUTH:

    result = setstropt(&data->set.str[STRING_MAIL_AUTH],
                       va_arg(param, char *));
    break;

  case CURLOPT_MAIL_RCPT:

    data->set.mail_rcpt = va_arg(param, struct curl_slist *);
    break;

  case CURLOPT_SASL_IR:

    data->set.sasl_ir = (0 != va_arg(param, long)) ? TRUE : FALSE;
    break;

  case CURLOPT_RTSP_REQUEST:
    {


      long curl_rtspreq = va_arg(param, long);
      Curl_RtspReq rtspreq = RTSPREQ_NONE;
      switch(curl_rtspreq) {
        case CURL_RTSPREQ_OPTIONS:
          rtspreq = RTSPREQ_OPTIONS;
          break;

        case CURL_RTSPREQ_DESCRIBE:
          rtspreq = RTSPREQ_DESCRIBE;
          break;

        case CURL_RTSPREQ_ANNOUNCE:
          rtspreq = RTSPREQ_ANNOUNCE;
          break;

        case CURL_RTSPREQ_SETUP:
          rtspreq = RTSPREQ_SETUP;
          break;

        case CURL_RTSPREQ_PLAY:
          rtspreq = RTSPREQ_PLAY;
          break;

        case CURL_RTSPREQ_PAUSE:
          rtspreq = RTSPREQ_PAUSE;
          break;

        case CURL_RTSPREQ_TEARDOWN:
          rtspreq = RTSPREQ_TEARDOWN;
          break;

        case CURL_RTSPREQ_GET_PARAMETER:
          rtspreq = RTSPREQ_GET_PARAMETER;
          break;

        case CURL_RTSPREQ_SET_PARAMETER:
          rtspreq = RTSPREQ_SET_PARAMETER;
          break;

        case CURL_RTSPREQ_RECORD:
          rtspreq = RTSPREQ_RECORD;
          break;

        case CURL_RTSPREQ_RECEIVE:
          rtspreq = RTSPREQ_RECEIVE;
          break;
        default:
          rtspreq = RTSPREQ_NONE;
      }

      data->set.rtspreq = rtspreq;
    break;
    }


  case CURLOPT_RTSP_SESSION_ID:


    result = setstropt(&data->set.str[STRING_RTSP_SESSION_ID],
                       va_arg(param, char *));
    break;

  case CURLOPT_RTSP_STREAM_URI:


    result = setstropt(&data->set.str[STRING_RTSP_STREAM_URI],
                       va_arg(param, char *));
    break;

  case CURLOPT_RTSP_TRANSPORT:


    result = setstropt(&data->set.str[STRING_RTSP_TRANSPORT],
                       va_arg(param, char *));
    break;

  case CURLOPT_RTSP_CLIENT_CSEQ:


    data->state.rtsp_next_client_CSeq = va_arg(param, long);
    break;

  case CURLOPT_RTSP_SERVER_CSEQ:

    data->state.rtsp_next_client_CSeq = va_arg(param, long);
    break;

  case CURLOPT_INTERLEAVEDATA:
    data->set.rtp_out = va_arg(param, void *);
    break;
  case CURLOPT_INTERLEAVEFUNCTION:

    data->set.fwrite_rtp = va_arg(param, curl_write_callback);
    break;

  case CURLOPT_WILDCARDMATCH:
    data->set.wildcardmatch = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_CHUNK_BGN_FUNCTION:
    data->set.chunk_bgn = va_arg(param, curl_chunk_bgn_callback);
    break;
  case CURLOPT_CHUNK_END_FUNCTION:
    data->set.chunk_end = va_arg(param, curl_chunk_end_callback);
    break;
  case CURLOPT_FNMATCH_FUNCTION:
    data->set.fnmatch = va_arg(param, curl_fnmatch_callback);
    break;
  case CURLOPT_CHUNK_DATA:
    data->wildcard.customptr = va_arg(param, void *);
    break;
  case CURLOPT_FNMATCH_DATA:
    data->set.fnmatch_data = va_arg(param, void *);
    break;
#ifdef USE_TLS_SRP
  case CURLOPT_TLSAUTH_USERNAME:
    result = setstropt(&data->set.str[STRING_TLSAUTH_USERNAME],
                       va_arg(param, char *));
    if(data->set.str[STRING_TLSAUTH_USERNAME] && !data->set.ssl.authtype)
      data->set.ssl.authtype = CURL_TLSAUTH_SRP;
    break;
  case CURLOPT_TLSAUTH_PASSWORD:
    result = setstropt(&data->set.str[STRING_TLSAUTH_PASSWORD],
                       va_arg(param, char *));
    if(data->set.str[STRING_TLSAUTH_USERNAME] && !data->set.ssl.authtype)
      data->set.ssl.authtype = CURL_TLSAUTH_SRP;
    break;
  case CURLOPT_TLSAUTH_TYPE:
    if(strnequal((char *)va_arg(param, char *), "SRP", strlen("SRP")))
      data->set.ssl.authtype = CURL_TLSAUTH_SRP;
    else
      data->set.ssl.authtype = CURL_TLSAUTH_NONE;
    break;
#endif
  case CURLOPT_DNS_SERVERS:
    result = Curl_set_dns_servers(data, va_arg(param, char *));
    break;
  case CURLOPT_DNS_INTERFACE:
    result = Curl_set_dns_interface(data, va_arg(param, char *));
    break;
  case CURLOPT_DNS_LOCAL_IP4:
    result = Curl_set_dns_local_ip4(data, va_arg(param, char *));
    break;
  case CURLOPT_DNS_LOCAL_IP6:
    result = Curl_set_dns_local_ip6(data, va_arg(param, char *));
    break;

  case CURLOPT_TCP_KEEPALIVE:
    data->set.tcp_keepalive = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_TCP_KEEPIDLE:
    data->set.tcp_keepidle = va_arg(param, long);
    break;
  case CURLOPT_TCP_KEEPINTVL:
    data->set.tcp_keepintvl = va_arg(param, long);
    break;
  case CURLOPT_SSL_ENABLE_NPN:
    data->set.ssl_enable_npn = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_SSL_ENABLE_ALPN:
    data->set.ssl_enable_alpn = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

#ifdef USE_UNIX_SOCKETS
  case CURLOPT_UNIX_SOCKET_PATH:
    result = setstropt(&data->set.str[STRING_UNIX_SOCKET_PATH],
                       va_arg(param, char *));
    break;
#endif

  default:

    result = CURLE_UNKNOWN_OPTION;
    break;
  }

  return result;
}
