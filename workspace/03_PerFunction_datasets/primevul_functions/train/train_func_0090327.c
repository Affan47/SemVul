CURLcode operate(struct GlobalConfig *global, int argc, argv_item_t argv[])
{
  CURLcode result = CURLE_OK;
  char *first_arg = argc > 1 ? curlx_convert_tchar_to_UTF8(argv[1]) : NULL;


#ifdef HAVE_SETLOCALE
  setlocale(LC_ALL, "");
#endif


  if((argc == 1) ||
     (first_arg && strncmp(first_arg, "-q", 2) &&
      !curl_strequal(first_arg, "--disable"))) {
    parseconfig(NULL, global);


    if((argc < 2) && (!global->first->url_list)) {
      helpf(global->errors, NULL);
      result = CURLE_FAILED_INIT;
    }
  }

  curlx_unicodefree(first_arg);

  if(!result) {

    ParameterError res = parse_args(global, argc, argv);
    if(res) {
      result = CURLE_OK;


      if(res == PARAM_HELP_REQUESTED)
        tool_help(global->help_category);

      else if(res == PARAM_MANUAL_REQUESTED)
        hugehelp();

      else if(res == PARAM_VERSION_INFO_REQUESTED)
        tool_version_info();

      else if(res == PARAM_ENGINES_REQUESTED)
        tool_list_engines();
      else if(res == PARAM_LIBCURL_UNSUPPORTED_PROTOCOL)
        result = CURLE_UNSUPPORTED_PROTOCOL;
      else if(res == PARAM_READ_ERROR)
        result = CURLE_READ_ERROR;
      else
        result = CURLE_FAILED_INIT;
    }
    else {
#ifndef CURL_DISABLE_LIBCURL_OPTION
      if(global->libcurl) {

        result = easysrc_init();
      }
#endif


      if(!result) {
        size_t count = 0;
        struct OperationConfig *operation = global->first;
        CURLSH *share = curl_share_init();
        if(!share) {
#ifndef CURL_DISABLE_LIBCURL_OPTION
          if(global->libcurl) {

            easysrc_cleanup();
          }
#endif
          return CURLE_OUT_OF_MEMORY;
        }

        curl_share_setopt(share, CURLSHOPT_SHARE, CURL_LOCK_DATA_COOKIE);
        curl_share_setopt(share, CURLSHOPT_SHARE, CURL_LOCK_DATA_DNS);
        curl_share_setopt(share, CURLSHOPT_SHARE, CURL_LOCK_DATA_SSL_SESSION);
        curl_share_setopt(share, CURLSHOPT_SHARE, CURL_LOCK_DATA_CONNECT);
        curl_share_setopt(share, CURLSHOPT_SHARE, CURL_LOCK_DATA_PSL);


        do {
          result = get_args(operation, count++);

          operation = operation->next;
        } while(!result && operation);


        global->current = global->first;


        result = run_all_transfers(global, share, result);

        curl_share_cleanup(share);
#ifndef CURL_DISABLE_LIBCURL_OPTION
        if(global->libcurl) {

          easysrc_cleanup();


          dumpeasysrc(global);
        }
#endif
      }
      else
        errorf(global, "out of memory\n");
    }
  }

  return result;
}
