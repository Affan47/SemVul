operate(struct Configurable *config, int argc, argv_item_t argv[])
{
  char errorbuffer[CURL_ERROR_SIZE];
  char useragent[128];
  struct ProgressData progressbar;
  struct getout *urlnode;
  struct getout *nextnode;

  struct OutStruct outs;
  struct OutStruct heads;
  struct InStruct input;

  URLGlob *urls=NULL;
  URLGlob *inglob=NULL;
  int urlnum;
  int infilenum;
  char *uploadfile=NULL;

  FILE *infd = stdin;
  bool infdfopen;
  FILE *headerfilep = NULL;
  curl_off_t uploadfilesize;
  bool stillflags=TRUE;

  bool allocuseragent=FALSE;

  char *httpgetfields=NULL;

  CURL *curl;
  int res = 0;
  int i;
  long retry_sleep_default;
  long retry_sleep;

  char *env;
#ifdef CURLDEBUG

  env = curlx_getenv("CURL_MEMDEBUG");
  if(env) {

    char *s = strdup(env);
    curl_free(env);
    curl_memdebug(s);
    free(s);


  }
  env = curlx_getenv("CURL_MEMLIMIT");
  if(env) {
    curl_memlimit(atoi(env));
    curl_free(env);
  }
#endif

  memset(&outs,0,sizeof(outs));

  config->outs = &outs;


  curlinfo = curl_version_info(CURLVERSION_NOW);

  errorbuffer[0]=0;


#ifdef HAVE_SETLOCALE
  setlocale(LC_ALL, "");
#endif


  if (main_init() != CURLE_OK) {
    helpf("error initializing curl library\n");
    return CURLE_FAILED_INIT;
  }
  config->postfieldsize = -1;
  config->showerror=TRUE;
  config->conf=CONF_DEFAULT;
  config->use_httpget=FALSE;
  config->create_dirs=FALSE;
  config->lastrecvtime = cutil_tvnow();
  config->lastsendtime = cutil_tvnow();
  config->maxredirs = DEFAULT_MAXREDIRS;

  if(argc>1 &&
     (!curlx_strnequal("--", argv[1], 2) && (argv[1][0] == '-')) &&
     strchr(argv[1], 'q')) {


    ;
  }
  else {
    parseconfig(NULL, config);
  }

  if ((argc < 2)  && !config->url_list) {
    helpf(NULL);
    return CURLE_FAILED_INIT;
  }


  for (i = 1; i < argc; i++) {
    if(stillflags &&
       ('-' == argv[i][0])) {
      char *nextarg;
      bool passarg;
      char *origopt=argv[i];

      char *flag = argv[i];

      if(curlx_strequal("--", argv[i]))


        stillflags=FALSE;
      else {
        nextarg= (i < argc - 1)? argv[i+1]: NULL;

        res = getparameter(flag, nextarg, &passarg, config);
        if(res) {
          const char *reason = param2text(res);
          if(res != PARAM_HELP_REQUESTED)
            helpf("option %s: %s\n", origopt, reason);
          clean_getout(config);
          return CURLE_FAILED_INIT;
        }

        if(passarg)
          i++;
      }
    }
    else {
      bool used;

      res = getparameter((char *)"--url", argv[i], &used, config);
      if(res)
        return res;
    }
  }

  retry_sleep_default = config->retry_delay?
    config->retry_delay*1000:RETRY_SLEEP_DEFAULT;
  retry_sleep = retry_sleep_default;

  if((!config->url_list || !config->url_list->url) && !config->list_engines) {
    clean_getout(config);
    helpf("no URL specified!\n");
    return CURLE_FAILED_INIT;
  }
  if(NULL == config->useragent) {

    snprintf(useragent, sizeof(useragent),
             CURL_NAME "/" CURL_VERSION " (" OS ") " "%s", curl_version());
    config->useragent= useragent;
  }
  else
    allocuseragent = TRUE;


  if (!config->cacert &&
      !config->capath &&
      !config->insecure_ok) {
    env = curlx_getenv("CURL_CA_BUNDLE");
    if(env)
      GetStr(&config->cacert, env);
    else {
      env = curlx_getenv("SSL_CERT_DIR");
      if(env)
        GetStr(&config->capath, env);
      else {
        env = curlx_getenv("SSL_CERT_FILE");
        if(env)
          GetStr(&config->cacert, env);
      }
    }

    if(env)
      curl_free(env);
#ifdef WIN32
    else
      FindWin32CACert(config, "curl-ca-bundle.crt");
#endif
  }

  if (config->postfields) {
    if (config->use_httpget) {

      httpgetfields = strdup(config->postfields);
      free(config->postfields);
      config->postfields = NULL;
      if(SetHTTPrequest(config,
                        (config->conf&CONF_NOBODY?HTTPREQ_HEAD:HTTPREQ_GET),
                        &config->httpreq)) {
        free(httpgetfields);
        return PARAM_BAD_USE;
      }
    }
    else {
      if(SetHTTPrequest(config, HTTPREQ_SIMPLEPOST, &config->httpreq))
        return PARAM_BAD_USE;
    }
  }


  curl = curl_easy_init();
  if(!curl) {
    clean_getout(config);
    return CURLE_FAILED_INIT;
  }


  easycode = curl_slist_append(easycode, "CURL *hnd = curl_easy_init();");
  if(!easycode) {
    clean_getout(config);
    res = CURLE_OUT_OF_MEMORY;
    goto quit_curl;
  }

  if (config->list_engines) {
    struct curl_slist *engines = NULL;

    curl_easy_getinfo(curl, CURLINFO_SSL_ENGINES, &engines);
    list_engines(engines);
    curl_slist_free_all(engines);
    res = CURLE_OK;
    goto quit_curl;
  }


  urlnode = config->url_list;

  if(config->headerfile) {

    if(strcmp(config->headerfile,"-")) {
      heads.filename = config->headerfile;
      headerfilep=NULL;
    }
    else
      headerfilep=stdout;
    heads.stream = headerfilep;
    heads.config = config;
  }


  while(urlnode) {
    int up;
    char *dourl;
    char *url;
    char *infiles;
    char *outfiles=NULL;


    dourl=urlnode->url;

    url = dourl;

    if(NULL == url) {

      if(urlnode->outfile)
        free(urlnode->outfile);


      nextnode=urlnode->next;
      free(urlnode);
      urlnode = nextnode;
      continue;
    }


    outs.stream = stdout;
    outs.config = config;
    outs.bytes = 0;


    if (urlnode->outfile) {
      outfiles = strdup(urlnode->outfile);
      if (!outfiles) {
        clean_getout(config);
        break;
      }
    }

    infiles = urlnode->infile;

    if(!config->globoff && infiles) {

      res = glob_url(&inglob, infiles, &infilenum,
                     config->showerror?
                     (config->errors?config->errors:stderr):NULL);
      if(res != CURLE_OK) {
        clean_getout(config);
        if(outfiles)
          free(outfiles);
        break;
      }
    }


    for(up = 0;
        (!up && !infiles) ||
          (uploadfile = inglob?
           glob_next_url(inglob):
           (!up?strdup(infiles):NULL));
        up++) {
      int separator = 0;
      long retry_numretries;
      uploadfilesize=-1;

      if(!config->globoff) {


        res = glob_url(&urls, dourl, &urlnum,
                       config->showerror?
                       (config->errors?config->errors:stderr):NULL);
        if(res != CURLE_OK) {
          break;
        }
      }
      else
        urlnum = 1;


      separator= ((!outfiles || curlx_strequal(outfiles, "-")) && urlnum > 1);


      for(i = 0;
          (url = urls?glob_next_url(urls):(i?NULL:strdup(url)));
          i++) {
        char *outfile;
        struct timeval retrystart;
        outfile = outfiles?strdup(outfiles):NULL;

        if((urlnode->flags&GETOUT_USEREMOTE) ||
           (outfile && !curlx_strequal("-", outfile)) ) {


          if(!outfile) {

            char * pc =strstr(url, "://");
            if(pc)
              pc+=3;
            else
              pc=url;
            pc = strrchr(pc, '/');

            if(pc) {

              pc++;
              outfile = *pc ? strdup(pc): NULL;
            }
            if(!outfile || !*outfile) {
              helpf("Remote file name has no length!\n");
              res = CURLE_WRITE_ERROR;
              free(url);
              break;
            }
#if defined(MSDOS)
            {


              char file1 [PATH_MAX];

              strcpy(file1, msdosify(outfile));
              free (outfile);
              outfile = strdup (rename_if_dos_device_name(file1));
            }
#endif
          }
          else if(urls) {

            char *storefile = outfile;
            outfile = glob_match_url(storefile, urls);
            free(storefile);
            if(!outfile) {

              warnf(config, "bad output glob!\n");
              free(url);
              res = CURLE_FAILED_INIT;
              break;
            }
          }


          if(config->create_dirs &&
             (-1 == create_dir_hierarchy(outfile)))
            return CURLE_WRITE_ERROR;

          if(config->resume_from_current) {


            struct_stat fileinfo;


            if(0 == stat(outfile, &fileinfo))

              config->resume_from = fileinfo.st_size;
            else

              config->resume_from = 0;
          }

          outs.filename = outfile;

          if(config->resume_from) {
            outs.init = config->resume_from;

            outs.stream=(FILE *) fopen(outfile, config->resume_from?"ab":"wb");
            if (!outs.stream) {
              helpf("Can't open '%s'!\n", outfile);
              return CURLE_WRITE_ERROR;
            }
          }
          else {
            outs.stream = NULL;
          }
        }
        infdfopen=FALSE;
        if(uploadfile && !curlx_strequal(uploadfile, "-")) {


          struct_stat fileinfo;


          char *ptr=strstr(url, "://");
          if(ptr)
            ptr+=3;
          else
            ptr=url;
          ptr = strrchr(ptr, '/');
          if(!ptr || !strlen(++ptr)) {


            char *filep = strrchr(uploadfile, '/');
            char *file2 = strrchr(filep?filep:uploadfile, '\\');

            if(file2)
              filep = file2+1;
            else if(filep)
              filep++;
            else
              filep = uploadfile;


            filep = curl_easy_escape(curl, filep, 0 );

            if(filep) {
              char *urlbuffer=(char *)malloc(strlen(url) + strlen(filep) + 3);
              if(!urlbuffer) {
                helpf("out of memory\n");
                return CURLE_OUT_OF_MEMORY;
              }
              if(ptr)

                sprintf(urlbuffer, "%s%s", url, filep);
              else

                sprintf(urlbuffer, "%s/%s", url, filep);

              curl_free(filep);

              free(url);
              url = urlbuffer;
            }
          }


          infd=(FILE *) fopen(uploadfile, "rb");
          if (!infd || stat(uploadfile, &fileinfo)) {
            helpf("Can't open '%s'!\n", uploadfile);
            if(infd)
              fclose(infd);
            return CURLE_READ_ERROR;
          }
          infdfopen=TRUE;
          uploadfilesize=fileinfo.st_size;

        }
        else if(uploadfile && curlx_strequal(uploadfile, "-")) {
          SET_BINMODE(stdin);
          infd = stdin;
        }

        if(uploadfile && config->resume_from_current)
          config->resume_from = -1;

        if(output_expected(url, uploadfile)
           && outs.stream && isatty(fileno(outs.stream)))


          config->conf |= CONF_NOPROGRESS|CONF_ISATTY;

        if (urlnum > 1 && !(config->conf&CONF_MUTE)) {
          fprintf(stderr, "\n[%d/%d]: %s --> %s\n",
                  i+1, urlnum, url, outfile ? outfile : "<stdout>");
          if (separator)
            printf("%s%s\n", CURLseparator, url);
        }
        if (httpgetfields) {
          char *urlbuffer;

          const char *pc =strstr(url, "://");
          char sep='?';
          if(pc)
            pc+=3;
          else
            pc=url;

          pc = strrchr(pc, '/');

          if(pc) {


            if(strchr(pc, '?'))


              sep='&';
          }


          urlbuffer=(char *)malloc(strlen(url) + strlen(httpgetfields) + 3);
          if(!urlbuffer) {
            helpf("out of memory\n");
            return CURLE_OUT_OF_MEMORY;
          }
          if (pc)
            sprintf(urlbuffer, "%s%c%s", url, sep, httpgetfields);
          else


            sprintf(urlbuffer, "%s/?%s", url, httpgetfields);

          free(url);
          url = urlbuffer;
        }

        if(!config->errors)
          config->errors = stderr;

        if(!outfile && !(config->conf & CONF_GETTEXT)) {


          SET_BINMODE(stdout);
        }

        if(1 == config->tcp_nodelay)
          my_setopt(curl, CURLOPT_TCP_NODELAY, 1);


        my_setopt(curl, CURLOPT_WRITEDATA, (FILE *)&outs);

        my_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);


        input.stream = infd;
        input.config = config;
        my_setopt(curl, CURLOPT_READDATA, &input);

        my_setopt(curl, CURLOPT_READFUNCTION, my_fread);


        my_setopt(curl, CURLOPT_IOCTLDATA, &input);
        my_setopt(curl, CURLOPT_IOCTLFUNCTION, my_ioctl);

        if(config->recvpersecond)


          my_setopt(curl, CURLOPT_BUFFERSIZE, config->recvpersecond);


        my_setopt(curl, CURLOPT_INFILESIZE_LARGE, uploadfilesize);
        my_setopt(curl, CURLOPT_URL, url);
        my_setopt(curl, CURLOPT_PROXY, config->proxy);
        my_setopt(curl, CURLOPT_HEADER, config->conf&CONF_HEADER);
        my_setopt(curl, CURLOPT_NOPROGRESS, config->conf&CONF_NOPROGRESS);
        my_setopt(curl, CURLOPT_NOBODY, config->conf&CONF_NOBODY);
        my_setopt(curl, CURLOPT_FAILONERROR,
                  config->conf&CONF_FAILONERROR);
        my_setopt(curl, CURLOPT_UPLOAD, uploadfile?TRUE:FALSE);
        my_setopt(curl, CURLOPT_FTPLISTONLY,
                  config->conf&CONF_FTPLISTONLY);
        my_setopt(curl, CURLOPT_FTPAPPEND, config->conf&CONF_FTPAPPEND);

        if (config->conf&CONF_NETRC_OPT)
          my_setopt(curl, CURLOPT_NETRC, CURL_NETRC_OPTIONAL);
        else if (config->conf&CONF_NETRC)
          my_setopt(curl, CURLOPT_NETRC, CURL_NETRC_REQUIRED);
        else
          my_setopt(curl, CURLOPT_NETRC, CURL_NETRC_IGNORED);

        my_setopt(curl, CURLOPT_FOLLOWLOCATION,
                  config->conf&CONF_FOLLOWLOCATION);
        my_setopt(curl, CURLOPT_UNRESTRICTED_AUTH,
                  config->conf&CONF_UNRESTRICTED_AUTH);
        my_setopt(curl, CURLOPT_TRANSFERTEXT, config->conf&CONF_GETTEXT);
        my_setopt(curl, CURLOPT_USERPWD, config->userpwd);
        my_setopt(curl, CURLOPT_PROXYUSERPWD, config->proxyuserpwd);
        my_setopt(curl, CURLOPT_RANGE, config->range);
        my_setopt(curl, CURLOPT_ERRORBUFFER, errorbuffer);
        my_setopt(curl, CURLOPT_TIMEOUT, config->timeout);

        switch(config->httpreq) {
        case HTTPREQ_SIMPLEPOST:
          my_setopt(curl, CURLOPT_POSTFIELDS, config->postfields);
          my_setopt(curl, CURLOPT_POSTFIELDSIZE, config->postfieldsize);
          break;
        case HTTPREQ_POST:
          my_setopt(curl, CURLOPT_HTTPPOST, config->httppost);
          break;
        default:
          break;
        }
        my_setopt(curl, CURLOPT_REFERER, config->referer);
        my_setopt(curl, CURLOPT_AUTOREFERER,
                  config->conf&CONF_AUTO_REFERER);
        my_setopt(curl, CURLOPT_USERAGENT, config->useragent);
        my_setopt(curl, CURLOPT_FTPPORT, config->ftpport);
        my_setopt(curl, CURLOPT_LOW_SPEED_LIMIT,
                  config->low_speed_limit);
        my_setopt(curl, CURLOPT_LOW_SPEED_TIME, config->low_speed_time);
        my_setopt(curl, CURLOPT_MAX_SEND_SPEED_LARGE,
                  config->sendpersecond);
        my_setopt(curl, CURLOPT_MAX_RECV_SPEED_LARGE,
                  config->recvpersecond);
        my_setopt(curl, CURLOPT_RESUME_FROM_LARGE,
                  config->use_resume?config->resume_from:0);
        my_setopt(curl, CURLOPT_COOKIE, config->cookie);
        my_setopt(curl, CURLOPT_HTTPHEADER, config->headers);
        my_setopt(curl, CURLOPT_SSLCERT, config->cert);
        my_setopt(curl, CURLOPT_SSLCERTTYPE, config->cert_type);
        my_setopt(curl, CURLOPT_SSLKEY, config->key);
        my_setopt(curl, CURLOPT_SSLKEYTYPE, config->key_type);
        my_setopt(curl, CURLOPT_SSLKEYPASSWD, config->key_passwd);


        my_setopt(curl, CURLOPT_SSH_PRIVATE_KEYFILE, config->key);
        my_setopt(curl, CURLOPT_SSH_PUBLIC_KEYFILE, config->pubkey);


        my_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2);
        if(config->cacert || config->capath) {
          if (config->cacert)
            my_setopt(curl, CURLOPT_CAINFO, config->cacert);

          if (config->capath)
            my_setopt(curl, CURLOPT_CAPATH, config->capath);
          my_setopt(curl, CURLOPT_SSL_VERIFYPEER, TRUE);
        }
        if(config->insecure_ok) {

          my_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
          my_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1);
        }

        if((config->conf&CONF_NOBODY) ||
           config->remote_time) {

          my_setopt(curl, CURLOPT_FILETIME, TRUE);
        }

        my_setopt(curl, CURLOPT_MAXREDIRS, config->maxredirs);
        my_setopt(curl, CURLOPT_CRLF, config->crlf);
        my_setopt(curl, CURLOPT_QUOTE, config->quote);
        my_setopt(curl, CURLOPT_POSTQUOTE, config->postquote);
        my_setopt(curl, CURLOPT_PREQUOTE, config->prequote);
        my_setopt(curl, CURLOPT_WRITEHEADER,
                  config->headerfile?&heads:NULL);
        my_setopt(curl, CURLOPT_COOKIEFILE, config->cookiefile);

        if(config->cookiejar)
          my_setopt(curl, CURLOPT_COOKIEJAR, config->cookiejar);

        my_setopt(curl, CURLOPT_COOKIESESSION, config->cookiesession);

        my_setopt(curl, CURLOPT_SSLVERSION, config->ssl_version);
        my_setopt(curl, CURLOPT_TIMECONDITION, config->timecond);
        my_setopt(curl, CURLOPT_TIMEVALUE, config->condtime);
        my_setopt(curl, CURLOPT_CUSTOMREQUEST, config->customrequest);
        my_setopt(curl, CURLOPT_STDERR, config->errors);


        my_setopt(curl, CURLOPT_HTTPPROXYTUNNEL, config->proxytunnel);
        my_setopt(curl, CURLOPT_INTERFACE, config->iface);
        my_setopt(curl, CURLOPT_KRB4LEVEL, config->krb4level);

        progressbarinit(&progressbar, config);
        if((config->progressmode == CURL_PROGRESS_BAR) &&
           !(config->conf&(CONF_NOPROGRESS|CONF_MUTE))) {


          my_setopt(curl, CURLOPT_PROGRESSFUNCTION, myprogress);
          my_setopt(curl, CURLOPT_PROGRESSDATA, &progressbar);
        }


        my_setopt(curl, CURLOPT_TELNETOPTIONS, config->telnet_options);


        my_setopt(curl, CURLOPT_RANDOM_FILE, config->random_file);
        my_setopt(curl, CURLOPT_EGDSOCKET, config->egd_file);
        my_setopt(curl, CURLOPT_CONNECTTIMEOUT, config->connecttimeout);

        if(config->cipher_list)
          my_setopt(curl, CURLOPT_SSL_CIPHER_LIST, config->cipher_list);

        if(config->httpversion)
          my_setopt(curl, CURLOPT_HTTP_VERSION, config->httpversion);


        if(config->disable_epsv)

          my_setopt(curl, CURLOPT_FTP_USE_EPSV, FALSE);


        if(config->disable_eprt)

          my_setopt(curl, CURLOPT_FTP_USE_EPRT, FALSE);


        if(config->authtype)
          my_setopt(curl, CURLOPT_HTTPAUTH, config->authtype);


        if(config->trace_dump) {
          my_setopt(curl, CURLOPT_DEBUGFUNCTION, my_trace);
          my_setopt(curl, CURLOPT_DEBUGDATA, config);
          my_setopt(curl, CURLOPT_VERBOSE, TRUE);
        }

        res = CURLE_OK;


        if (config->engine) {
          res = my_setopt(curl, CURLOPT_SSLENGINE, config->engine);
          my_setopt(curl, CURLOPT_SSLENGINE_DEFAULT, 1);
        }

        if (res != CURLE_OK)
           goto show_error;


        my_setopt(curl, CURLOPT_ENCODING,
                         (config->encoding) ? "" : NULL);


        my_setopt(curl, CURLOPT_FTP_CREATE_MISSING_DIRS,
                         config->ftp_create_dirs);
        if(config->proxyanyauth)
          my_setopt(curl, CURLOPT_PROXYAUTH, CURLAUTH_ANY);
        else if(config->proxyntlm)
          my_setopt(curl, CURLOPT_PROXYAUTH, CURLAUTH_NTLM);
        else if(config->proxydigest)
          my_setopt(curl, CURLOPT_PROXYAUTH, CURLAUTH_DIGEST);
        else if(config->proxybasic)
          my_setopt(curl, CURLOPT_PROXYAUTH, CURLAUTH_BASIC);


        if(config->max_filesize)
          my_setopt(curl, CURLOPT_MAXFILESIZE_LARGE,
                           config->max_filesize);

        if(4 == config->ip_version)
          my_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
        else if(6 == config->ip_version)
          my_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V6);
        else
          my_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_WHATEVER);


        if(config->ftp_ssl_reqd)
          my_setopt(curl, CURLOPT_FTP_SSL, CURLFTPSSL_ALL);


        else if(config->ftp_ssl)
          my_setopt(curl, CURLOPT_FTP_SSL, CURLFTPSSL_TRY);


        else if(config->ftp_ssl_control)
          my_setopt(curl, CURLOPT_FTP_SSL, CURLFTPSSL_CONTROL);


        if(config->ftp_ssl_ccc)
            my_setopt(curl, CURLOPT_FTP_SSL_CCC, config->ftp_ssl_ccc_mode);


        if(config->socksproxy) {
          my_setopt(curl, CURLOPT_PROXY, config->socksproxy);
          my_setopt(curl, CURLOPT_PROXYTYPE, config->socksver);
        }


        my_setopt(curl, CURLOPT_FTP_ACCOUNT, config->ftp_account);

        my_setopt(curl, CURLOPT_IGNORE_CONTENT_LENGTH, config->ignorecl);


        my_setopt(curl, CURLOPT_FTP_SKIP_PASV_IP, config->ftp_skip_ip);


        my_setopt(curl, CURLOPT_FTP_FILEMETHOD, config->ftp_filemethod);


        if(config->localport) {
          my_setopt(curl, CURLOPT_LOCALPORT, config->localport);
          my_setopt(curl, CURLOPT_LOCALPORTRANGE,
                    config->localportrange);
        }


        my_setopt(curl, CURLOPT_FTP_ALTERNATIVE_TO_USER,
                  config->ftp_alternative_to_user);


        my_setopt(curl, CURLOPT_SSL_SESSIONID_CACHE,
                  !config->disable_sessionid);


        if(config->raw) {
          my_setopt(curl, CURLOPT_HTTP_CONTENT_DECODING, FALSE);
          my_setopt(curl, CURLOPT_HTTP_TRANSFER_DECODING, FALSE);
        }

        retry_numretries = config->req_retry;

        retrystart = cutil_tvnow();

        do {
          res = curl_easy_perform(curl);
          if (!curl_slist_append(easycode, "ret = curl_easy_perform(hnd);")) {
            res = CURLE_OUT_OF_MEMORY;
            break;
          }


          if(retry_numretries &&
             (!config->retry_maxtime ||
              (cutil_tvdiff(cutil_tvnow(), retrystart)<
               config->retry_maxtime*1000)) ) {
            enum {
              RETRY_NO,
              RETRY_TIMEOUT,
              RETRY_HTTP,
              RETRY_FTP,
              RETRY_LAST
            } retry = RETRY_NO;
            long response;
            if(CURLE_OPERATION_TIMEDOUT == res)

              retry = RETRY_TIMEOUT;
            else if(CURLE_OK == res) {

              char *this_url=NULL;
              curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &this_url);
              if(this_url &&
                 curlx_strnequal(this_url, "http", 4)) {

                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);

                switch(response) {
                case 500:
                case 502:
                case 503:
                case 504:
                  retry = RETRY_HTTP;


                  break;
                }
              }
            }
            else if(CURLE_LOGIN_DENIED == res) {
              curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);

              if(response/100 == 5)


                retry = RETRY_FTP;
            }

            if(retry) {
              static const char * const m[]={NULL,
                                             "timeout",
                                             "HTTP error",
                                             "FTP error"
              };
              warnf(config, "Transient problem: %s "
                    "Will retry in %ld seconds. "
                    "%ld retries left.\n",
                    m[retry],
                    retry_sleep/1000,
                    retry_numretries);

              go_sleep(retry_sleep);
              retry_numretries--;
              if(!config->retry_delay) {
                retry_sleep *= 2;
                if(retry_sleep > RETRY_SLEEP_MAX)
                  retry_sleep = RETRY_SLEEP_MAX;
              }
              if(outs.bytes && outs.filename) {


                if(!(config->conf&CONF_MUTE))
                  fprintf(stderr, "Throwing away %Od bytes\n", outs.bytes);
                fflush(outs.stream);

#ifdef HAVE_FTRUNCATE
                ftruncate( fileno(outs.stream), outs.init);


                fseek(outs.stream, 0, SEEK_END);
#else


                fseek(outs.stream, (long)outs.init, SEEK_SET);
#endif
                outs.bytes = 0;
              }
              continue;
            }
          }


          retry_sleep = retry_sleep_default;
          break;

        } while(1);

        if((config->progressmode == CURL_PROGRESS_BAR) &&
           progressbar.calls) {


          fputs("\n", progressbar.out);
        }

        if(config->writeout) {
          ourWriteOut(curl, config->writeout);
        }
