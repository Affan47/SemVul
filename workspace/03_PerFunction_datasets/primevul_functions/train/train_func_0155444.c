CURLcode operate(struct GlobalConfig *config, int argc, argv_item_t argv[])
{
  CURLcode result = CURLE_OK;


#ifdef HAVE_SETLOCALE
  setlocale(LC_ALL, "");
#endif


  if((argc == 1) || (!curlx_strequal(argv[1], "-q"))) {
    parseconfig(NULL, config);


    if((argc < 2) && (!config->first->url_list)) {
      helpf(config->errors, NULL);
      result = CURLE_FAILED_INIT;
    }
  }

  if(!result) {

    ParameterError res = parse_args(config, argc, argv);
    if(res) {
      result = CURLE_OK;


      if(res == PARAM_HELP_REQUESTED)
        tool_help();

      else if(res == PARAM_MANUAL_REQUESTED)
        hugehelp();

      else if(res == PARAM_VERSION_INFO_REQUESTED)
        tool_version_info();

      else if(res == PARAM_ENGINES_REQUESTED)
        tool_list_engines(config->easy);
      else if(res == PARAM_LIBCURL_UNSUPPORTED_PROTOCOL)
        result = CURLE_UNSUPPORTED_PROTOCOL;
      else
        result = CURLE_FAILED_INIT;
    }
    else {
#ifndef CURL_DISABLE_LIBCURL_OPTION

      result = easysrc_init();
#endif


      if(!result) {
        size_t count = 0;
        struct OperationConfig *operation = config->first;


        while(!result && operation) {
          result = get_args(operation, count++);

          operation = operation->next;
        }


        config->current = config->first;


        while(!result && config->current) {
          result = operate_do(config, config->current);

          config->current = config->current->next;
        }

#ifndef CURL_DISABLE_LIBCURL_OPTION

        easysrc_cleanup();


        dumpeasysrc(config);
#endif
      }
      else
        helpf(config->errors, "out of memory\n");
    }
  }

  return result;
}
