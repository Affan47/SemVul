static ParameterError getparameter(char *flag,
                                   char *nextarg,
                                   bool *usedarg,

                                   struct Configurable *config)
{
  char letter;
  char subletter=0;
  int rc;
  const char *parse=NULL;
  unsigned int j;
  time_t now;
  int hit=-1;
  bool longopt=FALSE;
  bool singleopt=FALSE;
  ParameterError err;


  static const struct LongShort aliases[]= {


    {"*", "url",         TRUE},
    {"*a", "random-file", TRUE},
    {"*b", "egd-file",   TRUE},
    {"*c", "connect-timeout", TRUE},
    {"*d", "ciphers",    TRUE},
    {"*e", "disable-epsv", FALSE},
#ifdef USE_ENVIRONMENT
    {"*f", "environment", FALSE},
#endif
    {"*g", "trace",      TRUE},
    {"*h", "trace-ascii", TRUE},
    {"*i", "limit-rate", TRUE},
    {"*j", "compressed",  FALSE},
    {"*k", "digest",     FALSE},
    {"*l", "negotiate",  FALSE},
    {"*m", "ntlm",       FALSE},
    {"*n", "basic",      FALSE},
    {"*o", "anyauth",    FALSE},
#ifdef MSDOS
    {"*p", "wdebug",     FALSE},
#endif
    {"*q", "ftp-create-dirs", FALSE},
    {"*r", "create-dirs", FALSE},
    {"*s", "max-redirs",   TRUE},
    {"*t", "proxy-ntlm",   FALSE},
    {"*u", "crlf",        FALSE},
    {"*v", "stderr",      TRUE},
    {"*w", "interface",   TRUE},
    {"*x", "krb4",        TRUE},
    {"*y", "max-filesize", TRUE},
    {"*z", "disable-eprt", FALSE},
    {"$a", "ftp-ssl",    FALSE},
    {"$b", "ftp-pasv",   FALSE},
    {"$c", "socks5",     TRUE},
    {"$c", "socks",      TRUE},


    {"$d", "tcp-nodelay",FALSE},
    {"$e", "proxy-digest", FALSE},
    {"$f", "proxy-basic", FALSE},
    {"$g", "retry",      TRUE},
    {"$h", "retry-delay", TRUE},
    {"$i", "retry-max-time", TRUE},
    {"$m", "ftp-account", TRUE},
    {"$n", "proxy-anyauth", FALSE},
    {"$o", "trace-time", FALSE},
    {"$p", "ignore-content-length", FALSE},
    {"$q", "ftp-skip-pasv-ip", FALSE},
    {"$r", "ftp-method", TRUE},
    {"$s", "local-port", TRUE},
    {"$t", "socks4",     TRUE},
    {"$u", "ftp-alternative-to-user", TRUE},
    {"$v", "ftp-ssl-reqd", FALSE},
    {"$w", "no-sessionid", FALSE},
    {"$x", "ftp-ssl-control", FALSE},
    {"$y", "ftp-ssl-ccc", FALSE},
    {"$j", "ftp-ssl-ccc-mode", TRUE},
    {"$z", "libcurl",    TRUE},
    {"$#", "raw",        FALSE},

    {"0", "http1.0",     FALSE},
    {"1", "tlsv1",       FALSE},
    {"2", "sslv2",       FALSE},
    {"3", "sslv3",       FALSE},
    {"4", "ipv4",       FALSE},
    {"6", "ipv6",       FALSE},
    {"a", "append",      FALSE},
    {"A", "user-agent",  TRUE},
    {"b", "cookie",      TRUE},
    {"B", "use-ascii",   FALSE},
    {"c", "cookie-jar",  TRUE},
    {"C", "continue-at", TRUE},
    {"d", "data",        TRUE},
    {"da", "data-ascii", TRUE},
    {"db", "data-binary", TRUE},
    {"D", "dump-header", TRUE},
    {"e", "referer",     TRUE},
    {"E", "cert",        TRUE},
    {"Ea", "cacert",     TRUE},
    {"Eb","cert-type",   TRUE},
    {"Ec","key",         TRUE},
    {"Ed","key-type",    TRUE},
    {"Ee","pass",        TRUE},
    {"Ef","engine",      TRUE},
    {"Eg","capath ",     TRUE},
    {"Eh","pubkey",      TRUE},
    {"f", "fail",        FALSE},
    {"F", "form",        TRUE},
    {"Fs","form-string", TRUE},
    {"g", "globoff",     FALSE},
    {"G", "get",         FALSE},
    {"h", "help",        FALSE},
    {"H", "header",      TRUE},
    {"i", "include",     FALSE},
    {"I", "head",        FALSE},
    {"j", "junk-session-cookies", FALSE},
    {"k", "insecure",    FALSE},
    {"K", "config",      TRUE},
    {"l", "list-only",   FALSE},
    {"L", "location",    FALSE},
    {"Lt", "location-trusted", FALSE},
    {"m", "max-time",    TRUE},
    {"M", "manual",      FALSE},
    {"n", "netrc",       FALSE},
    {"no", "netrc-optional", FALSE},
    {"N", "no-buffer",   FALSE},
    {"o", "output",      TRUE},
    {"O", "remote-name", FALSE},
    {"p", "proxytunnel", FALSE},
    {"P", "ftpport",     TRUE},
    {"P", "ftp-port",    TRUE},
    {"q", "disable",     FALSE},
    {"Q", "quote",       TRUE},
    {"r", "range",       TRUE},
    {"R", "remote-time", FALSE},
    {"s", "silent",      FALSE},
    {"S", "show-error",  FALSE},
    {"t", "telnet-options", TRUE},
    {"T", "upload-file", TRUE},
    {"u", "user",        TRUE},
    {"U", "proxy-user",  TRUE},
    {"v", "verbose",     FALSE},
    {"V", "version",     FALSE},
    {"w", "write-out",   TRUE},
    {"x", "proxy",       TRUE},
    {"X", "request",     TRUE},
    {"X", "http-request", TRUE},
    {"Y", "speed-limit",  TRUE},
    {"y", "speed-time", TRUE},
    {"z", "time-cond",   TRUE},
    {"#", "progress-bar",FALSE},
  };