#ifdef USE_ENVIRONMENT
        if (config->writeenv)
          ourWriteEnv(curl);
#endif

show_error:

#ifdef  VMS
        if (!config->showerror)  {
          vms_show = VMSSTS_HIDE;
        }
#else
        if((res!=CURLE_OK) && config->showerror) {
          fprintf(config->errors, "curl: (%d) %s\n", (int)res,
                  errorbuffer[0]? errorbuffer:
                  curl_easy_strerror((CURLcode)res));
          if(CURLE_SSL_CACERT == res) {
#define CURL_CA_CERT_ERRORMSG1 \
"More details here: http://curl.haxx.se/docs/sslcerts.html\n\n" \
"curl performs SSL certificate verification by default, using a \"bundle\"\n" \
" of Certificate Authority (CA) public keys (CA certs). The default\n" \
" bundle is named curl-ca-bundle.crt; you can specify an alternate file\n" \
" using the --cacert option.\n"

#define CURL_CA_CERT_ERRORMSG2 \
"If this HTTPS server uses a certificate signed by a CA represented in\n" \
" the bundle, the certificate verification probably failed due to a\n" \
" problem with the certificate (it might be expired, or the name might\n" \
" not match the domain name in the URL).\n" \
"If you'd like to turn off curl's verification of the certificate, use\n" \
" the -k (or --insecure) option.\n"

            fprintf(config->errors, "%s%s",
                    CURL_CA_CERT_ERRORMSG1,
                    CURL_CA_CERT_ERRORMSG2 );
          }
        }
