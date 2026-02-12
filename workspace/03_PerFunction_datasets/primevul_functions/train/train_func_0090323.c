static CURLcode single_transfer(struct GlobalConfig *global,
                                struct OperationConfig *config,
                                CURLSH *share,
                                bool capath_from_env,
                                bool *added)
{
  CURLcode result = CURLE_OK;
  struct getout *urlnode;
  bool orig_noprogress = global->noprogress;
  bool orig_isatty = global->isatty;
  struct State *state = &config->state;
  char *httpgetfields = state->httpgetfields;
  *added = FALSE;

  if(config->postfields) {
    if(config->use_httpget) {
      if(!httpgetfields) {

        httpgetfields = state->httpgetfields = strdup(config->postfields);
        Curl_safefree(config->postfields);
        if(!httpgetfields) {
          errorf(global, "out of memory\n");
          result = CURLE_OUT_OF_MEMORY;
        }
        else if(SetHTTPrequest(config,
                               (config->no_body?HTTPREQ_HEAD:HTTPREQ_GET),
                               &config->httpreq)) {
          result = CURLE_FAILED_INIT;
        }
      }
    }
    else {
      if(SetHTTPrequest(config, HTTPREQ_SIMPLEPOST, &config->httpreq))
        result = CURLE_FAILED_INIT;
    }
    if(result) {
      single_transfer_cleanup(config);
      return result;
    }
  }
  if(!state->urlnode) {

    state->urlnode = config->url_list;
    state->infilenum = 1;
  }

  while(config->state.urlnode) {
    static bool warn_more_options = FALSE;
    char *infiles;
    struct URLGlob *inglob = state->inglob;
    urlnode = config->state.urlnode;


    if(!urlnode->url) {


      Curl_safefree(urlnode->outfile);
      Curl_safefree(urlnode->infile);
      urlnode->flags = 0;
      config->state.urlnode = urlnode->next;
      state->up = 0;
      if(!warn_more_options) {

        warnf(config->global, "Got more output options than URLs\n");
        warn_more_options = TRUE;
      }
      continue;
    }


    if(urlnode->outfile && !state->outfiles) {
      state->outfiles = strdup(urlnode->outfile);
      if(!state->outfiles) {
        errorf(global, "out of memory\n");
        result = CURLE_OUT_OF_MEMORY;
        break;
      }
    }

    infiles = urlnode->infile;

    if(!config->globoff && infiles && !inglob) {

      result = glob_url(&inglob, infiles, &state->infilenum,
                        global->showerror?global->errors:NULL);
      if(result)
        break;
      config->state.inglob = inglob;
    }

    {
      unsigned long urlnum;

      if(!state->up && !infiles)
        Curl_nop_stmt;
      else {
        if(!state->uploadfile) {
          if(inglob) {
            result = glob_next_url(&state->uploadfile, inglob);
            if(result == CURLE_OUT_OF_MEMORY)
              errorf(global, "out of memory\n");
          }
          else if(!state->up) {
            state->uploadfile = strdup(infiles);
            if(!state->uploadfile) {
              errorf(global, "out of memory\n");
              result = CURLE_OUT_OF_MEMORY;
            }
          }
        }
        if(result)
          break;
      }

      if(!state->urlnum) {
        if(!config->globoff) {


          result = glob_url(&state->urls, urlnode->url, &state->urlnum,
                            global->showerror?global->errors:NULL);
          if(result)
            break;
          urlnum = state->urlnum;
        }
        else
          urlnum = 1;
      }
      else
        urlnum = state->urlnum;

      if(state->up < state->infilenum) {
        struct per_transfer *per = NULL;
        struct OutStruct *outs;
        struct InStruct *input;
        struct OutStruct *heads;
        struct OutStruct *etag_save;
        struct HdrCbData *hdrcbdata = NULL;
        struct OutStruct etag_first;
        long use_proto;
        CURL *curl;


        memset(&etag_first, 0, sizeof(etag_first));
        etag_save = &etag_first;
        etag_save->stream = stdout;


        if(config->etag_compare_file) {
          char *etag_from_file = NULL;
          char *header = NULL;
          ParameterError pe;


          FILE *file = fopen(config->etag_compare_file, FOPEN_READTEXT);
          if(!file && !config->etag_save_file) {
            errorf(global,
                   "Failed to open %s\n", config->etag_compare_file);
            result = CURLE_READ_ERROR;
            break;
          }

          if((PARAM_OK == file2string(&etag_from_file, file)) &&
             etag_from_file) {
            header = aprintf("If-None-Match: %s", etag_from_file);
            Curl_safefree(etag_from_file);
          }
          else
            header = aprintf("If-None-Match: \"\"");

          if(!header) {
            if(file)
              fclose(file);
            errorf(global,
                   "Failed to allocate memory for custom etag header\n");
            result = CURLE_OUT_OF_MEMORY;
            break;
          }


          pe = add2list(&config->headers, header);
          Curl_safefree(header);

          if(file)
            fclose(file);
          if(pe != PARAM_OK) {
            result = CURLE_OUT_OF_MEMORY;
            break;
          }
        }

        if(config->etag_save_file) {

          if(strcmp(config->etag_save_file, "-")) {
            FILE *newfile = fopen(config->etag_save_file, "wb");
            if(!newfile) {
              warnf(global, "Failed creating file for saving etags: \"%s\". "
                    "Skip this transfer\n", config->etag_save_file);
              Curl_safefree(state->outfiles);
              glob_cleanup(state->urls);
              return CURLE_OK;
            }
            else {
              etag_save->filename = config->etag_save_file;
              etag_save->s_isreg = TRUE;
              etag_save->fopened = TRUE;
              etag_save->stream = newfile;
            }
          }
          else {

            set_binmode(etag_save->stream);
          }
        }

        curl = curl_easy_init();
        if(curl)
          result = add_per_transfer(&per);
        else
          result = CURLE_OUT_OF_MEMORY;
        if(result) {
          curl_easy_cleanup(curl);
          if(etag_save->fopened)
            fclose(etag_save->stream);
          break;
        }
        per->etag_save = etag_first;
        if(state->uploadfile) {
          per->uploadfile = strdup(state->uploadfile);
          if(!per->uploadfile) {
            curl_easy_cleanup(curl);
            result = CURLE_OUT_OF_MEMORY;
            break;
          }
          if(SetHTTPrequest(config, HTTPREQ_PUT, &config->httpreq)) {
            Curl_safefree(per->uploadfile);
            curl_easy_cleanup(curl);
            result = CURLE_FAILED_INIT;
            break;
          }
        }
        *added = TRUE;
        per->config = config;
        per->curl = curl;
        per->urlnum = urlnode->num;


        heads = &per->heads;
        heads->stream = stdout;


        if(config->headerfile) {

          if(strcmp(config->headerfile, "-")) {
            FILE *newfile;
            newfile = fopen(config->headerfile, per->prev == NULL?"wb":"ab");
            if(!newfile) {
              warnf(global, "Failed to open %s\n", config->headerfile);
              result = CURLE_WRITE_ERROR;
              break;
            }
            else {
              heads->filename = config->headerfile;
              heads->s_isreg = TRUE;
              heads->fopened = TRUE;
              heads->stream = newfile;
            }
          }
          else {

            set_binmode(heads->stream);
          }
        }

        hdrcbdata = &per->hdrcbdata;

        outs = &per->outs;
        input = &per->input;

        per->outfile = NULL;
        per->infdopen = FALSE;
        per->infd = STDIN_FILENO;


        outs->stream = stdout;

        if(state->urls) {
          result = glob_next_url(&per->this_url, state->urls);
          if(result)
            break;
        }
        else if(!state->li) {
          per->this_url = strdup(urlnode->url);
          if(!per->this_url) {
            result = CURLE_OUT_OF_MEMORY;
            break;
          }
        }
        else
          per->this_url = NULL;
        if(!per->this_url)
          break;

        if(state->outfiles) {
          per->outfile = strdup(state->outfiles);
          if(!per->outfile) {
            result = CURLE_OUT_OF_MEMORY;
            break;
          }
        }

        if(((urlnode->flags&GETOUT_USEREMOTE) ||
            (per->outfile && strcmp("-", per->outfile)))) {


          if(!per->outfile) {

            result = get_url_file_name(&per->outfile, per->this_url);
            if(result) {
              errorf(global, "Failed to extract a sensible file name"
                     " from the URL to use for storage!\n");
              break;
            }
            if(!*per->outfile && !config->content_disposition) {
              errorf(global, "Remote file name has no length!\n");
              result = CURLE_WRITE_ERROR;
              break;
            }
          }
          else if(state->urls) {

            char *storefile = per->outfile;
            result = glob_match_url(&per->outfile, storefile, state->urls);
            Curl_safefree(storefile);
            if(result) {

              warnf(global, "bad output glob!\n");
              break;
            }
            if(!*per->outfile) {
              warnf(global, "output glob produces empty string!\n");
              result = CURLE_WRITE_ERROR;
              break;
            }
          }

          if(config->output_dir && *config->output_dir) {
            char *d = aprintf("%s/%s", config->output_dir, per->outfile);
            if(!d) {
              result = CURLE_WRITE_ERROR;
              break;
            }
            free(per->outfile);
            per->outfile = d;
          }


          if(config->create_dirs) {
            result = create_dir_hierarchy(per->outfile, global->errors);

            if(result)
              break;
          }

          if((urlnode->flags & GETOUT_USEREMOTE)
             && config->content_disposition) {

            DEBUGASSERT(!outs->filename);
          }

          if(config->resume_from_current) {


            struct_stat fileinfo;

            if(0 == stat(per->outfile, &fileinfo))

              config->resume_from = fileinfo.st_size;
            else

              config->resume_from = 0;
          }

          if(config->resume_from) {
#ifdef __VMS


            FILE *file = fopen(outfile, "ab",
                               "ctx=stm", "rfm=stmlf", "rat=cr", "mrs=0");
#else

            FILE *file = fopen(per->outfile, "ab");
#endif
            if(!file) {
              errorf(global, "Can't open '%s'!\n", per->outfile);
              result = CURLE_WRITE_ERROR;
              break;
            }
            outs->fopened = TRUE;
            outs->stream = file;
            outs->init = config->resume_from;
          }
          else {
            outs->stream = NULL;
          }
          outs->filename = per->outfile;
          outs->s_isreg = TRUE;
        }

        if(per->uploadfile && !stdin_upload(per->uploadfile)) {


          char *nurl = add_file_name_to_url(per->this_url, per->uploadfile);
          if(!nurl) {
            result = CURLE_OUT_OF_MEMORY;
            break;
          }
          per->this_url = nurl;
        }
        else if(per->uploadfile && stdin_upload(per->uploadfile)) {


          int authbits = 0;
          int bitcheck = 0;
          while(bitcheck < 32) {
            if(config->authtype & (1UL << bitcheck++)) {
              authbits++;
              if(authbits > 1) {

                break;
              }
            }
          }


          if(config->proxyanyauth || (authbits>1)) {
            warnf(global,
                  "Using --anyauth or --proxy-anyauth with upload from stdin"
                  " involves a big risk of it not working. Use a temporary"
                  " file or a fixed auth type instead!\n");
          }

          DEBUGASSERT(per->infdopen == FALSE);
          DEBUGASSERT(per->infd == STDIN_FILENO);

          set_binmode(stdin);
          if(!strcmp(per->uploadfile, ".")) {
            if(curlx_nonblock((curl_socket_t)per->infd, TRUE) < 0)
              warnf(global,
                    "fcntl failed on fd=%d: %s\n", per->infd, strerror(errno));
          }
        }

        if(per->uploadfile && config->resume_from_current)
          config->resume_from = -1;

        if(output_expected(per->this_url, per->uploadfile) && outs->stream &&
           isatty(fileno(outs->stream)))


          per->noprogress = global->noprogress = global->isatty = TRUE;
        else {


          per->noprogress = global->noprogress = orig_noprogress;
          global->isatty = orig_isatty;
        }

        if(httpgetfields) {
          char *urlbuffer;

          const char *pc = strstr(per->this_url, "://");
          char sep = '?';
          if(pc)
            pc += 3;
          else
            pc = per->this_url;

          pc = strrchr(pc, '/');

          if(pc) {


            if(strchr(pc, '?'))


              sep = '&';
          }


          if(pc)
            urlbuffer = aprintf("%s%c%s", per->this_url, sep, httpgetfields);
          else


            urlbuffer = aprintf("%s/?%s", per->this_url, httpgetfields);

          if(!urlbuffer) {
            result = CURLE_OUT_OF_MEMORY;
            break;
          }

          Curl_safefree(per->this_url);
          per->this_url = urlbuffer;
        }

        if(!global->errors)
          global->errors = stderr;

        if((!per->outfile || !strcmp(per->outfile, "-")) &&
           !config->use_ascii) {


          set_binmode(stdout);
        }


        config->terminal_binary_ok =
          (per->outfile && !strcmp(per->outfile, "-"));


        result = curl_easy_setopt(curl, CURLOPT_SHARE, share);
        if(result)
          break;


        use_proto = url_proto(per->this_url);
#if 0
        if(!(use_proto & built_in_protos)) {
          warnf(global, "URL is '%s' but no support for the scheme\n",
                per->this_url);
        }
#endif

        if(!config->tcp_nodelay)
          my_setopt(curl, CURLOPT_TCP_NODELAY, 0L);

        if(config->tcp_fastopen)
          my_setopt(curl, CURLOPT_TCP_FASTOPEN, 1L);


        my_setopt(curl, CURLOPT_WRITEDATA, per);
        my_setopt(curl, CURLOPT_INTERLEAVEDATA, per);


        my_setopt(curl, CURLOPT_WRITEFUNCTION, tool_write_cb);


        input->config = config;


        my_setopt(curl, CURLOPT_READDATA, input);

        my_setopt(curl, CURLOPT_READFUNCTION, tool_read_cb);


        my_setopt(curl, CURLOPT_SEEKDATA, input);
        my_setopt(curl, CURLOPT_SEEKFUNCTION, tool_seek_cb);

        if(config->recvpersecond &&
           (config->recvpersecond < BUFFER_SIZE))

          my_setopt(curl, CURLOPT_BUFFERSIZE, (long)config->recvpersecond);
        else
          my_setopt(curl, CURLOPT_BUFFERSIZE, (long)BUFFER_SIZE);

        my_setopt_str(curl, CURLOPT_URL, per->this_url);
        my_setopt(curl, CURLOPT_NOPROGRESS, global->noprogress?1L:0L);
        if(config->no_body)
          my_setopt(curl, CURLOPT_NOBODY, 1L);

        if(config->oauth_bearer)
          my_setopt_str(curl, CURLOPT_XOAUTH2_BEARER, config->oauth_bearer);

        my_setopt_str(curl, CURLOPT_PROXY, config->proxy);

        if(config->proxy && result) {
          errorf(global, "proxy support is disabled in this libcurl\n");
          config->synthetic_error = TRUE;
          result = CURLE_NOT_BUILT_IN;
          break;
        }


        if(config->proxy)
          my_setopt_enum(curl, CURLOPT_PROXYTYPE, config->proxyver);

        my_setopt_str(curl, CURLOPT_PROXYUSERPWD, config->proxyuserpwd);


        my_setopt(curl, CURLOPT_HTTPPROXYTUNNEL, config->proxytunnel?1L:0L);


        if(config->preproxy)
          my_setopt_str(curl, CURLOPT_PRE_PROXY, config->preproxy);


        if(config->proxyanyauth)
          my_setopt_bitmask(curl, CURLOPT_PROXYAUTH,
                            (long)CURLAUTH_ANY);
        else if(config->proxynegotiate)
          my_setopt_bitmask(curl, CURLOPT_PROXYAUTH,
                            (long)CURLAUTH_GSSNEGOTIATE);
        else if(config->proxyntlm)
          my_setopt_bitmask(curl, CURLOPT_PROXYAUTH,
                            (long)CURLAUTH_NTLM);
        else if(config->proxydigest)
          my_setopt_bitmask(curl, CURLOPT_PROXYAUTH,
                            (long)CURLAUTH_DIGEST);
        else if(config->proxybasic)
          my_setopt_bitmask(curl, CURLOPT_PROXYAUTH,
                            (long)CURLAUTH_BASIC);


        my_setopt_str(curl, CURLOPT_NOPROXY, config->noproxy);

        my_setopt(curl, CURLOPT_SUPPRESS_CONNECT_HEADERS,
                  config->suppress_connect_headers?1L:0L);

        my_setopt(curl, CURLOPT_FAILONERROR, config->failonerror?1L:0L);
        my_setopt(curl, CURLOPT_REQUEST_TARGET, config->request_target);
        my_setopt(curl, CURLOPT_UPLOAD, per->uploadfile?1L:0L);
        my_setopt(curl, CURLOPT_DIRLISTONLY, config->dirlistonly?1L:0L);
        my_setopt(curl, CURLOPT_APPEND, config->ftp_append?1L:0L);

        if(config->netrc_opt)
          my_setopt_enum(curl, CURLOPT_NETRC, (long)CURL_NETRC_OPTIONAL);
        else if(config->netrc || config->netrc_file)
          my_setopt_enum(curl, CURLOPT_NETRC, (long)CURL_NETRC_REQUIRED);
        else
          my_setopt_enum(curl, CURLOPT_NETRC, (long)CURL_NETRC_IGNORED);

        if(config->netrc_file)
          my_setopt_str(curl, CURLOPT_NETRC_FILE, config->netrc_file);

        my_setopt(curl, CURLOPT_TRANSFERTEXT, config->use_ascii?1L:0L);
        if(config->login_options)
          my_setopt_str(curl, CURLOPT_LOGIN_OPTIONS, config->login_options);
        my_setopt_str(curl, CURLOPT_USERPWD, config->userpwd);
        my_setopt_str(curl, CURLOPT_RANGE, config->range);
        my_setopt(curl, CURLOPT_ERRORBUFFER, per->errorbuffer);
        my_setopt(curl, CURLOPT_TIMEOUT_MS, (long)(config->timeout * 1000));

        switch(config->httpreq) {
        case HTTPREQ_SIMPLEPOST:
          my_setopt_str(curl, CURLOPT_POSTFIELDS,
                        config->postfields);
          my_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE,
                    config->postfieldsize);
          break;
        case HTTPREQ_MIMEPOST:

          curl_mime_free(config->mimepost);
          config->mimepost = NULL;
          result = tool2curlmime(curl, config->mimeroot, &config->mimepost);
          if(result)
            break;
          my_setopt_mimepost(curl, CURLOPT_MIMEPOST, config->mimepost);
          break;
        default:
          break;
        }
        if(result)
          break;


        if(config->mime_options)
          my_setopt(curl, CURLOPT_MIME_OPTIONS, config->mime_options);


        if(config->authtype)
          my_setopt_bitmask(curl, CURLOPT_HTTPAUTH, (long)config->authtype);

        my_setopt_slist(curl, CURLOPT_HTTPHEADER, config->headers);

        if(built_in_protos & (CURLPROTO_HTTP | CURLPROTO_RTSP)) {
          my_setopt_str(curl, CURLOPT_REFERER, config->referer);
          my_setopt_str(curl, CURLOPT_USERAGENT, config->useragent);
        }

        if(built_in_protos & CURLPROTO_HTTP) {

          long postRedir = 0;

          my_setopt(curl, CURLOPT_FOLLOWLOCATION,
                    config->followlocation?1L:0L);
          my_setopt(curl, CURLOPT_UNRESTRICTED_AUTH,
                    config->unrestricted_auth?1L:0L);

          my_setopt(curl, CURLOPT_AUTOREFERER, config->autoreferer?1L:0L);


          if(config->proxyheaders) {
            my_setopt_slist(curl, CURLOPT_PROXYHEADER, config->proxyheaders);
            my_setopt(curl, CURLOPT_HEADEROPT, CURLHEADER_SEPARATE);
          }


          my_setopt(curl, CURLOPT_MAXREDIRS, config->maxredirs);

          if(config->httpversion)
            my_setopt_enum(curl, CURLOPT_HTTP_VERSION, config->httpversion);
          else if(curlinfo->features & CURL_VERSION_HTTP2) {
            my_setopt_enum(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);
          }


          if(config->post301)
            postRedir |= CURL_REDIR_POST_301;
          if(config->post302)
            postRedir |= CURL_REDIR_POST_302;
          if(config->post303)
            postRedir |= CURL_REDIR_POST_303;
          my_setopt(curl, CURLOPT_POSTREDIR, postRedir);


          if(config->encoding)
            my_setopt_str(curl, CURLOPT_ACCEPT_ENCODING, "");


          if(config->tr_encoding)
            my_setopt(curl, CURLOPT_TRANSFER_ENCODING, 1L);

          my_setopt(curl, CURLOPT_HTTP09_ALLOWED,
                    config->http09_allowed ? 1L : 0L);
          if(result) {
            errorf(global, "HTTP/0.9 is not supported in this build!\n");
            return result;
          }

        }

        my_setopt_str(curl, CURLOPT_FTPPORT, config->ftpport);
        my_setopt(curl, CURLOPT_LOW_SPEED_LIMIT,
                  config->low_speed_limit);
        my_setopt(curl, CURLOPT_LOW_SPEED_TIME, config->low_speed_time);
        my_setopt(curl, CURLOPT_MAX_SEND_SPEED_LARGE,
                  config->sendpersecond);
        my_setopt(curl, CURLOPT_MAX_RECV_SPEED_LARGE,
                  config->recvpersecond);

        if(config->use_resume)
          my_setopt(curl, CURLOPT_RESUME_FROM_LARGE, config->resume_from);
        else
          my_setopt(curl, CURLOPT_RESUME_FROM_LARGE, CURL_OFF_T_C(0));

        my_setopt_str(curl, CURLOPT_KEYPASSWD, config->key_passwd);
        my_setopt_str(curl, CURLOPT_PROXY_KEYPASSWD, config->proxy_key_passwd);

        if(use_proto & (CURLPROTO_SCP|CURLPROTO_SFTP)) {


          my_setopt_str(curl, CURLOPT_SSH_PRIVATE_KEYFILE, config->key);

          my_setopt_str(curl, CURLOPT_SSH_PUBLIC_KEYFILE, config->pubkey);


          my_setopt_str(curl, CURLOPT_SSH_HOST_PUBLIC_KEY_MD5,
                        config->hostpubmd5);


          my_setopt_str(curl, CURLOPT_SSH_HOST_PUBLIC_KEY_SHA256,
              config->hostpubsha256);


          if(config->ssh_compression)
            my_setopt(curl, CURLOPT_SSH_COMPRESSION, 1L);
        }

        if(config->cacert)
          my_setopt_str(curl, CURLOPT_CAINFO, config->cacert);
        if(config->proxy_cacert)
          my_setopt_str(curl, CURLOPT_PROXY_CAINFO, config->proxy_cacert);

        if(config->capath) {
          result = res_setopt_str(curl, CURLOPT_CAPATH, config->capath);
          if(result == CURLE_NOT_BUILT_IN) {
            warnf(global, "ignoring %s, not supported by libcurl\n",
                  capath_from_env?
                  "SSL_CERT_DIR environment variable":"--capath");
          }
          else if(result)
            break;
        }


        if(config->proxy_capath || config->capath) {
          result = res_setopt_str(curl, CURLOPT_PROXY_CAPATH,
                                  (config->proxy_capath ?
                                   config->proxy_capath :
                                   config->capath));
          if(result == CURLE_NOT_BUILT_IN) {
            if(config->proxy_capath) {
              warnf(global,
                    "ignoring --proxy-capath, not supported by libcurl\n");
            }
          }
          else if(result)
            break;
        }

        if(config->crlfile)
          my_setopt_str(curl, CURLOPT_CRLFILE, config->crlfile);
        if(config->proxy_crlfile)
          my_setopt_str(curl, CURLOPT_PROXY_CRLFILE, config->proxy_crlfile);
        else if(config->crlfile)
          my_setopt_str(curl, CURLOPT_PROXY_CRLFILE, config->crlfile);

        if(config->pinnedpubkey)
          my_setopt_str(curl, CURLOPT_PINNEDPUBLICKEY, config->pinnedpubkey);

        if(config->ssl_ec_curves)
          my_setopt_str(curl, CURLOPT_SSL_EC_CURVES, config->ssl_ec_curves);

        if(curlinfo->features & CURL_VERSION_SSL) {


          if(config->cert) {
            if(!config->cert_type) {
              if(is_pkcs11_uri(config->cert)) {
                config->cert_type = strdup("ENG");
              }
            }
          }


          if(config->key) {
            if(!config->key_type) {
              if(is_pkcs11_uri(config->key)) {
                config->key_type = strdup("ENG");
              }
            }
          }


          if(config->proxy_cert) {
            if(!config->proxy_cert_type) {
              if(is_pkcs11_uri(config->proxy_cert)) {
                config->proxy_cert_type = strdup("ENG");
              }
            }
          }


          if(config->proxy_key) {
            if(!config->proxy_key_type) {
              if(is_pkcs11_uri(config->proxy_key)) {
                config->proxy_key_type = strdup("ENG");
              }
            }
          }


#if defined(CURLDEBUG) || defined(DEBUGBUILD)
          if(config->cert && (strlen(config->cert) > 8) &&
             (memcmp(config->cert, "loadmem=",8) == 0)) {
            FILE *fInCert = fopen(config->cert + 8, "rb");
            void *certdata = NULL;
            long filesize = 0;
            bool continue_reading = fInCert != NULL;
            if(continue_reading)
              continue_reading = fseek(fInCert, 0, SEEK_END) == 0;
            if(continue_reading)
              filesize = ftell(fInCert);
            if(filesize < 0)
              continue_reading = FALSE;
            if(continue_reading)
              continue_reading = fseek(fInCert, 0, SEEK_SET) == 0;
            if(continue_reading)
              certdata = malloc(((size_t)filesize) + 1);
            if((!certdata) ||
                ((int)fread(certdata, (size_t)filesize, 1, fInCert) != 1))
              continue_reading = FALSE;
            if(fInCert)
              fclose(fInCert);
            if((filesize > 0) && continue_reading) {
              struct curl_blob structblob;
              structblob.data = certdata;
              structblob.len = (size_t)filesize;
              structblob.flags = CURL_BLOB_COPY;
              my_setopt_str(curl, CURLOPT_SSLCERT_BLOB, &structblob);


              memset(certdata, 0, (size_t)filesize);
            }
            free(certdata);
          }
          else
#endif
          my_setopt_str(curl, CURLOPT_SSLCERT, config->cert);
          my_setopt_str(curl, CURLOPT_PROXY_SSLCERT, config->proxy_cert);
          my_setopt_str(curl, CURLOPT_SSLCERTTYPE, config->cert_type);
          my_setopt_str(curl, CURLOPT_PROXY_SSLCERTTYPE,
                        config->proxy_cert_type);


#if defined(CURLDEBUG) || defined(DEBUGBUILD)
          if(config->key && (strlen(config->key) > 8) &&
             (memcmp(config->key, "loadmem=",8) == 0)) {
            FILE *fInCert = fopen(config->key + 8, "rb");
            void *certdata = NULL;
            long filesize = 0;
            bool continue_reading = fInCert != NULL;
            if(continue_reading)
              continue_reading = fseek(fInCert, 0, SEEK_END) == 0;
            if(continue_reading)
              filesize = ftell(fInCert);
            if(filesize < 0)
              continue_reading = FALSE;
            if(continue_reading)
              continue_reading = fseek(fInCert, 0, SEEK_SET) == 0;
            if(continue_reading)
              certdata = malloc(((size_t)filesize) + 1);
            if((!certdata) ||
                ((int)fread(certdata, (size_t)filesize, 1, fInCert) != 1))
              continue_reading = FALSE;
            if(fInCert)
              fclose(fInCert);
            if((filesize > 0) && continue_reading) {
              struct curl_blob structblob;
              structblob.data = certdata;
              structblob.len = (size_t)filesize;
              structblob.flags = CURL_BLOB_COPY;
              my_setopt_str(curl, CURLOPT_SSLKEY_BLOB, &structblob);


              memset(certdata, 0, (size_t)filesize);
            }
            free(certdata);
          }
          else
#endif
          my_setopt_str(curl, CURLOPT_SSLKEY, config->key);
          my_setopt_str(curl, CURLOPT_PROXY_SSLKEY, config->proxy_key);
          my_setopt_str(curl, CURLOPT_SSLKEYTYPE, config->key_type);
          my_setopt_str(curl, CURLOPT_PROXY_SSLKEYTYPE,
                        config->proxy_key_type);
          my_setopt_str(curl, CURLOPT_AWS_SIGV4,
                        config->aws_sigv4);

          if(config->insecure_ok) {
            my_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            my_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
          }
          else {
            my_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);


          }

          if(config->doh_insecure_ok) {
            my_setopt(curl, CURLOPT_DOH_SSL_VERIFYPEER, 0L);
            my_setopt(curl, CURLOPT_DOH_SSL_VERIFYHOST, 0L);
          }

          if(config->proxy_insecure_ok) {
            my_setopt(curl, CURLOPT_PROXY_SSL_VERIFYPEER, 0L);
            my_setopt(curl, CURLOPT_PROXY_SSL_VERIFYHOST, 0L);
          }
          else {
            my_setopt(curl, CURLOPT_PROXY_SSL_VERIFYPEER, 1L);
          }

          if(config->verifystatus)
            my_setopt(curl, CURLOPT_SSL_VERIFYSTATUS, 1L);

          if(config->doh_verifystatus)
            my_setopt(curl, CURLOPT_DOH_SSL_VERIFYSTATUS, 1L);

          if(config->falsestart)
            my_setopt(curl, CURLOPT_SSL_FALSESTART, 1L);

          my_setopt_enum(curl, CURLOPT_SSLVERSION,
                         config->ssl_version | config->ssl_version_max);
          if(config->proxy)
            my_setopt_enum(curl, CURLOPT_PROXY_SSLVERSION,
                           config->proxy_ssl_version);

          {
            long mask =
              (config->ssl_allow_beast ?
               CURLSSLOPT_ALLOW_BEAST : 0) |
              (config->ssl_no_revoke ?
               CURLSSLOPT_NO_REVOKE : 0) |
              (config->ssl_revoke_best_effort ?
               CURLSSLOPT_REVOKE_BEST_EFFORT : 0) |
              (config->native_ca_store ?
               CURLSSLOPT_NATIVE_CA : 0) |
              (config->ssl_auto_client_cert ?
               CURLSSLOPT_AUTO_CLIENT_CERT : 0);

            if(mask)
              my_setopt_bitmask(curl, CURLOPT_SSL_OPTIONS, mask);
          }

          {
            long mask =
              (config->proxy_ssl_allow_beast ?
               CURLSSLOPT_ALLOW_BEAST : 0) |
              (config->proxy_ssl_auto_client_cert ?
               CURLSSLOPT_AUTO_CLIENT_CERT : 0);

            if(mask)
              my_setopt_bitmask(curl, CURLOPT_PROXY_SSL_OPTIONS, mask);
          }
        }

        if(config->path_as_is)
          my_setopt(curl, CURLOPT_PATH_AS_IS, 1L);

        if((use_proto & (CURLPROTO_SCP|CURLPROTO_SFTP)) &&
           !config->insecure_ok) {
          char *known = findfile(".ssh/known_hosts", FALSE);
          if(known) {

            result = res_setopt_str(curl, CURLOPT_SSH_KNOWNHOSTS, known);
            curl_free(known);
            if(result == CURLE_UNKNOWN_OPTION)

              result = CURLE_OK;
            if(result)
              break;
          }
          else
            warnf(global, "Couldn't find a known_hosts file!");
        }

        if(config->no_body || config->remote_time) {

          my_setopt(curl, CURLOPT_FILETIME, 1L);
        }

        my_setopt(curl, CURLOPT_CRLF, config->crlf?1L:0L);
        my_setopt_slist(curl, CURLOPT_QUOTE, config->quote);
        my_setopt_slist(curl, CURLOPT_POSTQUOTE, config->postquote);
        my_setopt_slist(curl, CURLOPT_PREQUOTE, config->prequote);

        if(config->cookies) {
          struct curlx_dynbuf cookies;
          struct curl_slist *cl;


          curlx_dyn_init(&cookies, 4096);
          for(cl = config->cookies; cl; cl = cl->next) {
            if(cl == config->cookies)
              result = curlx_dyn_addf(&cookies, "%s", cl->data);
            else
              result = curlx_dyn_addf(&cookies, ";%s", cl->data);

            if(result)
              break;
          }

          my_setopt_str(curl, CURLOPT_COOKIE, curlx_dyn_ptr(&cookies));
          curlx_dyn_free(&cookies);
        }

        if(config->cookiefiles) {
          struct curl_slist *cfl;

          for(cfl = config->cookiefiles; cfl; cfl = cfl->next)
            my_setopt_str(curl, CURLOPT_COOKIEFILE, cfl->data);
        }


        if(config->cookiejar)
          my_setopt_str(curl, CURLOPT_COOKIEJAR, config->cookiejar);


        my_setopt(curl, CURLOPT_COOKIESESSION, config->cookiesession?1L:0L);

        my_setopt_enum(curl, CURLOPT_TIMECONDITION, (long)config->timecond);
        my_setopt(curl, CURLOPT_TIMEVALUE_LARGE, config->condtime);
        my_setopt_str(curl, CURLOPT_CUSTOMREQUEST, config->customrequest);
        customrequest_helper(config, config->httpreq, config->customrequest);
        my_setopt(curl, CURLOPT_STDERR, global->errors);


        my_setopt_str(curl, CURLOPT_INTERFACE, config->iface);
        my_setopt_str(curl, CURLOPT_KRBLEVEL, config->krblevel);
        progressbarinit(&per->progressbar, config);

        if((global->progressmode == CURL_PROGRESS_BAR) &&
           !global->noprogress && !global->mute) {


          my_setopt(curl, CURLOPT_XFERINFOFUNCTION, tool_progress_cb);
          my_setopt(curl, CURLOPT_XFERINFODATA, per);
        }
        else if(per->uploadfile && !strcmp(per->uploadfile, ".")) {


          my_setopt(curl, CURLOPT_NOPROGRESS, 0L);
          my_setopt(curl, CURLOPT_XFERINFOFUNCTION, tool_readbusy_cb);
          my_setopt(curl, CURLOPT_XFERINFODATA, per);
        }


        if(config->dns_servers)
          my_setopt_str(curl, CURLOPT_DNS_SERVERS, config->dns_servers);


        if(config->dns_interface)
          my_setopt_str(curl, CURLOPT_DNS_INTERFACE, config->dns_interface);
        if(config->dns_ipv4_addr)
          my_setopt_str(curl, CURLOPT_DNS_LOCAL_IP4, config->dns_ipv4_addr);
        if(config->dns_ipv6_addr)
        my_setopt_str(curl, CURLOPT_DNS_LOCAL_IP6, config->dns_ipv6_addr);


        my_setopt_slist(curl, CURLOPT_TELNETOPTIONS, config->telnet_options);


        my_setopt_str(curl, CURLOPT_RANDOM_FILE, config->random_file);
        my_setopt_str(curl, CURLOPT_EGDSOCKET, config->egd_file);
        my_setopt(curl, CURLOPT_CONNECTTIMEOUT_MS,
                  (long)(config->connecttimeout * 1000));

        if(config->doh_url)
          my_setopt_str(curl, CURLOPT_DOH_URL, config->doh_url);

        if(config->cipher_list)
          my_setopt_str(curl, CURLOPT_SSL_CIPHER_LIST, config->cipher_list);

        if(config->proxy_cipher_list)
          my_setopt_str(curl, CURLOPT_PROXY_SSL_CIPHER_LIST,
                        config->proxy_cipher_list);

        if(config->cipher13_list)
          my_setopt_str(curl, CURLOPT_TLS13_CIPHERS, config->cipher13_list);

        if(config->proxy_cipher13_list)
          my_setopt_str(curl, CURLOPT_PROXY_TLS13_CIPHERS,
                        config->proxy_cipher13_list);


        if(config->disable_epsv)

          my_setopt(curl, CURLOPT_FTP_USE_EPSV, 0L);


        if(config->disable_eprt)

          my_setopt(curl, CURLOPT_FTP_USE_EPRT, 0L);

        if(global->tracetype != TRACE_NONE) {
          my_setopt(curl, CURLOPT_DEBUGFUNCTION, tool_debug_cb);
          my_setopt(curl, CURLOPT_DEBUGDATA, config);
          my_setopt(curl, CURLOPT_VERBOSE, 1L);
        }


        if(config->engine) {
          result = res_setopt_str(curl, CURLOPT_SSLENGINE, config->engine);
          if(result)
            break;
        }


        my_setopt(curl, CURLOPT_FTP_CREATE_MISSING_DIRS,
                  (long)(config->ftp_create_dirs?
                         CURLFTP_CREATE_DIR_RETRY:
                         CURLFTP_CREATE_DIR_NONE));


        if(config->max_filesize)
          my_setopt(curl, CURLOPT_MAXFILESIZE_LARGE,
                    config->max_filesize);

        my_setopt(curl, CURLOPT_IPRESOLVE, config->ip_version);


        if(config->ftp_ssl_reqd)
          my_setopt_enum(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);


        else if(config->ftp_ssl)
          my_setopt_enum(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_TRY);


        else if(config->ftp_ssl_control)
          my_setopt_enum(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_CONTROL);


        if(config->ftp_ssl_ccc)
          my_setopt_enum(curl, CURLOPT_FTP_SSL_CCC,
                         (long)config->ftp_ssl_ccc_mode);


        if(config->socks5_gssapi_nec)
          my_setopt_str(curl, CURLOPT_SOCKS5_GSSAPI_NEC,
                        config->socks5_gssapi_nec);


        if(config->socks5_auth)
          my_setopt_bitmask(curl, CURLOPT_SOCKS5_AUTH,
                            (long)config->socks5_auth);


        if(config->proxy_service_name)
          my_setopt_str(curl, CURLOPT_PROXY_SERVICE_NAME,
                        config->proxy_service_name);


        if(config->service_name)
          my_setopt_str(curl, CURLOPT_SERVICE_NAME,
                        config->service_name);


        my_setopt_str(curl, CURLOPT_FTP_ACCOUNT, config->ftp_account);
        my_setopt(curl, CURLOPT_IGNORE_CONTENT_LENGTH, config->ignorecl?1L:0L);


        my_setopt(curl, CURLOPT_FTP_SKIP_PASV_IP, config->ftp_skip_ip?1L:0L);


        my_setopt(curl, CURLOPT_FTP_FILEMETHOD, (long)config->ftp_filemethod);


        if(config->localport) {
          my_setopt(curl, CURLOPT_LOCALPORT, config->localport);
          my_setopt_str(curl, CURLOPT_LOCALPORTRANGE, config->localportrange);
        }


        my_setopt_str(curl, CURLOPT_FTP_ALTERNATIVE_TO_USER,
                      config->ftp_alternative_to_user);


        if(config->disable_sessionid)

          my_setopt(curl, CURLOPT_SSL_SESSIONID_CACHE, 0L);


        if(config->raw) {
          my_setopt(curl, CURLOPT_HTTP_CONTENT_DECODING, 0L);
          my_setopt(curl, CURLOPT_HTTP_TRANSFER_DECODING, 0L);
        }


        if(!config->nokeepalive) {
          my_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
          if(config->alivetime) {
            my_setopt(curl, CURLOPT_TCP_KEEPIDLE, config->alivetime);
            my_setopt(curl, CURLOPT_TCP_KEEPINTVL, config->alivetime);
          }
        }
        else
          my_setopt(curl, CURLOPT_TCP_KEEPALIVE, 0L);


        if(config->tftp_blksize)
          my_setopt(curl, CURLOPT_TFTP_BLKSIZE, config->tftp_blksize);

        if(config->mail_from)
          my_setopt_str(curl, CURLOPT_MAIL_FROM, config->mail_from);

        if(config->mail_rcpt)
          my_setopt_slist(curl, CURLOPT_MAIL_RCPT, config->mail_rcpt);


        my_setopt(curl, CURLOPT_MAIL_RCPT_ALLLOWFAILS,
          config->mail_rcpt_allowfails ? 1L : 0L);


        if(config->ftp_pret)
          my_setopt(curl, CURLOPT_FTP_USE_PRET, 1L);

        if(config->create_file_mode)
          my_setopt(curl, CURLOPT_NEW_FILE_PERMS, config->create_file_mode);

        if(config->proto_present)
          my_setopt_flags(curl, CURLOPT_PROTOCOLS, config->proto);
        if(config->proto_redir_present)
          my_setopt_flags(curl, CURLOPT_REDIR_PROTOCOLS, config->proto_redir);

        if(config->content_disposition
           && (urlnode->flags & GETOUT_USEREMOTE))
          hdrcbdata->honor_cd_filename = TRUE;
        else
          hdrcbdata->honor_cd_filename = FALSE;

        hdrcbdata->outs = outs;
        hdrcbdata->heads = heads;
        hdrcbdata->etag_save = etag_save;
        hdrcbdata->global = global;
        hdrcbdata->config = config;

        my_setopt(curl, CURLOPT_HEADERFUNCTION, tool_header_cb);
        my_setopt(curl, CURLOPT_HEADERDATA, per);

        if(config->resolve)

          my_setopt_slist(curl, CURLOPT_RESOLVE, config->resolve);

        if(config->connect_to)

          my_setopt_slist(curl, CURLOPT_CONNECT_TO, config->connect_to);


        if(curlinfo->features & CURL_VERSION_TLSAUTH_SRP) {
          if(config->tls_username)
            my_setopt_str(curl, CURLOPT_TLSAUTH_USERNAME,
                          config->tls_username);
          if(config->tls_password)
            my_setopt_str(curl, CURLOPT_TLSAUTH_PASSWORD,
                          config->tls_password);
          if(config->tls_authtype)
            my_setopt_str(curl, CURLOPT_TLSAUTH_TYPE,
                          config->tls_authtype);
          if(config->proxy_tls_username)
            my_setopt_str(curl, CURLOPT_PROXY_TLSAUTH_USERNAME,
                          config->proxy_tls_username);
          if(config->proxy_tls_password)
            my_setopt_str(curl, CURLOPT_PROXY_TLSAUTH_PASSWORD,
                          config->proxy_tls_password);
          if(config->proxy_tls_authtype)
            my_setopt_str(curl, CURLOPT_PROXY_TLSAUTH_TYPE,
                          config->proxy_tls_authtype);
        }


        if(config->gssapi_delegation)
          my_setopt_str(curl, CURLOPT_GSSAPI_DELEGATION,
                        config->gssapi_delegation);

        if(config->mail_auth)
          my_setopt_str(curl, CURLOPT_MAIL_AUTH, config->mail_auth);


        if(config->sasl_authzid)
          my_setopt_str(curl, CURLOPT_SASL_AUTHZID, config->sasl_authzid);


        if(config->sasl_ir)
          my_setopt(curl, CURLOPT_SASL_IR, 1L);

        if(config->nonpn) {
          my_setopt(curl, CURLOPT_SSL_ENABLE_NPN, 0L);
        }

        if(config->noalpn) {
          my_setopt(curl, CURLOPT_SSL_ENABLE_ALPN, 0L);
        }


        if(config->unix_socket_path) {
          if(config->abstract_unix_socket) {
            my_setopt_str(curl, CURLOPT_ABSTRACT_UNIX_SOCKET,
                          config->unix_socket_path);
          }
          else {
            my_setopt_str(curl, CURLOPT_UNIX_SOCKET_PATH,
                          config->unix_socket_path);
          }
        }


        if(config->proto_default)
          my_setopt_str(curl, CURLOPT_DEFAULT_PROTOCOL, config->proto_default);


        if(config->expect100timeout > 0)
          my_setopt_str(curl, CURLOPT_EXPECT_100_TIMEOUT_MS,
                        (long)(config->expect100timeout*1000));


        if(config->tftp_no_options)
          my_setopt(curl, CURLOPT_TFTP_NO_OPTIONS, 1L);


        if(config->happy_eyeballs_timeout_ms != CURL_HET_DEFAULT)
          my_setopt(curl, CURLOPT_HAPPY_EYEBALLS_TIMEOUT_MS,
                    config->happy_eyeballs_timeout_ms);


        if(config->haproxy_protocol)
          my_setopt(curl, CURLOPT_HAPROXYPROTOCOL, 1L);

        if(config->disallow_username_in_url)
          my_setopt(curl, CURLOPT_DISALLOW_USERNAME_IN_URL, 1L);

        if(config->altsvc)
          my_setopt_str(curl, CURLOPT_ALTSVC, config->altsvc);

        if(config->hsts)
          my_setopt_str(curl, CURLOPT_HSTS, config->hsts);


        per->retry_sleep_default = (config->retry_delay) ?
          config->retry_delay*1000L : RETRY_SLEEP_DEFAULT;
        per->retry_numretries = config->req_retry;
        per->retry_sleep = per->retry_sleep_default;
        per->retrystart = tvnow();

        state->li++;

        if(state->li >= urlnum) {
          state->li = 0;
          state->urlnum = 0;
          glob_cleanup(state->urls);
          state->urls = NULL;
          state->up++;
          Curl_safefree(state->uploadfile);
        }
      }
      else {


        Curl_safefree(urlnode->outfile);
        Curl_safefree(urlnode->infile);
        urlnode->flags = 0;
        glob_cleanup(state->urls);
        state->urls = NULL;
        state->urlnum = 0;

        Curl_safefree(state->outfiles);
        Curl_safefree(state->uploadfile);
        if(state->inglob) {

          glob_cleanup(state->inglob);
          state->inglob = NULL;
        }
        config->state.urlnode = urlnode->next;
        state->up = 0;
        continue;
      }
    }
    break;
  }

  if(!*added || result) {
    *added = FALSE;
    single_transfer_cleanup(config);
  }
  return result;
}