  if(('-' != flag[0]) ||
     (('-' == flag[0]) && ('-' == flag[1]))) {

    char *word=('-' == flag[0])?flag+2:flag;
    size_t fnam=strlen(word);
    int numhits=0;
    for(j=0; j< sizeof(aliases)/sizeof(aliases[0]); j++) {
      if(curlx_strnequal(aliases[j].lname, word, fnam)) {
        longopt = TRUE;
        numhits++;
        if(curlx_strequal(aliases[j].lname, word)) {
          parse = aliases[j].letter;
          hit = j;
          numhits = 1;
          break;
        }
        parse = aliases[j].letter;
        hit = j;
      }
    }
    if(numhits>1) {

      return PARAM_OPTION_AMBIGUOUS;
    }
    if(hit < 0) {
      return PARAM_OPTION_UNKNOWN;
    }
  }
  else {
    flag++;
    hit=-1;
    parse = flag;
  }

  do {


    if(!longopt) {
      if(NULL != parse) {
        letter = (char)*parse;
      }
      else {
        letter = '\0';
      }
      subletter='\0';
    }
    else {
      letter = parse[0];
      subletter = parse[1];
    }
    *usedarg = FALSE;

    if(hit < 0) {
      for(j=0; j< sizeof(aliases)/sizeof(aliases[0]); j++) {
        if(letter == aliases[j].letter[0]) {
          hit = j;
          break;
        }
      }
      if(hit < 0) {
        return PARAM_OPTION_UNKNOWN;
      }
    }
    if(hit < 0) {
      return PARAM_OPTION_UNKNOWN;
    }
    if(!longopt && aliases[hit].extraparam && parse[1]) {
      nextarg=(char *)&parse[1];
      singleopt=TRUE;
    }
    else if(!nextarg && aliases[hit].extraparam) {
      return PARAM_REQUIRES_PARAMETER;
    }
    else if(nextarg && aliases[hit].extraparam)
      *usedarg = TRUE;

    switch(letter) {
    case '*':
      switch(subletter) {
      case 'a':
        GetStr(&config->random_file, nextarg);
        break;
      case 'b':
        GetStr(&config->egd_file, nextarg);
        break;
      case 'c':
        if(str2num(&config->connecttimeout, nextarg))
          return PARAM_BAD_NUMERIC;
        break;
      case 'd':
        GetStr(&config->cipher_list, nextarg);
        break;
      case 'e':
        config->disable_epsv ^= TRUE;
        break;
#ifdef USE_ENVIRONMENT
      case 'f':
        config->writeenv ^= TRUE;
        break;
#endif
      case 'g':
        GetStr(&config->trace_dump, nextarg);
        if(config->tracetype && (config->tracetype != TRACE_BIN))
          warnf(config, "--trace overrides an earlier trace/verbose option\n");
        config->tracetype = TRACE_BIN;
        break;
      case 'h':
        GetStr(&config->trace_dump, nextarg);
        if(config->tracetype && (config->tracetype != TRACE_ASCII))
          warnf(config,
                "--trace-ascii overrides an earlier trace/verbose option\n");
        config->tracetype = TRACE_ASCII;
        break;
      case 'i':
        {

          char *unit;
          curl_off_t value = curlx_strtoofft(nextarg, &unit, 0);

          if(!*unit)
            unit=(char *)"b";
          else if(strlen(unit) > 1)
            unit=(char *)"w";

          switch(*unit) {
          case 'G':
          case 'g':
            value *= 1024*1024*1024;
            break;
          case 'M':
          case 'm':
            value *= 1024*1024;
            break;
          case 'K':
          case 'k':
            value *= 1024;
            break;
          case 'b':
          case 'B':

            break;
          default:
            warnf(config, "unsupported rate unit. Use G, M, K or B!\n");
            return PARAM_BAD_USE;
          }
          config->recvpersecond = value;
          config->sendpersecond = value;
        }
        break;

      case 'j':
        config->encoding ^= TRUE;
        break;

      case 'k':
        config->authtype = CURLAUTH_DIGEST;
        break;

      case 'l':
        if(curlinfo->features & CURL_VERSION_GSSNEGOTIATE)
          config->authtype = CURLAUTH_GSSNEGOTIATE;
        else
          return PARAM_LIBCURL_DOESNT_SUPPORT;
        break;

      case 'm':
        if(curlinfo->features & CURL_VERSION_NTLM)
          config->authtype = CURLAUTH_NTLM;
        else
          return PARAM_LIBCURL_DOESNT_SUPPORT;
        break;

      case 'n':
        config->authtype = CURLAUTH_BASIC;
        break;

      case 'o':
        config->authtype = CURLAUTH_ANY;
        break;

#ifdef MSDOS
      case 'p':
        dbug_init();
        break;
#endif
      case 'q':
        config->ftp_create_dirs ^= TRUE;
        break;

      case 'r':
        config->create_dirs = TRUE;
        break;

      case 's':

        if(str2num(&config->maxredirs, nextarg))
          return PARAM_BAD_NUMERIC;
        break;

      case 't':
        if(curlinfo->features & CURL_VERSION_NTLM)
          config->proxyntlm ^= TRUE;
        else
          return PARAM_LIBCURL_DOESNT_SUPPORT;
        break;

      case 'u':

        config->crlf = TRUE;
        break;

      case 'v':
        if(strcmp(nextarg, "-")) {
          FILE *newfile = fopen(nextarg, "wt");
          if(!newfile)
            warnf(config, "Failed to open %s!\n", nextarg);
          else {
            config->errors = newfile;
            config->errors_fopened = TRUE;
          }
        }
        else
          config->errors = stdout;
      break;
      case 'w':

        GetStr(&config->iface, nextarg);
        break;
      case 'x':

        if(curlinfo->features & CURL_VERSION_KERBEROS4)
          GetStr(&config->krb4level, nextarg);
        else
          return PARAM_LIBCURL_DOESNT_SUPPORT;
        break;
      case 'y':
        if(str2offset(&config->max_filesize, nextarg))
          return PARAM_BAD_NUMERIC;
        break;
      case 'z':
        config->disable_eprt ^= TRUE;
        break;

      default:
        {
          struct getout *url;
          if(config->url_get || (config->url_get=config->url_list)) {


            while(config->url_get && (config->url_get->flags&GETOUT_URL))
              config->url_get = config->url_get->next;
          }


          if(config->url_get)

            url = config->url_get;
          else

            url=new_getout(config);

          if(url) {

            GetStr(&url->url, nextarg);
            url->flags |= GETOUT_URL;
          }
        }
      }
      break;
    case '$':
      switch(subletter) {
      case 'a':
        config->ftp_ssl ^= TRUE;
        break;
      case 'b':
        if(config->ftpport)
          free(config->ftpport);
        config->ftpport = NULL;
        break;
      case 'c':
        GetStr(&config->socksproxy, nextarg);
        config->socksver = CURLPROXY_SOCKS5;
        break;
      case 't':
        GetStr(&config->socksproxy, nextarg);
        config->socksver = CURLPROXY_SOCKS4;
        break;
      case 'd':
        config->tcp_nodelay ^= TRUE;
        break;
      case 'e':
        config->proxydigest ^= TRUE;
        break;
      case 'f':
        config->proxybasic ^= TRUE;
        break;
      case 'g':
        if(str2num(&config->req_retry, nextarg))
          return PARAM_BAD_NUMERIC;
        break;
      case 'h':
        if(str2num(&config->retry_delay, nextarg))
          return PARAM_BAD_NUMERIC;
        break;
      case 'i':
        if(str2num(&config->retry_maxtime, nextarg))
          return PARAM_BAD_NUMERIC;
        break;

      case 'm':
        GetStr(&config->ftp_account, nextarg);
        break;
      case 'n':
        config->proxyanyauth ^= TRUE;
        break;
      case 'o':
        config->tracetime ^= TRUE;
        break;
      case 'p':
        config->ignorecl ^= TRUE;
        break;
      case 'q':
        config->ftp_skip_ip ^= TRUE;
        break;
      case 'r':
        config->ftp_filemethod = ftpfilemethod(config, nextarg);
        break;
      case 's':
        rc = sscanf(nextarg, "%d - %d",
                    &config->localport,
                    &config->localportrange);
        if(!rc)
          return PARAM_BAD_USE;
        else if(rc == 1)
          config->localportrange = 1;
        else {
          config->localportrange -= config->localport;
          if(config->localportrange < 1) {
            warnf(config, "bad range input\n");
            return PARAM_BAD_USE;
          }
        }
        break;
      case 'u':
        GetStr(&config->ftp_alternative_to_user, nextarg);
        break;
      case 'v':
        config->ftp_ssl_reqd ^= TRUE;
        break;
      case 'w':
        config->disable_sessionid ^= TRUE;
        break;
      case 'x':
        config->ftp_ssl_control ^= TRUE;
        break;
      case 'y':
        config->ftp_ssl_ccc ^= TRUE;
        if(!config->ftp_ssl_ccc_mode)
            config->ftp_ssl_ccc_mode = CURLFTPSSL_CCC_PASSIVE;
        break;
      case 'j':
        config->ftp_ssl_ccc = TRUE;
        config->ftp_ssl_ccc_mode = ftpcccmethod(config, nextarg);
        break;
      case 'z':
        GetStr(&config->libcurl, nextarg);
        break;
      case '#':
        config->raw ^= TRUE;
        break;
      }
      break;
    case '#':
      config->progressmode ^= CURL_PROGRESS_BAR;
      break;
    case '0':

      config->httpversion = CURL_HTTP_VERSION_1_0;
      break;
    case '1':

      config->ssl_version = CURL_SSLVERSION_TLSv1;
      break;
    case '2':

      config->ssl_version = CURL_SSLVERSION_SSLv2;
      break;
    case '3':

      config->ssl_version = CURL_SSLVERSION_SSLv3;
      break;
    case '4':

      config->ip_version = 4;
      break;
    case '6':

      config->ip_version = 6;
      break;
    case 'a':

      config->conf ^= CONF_FTPAPPEND;
      break;
    case 'A':

      GetStr(&config->useragent, nextarg);
      break;
    case 'b':
      if(nextarg[0] == '@') {
        nextarg++;
      }
      else if(strchr(nextarg, '=')) {

        GetStr(&config->cookie, nextarg);
        break;
      }

      GetStr(&config->cookiefile, nextarg);
      break;
    case 'B':

      config->conf ^= CONF_GETTEXT;
      break;
    case 'c':

      GetStr(&config->cookiejar, nextarg);
      break;
    case 'C':

      if(!curlx_strequal(nextarg, "-")) {
        if(str2offset(&config->resume_from, nextarg))
          return PARAM_BAD_NUMERIC;
        config->resume_from_current = FALSE;
      }
      else {
        config->resume_from_current = TRUE;
        config->resume_from = 0;
      }
      config->use_resume=TRUE;
      break;
    case 'd':

      {
        char *postdata=NULL;

        if('@' == *nextarg) {


          FILE *file;

          nextarg++;

          if(curlx_strequal("-", nextarg)) {
            file = stdin;
            if(subletter == 'b')
              SET_BINMODE(stdin);
          }
          else {
            file = fopen(nextarg, "rb");
            if(!file)
              warnf(config, "Couldn't read data from file \"%s\", this makes "
                    "an empty POST.\n", nextarg);
          }

          if(subletter == 'b')
            postdata = file2memory(file, &config->postfieldsize);
          else
            postdata = file2string(file);

          if(file && (file != stdin))
            fclose(file);

          if(!postdata) {


            postdata=strdup("");
          }
        }
        else {
          GetStr(&postdata, nextarg);
        }

#ifdef CURL_DOES_CONVERSIONS
        if(subletter != 'b') {
          convert_to_network(postdata, strlen(postdata));
        }
#endif

        if(config->postfields) {


          char *oldpost=config->postfields;
          size_t newlen = strlen(oldpost) + strlen(postdata) + 2;
          config->postfields=malloc(newlen);
          if(!config->postfields) {
            free(postdata);
            return PARAM_NO_MEM;
          }

          snprintf(config->postfields, newlen, "%s\x26%s", oldpost, postdata);
          free(oldpost);
          free(postdata);
        }
        else
          config->postfields=postdata;
      }


      break;
    case 'D':

      GetStr(&config->headerfile, nextarg);
      break;
    case 'e':
      {
        char *ptr = strstr(nextarg, ";auto");
        if(ptr) {


          config->conf |= CONF_AUTO_REFERER;
          *ptr = 0;
        }
        GetStr(&config->referer, nextarg);
      }
      break;
    case 'E':
      switch(subletter) {
      case 'a':

        GetStr(&config->cacert, nextarg);
        break;
      case 'b':
        GetStr(&config->cert_type, nextarg);
        break;
      case 'c':
        GetStr(&config->key, nextarg);
        break;
      case 'd':
        GetStr(&config->key_type, nextarg);
        break;
      case 'e':
        GetStr(&config->key_passwd, nextarg);
        cleanarg(nextarg);
        break;
      case 'f':
        GetStr(&config->engine, nextarg);
        if (config->engine && curlx_strequal(config->engine,"list"))
           config->list_engines = TRUE;
        break;
      case 'g':

        GetStr(&config->capath, nextarg);
        break;
      case 'h':
        GetStr(&config->pubkey, nextarg);
        break;
      default:
        {
          char *ptr = strchr(nextarg, ':');


#ifdef WIN32
          if(ptr &&
             (ptr == &nextarg[1]) &&
             (nextarg[2] == '\\' || nextarg[2] == '/') &&
             (ISALPHA(nextarg[0])) )


            ptr = strchr(&nextarg[3], ':');
#endif
          if(ptr) {

            *ptr=0;
            ptr++;
            GetStr(&config->key_passwd, ptr);
          }
          GetStr(&config->cert, nextarg);
          cleanarg(nextarg);
        }
      }
      break;
    case 'f':

      config->conf ^= CONF_FAILONERROR;
      break;
    case 'F':


      if(formparse(config,
                   nextarg,
                   &config->httppost,
                   &config->last_post,
                   (bool) (subletter=='s')))
        return PARAM_BAD_USE;
      if(SetHTTPrequest(config, HTTPREQ_POST, &config->httpreq))
        return PARAM_BAD_USE;
      break;

    case 'g':
      config->globoff ^= TRUE;
      break;

    case 'G':
      config->use_httpget = TRUE;
      break;

    case 'h':
      help();
      return PARAM_HELP_REQUESTED;
    case 'H':

      err = add2list(&config->headers, nextarg);
      if(err)
        return err;
      break;
    case 'i':
      config->conf ^= CONF_HEADER;
      break;
    case 'j':
      config->cookiesession ^= TRUE;
      break;
    case 'I':


      if((CONF_HEADER|CONF_NOBODY) !=
         (config->conf&(CONF_HEADER|CONF_NOBODY)) ) {

        config->conf |= (CONF_HEADER|CONF_NOBODY);
        if(SetHTTPrequest(config, HTTPREQ_HEAD, &config->httpreq))
          return PARAM_BAD_USE;
      }
      else {

        config->conf &= ~(CONF_HEADER|CONF_NOBODY);
        if(SetHTTPrequest(config, HTTPREQ_GET, &config->httpreq))
          return PARAM_BAD_USE;
      }
      break;
    case 'k':
      config->insecure_ok ^= TRUE;
      break;
    case 'K':
      if(parseconfig(nextarg, config))
        warnf(config, "error trying read config from the '%s' file\n",
              nextarg);
      break;
    case 'l':
      config->conf ^= CONF_FTPLISTONLY;
      break;
    case 'L':
      config->conf ^= CONF_FOLLOWLOCATION;
      switch (subletter) {
      case 't':


        config->conf ^= CONF_UNRESTRICTED_AUTH;
        break;
      }
      break;
    case 'm':

      if(str2num(&config->timeout, nextarg))
        return PARAM_BAD_NUMERIC;
      break;
    case 'M':
#ifdef USE_MANUAL
      hugehelp();
      return PARAM_HELP_REQUESTED;
#else
      warnf(config,
            "built-in manual was disabled at build-time!\n");
      return PARAM_OPTION_UNKNOWN;
#endif
    case 'n':
      switch(subletter) {
      case 'o':

        config->conf ^= CONF_NETRC_OPT;
        break;
      default:


        config->conf ^= CONF_NETRC;
        break;
      }
      break;
    case 'N':

      config->nobuffer ^= 1;
      break;
    case 'o':
    case 'O':

      {
        struct getout *url;
        if(config->url_out || (config->url_out=config->url_list)) {


          while(config->url_out && (config->url_out->flags&GETOUT_OUTFILE))
            config->url_out = config->url_out->next;
        }


        if(config->url_out)

          url = config->url_out;
        else

          url=new_getout(config);

        if(url) {

          if('o' == letter)
            GetStr(&url->outfile, nextarg);
          else {
            url->outfile=NULL;
            url->flags |= GETOUT_USEREMOTE;
          }
          url->flags |= GETOUT_OUTFILE;
        }
      }
      break;
    case 'P':


      GetStr(&config->ftpport, nextarg);
      break;
    case 'p':

      config->proxytunnel ^= TRUE;
      break;

    case 'q':

      break;
    case 'Q':

      err = PARAM_OK;
      switch(nextarg[0]) {
      case '-':

        nextarg++;
        err = add2list(&config->postquote, nextarg);
        break;
      case '+':

        nextarg++;
        err = add2list(&config->prequote, nextarg);
        break;
      default:
        err = add2list(&config->quote, nextarg);
        break;
      }
      if(err)
        return err;
      break;
    case 'r':


      if(ISDIGIT(*nextarg) && !strchr(nextarg, '-')) {
        char buffer[32];
        curl_off_t off;
        warnf(config,
              "A specfied range MUST include at least one dash (-). "
              "Appending one for you!\n");
        off = curlx_strtoofft(nextarg, NULL, 10);
        snprintf(buffer, sizeof(buffer), "%Od-", off);
        GetStr(&config->range, buffer);
      }
      {

        char* tmp_range;
        tmp_range=nextarg;
        while(*tmp_range != '\0') {
          if(!ISDIGIT(*tmp_range)&&*tmp_range!='-'&&*tmp_range!=',') {
            warnf(config,"Invalid character is found in given range. "
                  "A specified range MUST have only digits in "
                  "\'start\'-\'stop\'. The server's response to this "
                  "request is uncertain.\n");
            break;
          }
          tmp_range++;
        }

        GetStr(&config->range, nextarg);
      }
      break;
    case 'R':

      config->remote_time ^= TRUE;
      break;
    case 's':

      config->conf |= (CONF_MUTE|CONF_NOPROGRESS);
      config->showerror ^= TRUE;
      break;
    case 'S':

      config->showerror ^= TRUE;
      break;
    case 't':

      err = add2list(&config->telnet_options, nextarg);
      if(err)
        return err;
      break;
    case 'T':

      {
        struct getout *url;
        if(config->url_out || (config->url_out=config->url_list)) {


          while(config->url_out && (config->url_out->flags&GETOUT_UPLOAD))
            config->url_out = config->url_out->next;
        }


        if(config->url_out)

          url = config->url_out;
        else

          url=new_getout(config);

        if(url) {
          url->flags |= GETOUT_UPLOAD;
          if(!*nextarg)
            url->flags |= GETOUT_NOUPLOAD;
          else {

            GetStr(&url->infile, nextarg);
          }
        }
      }
      break;
    case 'u':

      GetStr(&config->userpwd, nextarg);
      cleanarg(nextarg);
      checkpasswd("host", &config->userpwd);
      break;
    case 'U':

      GetStr(&config->proxyuserpwd, nextarg);
      cleanarg(nextarg);
      checkpasswd("proxy", &config->proxyuserpwd);
      break;
    case 'v':

      GetStr(&config->trace_dump, (char *)"%");
      if(config->tracetype && (config->tracetype != TRACE_PLAIN))
        warnf(config,
              "-v/--verbose overrides an earlier trace/verbose option\n");
      config->tracetype = TRACE_PLAIN;
      break;
    case 'V':
    {
      const char * const *proto;

      printf(CURL_ID "%s\n", curl_version());
      if (curlinfo->protocols) {
        printf("Protocols: ");
        for (proto=curlinfo->protocols; *proto; ++proto) {
          printf("%s ", *proto);
        }
        puts("");
      }
      if(curlinfo->features) {
        unsigned int i;
        struct feat {
          const char *name;
          int bitmask;
        };
        static const struct feat feats[] = {
          {"AsynchDNS", CURL_VERSION_ASYNCHDNS},
          {"Debug", CURL_VERSION_DEBUG},
          {"GSS-Negotiate", CURL_VERSION_GSSNEGOTIATE},
          {"IDN", CURL_VERSION_IDN},
          {"IPv6", CURL_VERSION_IPV6},
          {"Largefile", CURL_VERSION_LARGEFILE},
          {"NTLM", CURL_VERSION_NTLM},
          {"SPNEGO", CURL_VERSION_SPNEGO},
          {"SSL",  CURL_VERSION_SSL},
          {"SSPI",  CURL_VERSION_SSPI},
          {"krb4", CURL_VERSION_KERBEROS4},
          {"libz", CURL_VERSION_LIBZ},
          {"CharConv", CURL_VERSION_CONV}
        };
        printf("Features: ");
        for(i=0; i<sizeof(feats)/sizeof(feats[0]); i++) {
          if(curlinfo->features & feats[i].bitmask)
            printf("%s ", feats[i].name);
        }
        puts("");
      }
    }
    return PARAM_HELP_REQUESTED;
    case 'w':

      if('@' == *nextarg) {


        FILE *file;
        nextarg++;
        if(curlx_strequal("-", nextarg))
          file = stdin;
        else
          file = fopen(nextarg, "r");
        config->writeout = file2string(file);
        if(!config->writeout)
          warnf(config, "Failed to read %s", file);
        if(file && (file != stdin))
          fclose(file);
      }
      else
        GetStr(&config->writeout, nextarg);
      break;
    case 'x':

      GetStr(&config->proxy, nextarg);
      break;
    case 'X':

      GetStr(&config->customrequest, nextarg);
      break;
    case 'y':

      if(str2num(&config->low_speed_time, nextarg))
        return PARAM_BAD_NUMERIC;
      if(!config->low_speed_limit)
        config->low_speed_limit = 1;
      break;
    case 'Y':

      if(str2num(&config->low_speed_limit, nextarg))
        return PARAM_BAD_NUMERIC;
      if(!config->low_speed_time)
        config->low_speed_time=30;
      break;
    case 'z':
      switch(*nextarg) {
      case '+':
        nextarg++;
      default:

        config->timecond = CURL_TIMECOND_IFMODSINCE;
        break;
      case '-':

        config->timecond = CURL_TIMECOND_IFUNMODSINCE;
        nextarg++;
        break;
      case '=':

        config->timecond = CURL_TIMECOND_LASTMOD;
        nextarg++;
        break;
      }
      now=time(NULL);
      config->condtime=curl_getdate(nextarg, &now);
      if(-1 == (int)config->condtime) {

        struct_stat statbuf;
        if(-1 == stat(nextarg, &statbuf)) {

          config->timecond = CURL_TIMECOND_NONE;
          warnf(config,
                "Illegal date format for -z/--timecond (and not "
                "a file name). Disabling time condition. "
                "See curl_getdate(3) for valid date syntax.\n");
        }
        else {

          config->condtime = statbuf.st_mtime;
        }
      }
      break;
    default:
      return PARAM_OPTION_UNKNOWN;
    }
    hit = -1;

  } while(!longopt && !singleopt && *++parse && !*usedarg);

  return PARAM_OK;
}