#endif

        if (outfile && !curlx_strequal(outfile, "-") && outs.stream)
          fclose(outs.stream);

#ifdef HAVE_UTIME


        if(config->remote_time && outs.filename) {

          long filetime;
          curl_easy_getinfo(curl, CURLINFO_FILETIME, &filetime);
          if(filetime >= 0) {
            struct utimbuf times;
            times.actime = (time_t)filetime;
            times.modtime = (time_t)filetime;
            utime(outs.filename, &times);
          }
        }
#endif
#ifdef __AMIGA__


        if( strlen(url) > 78 )
          url[79] = '\0';

        SetComment( outs.filename, url);
#endif

        if(headerfilep)
          fclose(headerfilep);

        if(url)
          free(url);

        if(outfile)
          free(outfile);

        if(infdfopen)
          fclose(infd);

      }

      if(urls)

        glob_cleanup(urls);

      if(uploadfile)
        free(uploadfile);

    }

    if(inglob) {
      glob_cleanup(inglob);
      inglob = NULL;
    }

    if(outfiles)
      free(outfiles);


    if(urlnode->url)
      free(urlnode->url);
    if(urlnode->outfile)
      free(urlnode->outfile);
    if(urlnode->infile)
      free(urlnode->infile);


    nextnode=urlnode->next;
    free(urlnode);
    urlnode = nextnode;

  }

quit_curl:
  if (httpgetfields)
    free(httpgetfields);

  if (config->engine)
    free(config->engine);


  curl_easy_cleanup(curl);
  if (easycode)
    curl_slist_append(easycode, "curl_easy_cleanup(hnd);");

  if(config->headerfile && !headerfilep && heads.stream)
    fclose(heads.stream);

  if(allocuseragent)
    free(config->useragent);

  if(config->trace_fopened && config->trace_stream)
    fclose(config->trace_stream);

  if(config->errors_fopened)
    fclose(config->errors);

  main_free();

  dumpeasycode(config);

  return res;
}
