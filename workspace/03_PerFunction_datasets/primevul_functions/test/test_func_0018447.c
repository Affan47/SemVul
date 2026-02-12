CURLcode Curl_init_userdefined(struct UserDefined *set)
{
  CURLcode result = CURLE_OK;

  set->out = stdout;
  set->in  = stdin;
  set->err  = stderr;


  set->fwrite_func = (curl_write_callback)fwrite;


  set->fread_func = (curl_read_callback)fread;
  set->is_fread_set = 0;
  set->is_fwrite_set = 0;

  set->seek_func = ZERO_NULL;
  set->seek_client = ZERO_NULL;


  set->convfromnetwork = ZERO_NULL;
  set->convtonetwork   = ZERO_NULL;
  set->convfromutf8    = ZERO_NULL;

  set->filesize = -1;
  set->postfieldsize = -1;
  set->maxredirs = -1;

  set->httpreq = HTTPREQ_GET;
  set->rtspreq = RTSPREQ_OPTIONS;
  set->ftp_use_epsv = TRUE;
  set->ftp_use_eprt = TRUE;
  set->ftp_use_pret = FALSE;
  set->ftp_filemethod = FTPFILE_MULTICWD;

  set->dns_cache_timeout = 60;


  set->ssl.max_ssl_sessions = 5;

  set->proxyport = CURL_DEFAULT_PROXY_PORT;
  set->proxytype = CURLPROXY_HTTP;
  set->httpauth = CURLAUTH_BASIC;
  set->proxyauth = CURLAUTH_BASIC;


  set->hide_progress = TRUE;


  set->ssl.verifypeer = TRUE;
  set->ssl.verifyhost = TRUE;
#ifdef USE_TLS_SRP
  set->ssl.authtype = CURL_TLSAUTH_NONE;
#endif
  set->ssh_auth_types = CURLSSH_AUTH_DEFAULT;

  set->ssl.sessionid = TRUE;

  set->new_file_perms = 0644;
  set->new_directory_perms = 0755;


  set->allowed_protocols = CURLPROTO_ALL;
  set->redir_protocols = CURLPROTO_ALL &
                          ~(CURLPROTO_FILE | CURLPROTO_SCP | CURLPROTO_SMB |
                            CURLPROTO_SMBS);

#if defined(HAVE_GSSAPI) || defined(USE_WINDOWS_SSPI)


  set->socks5_gssapi_nec = FALSE;

  result = setstropt(&set->str[STRING_SOCKS5_GSSAPI_SERVICE],
                     (char *) CURL_DEFAULT_SOCKS5_GSSAPI_SERVICE);
  if(result)
    return result;
#endif


#if defined(CURL_CA_BUNDLE)
  result = setstropt(&set->str[STRING_SSL_CAFILE], (char *) CURL_CA_BUNDLE);
#elif defined(CURL_CA_PATH)
  result = setstropt(&set->str[STRING_SSL_CAPATH], (char *) CURL_CA_PATH);
#endif

  set->wildcardmatch  = FALSE;
  set->chunk_bgn      = ZERO_NULL;
  set->chunk_end      = ZERO_NULL;


  set->tcp_keepalive = FALSE;
  set->tcp_keepintvl = 60;
  set->tcp_keepidle = 60;

  set->ssl_enable_npn = TRUE;
  set->ssl_enable_alpn = TRUE;

  set->expect_100_timeout = 1000L;
  return result;
}
