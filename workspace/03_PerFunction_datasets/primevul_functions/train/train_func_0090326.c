static CURLcode transfer_per_config(struct GlobalConfig *global,
                                    struct OperationConfig *config,
                                    CURLSH *share,
                                    bool *added)
{
  CURLcode result = CURLE_OK;
  bool capath_from_env;
  *added = FALSE;


  if(!config->url_list || !config->url_list->url) {
    helpf(global->errors, "no URL specified!\n");
    return CURLE_FAILED_INIT;
  }


  capath_from_env = false;
  if(!config->cacert &&
     !config->capath &&
     (!config->insecure_ok || (config->doh_url && !config->doh_insecure_ok))) {
    CURL *curltls = curl_easy_init();
    struct curl_tlssessioninfo *tls_backend_info = NULL;


    result = curl_easy_getinfo(curltls, CURLINFO_TLS_SSL_PTR,
                               &tls_backend_info);
    if(result)
      return result;


    if(tls_backend_info->backend != CURLSSLBACKEND_SCHANNEL) {
      char *env;
      env = curlx_getenv("CURL_CA_BUNDLE");
      if(env) {
        config->cacert = strdup(env);
        if(!config->cacert) {
          curl_free(env);
          errorf(global, "out of memory\n");
          return CURLE_OUT_OF_MEMORY;
        }
      }
      else {
        env = curlx_getenv("SSL_CERT_DIR");
        if(env) {
          config->capath = strdup(env);
          if(!config->capath) {
            curl_free(env);
            helpf(global->errors, "out of memory\n");
            return CURLE_OUT_OF_MEMORY;
          }
          capath_from_env = true;
        }
        else {
          env = curlx_getenv("SSL_CERT_FILE");
          if(env) {
            config->cacert = strdup(env);
            if(!config->cacert) {
              curl_free(env);
              errorf(global, "out of memory\n");
              return CURLE_OUT_OF_MEMORY;
            }
          }
        }
      }

      if(env)
        curl_free(env);
#ifdef WIN32
      else {
        result = FindWin32CACert(config, tls_backend_info->backend,
                                 TEXT("curl-ca-bundle.crt"));
      }
#endif
    }
    curl_easy_cleanup(curltls);
  }

  if(!result)
    result = single_transfer(global, config, share, capath_from_env, added);

  return result;
}
